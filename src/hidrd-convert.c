/** @file
 * @brief HID report descriptor - conversion tool
 *
 * Copyright (C) 2010 Nikolai Kondrashov
 *
 * This file is part of hidrd.
 *
 * Hidrd is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Hidrd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with hidrd; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * @author Nikolai Kondrashov <spbnick@gmail.com>
 *
 * @(#) $Id$
 */

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include "hidrd/util/fd.h"
#include "hidrd/fmt.h"

static bool
usage(FILE *stream, const char *progname)
{
    const hidrd_fmt   **pfmt;
    size_t              max_len;
    size_t              len;

    if (fprintf(
            stream, 
            "Usage: %s [OPTION]... [INPUT [OUTPUT]]\n"
            "Convert a HID report descriptor.\n"
            "With no INPUT, or when INPUT is -, read standard input.\n"
            "With no OUTPUT, or when OUTPUT is -, write standard output.\n"

            "\n"
            "Options:\n"
            "  -h, --help                       this help message\n"
            "  -i, --input-format=FORMAT        use FORMAT for input\n"
            "  --io=LIST, --input-options=LIST  "
                                        "use LIST input format options\n"
            "  -o, --output-format=FORMAT       use FORMAT for output\n"
            "  --oo=LIST, --output-options=LIST "
                                        "use LIST output format options\n"
            "\n"
            "Default options are \"-i natv -o natv\".\n"
            "\n"
            "Formats:\n"
            "\n",
            progname) < 0)
        return false;

    for (max_len = 0, pfmt = hidrd_fmt_list; *pfmt != NULL; pfmt++)
    {
        len = strlen((*pfmt)->name);
        if (len > max_len)
            max_len = len;
    }

    for (pfmt = hidrd_fmt_list; *pfmt != NULL; pfmt++)
    {
        if (fprintf(stream, "  %*s - %s\n",
                    max_len, (*pfmt)->name, (*pfmt)->desc) < 0)
            return false;
    }

    if (fprintf(stream, "\n") < 0)
        return false;

    return true;
}


static int
process(const char *input_name,
        const char *input_fmt_name,
        const char *input_options,

        const char *output_name,
        const char *output_fmt_name,
        const char *output_options)
{
    int                 result          = 1;

    int                 input_fd        = -1;
    void               *input_buf       = NULL;
    size_t              input_size      = 0;
    const hidrd_fmt    *input_fmt       = NULL;
    hidrd_src          *input           = NULL;

    int                 output_fd       = -1;
    void               *output_buf      = NULL;
    size_t              output_size     = 0;
    const hidrd_fmt    *output_fmt      = NULL;
    hidrd_snk          *output          = NULL;

    const hidrd_item   *item;

    assert(input_name != NULL);
    assert(*input_name != '\0');
    assert(input_fmt_name != NULL);
    assert(*input_fmt_name != '\0');
    assert(input_options != NULL);

    assert(output_name != NULL);
    assert(*output_name != '\0');
    assert(output_fmt_name != NULL);
    assert(*output_fmt_name != '\0');
    assert(output_options != NULL);

    /*
     * Lookup and initialize input and output formats
     */
    input_fmt = hidrd_fmt_list_lkp(input_fmt_name);
    if (input_fmt == NULL)
    {
        fprintf(stderr, "Unknown input format \"%s\"\n", input_fmt_name);
        goto cleanup;
    }
    if (!hidrd_fmt_readable(input_fmt))
    {
        fprintf(stderr, "Reading of %s format is not supported",
                input_fmt->desc);
        goto cleanup;
    }
    if (!hidrd_fmt_init(input_fmt))
    {
        fprintf(stderr, "Failed to initialize %s format library",
                input_fmt->desc);
        goto cleanup;
    }


    output_fmt = hidrd_fmt_list_lkp(output_fmt_name);
    if (output_fmt == NULL)
    {
        fprintf(stderr, "Unknown output format \"%s\"\n", output_fmt_name);
        goto cleanup;
    }
    if (!hidrd_fmt_writable(output_fmt))
    {
        fprintf(stderr, "Writing to %s format is not supported",
                output_fmt->desc);
        goto cleanup;
    }
    if (!hidrd_fmt_init(output_fmt))
    {
        fprintf(stderr, "Failed to initialize %s format library",
                output_fmt->desc);
        goto cleanup;
    }

    /*
     * Open input and output files
     */
    if (input_name[0] == '-' && input_name[1] == '\0')
        input_fd = STDIN_FILENO;
    else
    {
        input_fd = open(input_name, O_RDONLY);
        if (input_fd < 0)
        {
            fprintf(stderr, "Failed to open input: %s\n", strerror(errno));
            goto cleanup;
        }
    }
    if (output_name[0] == '-' && output_name[1] == '\0')
        output_fd = STDOUT_FILENO;
    else
    {
        output_fd = open(output_name,
                         O_WRONLY | O_CREAT | O_TRUNC,
                         S_IRUSR | S_IWUSR |
                         S_IRGRP | S_IWGRP |
                         S_IROTH | S_IWOTH);
        if (output_fd < 0)
        {
            fprintf(stderr, "Failed to open output: %s\n", strerror(errno));
            goto cleanup;
        }
    }

    /*
     * Read the whole input file
     */
    if (!hidrd_fd_read_whole(input_fd, &input_buf, &input_size))
    {
        fprintf(stderr, "Failed to read input: %s\n", strerror(errno));
        goto cleanup;
    }

    /*
     * Open input and output streams
     */
    input = hidrd_src_new_opts(input_fmt->src,
                               input_buf, input_size, input_options);
    if (input == NULL)
    {
        fprintf(stderr, "Failed to open input stream\n");
        goto cleanup;
    }
    output = hidrd_snk_new_opts(output_fmt->snk,
                                &output_buf, &output_size, output_options);
    if (output == NULL)
    {
        fprintf(stderr, "Failed to open output stream\n");
        goto cleanup;
    }

    /*
     * Transfer the stream
     */
    while ((item = hidrd_src_get(input)) != NULL)
        if (!hidrd_snk_put(output, item))
        {
            fprintf(stderr, "Failed to write output stream\n");
            goto cleanup;
        }
    if (hidrd_src_error(input))
    {
        fprintf(stderr, "Failed to read input stream\n");
        goto cleanup;
    }

    /*
     * Close input and output streams
     */
    hidrd_src_delete(input);
    input = NULL;
    if (!hidrd_snk_close(output))
    {
        fprintf(stderr, "Failed to close output stream\n");
        goto cleanup;
    }
    output = NULL;

    /*
     * Write the output file
     */
    if (!hidrd_fd_write_whole(output_fd, output_buf, output_size))
    {
        fprintf(stderr, "Failed to write output stream: %s\n",
                strerror(errno));
        goto cleanup;
    }

    /* Success! */
    result = 0;

cleanup:

    hidrd_src_delete(input);
    hidrd_snk_delete(output);

    free(output_buf);
    free(input_buf);

    if (input_fd >= 0 && input_fd != STDIN_FILENO)
        close(input_fd);
    if (output_fd >= 0 && output_fd != STDOUT_FILENO)
        close(output_fd);

    if (output_fmt != NULL)
        hidrd_fmt_clnp(output_fmt);
    if (input_fmt != NULL)
        hidrd_fmt_clnp(input_fmt);

    return result;
}


typedef enum opt_val {
    /* Long and short options */
    OPT_VAL_HELP           = 'h',
    OPT_VAL_INPUT_FORMAT   = 'i',
    OPT_VAL_OUTPUT_FORMAT  = 'o',

    /* Long options only */
    OPT_VAL_INPUT_OPTIONS  = UINT8_MAX + 1,
    OPT_VAL_OUTPUT_OPTIONS,
} opt_val;


int
main(int argc, char **argv)
{
    static const struct option long_opt_list[] = {
        {.name      = "help",
         .has_arg   = 0,
         .flag      = NULL,
         .val       = OPT_VAL_HELP},
        {.name      = "input-format",
         .has_arg   = 1,
         .flag      = NULL,
         .val       = OPT_VAL_INPUT_FORMAT},
        {.name      = "input-options",
         .has_arg   = 1,
         .flag      = NULL,
         .val       = OPT_VAL_INPUT_OPTIONS},
        {.name      = "io",
         .has_arg   = 1,
         .flag      = NULL,
         .val       = OPT_VAL_INPUT_OPTIONS},
        {.name      = "output-format",
         .has_arg   = 1,
         .flag      = NULL,
         .val       = OPT_VAL_OUTPUT_FORMAT},
        {.name      = "output-options",
         .has_arg   = 1,
         .flag      = NULL,
         .val       = OPT_VAL_OUTPUT_OPTIONS},
        {.name      = "oo",
         .has_arg   = 1,
         .flag      = NULL,
         .val       = OPT_VAL_OUTPUT_OPTIONS},
        {.name      = NULL,
         .has_arg   = 0,
         .flag      = NULL,
         .val       = 0}
    };
    static const char  *short_opt_list = "hi:o:";

    const char *input_name      = "-";
    const char *output_name     = "-";
    const char *input_format    = "natv";
    const char *input_options   = "";
    const char *output_format   = "natv";
    const char *output_options  = "";
    int         c;

    /*
     * Parse command line arguments
     */
    while ((c = getopt_long(argc, argv,
                            short_opt_list, long_opt_list, NULL)) >= 0)
    {
        switch (c)
        {
            case OPT_VAL_HELP:
                usage(stdout, program_invocation_short_name);
                return 0;
                break;
            case OPT_VAL_INPUT_FORMAT:
                input_format = optarg;
                break;
            case OPT_VAL_INPUT_OPTIONS:
                input_options = optarg;
                break;
            case OPT_VAL_OUTPUT_FORMAT:
                output_format = optarg;
                break;
            case OPT_VAL_OUTPUT_OPTIONS:
                output_options = optarg;
                break;
            case '?':
                usage(stderr, program_invocation_short_name);
                return 1;
                break;
        }
    }

    if (optind < argc)
    {
        input_name = argv[optind++];
        if (optind < argc)
        {
            output_name = argv[optind++];
            if (optind < argc)
            {
                fprintf(stderr, "Too many arguments\n");
                usage(stderr, program_invocation_short_name);
                return 1;
            }
        }
    }

    /*
     * Verify command line arguments
     */
    if (*input_name == '\0')
    {
        fprintf(stderr, "Empty input file name\n");
        usage(stderr, program_invocation_short_name);
        return 1;
    }
    if (*input_format == '\0')
    {
        fprintf(stderr, "Empty input format name\n");
        usage(stderr, program_invocation_short_name);
        return 1;
    }
    if (*output_name == '\0')
    {
        fprintf(stderr, "Empty output file name\n");
        usage(stderr, program_invocation_short_name);
        return 1;
    }
    if (*output_format == '\0')
    {
        fprintf(stderr, "Empty output format name\n");
        usage(stderr, program_invocation_short_name);
        return 1;
    }

    /*
     * Run
     */
    return process(input_name, input_format, input_options,
                   output_name, output_format, output_options);
}



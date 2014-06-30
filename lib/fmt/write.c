/** @file
 * @brief HID report descriptor - XML sink - test
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
 */

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "hidrd/util/fd.h"
#include "hidrd/fmt/list.h"

static int
usage(FILE *stream, const char *progname)
{
    return 
        fprintf(
            stream, 
            "Usage: %s [OUTPUT_FORMAT [OUTPUT_OPTS [INPUT [OUTPUT]]]]\n"
            "Convert a HID report descriptor "
            "from native to OUTPUT_FORMAT.\n"
            "With no INPUT, or when INPUT is -, read standard input.\n"
            "With no OUTPUT, or when OUTPUT is -, write standard output.\n"
            "\n",
            progname);
}


int
main(int argc, char **argv)
{
    int                 result              = 1;

    const char         *input_name          = "-";
    int                 input_fd            = -1;
    void               *input_buf           = NULL;
    size_t              input_size          = 0;

    const char         *output_format_name  = "natv";
    const hidrd_fmt    *output_format       = NULL;
    const char         *output_options      = "";
    const char         *output_name         = "-";
    int                 output_fd           = -1;
    void               *output_buf          = NULL;
    size_t              output_size         = 0;
    hidrd_snk          *output              = NULL;

    const hidrd_item   *item;

    const char        **argp_list[]         = {&output_format_name,
                                               &output_options,
                                               &input_name,
                                               &output_name};
    size_t              i;

    char               *err                 = NULL;

    /*
     * Collect arguments
     */
    for (argc--, argv++, i = 0;
         argc > 0 && i < sizeof(argp_list) / sizeof(*argp_list);
         argc--, argv++, i++)
        *argp_list[i] = *argv;
    if (argc > 0)
    {
        usage(stderr, program_invocation_short_name);
        goto cleanup;
    }

    /*
     * Lookup output format
     */
    output_format = hidrd_fmt_list_lkp(output_format_name);
    if (output_format == NULL)
    {
        fprintf(stderr, "Output format \"%s\" not found\n",
                output_format_name);
        goto cleanup;
    }

    /* Initialize output format */
    hidrd_fmt_init(output_format);

    /* Check that output format supports writing */
    if (!hidrd_fmt_writable(output_format))
    {
        fprintf(stderr, "%s writing is not supported\n",
                output_format->desc);
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
     * Open output stream
     */
    output = hidrd_snk_new_opts(output_format->snk, &err,
                                &output_buf, &output_size, output_options);
    if (output == NULL)
    {
        fprintf(stderr, "Failed to open output stream\n:%s\n", err);
        goto cleanup;
    }
    free(err);
    err = NULL;

    /*
     * Transfer items
     */
    for (item = (const hidrd_item *)input_buf;
         (size_t)(item - (const hidrd_item *)input_buf) < input_size;
         item += hidrd_item_get_size(item))
        if (!hidrd_snk_put(output, item))
        {
            fprintf(stderr, "Failed to write output stream\n%s\n",
                    (err = hidrd_snk_errmsg(output)));
            goto cleanup;
        }

    /*
     * Close output stream
     */
    if (!hidrd_snk_close(output))
    {
        fprintf(stderr, "Failed to close output stream\n%s\n",
                (err = hidrd_snk_errmsg(output)));
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

    free(err);
    hidrd_snk_delete(output);

    free(output_buf);
    free(input_buf);

    if (input_fd >= 0 && input_fd != STDIN_FILENO)
        close(input_fd);
    if (output_fd >= 0 && output_fd != STDOUT_FILENO)
        close(output_fd);

    /* Cleanup output format */
    if (output_format != NULL)
        hidrd_fmt_clnp(output_format);

    return result;
}



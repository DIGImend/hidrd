/** @file
 * @brief HID report descriptor - source test
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
 * @(#) $Id: hidrd-convert.c 289 2010-03-21 20:45:27Z spb_nick $
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
            "Usage: %s [INPUT_FORMAT [INPUT_OPTS [INPUT [OUTPUT]]]]\n"
            "Convert a HID report descriptor from "
            "INPUT_FORMAT to native format.\n"
            "With no INPUT, or when INPUT is -, read standard input.\n"
            "With no OUTPUT, or when OUTPUT is -, write standard output.\n"
            "\n",
            progname);
}


int
main(int argc, char **argv)
{
    int                 result              = 1;

    const char         *input_format_name   = "natv";
    const hidrd_fmt    *input_format        = NULL;
    const char         *input_options       = "";
    const char         *input_name          = "-";
    int                 input_fd            = -1;
    void               *input_buf           = NULL;
    size_t              input_size          = 0;
    hidrd_src          *input               = NULL;

    const char         *output_name         = "-";
    int                 output_fd           = -1;

    const hidrd_item   *item;

    const char        **argp_list[]         = {&input_format_name,
                                               &input_options,
                                               &input_name,
                                               &output_name};
    size_t              i;

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
     * Lookup input format
     */
    input_format = hidrd_fmt_list_lkp(input_format_name);
    if (input_format == NULL)
    {
        fprintf(stderr, "Input format \"%s\" not found\n",
                input_format_name);
        goto cleanup;
    }

    /* Initialize input format */
    hidrd_fmt_init(input_format);

    /* Check that input format supports reading */
    if (!hidrd_fmt_readable(input_format))
    {
        fprintf(stderr, "%s reading is not supported\n",
                input_format->desc);
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
     * Open input stream
     */
    input = hidrd_src_new_opts(input_format->src,
                               input_buf, input_size, input_options);
    if (input == NULL)
    {
        fprintf(stderr, "Failed to open input stream\n");
        goto cleanup;
    }

    while ((item = hidrd_src_get(input)) != NULL)
        if (!hidrd_fd_write_whole(output_fd,
                                  item, hidrd_item_get_size(item)))
        {
            fprintf(stderr, "Failed to write output file\n");
            goto cleanup;
        }
    if (hidrd_src_error(input))
    {
        fprintf(stderr, "Failed to read input stream\n");
        goto cleanup;
    }

    /* Success! */
    result = 0;

cleanup:

    hidrd_src_delete(input);
    free(input_buf);
    if (input_fd >= 0 && input_fd != STDIN_FILENO)
        close(input_fd);
    if (output_fd >= 0 && output_fd != STDOUT_FILENO)
        close(output_fd);

    /* Cleanup input format */
    if (input_format != NULL)
        hidrd_fmt_clnp(input_format);

    return result;
}

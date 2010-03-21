/** @file
 * @brief HID report descriptor - utilities - file descriptor operations
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
 * @(#) $Id: str.h 277 2010-03-15 21:04:04Z spb_nick $
 */

#ifndef __HIDRD_UTIL_FD_H__
#define __HIDRD_UTIL_FD_H__

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read the whole file contents starting from the current position.
 *
 * @param fd    File descriptor to read from.
 * @param pbuf  Location for the pointer to the dynamically allocated buffer
 *              with file contents.
 * @param psize Location for the size of the content read from the file.
 *
 * @return True if read successfully, false otherwise (see errno in this
 *         case).
 */
extern bool hidrd_fd_read_whole(int fd, void **pbuf, size_t *psize);

/**
 * Write the whole buffer to the file.
 *
 * @param fd    File descriptor write to.
 * @param buf   Pointer to the buffer to write to the file.
 * @param size  Size of the buffer to write to the file.
 *
 * @return True if written successfully, false otherwise (see errno in this
 *         case).
 */
extern bool hidrd_fd_write_whole(int fd, const void *buf, size_t size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_UTIL_FD_H__ */

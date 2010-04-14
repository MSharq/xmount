/*
 * Byte stream functions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBUNA_BYTE_STREAM_H )
#define _LIBUNA_BYTE_STREAM_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libuna_extern.h"
#include "libuna_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBUNA_EXTERN int libuna_byte_stream_size_from_utf8(
                   const libuna_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   int codepage,
                   size_t *byte_stream_size,
                   liberror_error_t **error );

LIBUNA_EXTERN int libuna_byte_stream_copy_from_utf8(
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   int codepage,
                   const libuna_utf8_character_t *utf8_string,
                   size_t utf8_string_size,
                   liberror_error_t **error );

/* The functionality for libuna_byte_stream_copy_to_utf8 is implemented by
 * libuna_utf8_string_copy_from_byte_stream
 */

LIBUNA_EXTERN int libuna_byte_stream_size_from_utf16(
                   const libuna_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   int codepage,
                   size_t *byte_stream_size,
                   liberror_error_t **error );

LIBUNA_EXTERN int libuna_byte_stream_copy_from_utf16(
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   int codepage,
                   const libuna_utf16_character_t *utf16_string,
                   size_t utf16_string_size,
                   liberror_error_t **error );

/* The functionality for libuna_byte_stream_copy_to_utf16 is implemented by
 * libuna_utf16_string_copy_from_byte_stream
 */

LIBUNA_EXTERN int libuna_byte_stream_size_from_utf32(
                   const libuna_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   int codepage,
                   size_t *byte_stream_size,
                   liberror_error_t **error );

LIBUNA_EXTERN int libuna_byte_stream_copy_from_utf32(
                   uint8_t *byte_stream,
                   size_t byte_stream_size,
                   int codepage,
                   const libuna_utf32_character_t *utf32_string,
                   size_t utf32_string_size,
                   liberror_error_t **error );

/* The functionality for libuna_byte_stream_copy_to_utf32 is implemented by
 * libuna_utf32_string_copy_from_byte_stream
 */

#if defined( __cplusplus )
}
#endif

#endif


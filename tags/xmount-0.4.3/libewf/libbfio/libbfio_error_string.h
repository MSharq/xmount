/*
 * Error string functions
 *
 * Copyright (c) 2006-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBBFIO_ERROR_STRING_H )
#define _LIBBFIO_ERROR_STRING_H

#include <common.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include <liberror.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define LIBBFIO_ERROR_STRING_DEFAULT_SIZE	512

int libbfio_error_string_from_error_number(
       char **error_string,
       size_t *error_string_size,
       int error_number,
       liberror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
int libbfio_error_string_from_error_number_wide(
       wchar_t **error_string,
       size_t *error_string_size,
       int error_number,
       liberror_error_t **error );
#endif

#if defined( __cplusplus )
}
#endif

#endif


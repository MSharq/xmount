/*
 * Error functions
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

#if !defined( _LIBERROR_INTERNAL_ERROR_H )
#define _LIBERROR_INTERNAL_ERROR_H

#include <common.h>
#include <types.h>

#include <stdio.h>

#if defined( HAVE_STDARG_H )
#include <stdarg.h>
#elif defined( HAVE_VARARGS_H )
#include <varargs.h>
#else
#error Missing headers stdarg.h and varargs.h
#endif

#include "liberror_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( WINAPI )
#define liberror_error_vsnprintf( string, size, format, ... ) \
	_vsnprintf( string, size, format, __VA_ARGS__ )

#else
#define liberror_error_vsnprintf( string, size, format, ... ) \
	vsnprintf( string, size, format, __VA_ARGS__ )

#endif

typedef struct liberror_internal_error liberror_internal_error_t;

struct liberror_internal_error
{
	/* The error domain
	 */
	int domain;

	/* The error code
	 */
	int code;

	/* The amount of messages
	 */
	int amount_of_messages;

	/* The error messages
	 */
	char **message;
};

void liberror_error_set(
      liberror_error_t **error,
      int error_domain,
      int error_code,
      const char *format,
      ... );

int liberror_error_matches(
     liberror_error_t *error,
     int error_domain,
     int error_code );

void liberror_error_free(
      liberror_error_t **error );

void liberror_error_fprint(
      liberror_error_t *error,
      FILE *stream );

void liberror_error_backtrace_fprint(
      liberror_error_t *error,
      FILE *stream );

#if defined( __cplusplus )
}
#endif

#endif


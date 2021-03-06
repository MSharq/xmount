/*
 * User input functions for the ewftools
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include <liberror.h>

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#if defined( HAVE_STRING_H )
#include <string.h>
#endif

#include <libewf.h>

#include "byte_size_string.h"
#include "ewfinput.h"
#include "system_string.h"

/* Input selection defintions
 */
system_character_t *ewfinput_compression_levels[ 4 ] = \
 { _SYSTEM_CHARACTER_T_STRING( "none" ),
   _SYSTEM_CHARACTER_T_STRING( "empty-block" ),
   _SYSTEM_CHARACTER_T_STRING( "fast" ),
   _SYSTEM_CHARACTER_T_STRING( "best" ) };

system_character_t *ewfinput_format_types[ 12 ] = \
 { _SYSTEM_CHARACTER_T_STRING( "ewf" ),
   _SYSTEM_CHARACTER_T_STRING( "smart" ),
   _SYSTEM_CHARACTER_T_STRING( "ftk" ),
   _SYSTEM_CHARACTER_T_STRING( "encase1" ),
   _SYSTEM_CHARACTER_T_STRING( "encase2" ),
   _SYSTEM_CHARACTER_T_STRING( "encase3" ),
   _SYSTEM_CHARACTER_T_STRING( "encase4" ),
   _SYSTEM_CHARACTER_T_STRING( "encase5" ),
   _SYSTEM_CHARACTER_T_STRING( "encase6" ),
   _SYSTEM_CHARACTER_T_STRING( "linen5" ),
   _SYSTEM_CHARACTER_T_STRING( "linen6" ),
   _SYSTEM_CHARACTER_T_STRING( "ewfx" ) };

system_character_t *ewfinput_media_types[ 4 ] = \
 { _SYSTEM_CHARACTER_T_STRING( "fixed" ),
   _SYSTEM_CHARACTER_T_STRING( "removable" ),
   _SYSTEM_CHARACTER_T_STRING( "optical" ),
   _SYSTEM_CHARACTER_T_STRING( "memory" ) };

system_character_t *ewfinput_media_flags[ 2 ] = \
 { _SYSTEM_CHARACTER_T_STRING( "logical" ),
   _SYSTEM_CHARACTER_T_STRING( "physical" ) };

system_character_t *ewfinput_sector_per_block_sizes[ 10 ] = \
 { _SYSTEM_CHARACTER_T_STRING( "64" ),
   _SYSTEM_CHARACTER_T_STRING( "128" ),
   _SYSTEM_CHARACTER_T_STRING( "256" ),
   _SYSTEM_CHARACTER_T_STRING( "512" ),
   _SYSTEM_CHARACTER_T_STRING( "1024" ),
   _SYSTEM_CHARACTER_T_STRING( "2048" ),
   _SYSTEM_CHARACTER_T_STRING( "4096" ),
   _SYSTEM_CHARACTER_T_STRING( "8192" ),
   _SYSTEM_CHARACTER_T_STRING( "16384" ),
   _SYSTEM_CHARACTER_T_STRING( "32768" ) };

system_character_t *ewfinput_yes_no[ 2 ] = \
 { _SYSTEM_CHARACTER_T_STRING( "yes" ),
   _SYSTEM_CHARACTER_T_STRING( "no" ) };

/* Determines the EWF format from an argument string
 * Returns 1 if successful or -1 on error
 */
int ewfinput_determine_ewf_format(
     const system_character_t *argument,
     uint8_t *ewf_format,
     liberror_error_t **error )
{
	static char *function = "ewfinput_determine_ewf_format";
	int result            = -1;

	if( argument == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid argument string.",
		 function );

		return( -1 );
	}
	if( ewf_format == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid libewf format.",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "smart" ),
	     5 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_SMART;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "ftk" ),
	          3 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_FTK;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "encase1" ),
	          7 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_ENCASE1;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "encase2" ),
	          7 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_ENCASE2;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "encase3" ),
	          7 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_ENCASE3;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "encase4" ),
	          7 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_ENCASE4;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "encase5" ),
	          7 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_ENCASE5;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "encase6" ),
	          7 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_ENCASE6;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "linen5" ),
	          6 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_LINEN5;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "linen6" ),
	          6 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_LINEN6;
		result      = 1;
	}
	/* This check must before the check for "ewf"
	 */
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "ewfx" ),
	          4 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_EWFX;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "ewf" ),
	          3 ) == 0 )
	{
		*ewf_format = LIBEWF_FORMAT_EWF;
		result      = 1;
	}
	return( result );
}

/* Determines the sectors per chunk value from an argument string
 * Returns 1 if successful or -1 on error
 */
int ewfinput_determine_sectors_per_chunk(
     const system_character_t *argument,
     uint32_t *sectors_per_chunk,
     liberror_error_t **error )
{
	static char *function = "ewfinput_determine_sectors_per_chunk";
	int result            = -1;

	if( argument == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid argument string.",
		 function );

		return( -1 );
	}
	if( sectors_per_chunk == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sectors per chunk.",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "32768" ),
	     5 ) == 0 )
	{
		*sectors_per_chunk = 32768;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "16384" ),
	          5 ) == 0 )
	{
		*sectors_per_chunk = 16384;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "8192" ),
	          4 ) == 0 )
	{
		*sectors_per_chunk = 8192;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "4096" ),
	          4 ) == 0 )
	{
		*sectors_per_chunk = 4096;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "2048" ),
	          4 ) == 0 )
	{
		*sectors_per_chunk = 2048;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "1024" ),
	          4 ) == 0 )
	{
		*sectors_per_chunk = 1024;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "512" ),
	          3 ) == 0 )
	{
		*sectors_per_chunk = 512;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "256" ),
	          3 ) == 0 )
	{
		*sectors_per_chunk = 256;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "128" ),
	          3 ) == 0 )
	{
		*sectors_per_chunk = 128;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "64" ),
	          2 ) == 0 )
	{
		*sectors_per_chunk = 64;
		result             = 1;
	}
	return( result );
}

/* Determines the compression level value from an argument string
 * Returns 1 if successful or -1 on error
 */
int ewfinput_determine_compression_level(
     const system_character_t *argument,
     int8_t *compression_level,
     uint8_t *compression_flags,
     liberror_error_t **error )
{
	static char *function = "ewfinput_determine_compression_level";
	int result            = 1;

	if( argument == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid argument string.",
		 function );

		return( -1 );
	}
	if( compression_level == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compression level.",
		 function );

		return( -1 );
	}
	if( compression_flags == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compression flags.",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "none" ),
	     4 ) == 0 )
	{
		*compression_level = LIBEWF_COMPRESSION_NONE;
		*compression_flags = 0;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "empty-block" ),
	          11 ) == 0 )
	{
		*compression_level = LIBEWF_COMPRESSION_NONE;
		*compression_flags = LIBEWF_FLAG_COMPRESS_EMPTY_BLOCK;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "empty_block" ),
	          11 ) == 0 )
	{
		*compression_level = LIBEWF_COMPRESSION_NONE;
		*compression_flags = LIBEWF_FLAG_COMPRESS_EMPTY_BLOCK;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "fast" ),
	          4 ) == 0 )
	{
		*compression_level = LIBEWF_COMPRESSION_FAST;
		*compression_flags = 0;
		result             = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "best" ),
	          4 ) == 0 )
	{
		*compression_level = LIBEWF_COMPRESSION_BEST;
		*compression_flags = 0;
		result             = 1;
	}
	return( result );
}

/* Determines the media type value from an argument string
 * Returns 1 if successful or -1 on error
 */
int ewfinput_determine_media_type(
     const system_character_t *argument,
     uint8_t *media_type,
     liberror_error_t **error )
{
	static char *function = "ewfinput_determine_media_type";
	int result            = -1;

	if( argument == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid argument string.",
		 function );

		return( -1 );
	}
	if( media_type == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid media type.",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "fixed" ),
	          5 ) == 0 )
	{
		*media_type = LIBEWF_MEDIA_TYPE_FIXED;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "removable" ),
	          9 ) == 0 )
	{
		*media_type = LIBEWF_MEDIA_TYPE_REMOVABLE;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "optical" ),
	          7 ) == 0 )
	{
		*media_type = LIBEWF_MEDIA_TYPE_OPTICAL;
		result      = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "memory" ),
	          6 ) == 0 )
	{
		*media_type = LIBEWF_MEDIA_TYPE_MEMORY;
		result      = 1;
	}
	return( result );
}

/* Determines the media flags value from an argument string
 * Returns 1 if successful or -1 on error
 */
int ewfinput_determine_media_flags(
     const system_character_t *argument,
     uint8_t *media_flags,
     liberror_error_t **error )
{
	static char *function = "ewfinput_determine_media_flags";
	int result            = -1;

	if( argument == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid argument string.",
		 function );

		return( -1 );
	}
	if( media_flags == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid media flags.",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "logical" ),
	     7 ) == 0 )
	{
		*media_flags &= ~LIBEWF_MEDIA_FLAG_PHYSICAL;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "physical" ),
	          8 ) == 0 )
	{
		*media_flags |= LIBEWF_MEDIA_FLAG_PHYSICAL;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "fastbloc" ),
	          8 ) == 0 )
	{
		*media_flags |= LIBEWF_MEDIA_FLAG_FASTBLOC;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "tableau" ),
	          8 ) == 0 )
	{
		*media_flags |= LIBEWF_MEDIA_FLAG_TABLEAU;
		result        = 1;
	}
	return( result );
}

/* Determines the codepage from an argument string
 * Returns 1 if successful or -1 on error
 */
int ewfinput_determine_header_codepage(
     const system_character_t *argument,
     int *header_codepage,
     liberror_error_t **error )
{
	static char *function = "ewfinput_determine_header_codepage";
	int result            = -1;

	if( argument == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid argument string.",
		 function );

		return( -1 );
	}
	if( header_codepage == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream codepage.",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "ascii" ),
	          4 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_ASCII;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1250" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1250;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1250" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1250;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1251" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1251;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1251" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1251;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1252" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1252;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1252" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1252;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1253" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1253;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1253" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1253;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1254" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1254;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1254" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1254;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1255" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1255;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1255" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1255;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1256" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1256;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1256" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1256;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1257" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1257;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1257" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1257;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows-1258" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1258;
		result           = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "windows_1258" ),
	          12 ) == 0 )
	{
		*header_codepage = LIBEWF_CODEPAGE_WINDOWS_1258;
		result           = 1;
	}
	return( result );
}

/* Determines the yes or no value from an argument string
 * Returns 1 if successful or -1 on error
 */
int ewfinput_determine_yes_no(
     const system_character_t *argument,
     uint8_t *yes_no_value,
     liberror_error_t **error )
{
	static char *function = "ewfinput_determine_yes_no";
	int result            = -1;

	if( argument == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid argument string.",
		 function );

		return( -1 );
	}
	if( yes_no_value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid yes no value.",
		 function );

		return( -1 );
	}
	if( system_string_compare(
	     argument,
	     _SYSTEM_CHARACTER_T_STRING( "yes" ),
	     3 ) == 0 )
	{
		*yes_no_value = 1;
		result        = 1;
	}
	else if( system_string_compare(
	          argument,
	          _SYSTEM_CHARACTER_T_STRING( "no" ),
	          2 ) == 0 )
	{
		*yes_no_value = 0;
		result        = 1;
	}
	return( result );
}

/* Get a string variable
 * Returns 1 if successful, 0 if no input was provided or -1 on error
 */
int ewfinput_get_string_variable(
     FILE *stream,
     system_character_t *request_string,
     system_character_t *string_variable,
     size_t string_variable_size,
     liberror_error_t **error )
{
	system_character_t *end_of_input  = NULL;
	system_character_t *result_string = NULL;
	static char *function             = "ewfinput_get_variabl_string";
	ssize_t input_length              = 0;

	if( stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid output stream.",
		 function );

		return( -1 );
	}
	if( request_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid request string.",
		 function );

		return( -1 );
	}
	if( string_variable == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string variable.",
		 function );

		return( -1 );
	}
	if( string_variable_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string variable size value exceeds maximum.",
		 function );

		return( -1 );
	}
	/* Safe guard the end of the input string
	 */
	string_variable[ string_variable_size - 1 ] = 0;

	while( 1 )
	{
		fprintf(
		 stream,
		 "%" PRIs_SYSTEM ": ",
		 request_string );

		result_string = system_string_get_from_stream(
		                 string_variable,
		                 string_variable_size - 1,
		                 stdin );

		if( result_string != NULL )
		{
			end_of_input = system_string_search(
			                string_variable,
			                (system_character_t) '\n',
			                string_variable_size );

			/* Input was larger than size of buffer
			 */
			if( end_of_input == NULL )
			{
				/* Flush the stdin stream
				 */
				while( end_of_input == NULL )
				{
					result_string = system_string_get_from_stream(
					                 string_variable,
					                 string_variable_size - 1,
					                 stdin );

					end_of_input = system_string_search(
					                string_variable,
					                (system_character_t) '\n',
					                string_variable_size );

				}
				return( -1 );
			}
			input_length = (ssize_t) ( end_of_input - string_variable );

			if( input_length < 0 )
			{
				return( -1 );
			}
			/* Make sure the string is terminated with an end of string character
			 */
			string_variable[ input_length ] = 0;

			break;
		}
		else
		{
			fprintf(
			 stream,
			 "Error reading input, please try again or terminate using Ctrl^C.\n" );
		}
	}
	if( input_length == 0 )
	{
		return( 0 );
	}
	return( 1 );
}

/* Get a size variable
 * Returns 1 if successful, 0 if no input was provided or -1 on error
 */
int ewfinput_get_size_variable(
     FILE *stream,
     system_character_t *input_buffer,
     size_t input_buffer_size,
     system_character_t *request_string,
     uint64_t minimum,
     uint64_t maximum,
     uint64_t default_value,
     uint64_t *size_variable,
     liberror_error_t **error )
{
	system_character_t *end_of_input  = NULL;
	system_character_t *result_string = NULL;
	static char *function             = "ewfinput_get_size_variable";
	ssize_t input_length              = 0;

	if( stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid output stream.",
		 function );

		return( -1 );
	}
	if( input_buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid input buffer.",
		 function );

		return( -1 );
	}
	if( input_buffer_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid input buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( request_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid request string.",
		 function );

		return( -1 );
	}
	if( size_variable == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size variable.",
		 function );

		return( -1 );
	}
	/* Safe guard the end of the input buffer
	 */
	input_buffer[ input_buffer_size - 1 ] = 0;

	while( 1 )
	{
		fprintf(
		 stream,
		 "%" PRIs_SYSTEM " (%" PRIu64 " >= value >= %" PRIu64 ") [%" PRIu64 "]: ",
		 request_string,
		 minimum,
		 maximum,
		 default_value );

		result_string = system_string_get_from_stream(
		                 input_buffer,
		                 input_buffer_size - 1,
		                 stdin );

		if( result_string != NULL )
		{
			end_of_input = system_string_search(
			                input_buffer,
			                (system_character_t) '\n',
			                input_buffer_size );

			/* Input was larger than size of buffer
			 */
			if( end_of_input == NULL )
			{
				/* Flush the stdin stream
				 */
				while( end_of_input == NULL )
				{
					result_string = system_string_get_from_stream(
					                 input_buffer,
					                 input_buffer_size - 1,
					                 stdin );

					end_of_input = system_string_search(
					                input_buffer,
					                (system_character_t) '\n',
					                input_buffer_size );

				}
				return( -1 );
			}
			input_length = (ssize_t) ( end_of_input - input_buffer );

			if( input_length < 0 )
			{
				return( -1 );
			}
			else if( input_length == 0 )
			{
				*size_variable = default_value;

				return( 0 );
			}
			if( system_string_to_uint64(
			     input_buffer,
			     input_length,
			     size_variable,
			     NULL ) != 1 )
			{
				fprintf(
				 stream,
				 "Unable to convert value into number, please try again or terminate using Ctrl^C.\n" );
			}
			else if( ( *size_variable >= minimum )
			      && ( *size_variable <= maximum ) )
			{
				break;
			}
			else
			{
				fprintf(
				 stream,
				 "Value not within specified range, please try again or terminate using Ctrl^C.\n" );
			}
		}
		else
		{
			fprintf(
			 stream,
			 "Error reading input, please try again or terminate using Ctrl^C.\n" );
		}
	}
	return( 1 );
}

/* Get a byte size variable
 * Returns 1 if successful, 0 if no input was provided or -1 on error
 */
int ewfinput_get_byte_size_variable(
     FILE *stream,
     system_character_t *input_buffer,
     size_t input_buffer_size,
     system_character_t *request_string,
     uint64_t minimum,
     uint64_t maximum,
     uint64_t default_value,
     uint64_t *byte_size_variable,
     liberror_error_t **error )
{
	system_character_t minimum_size_string[ 16 ];
	system_character_t maximum_size_string[ 16 ];
	system_character_t default_size_string[ 16 ];

	system_character_t *end_of_input  = NULL;
	system_character_t *result_string = NULL;
	static char *function             = "ewfinput_get_byte_size_variable";
	ssize_t input_length              = 0;

	if( stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid output stream.",
		 function );

		return( -1 );
	}
	if( input_buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid input buffer.",
		 function );

		return( -1 );
	}
	if( input_buffer_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid input buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( request_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid request string.",
		 function );

		return( -1 );
	}
	if( byte_size_variable == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte size variable.",
		 function );

		return( -1 );
	}
	if( byte_size_string_create(
	     minimum_size_string,
	     16,
	     minimum,
	     BYTE_SIZE_STRING_UNIT_MEBIBYTE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to create minimum byte size string.",
		 function );

		return( -1 );
	}
	if( byte_size_string_create(
	     default_size_string,
	     16,
	     default_value,
	     BYTE_SIZE_STRING_UNIT_MEBIBYTE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to create default byte size string.",
		 function );

		return( -1 );
	}
	if( byte_size_string_create(
	     maximum_size_string,
	     16,
	     maximum,
	     BYTE_SIZE_STRING_UNIT_MEBIBYTE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to create maximum byte size string.",
		 function );

		return( -1 );
	}
	/* Safe guard the end of the input buffer
	 */
	input_buffer[ input_buffer_size - 1 ] = 0;

	while( 1 )
	{
		fprintf(
		 stream,
		 "%" PRIs_SYSTEM " (%" PRIs_SYSTEM " >= value >= %" PRIs_SYSTEM ") [%" PRIs_SYSTEM "]: ",
		 request_string,
		 minimum_size_string,
		 maximum_size_string,
		 default_size_string );

		result_string = system_string_get_from_stream(
		                 input_buffer,
		                 input_buffer_size - 1,
		                 stdin );

		if( result_string != NULL )
		{
			end_of_input = system_string_search(
			                input_buffer,
			                (system_character_t) '\n',
			                input_buffer_size );

			/* Input was larger than size of buffer
			 */
			if( end_of_input == NULL )
			{
				/* Flush the stdin stream
				 */
				while( end_of_input == NULL )
				{
					result_string = system_string_get_from_stream(
					                 input_buffer,
					                 input_buffer_size - 1,
					                 stdin );

					end_of_input = system_string_search(
					                input_buffer,
					                (system_character_t) '\n',
					                input_buffer_size );

				}
				return( -1 );
			}
			input_length = (ssize_t) ( end_of_input - input_buffer );

			if( input_length < 0 )
			{
				return( -1 );
			}
			else if( input_length == 0 )
			{
				*byte_size_variable = default_value;

				return( 0 );
			}
			if( byte_size_string_convert(
			     input_buffer,
			     (size_t) input_length,
			     byte_size_variable,
			     NULL ) != 1 )
			{
				fprintf(
				 stream,
				 "Invalid value, please try again or terminate using Ctrl^C.\n" );
			}
			else if( ( *byte_size_variable >= minimum )
			      && ( *byte_size_variable <= maximum ) )
			{
				break;
			}
			else
			{
				fprintf(
				 stream,
				 "Value not within specified range, please try again or terminate using Ctrl^C.\n" );
			}
		}
		else
		{
			fprintf(
			 stream,
			 "Error reading input, please try again or terminate using Ctrl^C.\n" );
		}
	}
	return( 1 );
}

/* Get a fixed value string variable
 * Returns 1 if successful, 0 if no input was provided or -1 on error
 */
int ewfinput_get_fixed_string_variable(
     FILE *stream,
     system_character_t *input_buffer,
     size_t input_buffer_size,
     system_character_t *request_string,
     system_character_t **values,
     uint8_t amount_of_values,
     uint8_t default_value,
     system_character_t **fixed_string_variable,
     liberror_error_t **error )
{

	system_character_t *end_of_input  = NULL;
	system_character_t *result_string = NULL;
	static char *function             = "ewfinput_get_fixed_value";
	size_t value_length               = 0;
	ssize_t input_length              = 0;
	uint8_t value_iterator            = 0;

	if( stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid output stream.",
		 function );

		return( -1 );
	}
	if( input_buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid input buffer.",
		 function );

		return( -1 );
	}
	if( input_buffer_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid input buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( request_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid request string.",
		 function );

		return( -1 );
	}
	if( default_value >= amount_of_values )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: default value exceeds amount.",
		 function );

		return( -1 );
	}
	if( fixed_string_variable == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid fixed string variable.",
		 function );

		return( -1 );
	}
	while( 1 )
	{
		fprintf(
		 stream,
		 "%" PRIs_SYSTEM " (",
		 request_string );

		for( value_iterator = 0; value_iterator < amount_of_values; value_iterator++ )
		{
			if( value_iterator > 0 )
			{
				fprintf(
				 stream,
				 ", " );
			}
			fprintf(
			 stream,
			 "%" PRIs_SYSTEM "",
			 values[ value_iterator ] );
		}
		fprintf(
		 stream,
		 ") [%" PRIs_SYSTEM "]: ",
		 values[ default_value ] );

		result_string = system_string_get_from_stream(
		                 input_buffer,
		                 input_buffer_size - 1,
		                 stdin );

		if( result_string != NULL )
		{
			end_of_input = system_string_search(
			                input_buffer,
			                (system_character_t) '\n',
			                input_buffer_size );

			/* Input was larger than size of buffer
			 */
			if( end_of_input == NULL )
			{
				/* Flush the stdin stream
				 */
				while( end_of_input == NULL )
				{
					result_string = system_string_get_from_stream(
					                 input_buffer,
					                 input_buffer_size - 1,
					                 stdin );

					end_of_input = system_string_search(
					                input_buffer,
					                (system_character_t) '\n',
					                input_buffer_size );

				}
				return( -1 );
			}
			input_length = (ssize_t) ( end_of_input - input_buffer );

			if( input_length < 0 )
			{
				return( -1 );
			}
			else if( input_length == 0 )
			{
				*fixed_string_variable = values[ default_value ];

				return( 0 );
			}
			for( value_iterator = 0; value_iterator < amount_of_values; value_iterator++ )
			{
				value_length = system_string_length(
						values[ value_iterator ] );

				if( ( value_length == (size_t) input_length )
				 && ( system_string_compare(
				       input_buffer,
				       values[ value_iterator ],
				       value_length ) == 0 ) )
				{
					break;
				}
			}
			if( value_iterator < amount_of_values )
			{
				*fixed_string_variable = values[ value_iterator ];

				break;
			}
			fprintf(
			 stream,
			 "Selected option not supported, please try again or terminate using Ctrl^C.\n" );
		}
		else
		{
			fprintf(
			 stream,
			 "Error reading input, please try again or terminate using Ctrl^C.\n" );
		}
	}
	return( 1 );
}


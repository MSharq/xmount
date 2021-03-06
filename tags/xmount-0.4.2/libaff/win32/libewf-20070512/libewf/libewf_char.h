/*
 * libewf character type to wrap both char and wchar_t
 *
 * Copyright (c) 2006-2007, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the creator, related organisations, nor the names of
 *   its contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * - All advertising materials mentioning features or use of this software
 *   must acknowledge the contribution by people stated in the acknowledgements.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER, COMPANY AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _LIBEWF_CHAR_H
#define _LIBEWF_CHAR_H

#include "libewf_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LIBEWF_CHAR libewf_char_t
#define LIBEWF_CHAR_SIZE sizeof( LIBEWF_CHAR )

#if defined( HAVE_WIDE_CHARACTER_TYPE )

typedef wchar_t libewf_char_t;

#define PRIc_EWF			"lc"
#define PRIs_EWF			"ls"

/* Intermediate version of the macro
 * required for correct evaluation
 * predefined string
 */
#define _S_LIBEWF_CHAR_I( string )	L ## string
#define _S_LIBEWF_CHAR( string )	_S_LIBEWF_CHAR_I( string )

#else

typedef char libewf_char_t;

#define PRIc_EWF			"c"
#define PRIs_EWF			"s"

#define _S_LIBEWF_CHAR( string )	string

#endif

#ifdef __cplusplus
}
#endif

#endif


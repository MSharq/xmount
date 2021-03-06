/*
 * EWF ltree section
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

#ifndef _EWF_LTREE_H
#define _EWF_LTREE_H

#include "libewf_includes.h"

#include "ewf_char.h"
#include "ewf_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EWF_LTREE ewf_ltree_t
#define EWF_LTREE_SIZE sizeof( EWF_LTREE )

#define EWF_LTREE_DATA EWF_CHAR

typedef struct ewf_ltree ewf_ltree_t;

struct ewf_ltree
{
	/* Unknown
	 * consists of 16 bytes
	 */
	uint8_t unknown1[ 16 ];

	/* The size of the tree in bytes
	 * consists of 4 bytes (32 bits)
	 */
	uint8_t tree_size[ 4 ];

	/* Unknown
	 * consists of 4 bytes
	 * contains 0x00
	 */
	uint8_t unknown2[ 4 ];

	/* Unknown
	 * consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * consists of 20 bytes
	 * contains 0x00
	 */
	uint8_t unknown4[ 20 ];
};

ssize_t ewf_ltree_read( EWF_LTREE *ltree, int file_descriptor );
ssize_t ewf_ltree_write( EWF_LTREE *ltree, int file_descriptor );

#define ewf_tree_data_read( file_descriptor, length ) \
	ewf_string_read( file_descriptor, length )

#ifdef __cplusplus
}
#endif

#endif


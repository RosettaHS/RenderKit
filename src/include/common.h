/**********************************************************************************/
/*                                                                                */
/*                              Copyright (c) 2021                                */
/*                           Rosetta H&S International                            */
/*                                                                                */
/*  Permission is hereby granted, free of charge, to any person obtaining a copy  */
/*  of this software and associated documentation files (the "Software"), to deal */
/*  in the Software without restriction, including without limitation the right   */
/*    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell   */
/*       copies of the Software, and to permit persons to whom the Software is    */
/*          furnished to do so, subject to the following conditions:              */
/*                                                                                */
/* The above copyright notice and this permission notice shall be included in all */
/*                copies or substantial portions of the Software.                 */
/*                                                                                */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  */
/* SOFTWARE.                                                                      */
/*                                                                                */
/**********************************************************************************/

#ifndef __RENDERKIT_COMMON_H__
#define __RENDERKIT_COMMON_H__

#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
	#define _RKBEGIN extern "C" {
	#define _RKEND }
#else
	#define _RKBEGIN
	#define _RKEND
#endif

_RKBEGIN

/*** Generic types ***/

/* A Boolean, can be 1 or 0. */
typedef _Bool rkbool_t;
/* Used for colouring Elements. */
typedef uint32_t rkcol_t;
/* A generic identifier for all Elements. */
typedef uint32_t rkgid_t;
/* Emitted by a RenderKit function whenever there is an error or warning, check "errdef.h" for the definition of the error code. */
typedef uint16_t rkerr_t;

/* An enumeration of RenderKit Elements. */
typedef enum{
	RKT_ERROR,
	RKT_CONNECTION,
	RKT_CONTEXT
}rktype_t;

/* The base for all RenderKit Elements. */
typedef struct{
	/* The Type of this Element. */
	rktype_t type;
	/* The X Identifier of this Element. */
	rkgid_t  xid;
}rkgeneric_t;

_RKEND

#endif /* !__RENDERKIT_COMMON_H__ */
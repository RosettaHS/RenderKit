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

#ifndef __RENDERKIT_CONTEXT_H__
#define __RENDERKIT_CONTEXT_H__

#include "common.h"

_RKBEGIN

/* An enumeration of possible types for a Context. */
typedef enum{
	RKCT_ELEMENT,
	RKCT_TOPLEVEL,
	RKCT_TOPLEVEL_BORDERLESS,
	RKCT_INPUTONLY
}rkcontexttype_t;

/* An absraction of the X Window, basis for all graphics in RenderKit. */
typedef struct rkcontext_t{
	/* The Type of this Element. */
	rktype_t type;
	/* The X Identifier of this Context. */
	rkgid_t  xid;
	/* The X Identifier of the internal X Graphics Context used by this Context. */
	rkgid_t  xgc;
	/* The special Type of this Context. */
	rkcontexttype_t contextType;
	/* This Context's parent. */
	struct rkcontext_t* parent;
	/* Has this Context been mapped? */
	rkbool_t mapped; 
	/* The event mask used by this Context. */
	rkmask_t eventMask;
	/* The Colour of the border of this Context. */
	rkcol_t  bordCol;
	/* The Colour of the foreground of this Context. */
	rkcol_t  foreCol;
	/* The size of the border of this Context. */
	uint16_t borderSize;
	/* The title of the border of this Context. - Only used in a non-RKCT_ELEMENT Context. */
	char*    title;
}rkcontext_t;

/* A representation of the X Root Window (The WM) as a Context. */
extern rkcontext_t RK_ROOTCONTEXT;

extern rkcontext_t* rk_createContext(rkcontext_t* root, int16_t x, int16_t y, uint16_t w, uint16_t h,
                                     uint16_t borderSize, rkcol_t borderCol, rkcol_t foregroundCol, rkmask_t eventMask, rkcontexttype_t type);
extern rkbool_t     rk_destroyContext(rkcontext_t*);

extern rkbool_t rk_contextMap(rkcontext_t*);

_RKEND

#endif /* !__RENDERKIT_CONTEXT_H__ */
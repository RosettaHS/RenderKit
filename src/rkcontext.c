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

#define RK_INTERNAL

#include <string.h>
#include <malloc.h>
#include <xcb/xcb.h>
#include "logging.h"
#include "include/connection.h"
#include "include/rkcontext.h"

rkcontext_t RK_ROOTCONTEXT={ RKCT_TOPLEVEL,0,0,0,0,0,0,0,0,0,0 };

/* Creation */

rkcontext_t* rk_createContext(rkcontext_t* root, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t borderSize, rkcol_t borderCol, rkcol_t foregroundCol, rkmask_t eventMask, rkcontexttype_t type){
	XONLY{
		rkcontext_t* context=(rkcontext_t*)malloc(sizeof(rkcontext_t));
		if(!context){ return 0; }
	/* Context initialisation */
		context->type=RKT_CONTEXT;
		context->xid=xcb_generate_id(XCON);
		context->xgc=( (type!=RKCT_INPUTONLY) ? xcb_generate_id(XCON) : 0 ); /* TODO: Do something with this soon! */
		context->contextType=type;
		context->parent=( (root) ? root : &RK_ROOTCONTEXT );
		context->mapped=0;
		context->eventMask=eventMask;
		context->bordCol=borderCol;
		context->foreCol=foregroundCol;
		context->borderSize=borderSize;
		context->title=0;
	/* Creating X Window */
		/* uint32_t* events; TODO: Come back to this once you have a proper event system. */
		xcb_create_window(
			XCON,XCB_COPY_FROM_PARENT, context->xid, context->parent->xid,
			x,y,w,h,borderSize, ( (type!=RKCT_INPUTONLY) ? XCB_WINDOW_CLASS_INPUT_OUTPUT : XCB_WINDOW_CLASS_INPUT_ONLY ),
			XSCR->root_visual,0,0
		);
	/* Type checking */
		xcb_intern_atom_cookie_t atype;
		xcb_intern_atom_reply_t* arepl;
		switch(type){ /* TODO: Add proper support, similar to the old CContext of OKit. */
			case RKCT_ELEMENT:  { break; }
			case RKCT_TOPLEVEL: { break; }
			case RKCT_TOPLEVEL_BORDERLESS:{
				atype=xcb_intern_atom(XCON,0,strlen("_MOTIF_WM_HINTS"),"_MOTIF_WM_HINTS");
				arepl=xcb_intern_atom_reply(XCON,atype,0);
				uint32_t buff[5]={2,0,0,0,0};
				xcb_change_property(XCON,XCB_PROP_MODE_REPLACE,context->xid,arepl->atom,arepl->atom,32,5,buff);
				free(arepl);
				break;
			}
			case RKCT_INPUTONLY:{ break; }
		}
	/* Finishing up */
		XAUTO{
			rk_contextMap(context);
			rk_flush();
		}
		return context;
	}else{ return 0; }
}

rkbool_t rk_contextMap(rkcontext_t* contextToMap){
	XONLY{
		if(contextToMap->mapped){ return 0; }
		xcb_map_window(XCON,contextToMap->xid);
		contextToMap->mapped=1;
		return 1;
	}else{ return 0; }
}

/* Deletion */

// extern rkbool_t     rk_destroyContext(rkcontext_t*);
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

#ifndef __RENDERKIT_CONNECTION_H__
#define __RENDERKIT_CONNECTION_H__

#include "common.h"

_RKBEGIN

#ifdef RK_INTERNAL
	/* Internal. A struct that contains internal X connection information. */
	struct rkConnection_t{
		void*   XCB_CON;
		void*   XCB_SCR;
		int     XCB_SID;
		rkgid_t XCB_ROOT;
	};

	/* Internal. A global instance of a struct that contains internal X connection information for this program. */
	extern struct rkConnection_t RK_CON;
	/* Internal. A boolean that states whether RenderKit has been fully initialised. */
	extern rkbool_t RK_CONNNECTED;

	/* Wrapper if() statement. Will only run the code in the brackets if RenderKit has been successfully initalised. */
	#define CONNECTED if(RK_CONNNECTED)
	/*** The following #defines require the inclusion of <xcb/xcb.h> ***/

	/* Casts the RenderKit connection pointer to a usable xcb_connection_t pointer. */
	#define XCON  ((xcb_connection_t*)RK_CON.XCB_CON)
	/* Casts the RenderKit screen pointer to a usable xcb_screen_t pointer. */
	#define XSCR  ((xcb_screen_t*)RK_CON.XCB_SCR)
	/* Retrieves the RenderKit connection screen ID. */
	#define XSID  (RK_CON.XCB_SID)
	/* Retrieves the RenderKit connection root context ID. */
	#define XROOT (RK_CON.XCB_ROOT)

#endif /* RK_INTERNAL */

/* Activates the RenderKit service. Required for use of any RenderKit elements. Returns 1 on success. */
extern rkbool_t rk_connect(void);
/* Disconnects from the RenderKit service. Returns 1 on success. */
extern rkbool_t rk_disconnect(void);

_RKEND

#endif /* !__RENDERKIT_CONNECTION_H__*/
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
	typedef struct{
		/* The Type of this Element - Always RKT_CONNECTION. */
		rktype_t type;
		/* The X Identifier of this Element - Always 0. */
		rkgid_t  xid; /* Unused */
		void*    XCB_CON;
		void*    XCB_SCR;
		int      XCB_SID;
		rkgid_t  XCB_ROOT;
	}rkconnection_t;

	/* Internal. A global instance of a struct that contains internal X connection information for this program. */
	extern rkconnection_t RK_CON;
	/* Internal. A boolean that states whether RenderKit has been fully initialised. */
	extern rkbool_t RK_CONNECTED;

	/* Wrapper if() statement. Will only run the code in the brackets if RenderKit has been successfully initalised. */
	#define XONLY if(RK_CONNECTED)
	/* Wrapper if() statement. Will only run the code in the brackets if RenderKit's mode is set to RKM_AUTO. */
	#define XAUTO if(RK_MODE==RKM_AUTO)
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

/* An enumeration of different modes for RenderKit to run as. */
typedef enum{
	/*
	 * When RK_MODE is set to this, RenderKit will automatically map Contexts and flush requests when they are called,
	 * much like how Xlib does. This makes RenderKit easier to use, however not as efficient.
	 */
	RKM_AUTO,
	/*
	 * When RK_MODE is set to this, RenderKit will NOT automatically map Contexts and flush requests when they are called,
	 * much like how XCB does. This makes RenderKit harder to use, however dramatically increases its efficiency if you use this properly.
	 */
	RKM_MANUAL
}rkmode_t;

/* The operating mode that RenderKit will run as. */
extern rkmode_t RK_MODE;

/**
 * @brief Activates the RenderKit service. Required for use of any RenderKit elements.
 * @param mode The operating mode of the service, either RKM_AUTO or RKM_MANUAL can be passed. 
 * @return 1 on success.
 */
extern rkbool_t rk_connect(rkmode_t mode);
/**
 * @brief Disconnects from the RenderKit service.
 * @return 1 on success.
 */
extern rkbool_t rk_disconnect(void);

/**
 * @brief Flushes and sends any pending requests to the X Server. Only call this manually if RK_MODE is RKM_MANUAL. 
 * @return 1 on success.
 */
extern rkbool_t rk_flush(void);

_RKEND

#endif /* !__RENDERKIT_CONNECTION_H__*/
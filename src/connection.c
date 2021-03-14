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

#include <stdlib.h>
#include <xcb/xcb.h>
#include "logging.h"
#include "include/connection.h"

/*
 * NOTE: "XCON", "XSCR", "XSID", and "XROOT" are #defines just to retrieve RK_CON's values easier, and without potential tampering. 
 * Check "connection.h" for more information.
 */

struct rkconnection_t RK_CON={RKT_CONNECTION,0,0,0,0,0};
rkbool_t RK_CONNECTED=0;

rkbool_t rk_connect(void){
	if(RK_CONNECTED){ return 0; }
	RK_CON.XCB_CON=xcb_connect(0,&RK_CON.XCB_SID);
	if(xcb_connection_has_error(XCON)){ return 0; }
	/* TODO: Replace this with a cleaner solution. XCB's documentation isn't very friendly. */
	xcb_screen_iterator_t scrite=xcb_setup_roots_iterator( xcb_get_setup(XCON) );
	for(; scrite.rem; ( --RK_CON.XCB_SID, xcb_screen_next(&scrite) ) ){
		if(!RK_CON.XCB_SID){ RK_CON.XCB_SCR=scrite.data; break; }
	}
	RK_CON.XCB_ROOT=XSCR->root;
	RK_CONNECTED=1;
	return 1;
}

rkbool_t rk_disconnect(void){
	if(!RK_CONNECTED){ return 0; }
	xcb_disconnect(XCON);
	RK_CON.XCB_CON=0;
	RK_CON.XCB_SCR=0;
	RK_CON.XCB_SID=0;
	RK_CON.XCB_ROOT=0;
	RK_CONNECTED=0;
	return 1;
}
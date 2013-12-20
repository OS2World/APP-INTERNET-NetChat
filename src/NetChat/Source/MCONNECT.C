/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : MCONNECT.C                                                     */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Gary L. Robinson                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

/* ##START Form.41 Top of source file */
/* ##END Top of source file */
#define INCL_WIN
#define INCL_NLS
#define INCL_DOS
#define INCL_GPI
#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/* ##START Form.43 Pre include files */
/* ##END Pre include files */
#include "MAIN.H"
#include "MCONNECT.H"
#include "NETCHAT.RCH"
#include "MCONNECT.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include<xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY MCONNECTDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      {
      /* ##START Form.1  */
      /* Form events - Opened */

      CHAR bstatus[20];


      WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);
      if( strcmp(bstatus, "Listen OFF") == 0 )
         {
         MLISTENWASOFF = TRUE;
         WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
         }
      else   
         MLISTENWASOFF = FALSE;
         

      {
      SWP swp, swpD;
      int dtWidth;
      int offX, offY;
      dtWidth = WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN);
      offX = 50;
      offY = 70;
      WinQueryWindowPos(WinQueryWindow(hwndDlg, QW_OWNER), (PSWP) &swp);
      WinQueryWindowPos(hwndDlg, (PSWP) &swpD);
      if( swp.x < 5 )
         swp.x += ((-swp.x) + 1); 
      if( (swp.x+offX+swpD.cx) > (dtWidth-5) )
         {
         int over;
         over = (swp.x+offX+swpD.cx) - (dtWidth-5);
         offX = - (offX+over);   
         }
      if( (swp.y-70) < 5 )
         offY = - offY; 
      WinSetWindowPos(hwndDlg, HWND_TOP, 
                      swp.x+offX, swp.y-offY, 0, 0,
      		SWP_ACTIVATE | SWP_MOVE | SWP_SHOW );
      }

      WinSetDlgItemText(hwndDlg, 1002, guestIP);
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      /* ##START Form.2  */
      /* ##END  */
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1003 Clicked/Selected */
      case 1003:
         {
         /* ##START 1003.0  */
         /* Event Clicked/selected - Co~nnect  1003 */

         CHAR bstatus[40];
         // INT kb;

         if( WinQueryDlgItemTextLength(hwndDlg, 1002) < 1 )
            {
            msgBox(hwndDlg, "Attention!", "You must enter a valid IP address for NetChat to work properly.");
            return(0);
            }

         WinQueryDlgItemText(hwndDlg, 1002, sizeof(guestIP), guestIP);


         // WinEnableControl(hwndDlg, 1003, FALSE);
         // WinEnableControl(hwndDlg, 1004, FALSE);
         // WinEnableWindow(hwndDlg, FALSE);
         // NOWLISTENING = FALSE;
         // kb = 0;
         // do
         //    {
         //   DosSleep(50);
         //   WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);
         //   kb++;
         //   }
         // while( !NOWLISTENING && kb < 40 );   

         WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);

         if( strcmp(bstatus, "Listen ON") == 0 )
            {
            if( (INT)guestIP[0] > 47 && (INT)guestIP[0] < 58 )  
               _beginthread(attemptConnect, NULL, BSTACK, (PVOID)&hwndMainDlg);
            else   
               _beginthread(attemptConnect2, NULL, BSTACK, (PVOID)&hwndMainDlg);
            }

         if( strcmp(bstatus, "Listen OFF") == 0 )
            {
            WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
            if( (INT)guestIP[0] > 47 && (INT)guestIP[0] < 58 )  
               _beginthread(attemptConnect, NULL, BSTACK, (PVOID)&hwndMainDlg);
            else   
               _beginthread(attemptConnect2, NULL, BSTACK, (PVOID)&hwndMainDlg);
            }

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1004 Clicked/Selected */
      case 1004:
         {
         /* ##START 1004.0  */
         /* Event Clicked/selected - ~Cancel  1004 */

         CHAR bstatus[20];

         WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);
         if( strcmp(bstatus, "Listen ON") == 0 )
            {
            if( MLISTENWASOFF )
               WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
            }

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenMCONNECT(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           MCONNECTDlgProc, 
           0, ID_MCONNECTFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

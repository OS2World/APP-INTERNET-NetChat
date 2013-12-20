/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : ABOUT.C                                                        */
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
#include "ABOUT.H"
#include "NETCHAT.RCH"
#include "ABOUT.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY ABOUTDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* Code sections - Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      {
      /* ##START Form.1  */
      /* Form events - Opened */

      SWP swp, swpD;
      int dtWidth;
      int offX, offY;

      // msgBox(hwndDlg, "ncversion", ncversion);
      WinSetDlgItemText(hwndDlg, 1000, ncversion);

      dtWidth = WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN);
      offX = 50;  // 50
      offY = 120;  // 70
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

      if( !registered(ncpw) )
         {
         WinEnableWindow(WinWindowFromID(hwndDlg, FID_SYSMENU), FALSE);
         }
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      /* ##START Form.2  */
      /* ##END  */
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   /* Form event Destroyed WM_DESTROY */
   case WM_DESTROY :
      {
      /* ##START Form.3  */
      /* Form events - Destroyed */
      /* ##END  */
      }
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1002 Clicked/Selected */
      case 1002:
         {
         /* ##START 1002.0  */
         /* Event Clicked/selected - ~OK  1002 */

         INT k;


         if( !registered(ncpw) )
            {
            for(k=0;k<8;k++)
               {
               DosBeep(1100-(k*100), 100);
               DosSleep(200);
               }
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
HWND OpenABOUT(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           ABOUTDlgProc, 
           0, ID_ABOUTFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

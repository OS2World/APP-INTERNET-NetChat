/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : SETTINGS.C                                                     */
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
#include "SETTINGS.H"
#include "NETCHAT.RCH"
#include "SETTINGS.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY SETTINGSDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
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


      {
      ULONG dtHeight, dtWidth, lHeight, lWidth;
      SWP swp;
      dtHeight = WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN);
      dtWidth = WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN);
      WinQueryWindowPos(hwndDlg, (PSWP) &swp);
      lWidth = (dtWidth/2) - (swp.cx/2); 
      lHeight = (dtHeight/2) - (swp.cy/2); 
      WinSetWindowPos(hwndDlg, HWND_TOP, lWidth, lHeight, 0, 0, SWP_MOVE | SWP_SHOW | SWP_ACTIVATE);
      }

      queryNCSet();

      if( pgmData[38] == 1 )
         WinCheckButton(hwndDlg, 1024, 1);

      WinSetDlgItemText(hwndDlg, 1004, mailServer);
      WinSetDlgItemText(hwndDlg, 1005, userName);
      WinSetDlgItemText(hwndDlg, 1006, passWord);
      WinSetDlgItemText(hwndDlg, 1012, mailServer2);
      WinSetDlgItemText(hwndDlg, 1013, userName2);
      WinSetDlgItemText(hwndDlg, 1016, passWord2);
      WinSetDlgItemText(hwndDlg, 1007, nickName);
      WinSetDlgItemText(hwndDlg, 1017, rtema);
      WinSetDlgItemText(hwndDlg, 1018, rtname);
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
      /* Button 1019 Clicked/Selected */
      case 1019:
         {
         /* ##START 1019.0  */
         /* Event Clicked/selected - ~OK  1019 */


         WinQueryDlgItemText(hwndDlg, 1004, CCHMAXPATH, mailServer);
         WinQueryDlgItemText(hwndDlg, 1005, CCHMAXPATH, userName);
         WinQueryDlgItemText(hwndDlg, 1006, CCHMAXPATH, passWord);
         WinQueryDlgItemText(hwndDlg, 1012, CCHMAXPATH, mailServer2);
         WinQueryDlgItemText(hwndDlg, 1013, CCHMAXPATH, userName2);
         WinQueryDlgItemText(hwndDlg, 1016, CCHMAXPATH, passWord2);
         WinQueryDlgItemText(hwndDlg, 1007, CCHMAXPATH, nickName);
         WinQueryDlgItemText(hwndDlg, 1017, CCHMAXPATH, rtema);
         WinQueryDlgItemText(hwndDlg, 1018, CCHMAXPATH, rtname);
         if( WinQueryButtonCheckstate(hwndDlg,1024) )
            pgmData[38] = 1;
         else   
            pgmData[38] = 0;
         // bugem(hwndDlg);
         saveNCSet();
         makeTBar();
         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1020 Clicked/Selected */
      case 1020:
         {
         /* ##START 1020.0  */
         /* Event Clicked/selected - ~Cancel  1020 */

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* Event Code sections, User defined messages */
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenSETTINGS(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           SETTINGSDlgProc, 
           0, ID_SETTINGSFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

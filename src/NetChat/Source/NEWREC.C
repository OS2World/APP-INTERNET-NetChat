/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.29f                                   */
/*                                                                            */
/* File Name : NEWREC.C                                                       */
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
#include "NEWREC.H"
#include "NETCHAT.RCH"
#include "NEWREC.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */


#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY NEWRECDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
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

      zeroNCTmpr();
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
         /* Event Clicked/selected - ~Save  1003 */

         bugem(hwndDlg);

         if( WinQueryDlgItemTextLength(hwndDlg, 1000) <= 0 )
            return(0);

         if( WinQueryDlgItemTextLength(hwndDlg, 1001) <= 0 )
            return(0);

         WinQueryDlgItemText(hwndDlg, 1000, sizeof(ncTmpr.ncName), ncTmpr.ncName);
         WinQueryDlgItemText(hwndDlg, 1001, sizeof(ncTmpr.ncURL), ncTmpr.ncURL);
         WinQueryDlgItemText(hwndDlg, 1002, sizeof(ncTmpr.ncNote), ncTmpr.ncNote);
         ncTmpr.indx = 1;

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1004 Clicked/Selected */
      case 1004:
         {
         /* ##START 1004.0  */
         /* Event Clicked/selected - ~Cancel  1004 */

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
HWND OpenNEWREC(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           NEWRECDlgProc, 
           0, ID_NEWRECFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

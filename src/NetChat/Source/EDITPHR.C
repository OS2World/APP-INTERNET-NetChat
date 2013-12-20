/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.29f                                   */
/*                                                                            */
/* File Name : EDITPHR.C                                                      */
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
#include "EDITPHR.H"
#include "NETCHAT.RCH"
#include "EDITPHR.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */


#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY EDITPHRDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PEDITPHRFORMINFO pEDITPHRFormInfo=(PEDITPHRFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(EDITPHRFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pEDITPHRFormInfo=(PEDITPHRFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      {
      /* ##START Form.1  */
      /* Event Form events, Opened */

      WinSendDlgItemMsg(hwndDlg, 1000,
                        MLM_SETTEXTLIMIT,
                        MPFROMLONG(PHRTXTLIMIT), 0);
                        
                        
      WinSetDlgItemText(hwndDlg, 1000, PHRTMP.phrase);
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

      zeroPHRTMP();
      /* ##END  */
      }
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1001 Clicked/Selected */
      case 1001:
         {
         /* ##START 1001.0  */
         /* Event Clicked/selected - ~Save  1001 */

         bugem(hwndDlg);

         if( WinQueryDlgItemTextLength(hwndDlg, 1000) <= 0 )
            return(0);

         WinQueryDlgItemText(hwndDlg, 1000, sizeof(PHR[PHRTMP.index].phrase), PHR[PHRTMP.index].phrase);

         savePHRData(PHRDATAFILE);

         loadPHRLBox(pEDITPHRFormInfo->hwnd, PHRDATAFILE);

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1002 Clicked/Selected */
      case 1002:
         {
         /* ##START 1002.0  */
         /* Event Clicked/selected - ~Cancel  1002 */


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
HWND OpenEDITPHR(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           EDITPHRDlgProc, 
           0, ID_EDITPHRFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

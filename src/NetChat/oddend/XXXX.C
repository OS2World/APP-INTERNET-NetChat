/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : HAILLIST.C                                                     */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Copyright notice                                            */
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
#include "HAILLIST.H"
#include "NETCHAT.RCH"
#include "HAILLIST.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include <xtra.h>
#include <xtrarc.h>
#include <EDITREC.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY HAILLISTDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PHAILLISTFORMINFO pHAILLISTFormInfo=(PHAILLISTFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = WinQueryWindow(hwndDlg, QW_PARENT);
 /* ##START Form.37 Top of window procedure */
 /* Code sections - Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(HAILLISTFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pHAILLISTFormInfo=(PHAILLISTFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      {
      /* ##START Form.1  */
      /* Form events - Opened */


      WinEnableWindow(hwndDlg, FALSE);

      zeroNCData();
      if( !loadNCLBox(hwndDlg, ncDataFile) )
         zeroNCData();

      WinEnableWindow(hwndDlg, TRUE);

      if( pHAILLISTFormInfo->mode == 0 )
         {
         WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), "Double left click to send.  Right click for menu.");
         }

      if( pHAILLISTFormInfo->mode == 1 )
         {
         WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), "Double left click to edit.  Right click for menu.");
         }

      hwndMLBPopup = WinLoadMenu(WinWindowFromID(hwndDlg, 1000),
                                 0, ID_NCMAIN);


      moldWinProc = WinSubclassWindow(WinWindowFromID(hwndDlg, 1000), NewListProc);
      WinSetWindowPtr(WinWindowFromID(hwndDlg, 1000), 0, (PVOID) moldWinProc);
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      /* ##START Form.2  */
      /* ##END  */
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   /* Form event Activation changed WM_ACTIVATE */
   case WM_ACTIVATE :
      {
      /* ##START Form.10  */
      /* Form events - Activation changed */
      /* ##END  */
      }
      break;

   case WM_COMMAND :
      menuChoice(hwndDlg, hwndFrame, hwndMLBPopup, msg, mp1, mp2);
      break;
     
   case WM_CONTROL :
      switch (SHORT1FROMMP(mp1)) {
      /* List Box 1000 Event Handlers */
      case 1000:
         switch (SHORT2FROMMP(mp1)) {
         /* Mouse button 1 double click */
         case LN_ENTER:
            {
            /* ##START 1000.3  */
            /* Event Mouse button 1 double click - List Box  1000 */

            INT sel;
            INT handle;
            CHAR bstatus[20];


            WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);

            sel = (LONG)WinSendDlgItemMsg(hwndDlg, 1000,
                                          LM_QUERYSELECTION,
                                          MPFROMLONG(LIT_FIRST),
                                          MPFROMLONG(0));

            handle = (LONG)WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_QUERYITEMHANDLE,
                                MPFROMSHORT(sel), 0); 


            if( pHAILLISTFormInfo->mode == 0 )
               {
               haildat.hwndDlg = WinQueryWindow(hwndFrame, QW_OWNER);
               haildat.interval = handle;
               _beginthread(sendEMail, NULL, BSTACK, (PVOID)&haildat);
               
               if( strcmp(bstatus, "Listen OFF") == 0 )
                  {
                  if( pgmData[7] > 1 )
                     WinPostMsg(pHAILLISTFormInfo->hwnd, WM_COMMAND, MPFROM2SHORT(1002, 0), 0);
                  }
                     
               WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
               }

            if( pHAILLISTFormInfo->mode == 1 )
               {
               // DosBeep(100, 100);
               USHORT usReturn;
               HWND hNewFrame;
               // PEDITRECFORMINFO pEditrecFormInfo = malloc(sizeof(EDITRECFORMINFO));
                  
               editRecord(ncDataFile, hwndDlg);
               // pEditrecFormInfo->hwnd = hwndDlg;
               // hNewFrame = OpenEDITREC(hwndDlg, pEditrecFormInfo);
               hNewFrame = OpenEDITREC(hwndDlg, 0);
               usReturn = (USHORT) WinProcessDlg(hNewFrame);
               }
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      } /* end switch */
      break;

   /* Allow frame window to handle accelerators */
   case WM_TRANSLATEACCEL:
        if (WinSendMsg(hwndFrame, msg, mp1, mp2 ))
           return (MRESULT) TRUE;
        return WinDefDlgProc( hwndDlg, msg, mp1, mp2 );
   break;
 /* ##START Form.38 User defined messages */
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenHAILLIST(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   HWND hwndClient;
   FRAMECDATA frameData;
   frameData.cb=sizeof(FRAMECDATA);
   frameData.flCreateFlags= FCF_NOBYTEALIGN | FCF_SIZEBORDER | FCF_TITLEBAR | FCF_SYSMENU | FCF_TASKLIST | FCF_ICON ;
   frameData.hmodResources=0;
   frameData.idResources=ID_HAILLISTFORM;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame=WinCreateWindow(HWND_DESKTOP, WC_FRAME, "NetChat hailing address list", 0,0,0,0,0,hwndOwner,HWND_TOP,ID_HAILLISTFORM,&frameData,0);
   if (hwndFrame) {
      hwndClient =(HWND) WinLoadDlg(hwndFrame,
              hwndFrame,   
              HAILLISTDlgProc, 
              0, ID_HAILLISTFORM, 
              pInfo); 
      WinShowWindow(hwndFrame, TRUE);
   }
   return hwndFrame;
}

/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.29f                                   */
/*                                                                            */
/* File Name : PHRLIST.C                                                      */
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
#include "PHRLIST.H"
#include "NETCHAT.RCH"
#include "PHRLIST.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include <xtra.h>
#include <xtrarc.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY PHRLISTDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PPHRLISTFORMINFO pPHRLISTFormInfo=(PPHRLISTFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = WinQueryWindow(hwndDlg, QW_PARENT);
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(PHRLISTFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pPHRLISTFormInfo=(PPHRLISTFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      {
      /* ##START Form.1  */
      /* Form events - Opened */

      hwndMLPPopup = WinLoadMenu(WinWindowFromID(hwndDlg, 1000), 0, ID_PHRMAIN);

      poldWinProc = WinSubclassWindow(WinWindowFromID(hwndDlg, 1000), newPhrProc);
      WinSetWindowPtr(WinWindowFromID(hwndDlg, 1000), 0, (PVOID) poldWinProc);

      zeroPHRData();
      loadPHRData(PHRDATAFILE);
      loadPHRLBox(hwndDlg, PHRDATAFILE);

      if( STARTMIN )
         {
         WinSetWindowPos(hwndFrame, 0, pgmData[10], pgmData[11], pgmData[12], pgmData[13], SWP_MOVE | SWP_SIZE | SWP_MINIMIZE);
         STARTMIN = 0;
         }
      else   
         {
         WinSetWindowPos(hwndFrame, 0, pgmData[10], pgmData[11], pgmData[12], pgmData[13], SWP_MOVE|SWP_SIZE);
         }
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Form events - Closed */

      SWP  swp;

      WinQueryWindowPos(hwndFrame, &swp);
      pgmData[10] = swp.x ;
      pgmData[11] = swp.y ;
      pgmData[12] = swp.cx ;
      pgmData[13] = swp.cy ;

      saveNCSet();
      /* ##END  */
      }
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

   /* Form event Activation changed WM_ACTIVATE */
   case WM_ACTIVATE :
      {
      /* ##START Form.10  */
      /* Form events - Activation changed */


      /*
      WinSetWindowPos(hwndFrame,
                      0, 
                      pgmData[10], 
                      pgmData[11],   
                      pgmData[12],  
                      pgmData[13],  
                      SWP_MOVE|SWP_SIZE);

      */
      /* ##END  */
      }
      break;

   /* Form event Popup menu WM_CONTEXTMENU */
   case WM_CONTEXTMENU :
      {
      /* ##START Form.12  */
      /* Form events - Popup menu */
      /* ##END  */
      }
      break;

   case WM_COMMAND :
      phrmenuChoice(hwndDlg, hwndFrame, hwndMLBPopup, msg, mp1, mp2);
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
            /* Event List Box  1000, Mouse button 1 double click */

            LONG sel;
            INT index;
            LONG curpos;


            sel = (LONG)WinSendDlgItemMsg(hwndDlg, 1000,
                                          LM_QUERYSELECTION,
                                          MPFROMLONG(LIT_FIRST),
                                          MPFROMLONG(0));

            index = (ULONG)WinSendDlgItemMsg(hwndDlg, 1000,
                                             LM_QUERYITEMHANDLE,
                                             MPFROMLONG(sel), 0);

            MLEInsertText(hwndMainDlg, 1001, -1, PHR[index].phrase);

            WinSetFocus(HWND_DESKTOP,WinWindowFromID(hwndMainDlg, 1001));

            _beginthread(pressOK, NULL, BSTACK, NULL);
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
HWND OpenPHRLIST(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   HWND hwndClient;
   FRAMECDATA frameData;
   frameData.cb=sizeof(FRAMECDATA);
   frameData.flCreateFlags= FCF_NOBYTEALIGN | FCF_SIZEBORDER | FCF_TITLEBAR | FCF_SYSMENU | FCF_MINBUTTON | FCF_ICON ;
   frameData.hmodResources=0;
   frameData.idResources=ID_PHRLISTFORM;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame=WinCreateWindow(HWND_DESKTOP, WC_FRAME, "Double left click to send selection.  Right click for menu.", 0,0,0,0,0,hwndOwner,HWND_TOP,ID_PHRLISTFORM,&frameData,0);
   if (hwndFrame) {
      hwndClient =(HWND) WinLoadDlg(hwndFrame,
              hwndFrame,   
              PHRLISTDlgProc, 
              0, ID_PHRLISTFORM, 
              pInfo); 
      WinShowWindow(hwndFrame, TRUE);
   }
   return hwndFrame;
}

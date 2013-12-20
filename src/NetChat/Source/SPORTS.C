/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : SPORTS.C                                                       */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Gary L. Robinson                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

/* ##START Form.41 Top of source file */
/* Code sections - Top of source file */
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
#include "SPORTS.H"
#include "NETCHAT.RCH"
#include "SPORTS.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */


#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY SPORTSDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
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

      CHAR cstatus[20];
      CHAR buttontxt[40];
      CHAR rtxt[6];
      CHAR ttxt[6];
      CHAR ftxt[6];


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


      itoa(pgmData[35], rtxt, 10);
      itoa(pgmData[36], ttxt, 10);
      itoa(pgmData[37], ftxt, 10);
      strcpy(buttontxt, "Reset ports to R:");
      strcat(buttontxt, rtxt);
      strcat(buttontxt, " T:");
      strcat(buttontxt, ttxt);
      strcat(buttontxt, " F:");
      strcat(buttontxt, ftxt);
      WinSetDlgItemText(hwndDlg, 1006, buttontxt);

      WinSetDlgItemShort(hwndDlg, 1003, (SHORT)pgmData[4], TRUE);
      WinSetDlgItemShort(hwndDlg, 1002, (SHORT)pgmData[5], TRUE);
      WinSetDlgItemShort(hwndDlg, 1004, (SHORT)pgmData[8], TRUE);

      WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(cstatus), cstatus);

      if( strcmp(cstatus, "Listen ON") == 0 )
         {
         WASCONNECTED = TRUE;
         WinPostMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002, 0), 0);
         }
      else
         WASCONNECTED = FALSE;
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

      if( WASCONNECTED )
         {
         WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002, 0), 0);
         }
      /* ##END  */
      }
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1000 Clicked/Selected */
      case 1000:
         {
         /* ##START 1000.0  */
         /* Event Clicked/selected - ~Save  1000 */

         SHORT g;
         CHAR bstatus[20];


         // bugem(hwndDlg);

         WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);

         if( strcmp(bstatus, "Connected!") == 0 )
            {
            if( !FTPINPROGRESS )
               {
               if( WinQueryDlgItemTextLength(hwndDlg, 1004) > 0 )
                  {
                  WinQueryDlgItemShort(hwndDlg, 1004, &g, TRUE);
                  pgmData[8] = g;

                  saveNCSet();
                  makeTBar();

                  msgBox(hwndDlg, "Notice :", "ONLY the current FTP port will be changed while connected.");
                  WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
                  }
               else
                  {
                  msgBox(hwndDlg, "Attention!", "You must enter a port number between 0-9999.");   
                  return(0);
                  }
               }
            else
               msgBox(hwndDlg, "Attention!", "No Current ports will be changed while connected and transfering files.");
            }
         else
            {   
            if( WinQueryDlgItemTextLength(hwndDlg, 1003) > 0 && 
                WinQueryDlgItemTextLength(hwndDlg, 1002) > 0 && 
                WinQueryDlgItemTextLength(hwndDlg, 1004) > 0 )
               {
               WinQueryDlgItemShort(hwndDlg, 1003, &g, TRUE);
               pgmData[4] = g;

               WinQueryDlgItemShort(hwndDlg, 1002, &g, TRUE);
               pgmData[5] = g;

               WinQueryDlgItemShort(hwndDlg, 1004, &g, TRUE);
               pgmData[8] = g;
               saveNCSet();
               makeTBar();
               WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
               }
            else
               {
               msgBox(hwndDlg, "Attention!", "You must enter a port number between 0-9999 for every entry.");   
               return(0);
               }
            }
         /* ##END  */
         }
         break;
      /* Button 1001 Clicked/Selected */
      case 1001:
         {
         /* ##START 1001.0  */
         /* Event Clicked/selected - ~Cancel  1001 */



         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1006 Clicked/Selected */
      case 1006:
         {
         /* ##START 1006.0  */
         /* Event Clicked/selected - Reset ports (6667, 6667, 21)  1006 */


         pgmData[4] = pgmData[35];
         pgmData[5] = pgmData[36];
         pgmData[8] = pgmData[37];

         WinSetDlgItemShort(hwndDlg, 1003, (SHORT)pgmData[4], FALSE);
         WinSetDlgItemShort(hwndDlg, 1002, (SHORT)pgmData[5], FALSE);
         WinSetDlgItemShort(hwndDlg, 1004, (SHORT)pgmData[8], FALSE);

         saveNCSet();
         makeTBar();
         WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
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
HWND OpenSPORTS(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           SPORTSDlgProc, 
           0, ID_SPORTSFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

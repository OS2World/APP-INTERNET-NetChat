/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.29f                                   */
/*                                                                            */
/* File Name : FPROMPT.C                                                      */
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
#include "FPROMPT.H"
#include "NETCHAT.RCH"
#include "FPROMPT.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY FPROMPTDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
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

      INT k, h;
      CHAR tsfile[MAXSTRING];
           

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

          
      if( existPath(DEFDLDIR) )    
         {
         strcpy(tsfile, DEFDLDIR);
         if( tsfile[strlen(tsfile)-1] != '\\' )
            strcat(tsfile, "\\");
         strcat(tsfile, RFile);
         }
      else
         {
         _getcwd(tsfile, MAXSTRING);
         if( tsfile[strlen(tsfile)-1] != '\\' )
            strcat(tsfile, "\\");
         strcat(tsfile, RFile);
         }   
            
      WinSetDlgItemText(hwndDlg, 1000, tsfile);
      WinSetDlgItemText(hwndFrame, FID_TITLEBAR, ftPromptTB);

      strcpy(FQRFile, "");
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
      /* Button 1001 Clicked/Selected */
      case 1001:
         {
         /* ##START 1001.0  */
         /* Event Clicked/selected - ~Accept file  1001 */

         CHAR tmp[MAXSTRING];
         INT k, x, strl;


         WinQueryDlgItemText(hwndDlg, 1000, sizeof(tmp), tmp);
         strl = strlen(tmp);
         if( strl < 4 )
            return(0);

         strcpy(FQRFile, tmp);

         x = 0;
         for( k=0;k<strl;k++ )
            {
            if( tmp[k] == '\\' )
               x = k;
            }

         if( x < 2 )
            {
            strcpy(FQRFile, "");
            msgBox(hwndDlg, "Attention!", "Path is NOT valid.");
            return(0);
            }
            
         tmp[k+1] = '\0';
         if( !existPath(tmp) )
            {
            strcpy(FQRFile, "");
            msgBox(hwndDlg, "Attention!", "Path is NOT valid.");
            return(0);
            }

         if( existFile(FQRFile) )
            {
            if(WinMessageBox(HWND_DESKTOP,
                             hwndDlg,
                             "File already exists!",
                             "Replace file?",
                             0,
                             MB_ICONEXCLAMATION | MB_OKCANCEL) == MBID_CANCEL )
               {
               strcpy(FQRFile, "");
               return(0);
               }
            }

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1002 Clicked/Selected */
      case 1002:
         {
         /* ##START 1002.0  */
         /* Event Clicked/selected - ~Reject file  1002 */

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
HWND OpenFPROMPT(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           FPROMPTDlgProc, 
           0, ID_FPROMPTFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

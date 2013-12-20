/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : MISCSET.C                                                      */
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
#include "MISCSET.H"
#include "NETCHAT.RCH"
#include "MISCSET.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */


#include <xtra.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY MISCSETDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
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
      /* Event Form events, Opened */


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

      WinSendDlgItemMsg(hwndDlg, 1000,
                        SPBM_SETLIMITS,
                        MPFROMLONG(3600),       
                        MPFROMLONG(10));          

      WinSendDlgItemMsg(hwndDlg, 1000,
                        SPBM_SETCURRENTVALUE,
                        MPFROMLONG(pgmData[6]), 0);

      pgmData[7] = 2;

      /*
      switch( pgmData[7] )
         {
         case 1:
            WinCheckButton(hwndDlg, 1003, 1);
            break;
            
         case 2:
            WinCheckButton(hwndDlg, 1005, 1);
            break;
            
         case 3:
            WinCheckButton(hwndDlg, 1004, 1);
            break;
         }
      */

      WinSetDlgItemText(hwndDlg, 1008, DEFDLDIR);
      WinSetDlgItemText(hwndDlg, 1009, DEFULDIR);

      if( pgmData[33] == 1 )
         WinCheckButton(hwndDlg, 1005, 1);

      if( pgmData[9] == 1 )
         WinCheckButton(hwndDlg, 1012, 1);

      if( pgmData[14] == 1 )
         WinCheckButton(hwndDlg, 1013, 1);



      if( pgmData[15] == 1 )
         WinCheckButton(hwndDlg, 1014, 1);

      if( pgmData[16] == 1 )
         WinCheckButton(hwndDlg, 1015, 1);

      if( pgmData[17] == 1 )
         WinCheckButton(hwndDlg, 1016, 1);

      if( pgmData[18] == 1 )
         WinCheckButton(hwndDlg, 1017, 1);

      if( pgmData[19] == 1 )
         WinCheckButton(hwndDlg, 1018, 1);

      if( pgmData[20] == 1 )
         WinCheckButton(hwndDlg, 1019, 1);

      if( pgmData[21] == 1 )
         WinCheckButton(hwndDlg, 1020, 1);

      if( pgmData[22] == 1 )
         WinCheckButton(hwndDlg, 1021, 1);

      if( pgmData[23] == 1 )
         WinCheckButton(hwndDlg, 1022, 1);

      if( pgmData[24] == 1 )
         WinCheckButton(hwndDlg, 1023, 1);

      if( pgmData[29] == 1 )
         WinCheckButton(hwndDlg, 1024, 1);

      if( pgmData[30] == 1 )
         WinCheckButton(hwndDlg, 1025, 1);

      if( pgmData[31] == 1 )
         WinCheckButton(hwndDlg, 1002, 1);

      if( pgmData[32] == 1 )
         WinCheckButton(hwndDlg, 1004, 1);

      if( pgmData[39] == 1 )
         WinCheckButton(hwndDlg, 1033, 1);

      if( pgmData[40] == 1 )
         WinCheckButton(hwndDlg, 1034, 1);

      if( pgmData[35] <= 0 )
         {
         WinSetDlgItemShort(hwndDlg, 1026, (SHORT)6667, FALSE);
         }
      else
         {
         WinSetDlgItemShort(hwndDlg, 1026, (SHORT)pgmData[35], FALSE);
         }
         
      if( pgmData[36] <= 0 )
         {
         WinSetDlgItemShort(hwndDlg, 1027, (SHORT)6667, FALSE);
         }
      else
         {
         WinSetDlgItemShort(hwndDlg, 1027, (SHORT)pgmData[36], FALSE);
         }
         
      if( pgmData[37] <= 0 )
         {
         WinSetDlgItemShort(hwndDlg, 1028, (SHORT)21, FALSE);
         }
      else
         {
         WinSetDlgItemShort(hwndDlg, 1028, (SHORT)pgmData[37], FALSE);
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

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1006 Clicked/Selected */
      case 1006:
         {
         /* ##START 1006.0  */
         /* Event ~Save  1006, Clicked/selected */


         WinSendDlgItemMsg(hwndDlg, 1000,
                           SPBM_QUERYVALUE,
                           MPFROMP(&pgmData[6]),  
                           MPFROM2SHORT(0,SPBQ_ALWAYSUPDATE));


         pgmData[7] = 2;

         WinQueryDlgItemText(hwndDlg, 1008, sizeof(DEFDLDIR), DEFDLDIR);
         WinQueryDlgItemText(hwndDlg, 1009, sizeof(DEFULDIR), DEFULDIR);

         WinQueryDlgItemShort(hwndDlg, 1026, (SHORT *)&pgmData[35], FALSE);
         WinQueryDlgItemShort(hwndDlg, 1027, (SHORT *)&pgmData[36], FALSE);
         WinQueryDlgItemShort(hwndDlg, 1028, (SHORT *)&pgmData[37], FALSE);

         if( WinQueryButtonCheckstate(hwndDlg,1005) )
            pgmData[33] = 1;
         else
            pgmData[33] = 0;   

         if( WinQueryButtonCheckstate(hwndDlg,1012) )
            pgmData[9] = 1;
         else
            pgmData[9] = 0;   

         if( WinQueryButtonCheckstate(hwndDlg,1013) )
            {
            pgmData[14] = 1;
            }
         else   
            {
            pgmData[14] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1014) )
            {
            pgmData[15] = 1;
            }
         else   
            {
            pgmData[15] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1015) )
            {
            pgmData[16] = 1;
            }
         else   
            {
            pgmData[16] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1016) )
            {
            pgmData[17] = 1;
            }
         else   
            {
            pgmData[17] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1017) )
            {
            pgmData[18] = 1;
            }
         else   
            {
            pgmData[18] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1018) )
            {
            pgmData[19] = 1;
            }
         else   
            {
            pgmData[19] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1019) )
            {
            pgmData[20] = 1;
            }
         else   
            {
            pgmData[20] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1020) )
            {
            pgmData[21] = 1;
            }
         else   
            {
            pgmData[21] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1021) )
            {
            pgmData[22] = 1;
            }
         else   
            {
            pgmData[22] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1022) )
            {
            pgmData[23] = 1;
            }
         else   
            {
            pgmData[23] = 0;
            }

         if( WinQueryButtonCheckstate(hwndDlg,1023) )
            {
            pgmData[24] = 1;
            }
         else   
            {
            pgmData[24] = 0;
            }


         if( WinQueryButtonCheckstate(hwndDlg,1024) )
            {
            pgmData[29] = 1;
            }
         else   
            {
            pgmData[29] = 0;
            }


         if( WinQueryButtonCheckstate(hwndDlg,1025) )
            {
            pgmData[30] = 1;
            }
         else   
            {
            pgmData[30] = 0;
            }


         if( WinQueryButtonCheckstate(hwndDlg,1002) )
            {
            pgmData[31] = 1;
            }
         else   
            {
            pgmData[31] = 0;
            }


         if( WinQueryButtonCheckstate(hwndDlg,1004) )
            {
            pgmData[32] = 1;
            }
         else   
            {
            pgmData[32] = 0;
            }


         if( WinQueryButtonCheckstate(hwndDlg,1033) )
            {
            pgmData[39] = 1;
            }
         else   
            {
            pgmData[39] = 0;
            }


         if( WinQueryButtonCheckstate(hwndDlg,1034) )
            {
            pgmData[40] = 1;
            }
         else   
            {
            pgmData[40] = 0;
            }


         saveNCSet();

         makeTBar();
         WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
         // bugem(hwndDlg);

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1007 Clicked/Selected */
      case 1007:
         {
         /* ##START 1007.0  */
         /* Event Clicked/selected - ~Cancel  1007 */

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
HWND OpenMISCSET(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           MISCSETDlgProc, 
           0, ID_MISCSETFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}

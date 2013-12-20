/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : HAILNOTE.C                                                     */
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
#include "HAILNOTE.H"
#include "NETCHAT.RCH"
#include "HAILNOTE.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */


#include <xtra.h>
#include <main.h>
#include <about.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY HAILNOTEDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PHAILNOTEFORMINFO pHAILNOTEFormInfo=(PHAILNOTEFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = WinQueryWindow(hwndDlg, QW_PARENT);
 /* ##START Form.37 Top of window procedure */
 /* Code sections - Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(HAILNOTEFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pHAILNOTEFormInfo=(PHAILNOTEFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      {
      /* ##START Form.1  */
      /* Form events - Opened */

      CHAR comboaddr[260];
      INT vh;
      ULONG fgndcolor;
      CHAR bstatus[20];



      fgndcolor = CLR_DARKBLUE;   
      WinSetPresParam(WinWindowFromID(hwndDlg, 1003), 
                      PP_FOREGROUNDCOLORINDEX,
                      sizeof(ULONG),     
                      &fgndcolor);     

      WinSetPresParam(WinWindowFromID(hwndDlg, 1004), 
                      PP_FOREGROUNDCOLORINDEX,
                      sizeof(ULONG),     
                      &fgndcolor);     

      for( vh=0;vh<pHAILNOTEFormInfo->index;vh++ )
         {
         WinSendDlgItemMsg(hwndDlg, 1000,
                           LM_INSERTITEM,
                           // MPFROMSHORT(LIT_SORTASCENDING),
                           MPFROMSHORT(LIT_END),
                           MPFROMP(pvdat[vh].INFROM));  

         }


      if( pgmData[33] == 1 )
         WinCheckButton(hwndDlg, 1007, 1);
         
         
      WinSendDlgItemMsg(hwndDlg, 1000,
                        LM_SELECTITEM,
                        MPFROMLONG(0),   
                        MPFROMLONG(TRUE));

      strcpy(hnipaddr, pvdat[0].INSUBJECT+strlen(cphrase)); 
      strcpy(comboaddr, "IP : ");
      strcat(comboaddr, hnipaddr);
      strcat(comboaddr, "   Ports : ");
      strcat(comboaddr, pvdat[0].INPORTS);
      WinSetDlgItemText(hwndDlg, 1003, comboaddr); 
      // WinSetDlgItemText(hwndDlg, 1003, hnipaddr); 
      WinSetDlgItemText(hwndDlg, 1004, pvdat[0].INDATE); 
      WinSetDlgItemText(hwndDlg, 1005, pvdat[0].REPTO); 
      WinSetDlgItemText(hwndDlg, 1008, pvdat[0].INNOTE); 

      WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);
      if( strcmp(bstatus, "Listen OFF") == 0 )
         {
         LISTENWASOFF = TRUE;
         // WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
         }
      else   
         LISTENWASOFF = FALSE;
         
      if( pgmData[21] )
         {
         DosBeep(900, 50);
         DosBeep(1200, 50);
         DosBeep(1500, 50);
         DosBeep(900, 50);
         DosBeep(1200, 50);
         DosBeep(1500, 50);
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
      /* Button 1001 Clicked/Selected */
      case 1001:
         {
         /* ##START 1001.0  */
         /* Event Clicked/selected - ~Connect  1001 */

         CHAR bstatus[20];
         CHAR gp[40];
         INT sel, k, h;
         INT ret;
         BOOL TOBU;



         if( !registered(ncpw) )
            {
            USHORT usReturn;
            HWND hNewFrame;
            
            
            hNewFrame = OpenABOUT(hwndDlg, 0);
            usReturn = (USHORT) WinProcessDlg(hNewFrame);
            }
               
         if( WinQueryButtonCheckstate(hwndDlg,1007) == 1 )
            {
            ret = 1;
            }
         else
            {   
            ret = 0;
            }

         WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);

         if( pgmData[31] )
            {
            WinSetWindowPos(hwndMainF, HWND_TOP, 0, 0, 0, 0, SWP_ACTIVATE | SWP_SHOW | SWP_RESTORE);
            }                
                         
         strcpy(guestIP, hnipaddr); 

         sel = (LONG)WinSendDlgItemMsg(hwndDlg, 1000,
                                       LM_QUERYSELECTION,
                                       MPFROMLONG(LIT_FIRST),
                                       MPFROMLONG(0));

         if( strcmp(pvdat[sel].INPORTS, "Unknown") != 0 && ret == 1 ) 
            {
            strcpy(gp, pvdat[sel].INPORTS);
            k = 2;
            h = 0;
            do
               {
               grport[h] = gp[k];
               h++;
               }
            while( gp[k++] != ' ' && h < 5 );    
            grport[h-1] = '\0';
                  

            k += 2;
            h = 0;
            do
               {
               gsport[h] = gp[k];
               h++;
               }
            while( gp[k++] != ' ' && h < 5 );    
            gsport[h-1] = '\0';
            
            
            k += 2;
            h = 0;
            do
               {
               gfport[h] = gp[k];
               h++;
               }
            while( gp[k++] != ' ' && h < 5 );    
            gfport[h-1] = '\0';

            
            if( atoi(grport) != atoi(gsport) )
               {
               if( pgmData[4] != atoi(gsport) ||
                   pgmData[5] != atoi(grport) ||
                   pgmData[8] != atoi(gfport) )
                  TOBU = TRUE;    
               else
                  TOBU = FALSE;
               }
            else
               {
               if( pgmData[4] != atoi(grport) ||
                  pgmData[5] != atoi(gsport) || 
                  pgmData[8] != atoi(gfport) )
                  TOBU = TRUE;
               else
                  TOBU = FALSE;   
               }      

            // if( pgmData[4] != atoi(grport) ||
            //     pgmData[5] != atoi(gsport) || 
            //    pgmData[8] != atoi(gfport) )
            
            if( TOBU )
               {
               if( strcmp(bstatus, "Listen ON") == 0 )
                  {
                  WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
            
                  if( atoi(grport) == atoi(gsport) )
                     {
                     pgmData[4] = atoi(grport);
                     pgmData[5] = atoi(gsport);
                     pgmData[8] = atoi(gfport);
                     }
                  else   
                     {
                     pgmData[5] = atoi(grport);
                     pgmData[4] = atoi(gsport);
                     pgmData[8] = atoi(gfport);
                     }
                  saveNCSet();
                  makeTBar();
                  WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg); 
                  WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
                  }
               else
                  {
                  if( atoi(grport) == atoi(gsport) )
                     {
                     pgmData[4] = atoi(grport);
                     pgmData[5] = atoi(gsport);            
                     pgmData[8] = atoi(gfport);
                     }
                  else   
                     {
                     pgmData[5] = atoi(grport);
                     pgmData[4] = atoi(gsport);
                     pgmData[8] = atoi(gfport);
                     }
                  saveNCSet();
                  makeTBar();
                  WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg); 
                  WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
                  }   
               }
            else
               {
               if( strcmp(bstatus, "Listen OFF") == 0 )
                  {
                  WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
                  }
               }   
            }
         else
            {
            if( strcmp(bstatus, "Listen OFF") == 0 )
               {
               WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
               }
            }

         _beginthread(attemptConnect, NULL, BSTACK, (PVOID)&hwndMainDlg);
            
         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button 1002 Clicked/Selected */
      case 1002:
         {
         /* ##START 1002.0  */
         /* Event Clicked/selected - ~Don't connect  1002 */

         CHAR bstatus[20];

         WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);
         if( strcmp(bstatus, "Listen ON") == 0 )
            {
            if( LISTENWASOFF )
               WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
            }

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

   case WM_CONTROL :
      switch (SHORT1FROMMP(mp1)) {
      /* List Box 1000 Event Handlers */
      case 1000:
         switch (SHORT2FROMMP(mp1)) {
         /* Click/Selected */
         case LN_SELECT:
            {
            /* ##START 1000.0  */
            /* Event Click/Selected - List Box  1000 */

            INT sel;
            // CHAR ipaddr[260];
            CHAR comboaddr[260];



            sel = (LONG)WinSendDlgItemMsg(hwndDlg, 1000,
                                          LM_QUERYSELECTION,
                                          MPFROMLONG(LIT_FIRST),
                                          MPFROMLONG(0));

            strcpy(hnipaddr, pvdat[sel].INSUBJECT+strlen(cphrase)); 
            strcpy(comboaddr, "IP : ");
            strcat(comboaddr, hnipaddr);
            strcat(comboaddr, "   Ports : ");
            strcat(comboaddr, pvdat[sel].INPORTS);
            WinSetDlgItemText(hwndDlg, 1003, comboaddr); 
            // WinSetDlgItemText(hwndDlg, 1003, ipaddr); 
            WinSetDlgItemText(hwndDlg, 1004, pvdat[sel].INDATE); 
            WinSetDlgItemText(hwndDlg, 1005, pvdat[sel].REPTO); 
            WinSetDlgItemText(hwndDlg, 1008, pvdat[sel].INNOTE);
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
HWND OpenHAILNOTE(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   HWND hwndClient;
   FRAMECDATA frameData;
   frameData.cb=sizeof(FRAMECDATA);
   frameData.flCreateFlags= FCF_NOBYTEALIGN | FCF_SIZEBORDER | FCF_TITLEBAR | FCF_SYSMENU | FCF_TASKLIST | FCF_ICON ;
   frameData.hmodResources=0;
   frameData.idResources=ID_HAILNOTEFORM;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame=WinCreateWindow(HWND_DESKTOP, WC_FRAME, "You are being hailed!", 0,0,0,0,0,hwndOwner,HWND_TOP,ID_HAILNOTEFORM,&frameData,0);
   if (hwndFrame) {
      hwndClient =(HWND) WinLoadDlg(hwndFrame,
              hwndFrame,   
              HAILNOTEDlgProc, 
              0, ID_HAILNOTEFORM, 
              pInfo); 
      WinShowWindow(hwndFrame, TRUE);
   }
   return hwndFrame;
}

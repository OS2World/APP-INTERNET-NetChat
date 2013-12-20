/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : LOGNOTE.C                                                      */
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
#include "LOGNOTE.H"
#include "NETCHAT.RCH"
#include "LOGNOTE.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */


#include <xtra.h>
#include <main.h>
#include <about.h>
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY LOGNOTEDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PLOGNOTEFORMINFO pLOGNOTEFormInfo=(PLOGNOTEFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = WinQueryWindow(hwndDlg, QW_PARENT);
 /* ##START Form.37 Top of window procedure */
 /* Code sections - Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(LOGNOTEFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pLOGNOTEFormInfo=(PLOGNOTEFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      {
      /* ##START Form.1  */
      /* Form events - Opened */

      // CHAR ipaddr[260];
      CHAR comboaddr[260];
      INT vh;
      ULONG fgndcolor;
      CHAR bstatus[20];


      WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);
      if( strcmp(bstatus, "Listen OFF") == 0 )
         {
         LISTENWASOFF = TRUE;
         }
      else   
         LISTENWASOFF = FALSE;
         
      if( pgmData[33] == 1 )
         WinCheckButton(hwndDlg, 1007, 1);
         
      fgndcolor = CLR_DARKBLUE;   
      WinSetPresParam(WinWindowFromID(hwndDlg, 1003), 
                      PP_FOREGROUNDCOLORINDEX,
                      sizeof(ULONG),     
                      &fgndcolor);     

      WinSetPresParam(WinWindowFromID(hwndDlg, 1004), 
                      PP_FOREGROUNDCOLORINDEX,
                      sizeof(ULONG),     
                      &fgndcolor);     

      if( loadLogList(hwndDlg) == -1 )
         {
         msgBox(hwndDlg, "Attention!", "No log file found.");
         WinSendMsg(hwndDlg, WM_CLOSE, 0, 0);
         }
      else
         {
         INT slen, j;
         
         j = 0;
         do
            {
            slen = strlen(logdat[j].INDATE);
            if( slen > 0 )
               j++;
            }
         while( slen > 0 );
            
         // debugMsgInt(j, "j");
         
         for( vh=0;vh<j;vh++ )
            {
            WinSendDlgItemMsg(hwndDlg, 1000,
                              LM_INSERTITEM,
                              MPFROMSHORT(LIT_END),
                              MPFROMP(logdat[vh].INFROM));  

            }

         
         WinSendDlgItemMsg(hwndDlg, 1000,
                           LM_SELECTITEM,
                           MPFROMLONG(0),   
                           MPFROMLONG(TRUE));

         strcpy(logpaddr, logdat[0].INSUBJECT+strlen(cphrase)); 
         strcpy(comboaddr, "IP : ");
         strcat(comboaddr, logpaddr);
         strcat(comboaddr, "   Ports : ");
         strcat(comboaddr, logdat[0].INPORTS);
         WinSetDlgItemText(hwndDlg, 1003, comboaddr); 
         // WinSetDlgItemText(hwndDlg, 1003, ipaddr); 
         WinSetDlgItemText(hwndDlg, 1004, logdat[0].INDATE); 
         // WinSetDlgItemText(hwndDlg, 1008, logdat[0].INNOTE); 

         /* if( LISTENWASOFF )
            {
            WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
            } */
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


         WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);

         if( WinQueryButtonCheckstate(hwndDlg,1007) == 1 )
            {
            ret = 1;
            }
         else
            {   
            ret = 0;
            }

         strcpy(guestIP, logpaddr); 

         sel = (LONG)WinSendDlgItemMsg(hwndDlg, 1000,
                                       LM_QUERYSELECTION,
                                       MPFROMLONG(LIT_FIRST),
                                       MPFROMLONG(0));

         if( strcmp(logdat[sel].INPORTS, "Unknown") != 0 && ret == 1 ) 
            {
            strcpy(gp, logdat[sel].INPORTS);
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
            //     pgmData[8] != atoi(gfport) )
            
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

            strcpy(logpaddr, logdat[sel].INSUBJECT+strlen(cphrase)); 
            strcpy(comboaddr, "IP : ");
            strcat(comboaddr, logpaddr);
            strcat(comboaddr, "   Ports : ");
            strcat(comboaddr, logdat[sel].INPORTS);
            WinSetDlgItemText(hwndDlg, 1003, comboaddr); 
            // WinSetDlgItemText(hwndDlg, 1003, logpaddr); 
            WinSetDlgItemText(hwndDlg, 1004, logdat[sel].INDATE); 
            WinSetDlgItemText(hwndDlg, 1005, logdat[sel].REPTO); 
            WinSetDlgItemText(hwndDlg, 1008, logdat[sel].INNOTE);
            /* ##END  */
            }
            break;
         /* Enter */
         case LN_SETFOCUS:
            {
            /* ##START 1000.1  */
            /* Event Enter - List Box  1000 */
            /* ##END  */
            }
            break;
         /* Mouse button 1 double click */
         case LN_ENTER:
            {
            /* ##START 1000.3  */
            /* Event Mouse button 1 double click - List Box  1000 */

            WinSendMsg(hwndDlg, WM_COMMAND, MPFROM2SHORT(1001, 0), 0);
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
HWND OpenLOGNOTE(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   HWND hwndClient;
   FRAMECDATA frameData;
   frameData.cb=sizeof(FRAMECDATA);
   frameData.flCreateFlags= FCF_NOBYTEALIGN | FCF_SIZEBORDER | FCF_TITLEBAR | FCF_SYSMENU | FCF_TASKLIST | FCF_ICON ;
   frameData.hmodResources=0;
   frameData.idResources=ID_LOGNOTEFORM;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame=WinCreateWindow(HWND_DESKTOP, WC_FRAME, "NetChat log list", 0,0,0,0,0,hwndOwner,HWND_TOP,ID_LOGNOTEFORM,&frameData,0);
   if (hwndFrame) {
      hwndClient =(HWND) WinLoadDlg(hwndFrame,
              hwndFrame,   
              LOGNOTEDlgProc, 
              0, ID_LOGNOTEFORM, 
              pInfo); 
      WinShowWindow(hwndFrame, TRUE);
   }
   return hwndFrame;
}

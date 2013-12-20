/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : Main.C                                                         */
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
#include "NETCHAT.RCH"
#include "Main.RCH"

/* ##START Form.34 Extra include files */
/* Code sections - Extra include files */

#include <global.h>
#include <xtra.h>
#include "ABOUT.h"
#include "HAILLIST.h"
#include "SETTINGS.h"
#include "LOGNOTE.h"
#include "MCONNECT.h"
#include "SPORTS.h"
#include "MISCSET.h"
#include "PHRLIST.h"
#include <xtrarc.h>
#include "REG.h"
#include "CONINFO.h"
#include "STATS.h"
/* ##END Extra include files */
/* declare main forms info block */
PMAINFORMINFO pMainFormInfo;

int main(int argc, char *argv[], char *envp[])                                                  
{                                                                           
  HAB   hab;                                                                
  QMSG  qmsg;                                                               
  HMQ  hmq;                                                               
  HWND  hwndMainFrame;                                                               
                                                                            
  /* ##START Form.40 Top of application procedure */
  /* ##END Top of application procedure */
                                                                            
  hab = WinInitialize( 0 );                                                 
  if(!hab) {                                                                
    exit(1);                                                                
  }                                                                         
                                                                            
  hmq = WinCreateMsgQueue( hab, 0 );                                        
  if(!hmq) {                                                                
    WinTerminate(hab);                                                      
    exit(1);                                                                
  }                                                                         
  pMainFormInfo = malloc(sizeof(MAINFORMINFO));
  memset((PVOID) pMainFormInfo, 0, sizeof(MAINFORMINFO));

  /* ##START Form.35 Application initialization */
  /* Code sections - Application initialization */

  argcnt = argc;
  argL = FALSE;
  argM = FALSE;
  argMC = FALSE;

  // ncRunning();

  switch( argcnt )
     {
     case 1 :
        break;
        
     case 2 :
        {
        if( stricmp(argv[1], "-XX") == 0 )
           {
           ncRunning();
           break;
           }
        if( strnicmp(argv[1], "-NI", 3) == 0 )
           {
           if( strlen(argv[1]) > 7 && strnicmp(argv[1]+(strlen(argv[1])-4), ".INI", 4) == 0 )    
              {
              strcpy(INIFILE, argv[1]+3);
              }
           break;
           }
        if( stricmp(argv[1], "-L") == 0 )
           {
           argL = TRUE;
           break;
           }
        if( stricmp(argv[1], "-M") == 0 )
           {
           argM = TRUE;
           break;
           }
        if( stricmp(argv[1], "-MC") == 0 )
           {
           argMC = TRUE;
           break;
           }
        if( stricmp(argv[1], "-LXX") == 0 )
           {
           ncRunning();
           argL = TRUE;
           break;
           }
        if( stricmp(argv[1], "-MXX") == 0 )
           {
           ncRunning();
           argM = TRUE;
           break;
           }
        if( stricmp(argv[1], "-MCXX") == 0 )
           {
           ncRunning();
           argMC = TRUE;
           break;
           }
        }   
        break;
        
     case 3 :
        {
        if( stricmp(argv[1], argv[2]) == 0 )
           break;
        if( strnicmp(argv[1], "-NI", 3) == 0 )
           {
           if( strlen(argv[1]) > 7 && strnicmp(argv[1]+(strlen(argv[1])-4), ".INI", 4) == 0 )    
              {
              strcpy(INIFILE, argv[1]+3);
              }
           break;
           }
        if( stricmp(argv[1], "-L") == 0 )
           {
           argL = TRUE;
           }
        if( stricmp(argv[1], "-M") == 0 )
           {
           argM = TRUE;
           }
        if( stricmp(argv[1], "-MC") == 0 )
           {
           argMC = TRUE;
           }
        if( stricmp(argv[1], "-LXX") == 0 )
           {
           ncRunning();
           argL = TRUE;
           }
        if( stricmp(argv[1], "-MXX") == 0 )
           {
           ncRunning();
           argM = TRUE;
           }
        if( stricmp(argv[1], "-MCXX") == 0 )
           {
           ncRunning();
           argMC = TRUE;
           }
        if( strnicmp(argv[2], "-NI", 3) == 0 )
           {
           if( strlen(argv[2]) > 7 && strnicmp(argv[2]+(strlen(argv[2])-4), ".INI", 4) == 0 )    
              {
              strcpy(INIFILE, argv[2]+3);
              }
           break;
           }
        if( stricmp(argv[2], "-L") == 0 )
           {
           argL = TRUE;
           }
        if( stricmp(argv[2], "-M") == 0 )
           {
           argM = TRUE;
           }
        if( stricmp(argv[2], "-MC") == 0 )
           {
           argMC = TRUE;
           }
        }   
        break;
        
     case 4 :
        {
        if( stricmp(argv[1], argv[2]) == 0 )
           break;
        if( stricmp(argv[1], argv[3]) == 0 )
           break;
        if( stricmp(argv[2], argv[3]) == 0 )
           break;
        if( strnicmp(argv[1], "-NI", 3) == 0 )
           {
           if( strlen(argv[1]) > 7 && strnicmp(argv[1]+(strlen(argv[1])-4), ".INI", 4) == 0 )    
              {
              strcpy(INIFILE, argv[1]+3);
              }
           break;
           }
        if( stricmp(argv[1], "-L") == 0 )
           {
           argL = TRUE;
           }
        if( stricmp(argv[1], "-M") == 0 )
           {
           argM = TRUE;
           }
        if( stricmp(argv[1], "-MC") == 0 )
           {
           argMC = TRUE;
           }
        if( stricmp(argv[1], "-LXX") == 0 )
           {
           ncRunning();
           argL = TRUE;
           }
        if( stricmp(argv[1], "-MXX") == 0 )
           {
           ncRunning();
           argM = TRUE;
           }
        if( stricmp(argv[1], "-MCXX") == 0 )
           {
           ncRunning();
           argMC = TRUE;
           }
        if( strnicmp(argv[2], "-NI", 3) == 0 )
           {
           if( strlen(argv[2]) > 7 && strnicmp(argv[2]+(strlen(argv[2])-4), ".INI", 4) == 0 )    
              {
              strcpy(INIFILE, argv[2]+3);
              }
           break;
           }
        if( stricmp(argv[2], "-L") == 0 )
           {
           argL = TRUE;
           }
        if( stricmp(argv[2], "-M") == 0 )
           {
           argM = TRUE;
           }
        if( stricmp(argv[2], "-MC") == 0 )
           {
           argMC = TRUE;
           }
        if( strnicmp(argv[3], "-NI", 3) == 0 )
           {
           if( strlen(argv[3]) > 7 && strnicmp(argv[3]+(strlen(argv[3])-4), ".INI", 4) == 0 )    
              {
              strcpy(INIFILE, argv[3]+3);
              }
           break;
           }
        if( stricmp(argv[3], "-L") == 0 )
           {
           argL = TRUE;
           }
        if( stricmp(argv[3], "-M") == 0 )
           {
           argM = TRUE;
           }
        if( stricmp(argv[3], "-MC") == 0 )
           {
           argMC = TRUE;
           }
        }   
        break;
        
     default :
        break;
     }
  /* ##END Application initialization */

  hwndMainFrame = OpenMain(HWND_DESKTOP, pMainFormInfo);
  if (!hwndMainFrame) {
     WinDestroyMsgQueue( hmq );
     WinTerminate( hab );
     exit(1);
  }

  /* Get and dispatch messages from the application message queue  */
  /* until WinGetMsg returns FALSE, indicating a WM_QUIT message.  */
  while( WinGetMsg( hab, &qmsg, (HWND)NULL, 0, 0 ) )                        
    WinDispatchMsg( hab, &qmsg );                                           
                                                                            
  /* ##START Form.36 Application termination */
  /* ##END Application termination */
  WinDestroyWindow(hwndMainFrame);
  WinDestroyMsgQueue( hmq );            /* and                          */  
  WinTerminate( hab );                  /* terminate the application    */  
  return(0);                                                                
}                                                                          
MRESULT EXPENTRY MainDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PMAINFORMINFO pMainFormInfo=(PMAINFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = WinQueryWindow(hwndDlg, QW_PARENT);
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(MAINFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pMainFormInfo=(PMAINFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      {
      /* ##START Form.1  */
      /* Form events - Opened */

      ULONG bkgndcolor;


      ATTEMPTINGCONNECT = FALSE;
      NOWCONNECTED1 = FALSE;
      NOWCONNECTED2 = FALSE;

      queryNCSet();

      hinit.cb = sizeof( HELPINIT);
      hinit.ulReturnCode = 0L;
      hinit.pszTutorialName = NULL;
      hinit.phtHelpTable = (PHELPTABLE)MAKELONG(NULLHANDLE, 0xFFFF);
      hinit.hmodHelpTableModule = (HMODULE) NULL;
      hinit.hmodAccelActionBarModule = (HMODULE)NULL;
      hinit.idAccelTable = 0;
      hinit.idActionBar = 0;
      hinit.pszHelpWindowTitle = "NetChat for OS/2";
      hinit.fShowPanelId = CMIC_HIDE_PANEL_ID;
      hinit.pszHelpLibraryName = "netchat.hlp";

      if( (hwndHelp = WinCreateHelpInstance(WinQueryAnchorBlock(hwndDlg), &hinit)) != NULLHANDLE)
         {
         if(hinit.ulReturnCode)
            {
            WinDestroyHelpInstance( hwndHelp);
            }
         }

            
      if (hwndHelp)
         WinAssociateHelpInstance (hwndHelp, hwndDlg);
            
            
      if( readKey() == 1 )
         KEYISTHERE = TRUE;
      else
         KEYISTHERE = FALSE;   

      makeTBar();

      pgmData[7] = 2;

      if( pgmData[32] )
         WinSetWindowPos(hwndFrame, HWND_TOP, pgmData[0], pgmData[1], pgmData[2], pgmData[3], SWP_MOVE | SWP_SIZE | SWP_MINIMIZE);
      else
         WinSetWindowPos(hwndFrame, HWND_TOP, pgmData[0], pgmData[1], pgmData[2], pgmData[3], SWP_MOVE | SWP_SIZE );

      STARTMIN = 0;

      if( pgmData[14] )
         {
         if( pgmData[32] )
            {
            STARTMIN = 1;
            hNewPHRFrame = OpenPHRLIST(HWND_DESKTOP, 0);
            }
         else
            {   
            STARTMIN = 0;
            hNewPHRFrame = OpenPHRLIST(HWND_DESKTOP, 0);
            }
         }

      WinSetPresParam(WinWindowFromID(hwndDlg, 1001),
      		PP_FONTNAMESIZE,
      		sizeof(PPAttrValue1)+1,
      		&PPAttrValue1);

      WinSetPresParam(WinWindowFromID(hwndDlg, 1000),
      		PP_FONTNAMESIZE,
      		sizeof(PPAttrValue2)+1,
      		&PPAttrValue2);

      if( pgmData[25] >= 0 )
         {
         WinSetPresParam(WinWindowFromID(hwndDlg, 1001),
                         PP_BACKGROUNDCOLOR,
                         sizeof(ULONG),     
                         &pgmData[25]);
         }
      else
         {
         bkgndcolor = CLR_WHITE;   
         WinSetPresParam(WinWindowFromID(hwndDlg, 1001), 
                         PP_BACKGROUNDCOLORINDEX,
                         sizeof(ULONG),     
                         &bkgndcolor);     
         }   
         
      if( pgmData[26] >= 0 )
         {
         WinSetPresParam(WinWindowFromID(hwndDlg, 1001),
                         PP_FOREGROUNDCOLOR,
                         sizeof(ULONG),     
                         &pgmData[26]);
         }
         
      if( pgmData[27] >= 0 )
         {
         WinSetPresParam(WinWindowFromID(hwndDlg, 1000),
                         PP_BACKGROUNDCOLOR,
                         sizeof(ULONG),     
                         &pgmData[27]);
         }
      else
         {
         bkgndcolor = CLR_CYAN;   
         WinSetPresParam(WinWindowFromID(hwndDlg, 1000), 
                         PP_BACKGROUNDCOLORINDEX,
                         sizeof(ULONG),     
                         &bkgndcolor);     
         }   
         
      if( pgmData[28] >= 0 )
         {
         WinSetPresParam(WinWindowFromID(hwndDlg, 1000),
                         PP_FOREGROUNDCOLOR,
                         sizeof(ULONG),     
                         &pgmData[28]);
         }
         
      WinSendDlgItemMsg(hwndDlg, 1000,
                        MLM_SETTEXTLIMIT,
                        MPFROMLONG(-1), 0);

      WinSendDlgItemMsg(hwndDlg, 1000,
                        MLM_SETTEXTLIMIT,
                        MPFROMLONG(MSGSIZE), 0);


      WinSendMsg(WinWindowFromID(hwndDlg, 1001), MLM_SETTEXTLIMIT, MPFROMLONG(MSGSIZE-96), (MPARAM) 0L);

      hwndMLENEW1Popup = WinLoadMenu(WinWindowFromID(hwndDlg, 1000),
                                     0, ID_MAIN1);
                                 
      hwndMLENEW2Popup = WinLoadMenu(WinWindowFromID(hwndDlg, 1001),
                                     0, ID_MAIN2);
                                 
      oldmle1WinProc = WinSubclassWindow(WinWindowFromID(hwndDlg, 1000), newMLE1Proc);
      WinSetWindowPtr(WinWindowFromID(hwndDlg, 1000), 0, (PVOID) oldmle1WinProc);

      oldmle2WinProc = WinSubclassWindow(WinWindowFromID(hwndDlg, 1001), newMLE2Proc);
      WinSetWindowPtr(WinWindowFromID(hwndDlg, 1001), 0, (PVOID) oldmle2WinProc);

      WinSetDlgItemText(hwndDlg, 1002, "Listen OFF");

      hwndMainF = hwndFrame;
      hwndMainDlg = hwndDlg;

      WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), tbarmsg);

      if( argL )
         WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(1002, 0), 0);

      if( argM )
         WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(1006, 0), 0);

      if( argMC )
         WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(263, 0), 0);
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Form events - Closed */


      if( pgmData[40] )
         {
         if( !msgBoxOKCANCEL(hwndDlg, "Are you sure?", "Press OK to finish closing NetChat or Cancel to abort the operation.") )
            return(0);
         }
      /* ##END  */
      }
     WinPostMsg(hwndDlg, WM_QUIT, 0, 0);
      break;

   /* Form event Destroyed WM_DESTROY */
   case WM_DESTROY :
      {
      /* ##START Form.3  */
      /* Form events - Destroyed */

      SWP swp;
      HAB hb;
      ULONG attrf;


      if (hwndHelp)
         {
         WinAssociateHelpInstance (NULLHANDLE, hwndDlg);
         WinDestroyHelpInstance( hwndHelp);
         }
           
      if( !(WinQueryWindowULong(hwndFrame, QWL_STYLE) & WS_MINIMIZED) )
         {
         WinQueryWindowPos(hwndFrame, (PSWP) &swp);
         pgmData[0] = swp.x;
         pgmData[1] = swp.y;
         pgmData[2] = swp.cx;
         pgmData[3] = swp.cy;
         }

      if( WinIsWindow(hb, hNewPHRFrame) )
         {
         SWP swpphr;
         
         if( !(WinQueryWindowULong(hNewPHRFrame, QWL_STYLE) & WS_MINIMIZED) )
            {
            WinQueryWindowPos(hNewPHRFrame, (PSWP) &swpphr);
            pgmData[10] = swpphr.x;
            pgmData[11] = swpphr.y;
            pgmData[12] = swpphr.cx;
            pgmData[13] = swpphr.cy;
            // saveNCSet();
            }
         }


      WinQueryPresParam(WinWindowFromID(hwndDlg, 1001), 
                        PP_BACKGROUNDCOLOR, 0, 0,
      		  sizeof(pgmData[25]), &pgmData[25], QPF_NOINHERIT);

      WinQueryPresParam(WinWindowFromID(hwndDlg, 1001), 
                        PP_FOREGROUNDCOLOR, 0, 0,
      		  sizeof(pgmData[26]), &pgmData[26], QPF_NOINHERIT);

      WinQueryPresParam(WinWindowFromID(hwndDlg, 1000), 
                        PP_BACKGROUNDCOLOR, 0, 0,
      		  sizeof(pgmData[27]), &pgmData[27], QPF_NOINHERIT);

      WinQueryPresParam(WinWindowFromID(hwndDlg, 1000), 
                        PP_FOREGROUNDCOLOR, 0, 0,
      		  sizeof(pgmData[28]), &pgmData[28], QPF_NOINHERIT);

      saveNCSet();

      STOPME = 1; 
      DosPostEventSem(hev);
      DosCloseEventSem(hev);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1006), FALSE);


      if( !registered(ncpw) )
         {
         USHORT usReturn;
         HWND hNewFrame;
         
         
         hNewFrame = OpenABOUT(hwndDlg, 0);
         usReturn = (USHORT) WinProcessDlg(hNewFrame);
         }
      /* ##END  */
      }
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      if( chkCommand(SHORT1FROMMP(mp1)) )
         break;
      switch (SHORT1FROMMP(mp1)) {
      /* Button 1002 Clicked/Selected */
      case 1002:
         {
         /* ##START 1002.0  */
         /* Event Clicked/selected - ~Connect  1002 */

         // static CBD rcvdat;
         CHAR btext[30];
         ULONG fgndcolor;
         BOOL continueon;


         WinQueryDlgItemText(hwndDlg, 1002, sizeof(btext), btext);

         continueon = TRUE;
         if( strcmp(btext, "Connected!") == 0 )
            {
            if(WinMessageBox(HWND_DESKTOP,
         		    hwndDlg,
         		    "Press OK to disconnect or Cancel to abort the operation.",
         		    "Are you sure you want to disconnect?",
         		    0,
         		    MB_ICONEXCLAMATION | MB_OKCANCEL) == MBID_CANCEL )
               {
               continueon = FALSE;
               }
            else
               {
               continueon = TRUE;
               }   
            }


         if( continueon )
            {
            if( strcmp(btext, "Listen OFF") == 0 )
               {
               CHAR mo[30];
            
            
               WinSetDlgItemText(hwndDlg, 1002, "Listen ON");
               WinQueryDlgItemText(hwndDlg, 1006, sizeof(mo), mo);
               WinSetDlgItemText(hwndDlg, 1000, "");
               WinSetDlgItemText(hwndDlg, 1001, "");
               WinSetDlgItemText(hwndDlg, 1002, "Listen ON");
               // rcvdat.hwndDlg = hwndDlg;
               rcvthread = _beginthread(msgServer, NULL, BSTACK, (PVOID)0);
               }
            else
               {
               _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)7);
               ABORTME = TRUE;
               NOWLISTENING = FALSE;
               NOWCONNECTED1 = FALSE;
               NOWCONNECTED2 = FALSE;
               FTPINPROGRESS = FALSE;
               STILLWAITING = FALSE;
               soclose(ftpsock);
               soclose(ftpnsock);
               FILENOTIFY = FALSE;
               SERVERON = FALSE;
               shutdown(globsock, 2);
               so_cancel(globsock);
               so_cancel(globnsock);
               so_cancel(globsockt);
               WinSetDlgItemText(hwndDlg, 1000, "");
               WinSetDlgItemText(hwndDlg, 1001, "");
               WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
               fgndcolor = CLR_BLACK;   
               WinSetPresParam(WinWindowFromID(hwndDlg, 1002), 
                                         PP_FOREGROUNDCOLORINDEX,
                                         sizeof(ULONG),     
                                         &fgndcolor);     
               WinSetDlgItemText(hwndDlg, 1002, "Listen OFF");
               soclose(globnsock);   
               soclose(globsock);   
               soclose(globsockt);   
               DosKillThread(rcvthread);
               DosKillThread(activen);
               makeTBar(); 
               WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 
               }
            }
         /* ##END  */
         }
         break;
      /* Button 1003 Clicked/Selected */
      case 1003:
         {
         /* ##START 1003.0  */
         /* Event Clicked/selected - C~lose  1003 */



         mmm = 2;
         _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)mmm);
         /* ##END  */
         }
         break;
      /* Button 1006 Clicked/Selected */
      case 1006:
         {
         /* ##START 1006.0  */
         /* Event ~Word Wrap  1006, Clicked/selected */

         CHAR btext[30];
         static CBD maildat;

         WinQueryDlgItemText(hwndDlg, 1006, sizeof(btext), btext);

         if( strcmp(btext, "Monitor OFF") == 0 )
            {
            DosCloseEventSem(hev);
            maildat.hwndDlg = hwndDlg;
            WinSetDlgItemText(hwndDlg, 1006, "Monitor ON");
            _beginthread(chkForMail, NULL, BSTACK, (PVOID)&maildat);
            }
         else
            {
            if( !registered(ncpw) )
               {
               USHORT usReturn;
               HWND hNewFrame;
            
            
               hNewFrame = OpenABOUT(hwndMainDlg, 0);
               usReturn = (USHORT) WinProcessDlg(hNewFrame);
               }
            STOPME = 1; 
            DosPostEventSem(hev);
            DosCloseEventSem(hev);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1006), FALSE);
            WinSetDlgItemText(hwndDlg, 1006, "Monitor OFF");
            }




         /*
         if( (ULONG)WinSendDlgItemMsg(hwndDlg, 1000, MLM_QUERYWRAP, 0, 0) )
            {
            WinSendDlgItemMsg(hwndDlg, 1000,
                              MLM_SETWRAP,
                              MPFROMLONG(FALSE), 0);
            WinSendDlgItemMsg(hwndDlg, 1001,
                              MLM_SETWRAP,
                              MPFROMLONG(FALSE), 0);
            }
         else                        
            {
            WinSendDlgItemMsg(hwndDlg, 1000,
                              MLM_SETWRAP,
                              MPFROMLONG(TRUE), 0);
            WinSendDlgItemMsg(hwndDlg, 1001,
                              MLM_SETWRAP,
                              MPFROMLONG(TRUE), 0);
            }

         */
         /* ##END  */
         }
         break;
      /* Button 1007 Clicked/Selected */
      case 1007:
         {
         /* ##START 1007.0  */
         /* Event Clicked/selected - ~Help  1007 */

         USHORT usReturn;
         HWND hNewFrame;
         PHAILLISTFORMINFO pHaillistFormInfo = malloc(sizeof(HAILLISTFORMINFO));

         pHaillistFormInfo->hwnd = hwndDlg;
         pHaillistFormInfo->mode = 0;
         hNewFrame = OpenHAILLIST(hwndDlg, pHaillistFormInfo);
         usReturn = (USHORT) WinProcessDlg(hNewFrame);
         /* ##END  */
         }
         break;
      /* Button ID_COPYCB Clicked/Selected */
      case ID_COPYCB:
         {
         /* ##START 1004.0  */
         /* Event Clicked/selected - ~Copy ID_COPYCB */


         WinSendDlgItemMsg(hwndDlg, 1000,
                           MLM_COPY ,
                           0, 0);
         /* ##END  */
         }
         break;
      /* Button ID_PASTECB Clicked/Selected */
      case ID_PASTECB:
         {
         /* ##START 1005.0  */
         /* Event Clicked/selected - ~Paste ID_PASTECB */

         WinSendDlgItemMsg(hwndDlg, 1001,
                           MLM_PASTE ,
                           0, 0);

         // WinSetFocus(HWND_DESKTOP,WinWindowFromID(hwndDlg, 1001));
         /* ##END  */
         }
         break;
      /* Button 1008 Clicked/Selected */
      case 1008:
         {
         /* ##START 1008.0  */
         /* Event Clicked/selected - ~Incoming file  1008 */

            if( !registered(ncpw) )
               {
               USHORT usReturn;
               HWND hNewFrame;
            
            
               hNewFrame = OpenABOUT(hwndMainDlg, 0);
               usReturn = (USHORT) WinProcessDlg(hNewFrame);
               }

         FILENOTIFY = FALSE;
         _beginthread(handleXmtRequest, NULL, BSTACK, NULL);
         WinEnableControl(hwndDlg, 1008, FALSE);
         /* ##END  */
         }
         break;
      /* Menu item 275 Clicked/Selected */
      case 275:
         {
        /* ##START 275.0  */
        /* Menu events - ~Send file */

        CHAR vtxt[20];

        WinQueryDlgItemText(hwndDlg, 1002, sizeof(vtxt), vtxt);
        if( strcmp(vtxt, "Connected!") == 0 )
           {
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 275, FALSE);
           // FTPINPROGRESS = TRUE;
           sendFile(hwndDlg, "*");
           }
        /* ##END  */
         }
         break;
      /* Menu item 282 Clicked/Selected */
      case 282:
         {
        /* ##START 282.0  */
        /* Menu events - ~Abort file transfer */

        ABORTME = TRUE;
        FTPINPROGRESS = FALSE;
        STILLWAITING = FALSE;
        _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)12);
        soclose(ftpnsock);
        if( soclose(ftpsock) == 0 )
           {
           makeTBar(); 
           WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 
           }
        /* ##END  */
         }
         break;
      /* Menu item IDM_CONNECT Clicked/Selected */
      case IDM_CONNECT:
         {
        /* ##START 260.0  */
        /* Menu events - ~Connect                Ctrl+T */

        CHAR bstatus[20];

        WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);
        if( strcmp(bstatus, "Listen OFF") == 0 )
           WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
        /* ##END  */
         }
         break;
      /* Menu item IDM_WINDOWSTYLE Clicked/Selected */
      case IDM_WINDOWSTYLE:
         {
        /* ##START 263.0  */
        /* Menu events - ~Manual connect */

        USHORT usReturn;
        HWND hNewFrame;

        hNewFrame = OpenMCONNECT(hwndDlg, 0);
        usReturn = (USHORT) WinProcessDlg(hNewFrame);
        /* ##END  */
         }
         break;
      /* Menu item 279 Clicked/Selected */
      case 279:
         {
        /* ##START 279.0  */
        /* Menu events - ~Wake up */

        INT mn;

        mn = 10;
        _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)mn);
        /* ##END  */
         }
         break;
      /* Menu item 268 Clicked/Selected */
      case 268:
         {
        /* ##START 268.0  */
        /* Menu events - Remote party info ... */

        _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)15);
        /* ##END  */
         }
         break;
      /* Menu item IDM_INDEX Clicked/Selected */
      case IDM_INDEX:
         {
        /* ##START 265.0  */
        /* Menu events - D~ownload directory */

        CHAR tmpdir[260];


        strcpy(tmpdir, DEFDLDIR);
        if( tmpdir[strlen(tmpdir)-1] == '\\' )
           tmpdir[strlen(tmpdir)-1] = '\0';
           
        openFolder(tmpdir);
        /* ##END  */
         }
         break;
      /* Menu item 284 Clicked/Selected */
      case 284:
         {
        /* ##START 284.0  */
        /* Menu events - ~Upload directory */

        CHAR tmpdir[260];

        strcpy(tmpdir, DEFULDIR);
        if( tmpdir[strlen(tmpdir)-1] == '\\' )
           tmpdir[strlen(tmpdir)-1] = '\0';
           
        openFolder(tmpdir);
        /* ##END  */
         }
         break;
      /* Menu item IDM_EXITAPP Clicked/Selected */
      case IDM_EXITAPP:
         {
        /* ##START 270.0  */
        /* Menu events - ~Exit */

        WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
        /* ##END  */
         }
         break;
      /* Menu item IDM_CLOSECONNECTION Clicked/Selected */
      case IDM_CLOSECONNECTION:
         {
        /* ##START 271.0  */
        /* Menu events - ~Disconnect    Ctrl+Q */

        CHAR bstatus[20];

        WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);
        if( strcmp(bstatus, "Listen ON") == 0 || strcmp(bstatus, "Connected!") == 0  )
           WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(1002,2345), 0);
        WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 275, TRUE);
        /* ##END  */
         }
         break;
      /* Menu item 273 Clicked/Selected */
      case 273:
         {
        /* ##START 273.0  */
        /* Menu events - Current I~P address */

        USHORT usReturn;
        HWND hNewFrame;

              
        hNewFrame = OpenSTATS(hwndMainDlg, 0);
        usReturn = (USHORT) WinProcessDlg(hNewFrame);
        /* ##END  */
         }
         break;
      /* Menu item IDM_WORDWRAPL Clicked/Selected */
      case IDM_WORDWRAPL:
         {
        /* ##START 264.0  */
        /* Menu events - ~WordWrap */

        if( (ULONG)WinSendDlgItemMsg(hwndDlg, 1001, MLM_QUERYWRAP, 0, 0) )
           {
           WinCheckMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_WORDWRAPL, FALSE);
           WinSendDlgItemMsg(hwndDlg, 1001,
                             MLM_SETWRAP,
                             MPFROMLONG(FALSE), 0);
           }
        else
           {
           WinCheckMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_WORDWRAPL, TRUE);
           WinSendDlgItemMsg(hwndDlg, 1001,
                             MLM_SETWRAP,
                             MPFROMLONG(TRUE), 0);
           }
        /* ##END  */
         }
         break;
      /* Menu item IDM_WORDWRAPR Clicked/Selected */
      case IDM_WORDWRAPR:
         {
        /* ##START 274.0  */
        /* Menu events - WordWrap ~remote  CTRL+R */

        if( (ULONG)WinSendDlgItemMsg(hwndDlg, 1000, MLM_QUERYWRAP, 0, 0) )
           {
           WinCheckMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_WORDWRAPR, FALSE);
           WinSendDlgItemMsg(hwndDlg, 1000,
                             MLM_SETWRAP,
                             MPFROMLONG(FALSE), 0);
           }
        else
           {
           WinCheckMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_WORDWRAPR, TRUE);
           WinSendDlgItemMsg(hwndDlg, 1000,
                             MLM_SETWRAP,
                             MPFROMLONG(TRUE), 0);
           }
        /* ##END  */
         }
         break;
      /* Menu item IDM_COPY Clicked/Selected */
      case IDM_COPY:
         {
        /* ##START 261.0  */
        /* Menu events - ~Copy     Ctrl+C */

        ULONG ulLines, rSize;

        ulLines = (ULONG)WinSendMsg(WinWindowFromID(hwndDlg, 1000), MLM_QUERYLINECOUNT,
                                         MPFROMLONG( 0L), MPFROMLONG( 0L)) ;
        rSize = (ULONG)WinSendMsg(WinWindowFromID(hwndDlg, 1000), MLM_QUERYTEXTLENGTH,
                                               MPFROMLONG( 0L), MPFROMLONG( 0L)) ;
        rSize += ulLines - 1 ;

        WinSendMsg(WinWindowFromID(hwndDlg, 1000),
                   MLM_SETSEL,
                   MPFROMP(0),
                   MPFROMP(rSize));
                   
        WinSendMsg(WinWindowFromID(hwndDlg, 1000), MLM_COPY, NULL, NULL);
        /* ##END  */
         }
         break;
      /* Menu item IDM_PASTE Clicked/Selected */
      case IDM_PASTE:
         {
        /* ##START 262.0  */
        /* Menu events - ~Paste    Ctrl+V */

        WinSendMsg(hwndMainF, WM_COMMAND, MPFROM2SHORT(ID_PASTECB, 0), 0);
        /* ##END  */
         }
         break;
      /* Menu item 280 Clicked/Selected */
      case 280:
         {
        /* ##START 280.0  */
        /* Menu events - Cl~ear local entry area */


        /* Clear text 1000 Multi-Line Entry Field */
        WinSetDlgItemText(hwndDlg, 1001, "");
        /* ##END  */
         }
         break;
      /* Menu item 281 Clicked/Selected */
      case 281:
         {
        /* ##START 281.0  */
        /* Menu events - Cle~ar remote entry area */



        /* Clear text 1001 Multi-Line Entry Field */
        WinSetDlgItemText(hwndDlg, 1000, "");
        /* ##END  */
         }
         break;
      /* Menu item 267 Clicked/Selected */
      case 267:
         {
        /* ##START 267.0  */
        /* Menu events - ~Internet acct. settings */

        {
        USHORT usReturn;
        HWND hNewFrame;

        hNewFrame = OpenSETTINGS(hwndDlg, 0);
        usReturn = (USHORT) WinProcessDlg(hNewFrame);
        }

        WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), tbarmsg);
        /* ##END  */
         }
         break;
      /* Menu item 278 Clicked/Selected */
      case 278:
         {
        /* ##START 278.0  */
        /* Menu events - ~Misc. settings */

        USHORT usReturn;
        HWND hNewFrame;


        hNewFrame = OpenMISCSET(hwndDlg, 0);
        usReturn = (USHORT) WinProcessDlg(hNewFrame);
        /* ##END  */
         }
         break;
      /* Menu item IDM_USINGHELP Clicked/Selected */
      case IDM_USINGHELP:
         {
        /* ##START 266.0  */
        /* Menu events - Set ports */

        /* !place #include "SPORTS.h" in the Extra Include Code Section! */
        {
        USHORT usReturn;
        HWND hNewFrame;

        hNewFrame = OpenSPORTS(hwndDlg, 0);
        usReturn = (USHORT) WinProcessDlg(hNewFrame);
        }

        WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), tbarmsg);
        /* ##END  */
         }
         break;
      /* Menu item 283 Clicked/Selected */
      case 283:
         {
        /* ##START 283.0  */
        /* Menu events - H~ailing list */

        USHORT usReturn;
        HWND hNewFrame;
        PHAILLISTFORMINFO pHaillistFormInfo = malloc(sizeof(HAILLISTFORMINFO));
              
             
        pHaillistFormInfo->mode = 1;
        hNewFrame = OpenHAILLIST(hwndDlg, pHaillistFormInfo);
        usReturn = (USHORT) WinProcessDlg(hNewFrame);
        /* ##END  */
         }
         break;
      /* Menu item 269 Clicked/Selected */
      case 269:
         {
        /* ##START 269.0  */
        /* Menu events - Hail ~list */

        USHORT usReturn;
        HWND hNewFrame;


        hNewFrame = OpenLOGNOTE(hwndDlg, 0);
        usReturn = (USHORT) WinProcessDlg(hNewFrame);
        /* ##END  */
         }
         break;
      /* Menu item 276 Clicked/Selected */
      case 276:
         {
        /* ##START 276.0  */
        /* Menu events - Phra~ses */

        HAB hab;

        if( WinIsWindow(hab, hNewPHRFrame) )
           {
           WinSetWindowPos(hNewPHRFrame, 0, 0, 0, 0, 0, SWP_ACTIVATE | SWP_SHOW | SWP_RESTORE);
           }
        else
           {
           hNewPHRFrame = OpenPHRLIST(HWND_DESKTOP, 0);
           }
        /* ##END  */
         }
         break;
      /* Menu item IDM_ABOUTNETCHAT Clicked/Selected */
      case IDM_ABOUTNETCHAT:
         {
        /* ##START 272.0  */
        /* Menu events - ~About NetChat ... */

        /* !place #include "ABOUT.h" in the Extra Include Code Section! */
        /* Open the modal form F:\nchattcp\NetChat\ABOUT */
        {
           USHORT usReturn;
           HWND hNewFrame;
           hNewFrame = OpenABOUT(hwndDlg, 0);
           usReturn = (USHORT) WinProcessDlg(hNewFrame);
        }
        /* ##END  */
         }
         break;
      /* Menu item 286 Clicked/Selected */
      case 286:
         {
        /* ##START 286.0  */
        /* Menu events - menu item */

        if( hwndHelp )
           WinSendMsg(hwndHelp, HM_HELP_CONTENTS, (MPARAM)0, (MPARAM)0);
        /* ##END  */
         }
         break;
      /* Menu item 285 Clicked/Selected */
      case 285:
         {
        /* ##START 285.0  */
        /* Menu events - ~Register */

        /* !place #include "REG.h" in the Extra Include Code Section! */
        /* Open the modal form F:\nchattcp\NetChat\REG */
        {
           USHORT usReturn;
           HWND hNewFrame;
           hNewFrame = OpenREG(hwndDlg, 0);
           usReturn = (USHORT) WinProcessDlg(hNewFrame);
        }
        /* ##END  */
         }
         break;
      } /* end switch */
      break;

  /* Initialize sub menus, if any */
  case WM_INITMENU:
     switch (SHORT1FROMMP(mp1)) {
      /* Menu item IDM_FILE Clicked/Selected */
      case IDM_FILE:
         {
        /* ##START 256.0  */
        /* Menu events - ~File */

        CHAR bstatus[20];


        if( checkConnectionOnceNT() == 1 )
           {
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 268, TRUE);
           if( !FTPINPROGRESS ) 
              {
              if( STILLWAITING )
                 WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 275, FALSE);
              else
                 {   
                 WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 275, TRUE);
                 WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 282, FALSE);
                 }
              }
           else
              {
              WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 275, FALSE);
              if( FILENOTIFY )
                 WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 282, FALSE);
              else   
                 WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 282, TRUE);
              }
           }
        else
           {
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 268, FALSE);
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 275, FALSE);
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 282, FALSE);
           }         


        WinQueryDlgItemText(hwndDlg, 1002, sizeof(bstatus), bstatus);
        if( strcmp(bstatus, "Listen OFF") == 0 )
           {
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_CLOSECONNECTION, FALSE);
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_CONNECT, TRUE);
           }
        else
           {
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_CLOSECONNECTION, TRUE);
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_CONNECT, FALSE);
           }   

        if( strcmp(bstatus, "Connected!") == 0 )
           {
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_WINDOWSTYLE, FALSE);
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 279, TRUE);
           }
        else
           {
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_WINDOWSTYLE, TRUE);
           WinEnableMenuItem(WinWindowFromID(hwndFrame, FID_MENU), 279, FALSE);
           }
        /* ##END  */
         }
         break;
      /* Menu item IDM_EDIT Clicked/Selected */
      case IDM_EDIT:
         {
        /* ##START 257.0  */
        /* Menu events - ~Edit */

        if( (ULONG)WinSendDlgItemMsg(hwndDlg, 1000, MLM_QUERYWRAP, 0, 0) )
           WinCheckMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_WORDWRAPR, TRUE);
        else   
           WinCheckMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_WORDWRAPR, FALSE);

        if( (ULONG)WinSendDlgItemMsg(hwndDlg, 1001, MLM_QUERYWRAP, 0, 0) )
           WinCheckMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_WORDWRAPL, TRUE);
        else   
           WinCheckMenuItem(WinWindowFromID(hwndFrame, FID_MENU), IDM_WORDWRAPL, FALSE);
        /* ##END  */
         }
         break;
      /* Menu item IDM_CONFIGURE Clicked/Selected */
      case IDM_CONFIGURE:
         {
        /* ##START 258.0  */
        /* Menu events - ~Configure */
        /* ##END  */
         }
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
 /* Code sections - User defined messages */

 case WM_MINMAXFRAME:
    {
    pswp = PVOIDFROMMP (mp1);
    if (pswp->fl & SWP_MINIMIZE) 
       {
       WinSetWindowPos(hNewPHRFrame, 0, 0, 0, 0, 0, SWP_HIDE);
       }
    if (pswp->fl & SWP_RESTORE) 
       {
       WinSetWindowPos(hNewPHRFrame, 0, 0, 0, 0, 0, SWP_ACTIVATE | SWP_SHOW | SWP_RESTORE);
       }
    }
    return(0);
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenMain(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   HWND hwndClient;
   FRAMECDATA frameData;
   frameData.cb=sizeof(FRAMECDATA);
   frameData.flCreateFlags= FCF_NOBYTEALIGN | FCF_SIZEBORDER | FCF_TITLEBAR | FCF_SYSMENU | FCF_TASKLIST | FCF_MAXBUTTON | FCF_MINBUTTON | FCF_ACCELTABLE | FCF_MENU | FCF_ICON ;
   frameData.hmodResources=0;
   frameData.idResources=ID_MAINFORM;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame=WinCreateWindow(HWND_DESKTOP, WC_FRAME, "NetChat for OS/2", 0,0,0,0,0,hwndOwner,HWND_TOP,ID_MAINFORM,&frameData,0);
   if (hwndFrame) {
      hwndClient =(HWND) WinLoadDlg(hwndFrame,
              hwndFrame,   
              MainDlgProc, 
              0, ID_MAINFORM, 
              pInfo); 
      WinShowWindow(hwndFrame, TRUE);
   }
   return hwndFrame;
}
MRESULT HandleMessage(HWND hwndFrame, HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HENUM  henum;
  HWND   hwndCtl;
  HWND   hwndHScroll;
  HWND   hwndVScroll;
  LONG   lOffset;
  POINTL pointl;
  PSWP   pCtlSize;
  PSWP   pswp;
  PULONG *pWindowInfo;
  RECTL  rectl;
  SWP    swp;
  ULONG  ulCnt;
  switch (msg) {
  /* Default initialization of window */
  case WM_INITDLG:
     WinSetWindowULong(hwndDlg, QWL_USER, (ULONG) mp2);
     pWindowInfo = (PULONG *) mp2;
     if (pWindowInfo)
        *pWindowInfo=0; /* clear out size data pointer */
     if (hwndFrame == hwndDlg) {
        ULONG  ulPicture;
        HACCEL hAccel;
        WinLoadMenu(hwndFrame, 0, WinQueryWindowUShort(hwndFrame, QWS_ID));
        hAccel = WinLoadAccelTable(0,0,WinQueryWindowUShort(hwndFrame, QWS_ID));
        if (hAccel)
           WinSetAccelTable(0, hAccel, hwndFrame);
        WinQueryWindowRect(hwndDlg, &rectl);
        if (WinWindowFromID(hwndFrame, FID_MENU))
           rectl.yTop += WinQuerySysValue(HWND_DESKTOP, SV_CYMENU);
        WinQueryTaskSizePos(0, 0, &swp);
        if (swp.y+rectl.yTop>WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)) {
           swp.y=WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)-rectl.yTop;
        } /* endif */
        if (swp.x+rectl.xRight>WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)) {
           swp.x=WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)-rectl.xRight;
        } /* endif */
        WinSetWindowPos(hwndFrame,0,
           swp.x, swp.y, rectl.xRight, rectl.yTop, SWP_SIZE|SWP_MOVE);
        ulPicture=(ULONG) WinLoadPointer(HWND_DESKTOP, 0,
              WinQueryWindowUShort(hwndFrame, QWS_ID));
        if (!ulPicture)
           ulPicture=(ULONG)WinQuerySysPointer(HWND_DESKTOP,SPTR_APPICON,FALSE);
        WinSendMsg(hwndFrame, WM_SETICON, (MPARAM) ulPicture, (MPARAM) 0);
     } else {
        WinSetWindowUShort(hwndDlg, QWS_ID, FID_CLIENT);

        /* Calculate window positioning and size */
        WinQueryWindowRect(hwndDlg, &rectl);
        WinSendMsg(hwndFrame, WM_QUERYBORDERSIZE, (MPARAM)&pointl, 0);
        rectl.xLeft += pointl.x;
        rectl.xRight += pointl.x;
        rectl.yBottom += pointl.y;
        rectl.yTop += pointl.y;

        if (WinWindowFromID(hwndFrame,FID_HORZSCROLL)) {
           rectl.yBottom+=WinQuerySysValue(HWND_DESKTOP,SV_CYHSCROLL);
           rectl.yTop+=WinQuerySysValue(HWND_DESKTOP,SV_CYHSCROLL);
        }
        WinCalcFrameRect(hwndFrame, &rectl, FALSE);

        WinQueryTaskSizePos(0, 0, &swp);
        if (swp.y+rectl.yTop>WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)) {
           swp.y=WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)-rectl.yTop;
        } /* endif */
        if (swp.x+rectl.xRight>WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)) {
           swp.x=WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)-rectl.xRight;
        } /* endif */

        WinSetWindowPos(hwndFrame,0,
           swp.x, swp.y, rectl.xRight, rectl.yTop, SWP_SIZE|SWP_MOVE);

        /* Initialize information to handle sizing and scrolling windows */
        pWindowInfo = (PULONG *) mp2;
        if (pWindowInfo)
           *pWindowInfo = 0;

        /* Count number of controls */
        ulCnt=0;
        henum = WinBeginEnumWindows(hwndDlg);
        hwndCtl=WinGetNextWindow(henum);
        while (hwndCtl) {
           ulCnt++;
           hwndCtl=WinGetNextWindow(henum);
        } /* endwhile */
        WinEndEnumWindows(henum);

        pCtlSize = malloc(sizeof(SWP)*(ulCnt+2));

        /* Store client window information first */
        if (pCtlSize) {
           WinQueryWindowPos(hwndDlg, &(pCtlSize[0]));

           /* Query size information on all controls */
           ulCnt=1;
           henum = WinBeginEnumWindows(hwndDlg);
           hwndCtl=WinGetNextWindow(henum);
           while (hwndCtl) {
              if (WinQueryWindowPos(hwndCtl, &(pCtlSize[ulCnt]))) {
                 if (!pCtlSize[ulCnt].cx || !pCtlSize[ulCnt].cy)
                    pCtlSize[ulCnt].hwnd = 0;
                 else
                    ulCnt++;
              }
              hwndCtl=WinGetNextWindow(henum);
           } /* endwhile */
           WinEndEnumWindows(henum);
           pCtlSize[ulCnt].hwnd = 0;
        }
       /* Store number of controls */       pCtlSize[1].ulReserved1 = ulCnt;
        pWindowInfo = (PULONG *) mp2;
        *pWindowInfo = (PULONG) pCtlSize;

        /* If scrollable, initialize scroll bars */
        if (WinWindowFromID(hwndFrame,FID_HORZSCROLL)) {
           HandleMessage(hwndFrame, hwndDlg, WM_SIZE, 0, 0);
        }
     }
     break;
  /* Default WM_SIZE for sizeable or scrollable windows */
  case WM_SIZE:
     if (hwndFrame==hwndDlg)
        return 0;
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (!pWindowInfo)
        return 0;
     pCtlSize = (PSWP) *pWindowInfo;
     if (!pCtlSize)
        return 0;
     if (!WinQueryWindowPos(hwndDlg,&swp))
        return 0;
     if (!swp.cx || !swp.cy)
        return 0;

     /* Handle sizing of scrollable window */
     hwndHScroll=WinWindowFromID(hwndFrame,FID_HORZSCROLL);
     hwndVScroll=WinWindowFromID(hwndFrame,FID_VERTSCROLL);

     if (hwndHScroll && hwndVScroll) {
        /* Get viewable size of client area */
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);

        if (pCtlSize[0].cx<=rectl.xRight) {
           pCtlSize[0].x = 0;
           WinEnableWindow(hwndHScroll,FALSE);
           WinSendMsg(hwndHScroll,SBM_SETSCROLLBAR,MPFROMSHORT(0),
                      MPFROM2SHORT(0,0));
           WinSendMsg(hwndHScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(0,0),0);
        } else {
           pCtlSize[0].x = pCtlSize[0].cx-rectl.xRight+rectl.xLeft;
           pCtlSize[0].ulReserved1= 0;
           WinEnableWindow(hwndHScroll,TRUE);
           WinSendMsg(hwndHScroll,SBM_SETSCROLLBAR,
                      MPFROMSHORT(pCtlSize[0].ulReserved1),
                      MPFROM2SHORT(0,pCtlSize[0].x));
           WinSendMsg(hwndHScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(rectl.xRight,pCtlSize[0].cx),0);
        } /* endif */
        if (pCtlSize[0].cy<=rectl.yTop) {
           pCtlSize[0].y = 0;
           WinEnableWindow(hwndVScroll,FALSE);
           WinSendMsg(hwndVScroll,SBM_SETSCROLLBAR,MPFROMSHORT(0),
                      MPFROM2SHORT(0,0));
           WinSendMsg(hwndVScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(0,0),0);
        } else {
           pCtlSize[0].y = pCtlSize[0].cy-rectl.yTop+rectl.yBottom;
           pCtlSize[0].ulReserved2= pCtlSize[0].y;
           WinEnableWindow(hwndVScroll,TRUE);
           WinSendMsg(hwndVScroll,SBM_SETSCROLLBAR,
                      MPFROMSHORT(pCtlSize[0].ulReserved2),
                      MPFROM2SHORT(0,pCtlSize[0].y));
           WinSendMsg(hwndVScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(rectl.yTop, pCtlSize[0].cy),0);
        } /* endif */
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           WinSetWindowPos(hwndCtl, 0, pCtlSize[ulCnt].x,
              pCtlSize[ulCnt].y-pCtlSize[0].y+pCtlSize[0].ulReserved2,
              0, 0, SWP_MOVE);
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }

     }
     /* Handle sizing of a regular sizeable window */
     else {
        SWP   swpCtl;
        SWP   swpTest;
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           swpCtl.x = (pCtlSize[ulCnt].x * swp.cx)/pCtlSize[0].cx;
           swpCtl.y = (pCtlSize[ulCnt].y * swp.cy)/pCtlSize[0].cy;
           swpCtl.cx = (pCtlSize[ulCnt].cx * swp.cx)/pCtlSize[0].cx;
           swpCtl.cy = (pCtlSize[ulCnt].cy * swp.cy)/pCtlSize[0].cy;
           WinSetWindowPos(hwndCtl, 0, swpCtl.x, swpCtl.y, swpCtl.cx, swpCtl.cy, SWP_MOVE | SWP_SIZE);

           /* If needed, adjust the control position */
           WinQueryWindowPos(hwndCtl,&swpTest);
           if (swpTest.x != swpCtl.x || swpTest.y != swpCtl.y) {
              swpCtl.x += (swpCtl.x - swpTest.x);
              swpCtl.y += (swpCtl.y - swpTest.y);
              swpCtl.cx += (swpCtl.cx - swpTest.cx);
              swpCtl.cy += (swpCtl.cy - swpTest.cy);
              WinSetWindowPos(hwndCtl, 0, swpCtl.x, swpCtl.y, swpCtl.cx, swpCtl.cy, SWP_MOVE | SWP_SIZE);
           }
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }
     }
     break;
  /* If position changed, force a WM_SIZE message  */
  case WM_WINDOWPOSCHANGED:
     if (hwndFrame!=hwndDlg) {
        pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER );
        if (!pWindowInfo)
           return 0;
        pCtlSize = (PSWP) *pWindowInfo;
        if (pCtlSize) {
           pswp = (PSWP) mp1;
           if ((pswp[0].cx != pswp[1].cx) || (pswp[0].cy != pswp[1].cy))
              WinSendMsg(hwndDlg, WM_SIZE, MPFROM2SHORT(pswp[1].cx, pswp[1].cy),
                   MPFROM2SHORT(pswp[0].cx, pswp[0].cy));
        }
     }
     break;
  /* Default handling for WM_CLOSE */
  case WM_CLOSE:
     WinDismissDlg(hwndFrame, DID_CANCEL);
     WinDestroyWindow(hwndFrame);
     break;
  case WM_HSCROLL:
     if (hwndFrame==hwndDlg)
        return 0;
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (!pWindowInfo)
        return 0;
     pCtlSize = (PSWP) *pWindowInfo;
     if (!pCtlSize)
        return 0;
     hwndHScroll=WinWindowFromID(hwndFrame,FID_HORZSCROLL);
     lOffset = pCtlSize[0].ulReserved1;
     switch (SHORT2FROMMP(mp2)) {
     case SB_LINELEFT:
        lOffset--;
        break;
     case SB_LINERIGHT:
        lOffset++;
        break;
     case SB_PAGELEFT:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset-=rectl.xRight;
        break;
     case SB_PAGERIGHT:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset+=rectl.xRight;
        break;
     case SB_SLIDERTRACK:
     case SB_SLIDERPOSITION:
        lOffset = SHORT1FROMMP(mp2);
        break;
     } /* endswitch */

     if (lOffset < 0)
        lOffset = 0;
     if (lOffset > pCtlSize[0].x)
        lOffset = pCtlSize[0].x;
     if (lOffset > pCtlSize[0].ulReserved1) {
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           WinSetWindowPos(hwndCtl, 0, pCtlSize[ulCnt].x-lOffset,
              pCtlSize[ulCnt].y-pCtlSize[0].y+pCtlSize[0].ulReserved2,
              0, 0, SWP_MOVE );
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }
        pCtlSize[0].ulReserved1 = lOffset;
        WinSendMsg(hwndHScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
     } /* endif */
     else
     if (lOffset < pCtlSize[0].ulReserved1) {
        ulCnt = pCtlSize[1].ulReserved1;
        while (ulCnt >0) {
           hwndCtl=pCtlSize[ulCnt].hwnd;
           WinSetWindowPos(hwndCtl, 0, pCtlSize[ulCnt].x-lOffset,
              pCtlSize[ulCnt].y-pCtlSize[0].y+pCtlSize[0].ulReserved2,
              0, 0, SWP_MOVE);
           ulCnt--;
        }
        pCtlSize[0].ulReserved1 = lOffset;
        WinSendMsg(hwndHScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
     } /* endif */
     break;
  case WM_VSCROLL:
     if (hwndFrame==hwndDlg)
        return 0;
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (!pWindowInfo)
        return 0;
     pCtlSize = (PSWP) *pWindowInfo;
     if (!pCtlSize)
        return 0;
     hwndVScroll=WinWindowFromID(hwndFrame,FID_VERTSCROLL);
     lOffset = pCtlSize[0].ulReserved2;
     switch (SHORT2FROMMP(mp2)) {
     case SB_LINEUP:
        lOffset--;
        break;
     case SB_LINEDOWN:
        lOffset++;
        break;
     case SB_PAGEUP:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset-=rectl.yTop;
        break;
     case SB_PAGEDOWN:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset+=rectl.yTop;
        break;
     case SB_SLIDERTRACK:
     case SB_SLIDERPOSITION:
        lOffset = SHORT1FROMMP(mp2);  /* verified should be positive */
        break;
     } /* endswitch */

     if (lOffset < 0)
        lOffset = 0;
     if (lOffset > pCtlSize[0].y)
        lOffset = pCtlSize[0].y;
     if (lOffset < pCtlSize[0].ulReserved2) {
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           WinSetWindowPos(hwndCtl, 0,
              pCtlSize[ulCnt].x-pCtlSize[0].ulReserved1,
              pCtlSize[ulCnt].y-pCtlSize[0].y+lOffset, 0, 0, SWP_MOVE);
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }
        pCtlSize[0].ulReserved2 = lOffset;
        WinSendMsg(hwndVScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
     } /* endif */
    else
    if (lOffset > pCtlSize[0].ulReserved2) {
       ulCnt = pCtlSize[1].ulReserved1;
       while (ulCnt > 0) {
          hwndCtl=pCtlSize[ulCnt].hwnd;
          WinSetWindowPos(hwndCtl, 0,
             pCtlSize[ulCnt].x-pCtlSize[0].ulReserved1,
             pCtlSize[ulCnt].y-pCtlSize[0].y+lOffset, 0, 0, SWP_MOVE);
          ulCnt--;
       }
       pCtlSize[0].ulReserved2 = lOffset;
       WinSendMsg(hwndVScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
    } /* endif */
     break;
  /* When window is destroyed, deallocate window memory */
  case WM_DESTROY:
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (pWindowInfo) {
        pCtlSize = (PSWP) *pWindowInfo;
        if (pCtlSize)
           free(pCtlSize);
        free(pWindowInfo);
        WinSetWindowULong(hwndDlg, QWL_USER, 0L);
     }
     break;
  }
  return (MRESULT) FALSE;
}

/***************************************************************/
/* MLEGetItemText                                              */
/*                                                             */
/* Description:                                                */
/*                                                             */
/* This helper function is used easily retrieve all or part    */
/* of the text within an MLE.  There is no limit on the amount */
/* of text to be retrieved.                                    */
/*                                                             */
/* Parameters:                                                 */
/*                                                             */
/*    hwndDlg      - handle to window containing the MLE       */
/*    ulID         - MLE identifier                            */
/*    lIptPosition - Starting IPT position to get value        */
/*                   Use 0 to start at the beginning           */
/*                   Use -1 to start at the cursor position    */
/*    lBoundary    - Number of characters to get               */
/*                   Used -1 to get characters until the end   */
/*    ppText       - Pointer to receive a pointer to text area */
/***************************************************************/
ULONG MLEGetItemText(HWND hwndDlg, ULONG ulID, LONG lIptPosition,
      LONG lBoundary, PBYTE *ppText)
{
  ULONG ulTextSize;
  PBYTE pText=0;
  HWND  hwndControl = WinWindowFromID(hwndDlg, ulID);

  /* Get text length */
  ulTextSize = (LONG)WinSendMsg(hwndControl,MLM_QUERYFORMATTEXTLENGTH,MPFROMLONG(lIptPosition),MPFROMLONG(lBoundary));
  if (ulTextSize>0) {
     PBYTE pMLEBuff=0;
     ULONG ulBuffSize;
     pText = malloc(ulTextSize);

     /* Allocate MLE transfer buffer. MLE limited to 64K tiled memory */
     ulBuffSize = 65535;
     if (pText && !DosAllocMem((PPVOID) &pMLEBuff, (ULONG) ulBuffSize,
                PAG_COMMIT | PAG_READ | PAG_WRITE | OBJ_TILE)) {
        ULONG ulBytesCopied=0;
        ULONG ulBytesToCopy;
        ULONG ulTransfer;

        /* Set import/export MLE buffer */
        WinSendMsg(hwndControl, MLM_SETIMPORTEXPORT,
           MPFROMP(pMLEBuff), MPFROMLONG( ulBuffSize));

        do {
           if (ulBuffSize < ulTextSize-ulBytesCopied)
              ulBytesToCopy=ulBuffSize;
           else
              ulBytesToCopy=ulTextSize-ulBytesCopied;

           /* Get text at given IPT */
           ulTransfer = (ULONG) WinSendMsg(hwndControl,
                    MLM_EXPORT,
                    MPFROMLONG(&lIptPosition), MPFROMLONG(&ulBytesToCopy));

           if (!ulTransfer)
              ulBytesCopied=ulTextSize;
           else {
              memcpy((PVOID)&(pText[ulBytesCopied]),
                     (PVOID)pMLEBuff, ulTransfer);
              ulBytesCopied+=ulTransfer;
           }
        } while (ulBytesCopied < ulTextSize);

        /* Free MLE transfer buffer */
        DosFreeMem((PBYTE)pMLEBuff);
     }
  }
  pText[ulTextSize]=0;
  *ppText = pText;
  return ulTextSize;
}

/***************************************************************/
/* MLEInsertText                                               */
/*                                                             */
/* Description:                                                */
/*                                                             */
/* This helper function is used easily insert text within the  */
/* MLE.  There is no limit on the amount of text to be inserted*/
/*                                                             */
/* Parameters:                                                 */
/*                                                             */
/*    hwndDlg      - handle to window containing the MLE       */
/*    ulID         - MLE identifier                            */
/*    lIptPosition - IPT to insert text                        */
/*                   Use 0 to start at the beginning           */
/*                   Use -1 to start at the cursor position    */
/*    pText        - Pointer to text area                      */
/***************************************************************/
ULONG MLEInsertText(HWND hwndDlg, ULONG ulID, LONG iptPosition, PBYTE pText)
{
  PBYTE pMLEBuff=0;
  ULONG ulBuffSize;
  ULONG ulBytesCopied=0;
  HWND  hwndControl = WinWindowFromID(hwndDlg, ulID);

  /* Allocate MLE transfer buffer. MLE limited to 64K tiled memory */
  ulBuffSize = 65535;
  if (!DosAllocMem((PPVOID) &pMLEBuff, (ULONG) ulBuffSize,
             PAG_COMMIT | PAG_READ | PAG_WRITE | OBJ_TILE)) {
     ULONG ulBytesToCopy;
     ULONG ulTextSize = strlen((char *)pText);

     /* Set import/export MLE buffer */
     WinSendMsg(hwndControl, MLM_SETIMPORTEXPORT,
           MPFROMP(pMLEBuff), MPFROMLONG( ulBuffSize));
     do {
        if (ulBuffSize < ulTextSize-ulBytesCopied)
           ulBytesToCopy=ulBuffSize;
        else
           ulBytesToCopy=ulTextSize-ulBytesCopied;
        memcpy((PVOID) pMLEBuff, &(pText[ulBytesCopied]),
                     ulBytesToCopy);

        /* Insert text at given IPT */
        WinSendMsg(hwndControl, MLM_IMPORT,
                 (MPARAM) &iptPosition, (MPARAM) ulBytesToCopy);
        ulBytesCopied+=ulBytesToCopy;
     } while (ulBytesCopied < ulTextSize);

     /* Free MLE transfer buffer */
     DosFreeMem((PBYTE)pMLEBuff);
  }
  return ulBytesCopied;
}

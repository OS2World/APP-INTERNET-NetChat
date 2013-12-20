/* xtra.c  */



#include <xtra.h>
#include <xtrarc.h>
#include <NEWREC.h>
#include <EDITREC.h>
#include <HAILNOTE.h>
#include <ADDPHR.h>
#include <EDITPHR.h>
#include <FPROMPT.h>
#include <netchat.rch>
#include <main.rch>
#include <about.h>
#include <coninfo.h>
#include "stats.h"
#include "CPC.h"





INT existFile(CHAR *fileStr)
{
FILEFINDBUF3 findbuf;
HDIR hDir = HDIR_CREATE;
ULONG usSearchCount = 1;
ULONG ALLFILES;


ALLFILES = FILE_NORMAL | FILE_ARCHIVED | FILE_SYSTEM | FILE_READONLY | FILE_HIDDEN;
if(DosFindFirst(fileStr, &hDir, ALLFILES, (PVOID)&findbuf, sizeof(findbuf), &usSearchCount, FIL_STANDARD))
   {
   DosFindClose(hDir);
   return(0);
   }
else
   {
   DosFindClose(hDir);
   return(1);
   }
}




INT getmsgstr(INT sp, INT brd, CHAR *tmp, CHAR *dStr)
{
INT cw, iter;
BOOL ENDRCV;


for( iter=0;iter<brd;iter++ )
   {
   tmp[sp] = dStr[iter];
   sp++;
   }
return(sp);
}



INT checkConnectionOnceNT(VOID)
{
struct sockaddr_in srv;
INT srvlen;
CHAR onebuf[MSGSIZE];
CHAR typemsg[30];
CHAR bstatus[20];


strcpy(typemsg, "isconnection!!");
strcpy(onebuf, localIP);
strcat(onebuf, "<");
strcat(onebuf, typemsg);
strcat(onebuf, ">");
   
if (send(globsockt, onebuf, strlen(onebuf)+1, 0) < 0)
   {
   NOWCONNECTED1 = FALSE;
   return(-1);
   }
else   
   {
   NOWCONNECTED1 = TRUE;
   return(1);
   }

}



VOID msgServer(PVOID chkmaildat)
{
HAB habT;
HMQ hmqT;
INT i, sopt;
HWND hwndDlg;
ULONG len, pos;
ULONG fgndcolor;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);


hwndDlg = hwndMainDlg;

if( SERVERON )
   {
   WinDestroyMsgQueue(hmqT);
   WinTerminate(habT);
   _endthread();
   }

ATTEMPTINGCONNECT = FALSE;
NOWLISTENING = FALSE;
SERVERON = TRUE;
FTPINPROGRESS = FALSE;
NOWCONNECTED2 = FALSE;

sopt = 1;
sock_init();

SENTALREADY = FALSE;
globsock = socket(PF_INET, SOCK_STREAM, 0);
setsockopt(globsock, SOL_SOCKET, SO_REUSEADDR, (CHAR *)&sopt, sizeof(sopt));

if (globsock < 0)
   {
   WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
   WinEnableWindow(WinWindowFromID(hwndDlg, 1006), TRUE);
   WinEnableWindow(WinWindowFromID(hwndDlg, 1007), TRUE);
   DosBeep(1200, 50);
   WinSetDlgItemText(hwndDlg, 1002, "Listen OFF");   
   fgndcolor = CLR_BLACK;   
   WinSetPresParam(WinWindowFromID(hwndDlg, 1002), 
                           PP_FOREGROUNDCOLORINDEX,
                           sizeof(ULONG),     
                           &fgndcolor);     
   SERVERON = FALSE;
   soclose(globnsock);
   soclose(globsock);
   soclose(globsockt);
   WinDestroyMsgQueue(hmqT);
   WinTerminate(habT);
   _endthread();
   }
else
   {
   int namelen;

   
   getIPaddr(localIP);  
   // getIPaddr(localIP, tmpFileName);  
   
   memset(&globserver, 0, sizeof(globserver));
   globserver.sin_family = AF_INET;
   globserver.sin_addr.s_addr = inet_addr(localIP);
   globserver.sin_port = htons((SHORT)pgmData[4]);
      
   namelen = sizeof(globserver);
      
   if (bind(globsock, (struct sockaddr *)&globserver, sizeof(globserver)) < 0)
      {
      WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1006), TRUE);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1007), TRUE);
      // DosBeep(1200, 50);
      WinSetDlgItemText(hwndDlg, 1002, "Listen OFF");   
      cdat.hwndDlg = hwndDlg;
      cdat.interval = 7;
      _beginthread(mailSendStatus, NULL, BSTACK, (PVOID)&cdat);
      fgndcolor = CLR_BLACK;   
      WinSetPresParam(WinWindowFromID(hwndDlg, 1002), 
                              PP_FOREGROUNDCOLORINDEX,
                              sizeof(ULONG),     
                              &fgndcolor);     
      SERVERON = FALSE;
      soclose(globnsock);
      soclose(globsock);
      soclose(globsockt);
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }


   if (listen(globsock, 1) != 0)
      {
      soclose(globsock);   
      fgndcolor = CLR_BLACK;   
      WinSetPresParam(WinWindowFromID(hwndDlg, 1002), 
                                PP_FOREGROUNDCOLORINDEX,
                                sizeof(ULONG),     
                                 &fgndcolor);     
      WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1006), TRUE);
      WinEnableWindow(WinWindowFromID(hwndDlg, 1007), TRUE);
      DosBeep(1200, 50);
      WinSetDlgItemText(hwndDlg, 1002, "Listen OFF");   
      SERVERON = FALSE;
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }
   else   
      {
      fgndcolor = CLR_YELLOW;   
      WinSetPresParam(WinWindowFromID(hwndDlg, 1002), 
                                PP_FOREGROUNDCOLORINDEX,
                                sizeof(ULONG),     
                                &fgndcolor);     
      WinSetDlgItemText(hwndDlg, 1002, "Listen ON");
      NOWLISTENING = TRUE;
      }
      
   memset(&globclient, 0, sizeof(globclient));
   if ((globnsock = accept(globsock, (struct sockaddr *)&globclient, &namelen)) == -1)
      {
      SERVERON = FALSE;
      } 
   else  
      {
      setsockopt(globnsock, SOL_SOCKET, SO_REUSEADDR, (CHAR *)&sopt, sizeof(sopt));
      strcpy(guestIP, inet_ntoa(globclient.sin_addr));
         
      if( pgmData[31] )
         { 
         WinSetWindowPos(hwndMainF, HWND_TOP, 0, 0, 0, 0, SWP_ACTIVATE | SWP_SHOW | SWP_RESTORE);
         }
                                      
      NOWCONNECTED2 = TRUE;
         
      if( !NOWCONNECTED1 && !ATTEMPTINGCONNECT )
         {
         _beginthread(attemptConnect, NULL, BSTACK, (PVOID)&hwndMainDlg);
         SENTALREADY = TRUE;
         }
            
      fgndcolor = CLR_RED;   
      WinSetPresParam(WinWindowFromID(hwndDlg, 1002), 
                               PP_FOREGROUNDCOLORINDEX,
                               sizeof(ULONG),     
                               &fgndcolor);     
      WinSetDlgItemText(hwndDlg, 1002, "Connected!");
      listenToLoop(hwndDlg);
      }
   }

soclose(globnsock);
soclose(globsock);
soclose(globsockt);

memset(&globserver, 0, sizeof(globserver));

fgndcolor = CLR_BLACK;   
WinSetPresParam(WinWindowFromID(hwndDlg, 1002), 
                        PP_FOREGROUNDCOLORINDEX,
                        sizeof(ULONG),     
                        &fgndcolor);     
WinEnableWindow(WinWindowFromID(hwndDlg, 1002), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg, 1006), TRUE);
WinEnableWindow(WinWindowFromID(hwndDlg, 1007), TRUE);
WinSetDlgItemText(hwndDlg, 1002, "Listen OFF");   

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




INT listenToLoop(HWND hwndD)
{
INT i;
HWND hwndDlg;
BOOL NEVERMIND;
BOOL BYPASS;
BOOL NAMEID;
BOOL ECHOONE;
BOOL ECHOTWO;
BOOL CONMSG;
BOOL TRANSFERMSG;
CHAR tbuf[MSGSIZE];
CBD condat;
ULONG len, pos;
ULONG fgndcolor;


hwndDlg = hwndD;

do
   {
   INT br, lnum, ret;
   CHAR rbuf[MSGSIZE];
         

   strcpy(rbuf, "");
   strcpy(tmprcvbuf, "");
   lnum = 0;
   br = 0;
   do
      {
      lnum += br;
      br = recv(globnsock, rbuf, sizeof(rbuf), 0);
      getmsgstr(lnum, br, tmprcvbuf, rbuf);
      }
   while( rbuf[br-1] != '\0' && br != -1 );
   
   if( br <= 0  )
      {
      SERVERON = FALSE;
      FILENOTIFY = FALSE;
      STILLWAITING = FALSE;
      NOWCONNECTED1 = FALSE;
      NOWCONNECTED2 = FALSE;
      NOWLISTENING = FALSE;
      WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
      makeTBar(); 
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 
      strcpy(tmprcvbuf, "<<QUITNOWNC>>");
      so_cancel(globnsock);
      so_cancel(globsockt);
      so_cancel(globsock);
      DosBeep(800, 100);  
      DosBeep(1200, 50);  
      soclose(globnsock);
      soclose(globsock);
      soclose(globsockt);  
      return(-1); 
      }
      
   NAMEID = FALSE; 
   BYPASS = FALSE; 
   NEVERMIND = FALSE; 
   ECHOONE = FALSE;
   ECHOTWO = FALSE;
   CONMSG = FALSE;
   TRANSFERMSG = FALSE;

   if( strcmp(tmprcvbuf, "<<QUITNOWNC>>") == 0 )
      {
      WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
      SERVERON = FALSE;
      FILENOTIFY = FALSE;
      STILLWAITING = FALSE;
      }
   else   
      {
      INT n;
      ULONG forecolor;
      CHAR tbuf[MSGSIZE];
       
            
      pos = WinQueryWindowTextLength(WinWindowFromID(hwndDlg, 1000));
         
      strcpy(tbuf, tmprcvbuf);
             
      n = 0;
      do
         {
         guestIP[n] = tbuf[n];
         n++;
         }
      while( tbuf[n] != '<' );
      strndel(tbuf, n);  


      if( strcmp(tbuf, "<isconnection!!>") == 0 )
         {
         CONMSG = TRUE;
         NEVERMIND = TRUE;
         }  
         
         
      if( strcmp(tbuf, "<gotthewakeupok>") == 0 )
         {
         CONMSG = TRUE;
         NEVERMIND = TRUE;
         condat.hwndDlg = hwndDlg;
         condat.interval = 5;
         _beginthread(mailSendStatus, NULL, BSTACK, (PVOID)&condat);
         }  
            
            
      if( strcmp(tbuf, "<wakeupthedead!>") == 0 )
         {
         INT mb;
         
         
         mb = 9;
         CONMSG = TRUE;
         NEVERMIND = TRUE;
         condat.hwndDlg = hwndDlg;
         condat.interval = 6;
         _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)mb);
         _beginthread(mailSendStatus, NULL, BSTACK, (PVOID)&condat);
         }  
            

      if( strlen(tbuf) >= 15 )
         {  
         if( strncmp(tbuf, "<ncfilterRNAME>", 15) == 0 )
            {
            CHAR cbuf[MSGSIZE];
            
            
            strcpy(cbuf, "***** ");
            strndel(tbuf, 15);
            strcat(cbuf, tbuf);
            strcat(cbuf, " has connected with you! *****");
            strcpy(tbuf, cbuf);
            NAMEID = TRUE;   
            }
            
         if( strncmp(tbuf, "<nchatfilterID>", 15) == 0 )
            {
            CHAR cbuf[MSGSIZE];
            
            
            strcpy(cbuf, rkey);
            strcat(cbuf, rtype);
            strndel(tbuf, 15);
            if( strcmp(tbuf, cbuf) == 0 )
               {
               msgBox(hwndMainDlg, "Duplicate key!", "Connection not allowed because both parties have the same Registration Key!");
               SERVERON = FALSE;
               FILENOTIFY = FALSE;
               STILLWAITING = FALSE;
               NOWCONNECTED1 = FALSE;
               NOWCONNECTED2 = FALSE;
               NOWLISTENING = FALSE;
               WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
               strcpy(tmprcvbuf, "<<QUITNOWNC>>");
               so_cancel(globnsock);
               so_cancel(globsockt);
               so_cancel(globsock);
               DosBeep(800, 100);  
               DosBeep(1200, 50);  
               DosSleep(2000);
               makeTBar(); 
               WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 
               soclose(globnsock);
               soclose(globsock);
               soclose(globsockt);  
               return(-1); 
               }
            BYPASS = TRUE;
            }
            
         if( strncmp(tbuf, "<nchatfilter0", 13) == 0 )
            {
            if( strncmp(tbuf, "<nchatfilter00>", 15) == 0 )   // Get request for info
               {
               _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)16);
               BYPASS = TRUE;
               }
         
            if( strncmp(tbuf, "<nchatfilter01>", 15) == 0 )  // Get remote info
               {
               INT z;

            
               strndel(tbuf, 15);
            
               z = 0;
               do
                  {
                  rpVersion[z] = tbuf[z];
                  z++;
                  }
               while( tbuf[z] != '\xb0' );
               strndel(tbuf, z+1);
               rpVersion[z] = '\0';
               
               z = 0;
               do
                  {
                  rpFTPPort[z] = tbuf[z];
                  z++;
                  }
               while( tbuf[z] != '\xb0' );
               strndel(tbuf, z+1);
               rpFTPPort[z] = '\0';
            
               strcpy(rpIPAddress, tbuf);
               
               _beginthread(showRPInfo, NULL, BSTACK, (PVOID)0);
            
               // msgBox(hwndMainDlg, "rpVersion", rpVersion);
               // msgBox(hwndMainDlg, "rpFTPPort", rpFTPPort);
               // msgBox(hwndMainDlg, "rpIPAddress", rpIPAddress);
               BYPASS = TRUE;
               }
         
            if( strncmp(tbuf, "<nchatfilter02>", 15) == 0 )
               {
               BYPASS = TRUE;
               }
         
            if( strncmp(tbuf, "<nchatfilter03>", 15) == 0 )
               {
               BYPASS = TRUE;
               }
         
            if( strncmp(tbuf, "<nchatfilter04>", 15) == 0 )
               {
               BYPASS = TRUE;
               }
         
            if( strncmp(tbuf, "<nchatfilter05>", 15) == 0 )
               {
               BYPASS = TRUE;
               }
         
            if( strncmp(tbuf, "<nchatfilter06>", 15) == 0 )
               {
               BYPASS = TRUE;
               }
         
            if( strncmp(tbuf, "<nchatfilter07>", 15) == 0 )
               {
               BYPASS = TRUE;
               }
         
            if( strncmp(tbuf, "<nchatfilter08>", 15) == 0 )
               {
               BYPASS = TRUE;
               }
         
            if( strncmp(tbuf, "<nchatfilter09>", 15) == 0 )
               {
               BYPASS = TRUE;
               }
            }
         }      
         
      if( strcmp(tbuf, "<abortfilexmit>") == 0 )
         {
         if( FTPINPROGRESS )
            {
            FILENOTIFY = FALSE;
            FTPINPROGRESS = FALSE;
            WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
            WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, FALSE);
            WinEnableWindow(WinWindowFromID(hwndDlg, 1008), FALSE);
            TRANSFERMSG = FALSE;
            }
         BYPASS = TRUE;
         }
         
      if( strcmp(tbuf, "<attemptconnect>") == 0 )
         {
         CONMSG = TRUE;
         condat.hwndDlg = hwndDlg;
         condat.interval = 2;
         _beginthread(mailSendStatus, NULL, BSTACK, (PVOID)&condat);
         }  
            
      if( strcmp(tbuf, "<echotwomessage>") == 0 )
         ECHOTWO = TRUE;
          
      if( strcmp(tbuf, "<echoonemessage>") == 0 )
         {
         ECHOONE = TRUE;
         mmm = 3;
         _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)mmm);
         }
         
      if( strlen(tbuf) > 14 )
         {  
         if( strncmp(tbuf, "<rejectfilexmt", 14) == 0 )
            {
            FTPINPROGRESS = FALSE;
            WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
            STILLWAITING = FALSE;
            TRANSFERMSG = TRUE;
            condat.hwndDlg = hwndDlg;
            condat.interval = 4;
            soclose(ftpnsock);
            soclose(ftpsock);
            _beginthread(mailSendStatus, NULL, BSTACK, (PVOID)&condat);
            }
         }  
            
      if( strlen(tbuf) > 14 )
         {  
         if( strncmp(tbuf, "<acceptfilexmt", 14) == 0 )
            {
            if( !ABORTME )
               {
               FTPINPROGRESS = TRUE;
               TRANSFERMSG = TRUE;
               _beginthread(ftpConnect, NULL, BSTACK, NULL);
               }
            else
               {
               FTPINPROGRESS = FALSE;
               WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
               STILLWAITING = FALSE;
               TRANSFERMSG = TRUE;
               _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)7);
               }   
            }
         }
            
      if( strlen(tbuf) > 15 )
         {  
         strcpy(transfile, "");     
         if( strncmp(tbuf, "<requestfilexmt", 15) == 0 && !FTPINPROGRESS )
            {
            INT k;
            BOOL STOPHERE;
            
            
            FTPINPROGRESS = TRUE;
            WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, FALSE);
            TRANSFERMSG = TRUE;
            if( sizeof(transfile) > strlen(tbuf) )
               {
               strcpy(RFile, tbuf);
               strndel(RFile, 15);
               strcpy(transfile, RFile);
               k = 0;
               STOPHERE = FALSE;
               do
                  {
                  if( RFile[k] == '\xB0' )
                     {
                     STOPHERE = TRUE;
                     }
                  k++;
                  }
               while( !STOPHERE );
               RFile[k-1] = '\0';
               
               strndel(transfile, k);
               
               k = 0;
               do
                  {
                  k++;
                  }
               while(transfile[k] != ')');

               strcpy(packstorcvstr, transfile);
               strndel(packstorcvstr, k+2);
               packstorcvstr[strlen(packstorcvstr)-1] = '\0';
               transfile[k+1] = '\0';
               packstorcv = atoi(packstorcvstr);
               strcpy(ftPromptTB, "Accept this file transfer?");
               strcat(ftPromptTB, transfile);
               }
            else
               {
               strncpy(RFile, tbuf, MAXSTRING-1);
               RFile[MAXSTRING-1] = '\0';
               strndel(RFile, 15);
               strcpy(transfile, RFile);
               k = 0;
               STOPHERE = FALSE;
               do
                  {
                  if( RFile[k] == '\xB0' )
                     {
                     STOPHERE = TRUE;
                     }
                  k++;
                  }
               while( !STOPHERE );
               RFile[k-1] = '\0';
               
               strndel(transfile, k);
               
               k = 0;
               do
                  {
                  k++;
                  }
               while(transfile[k] != ')');

               strcpy(packstorcvstr, transfile);
               strndel(packstorcvstr, k+2);
               packstorcvstr[strlen(packstorcvstr)-1] = '\0';
               transfile[k+1] = '\0';
               packstorcv = atoi(packstorcvstr);
               strcpy(ftPromptTB, "Accept this file transfer?");
               strcat(ftPromptTB, transfile);
               }   
            _beginthread(flashFileButton, NULL, BSTACK, NULL);
            }
         }
            
      if( strcmp(tbuf, "<wakeupthedead!>") != 0 && strcmp(tbuf, "<connectmessage>") != 0 && strcmp(tbuf, "<attemptconnect>") != 0  && strcmp(tbuf, "<gotthewakeupok>") != 0 && !NEVERMIND  && !ECHOONE   && !ECHOTWO && !TRANSFERMSG && !BYPASS)
         {
         if( !NAMEID )
            {
            n = 0;
            do
               {
               if( tbuf[n] == '<' )
                  tbuf[n] = '[';
               n++;
               }
            while( tbuf[n] != '>' );
            tbuf[n] = ']';   
            strinsert(tbuf+n+1, ' ');
            }
         else
            NAMEID = FALSE;   

         if( pos > 0 )
            {
            strinsert(tbuf, '\x0a');
            strinsert(tbuf, '\x0d');
            }   
               
         pos = WinQueryWindowTextLength(WinWindowFromID(hwndDlg, 1000));
         WinSendMsg(WinWindowFromID(hwndDlg, 1000),
                           MLM_SETSEL,
                           MPFROMP(pos),
		   MPFROMP(pos));  
         MLEInsertText(hwndDlg, 1000, -1, tbuf);        
         pos = WinQueryWindowTextLength(WinWindowFromID(hwndDlg, 1000));
         WinSendMsg(WinWindowFromID(hwndDlg, 1000),
                           MLM_SETSEL,
		   MPFROMP(pos),
		   MPFROMP(pos));  
         }
      else
         {
         if( !BYPASS )
            {
            if( ECHOONE )
               {
               }
            if( ECHOTWO )
               {
               condat.hwndDlg = hwndDlg;
               condat.interval = 3;
               _beginthread(mailSendStatus, NULL, BSTACK, (PVOID)&condat);
               }
            }   
         }                    		         
      }   
   }   
while(SERVERON);      		      
makeTBar(); 
WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 
NOWCONNECTED2 = FALSE;
NOWCONNECTED1 = FALSE;
NOWLISTENING = FALSE;
return(1);
}




VOID showRPInfo(PVOID n)
{
HAB habT;
HMQ hmqT;
USHORT usReturn;
HWND hNewFrame;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

hNewFrame = OpenCONINFO(hwndMainDlg, 0);
usReturn = (USHORT) WinProcessDlg(hNewFrame);

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID sendQuitMSG(PVOID chkmaildat)
{
HAB habT;
HMQ hmqT;
INT mk, sopt;
HWND hwndDlg;
INT sock, rval, rv;
INT bytesend;
struct sockaddr_in server;
struct msghdr msg;
struct iovec iov[1];
CHAR conaddr[260];


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

hwndDlg = ((PFCBD)chkmaildat)->hwndDlg;

strcpy(conaddr, "0");
strcpy(tmpsendbuf, "<<QUITNOWNC>>");

sock_init();

sock = socket(PF_INET, SOCK_STREAM, 0);
setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (CHAR *)&sopt, sizeof(sopt));

if (sock < 0)
   {
   WinSetDlgItemText(hwndDlg, 1001, "Couldn't open socket!");
   WinDestroyMsgQueue(hmqT);
   WinTerminate(habT);
   _endthread();
   }
else
   {
   server.sin_family      = AF_INET;         
   server.sin_port        = htons((SHORT)pgmData[4]);               
   server.sin_addr.s_addr = inet_addr(conaddr); 
   
   
  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
      {
      soclose(sock);
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      } 
   
   if (send(sock, tmpsendbuf, strlen(tmpsendbuf)+1, 0) < 0)
      {
      soclose(sock);
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }
   
   soclose(sock);
   }


WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID attemptConnect(PVOID acdat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
INT rval, rv, kb;
INT sopt;



habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

ATTEMPTINGCONNECT = TRUE;
hwndDlg = hwndMainDlg;

kb = 0;

do
   {
   DosSleep(50);
   kb++;
   }
while( !NOWLISTENING && kb < 140 );
   
sock_init();

globsockt = socket(PF_INET, SOCK_STREAM, 0);
setsockopt(globsockt, SOL_SOCKET, SO_REUSEADDR, (CHAR *)&sopt, sizeof(sopt));

if (globsockt < 0)
   {
   WinSetDlgItemText(hwndDlg, 1001, "Couldn't open socket!");
    ATTEMPTINGCONNECT = FALSE;
   WinDestroyMsgQueue(hmqT);
   WinTerminate(habT);
   _endthread();
   }
else
   {
   INT rc, tries;
   

   tries = 0;
   do
      {
      if( tries > 0 )
         DosSleep(100);
      memset(&globservert, 0, sizeof(globservert));
      globservert.sin_family      = AF_INET;         
      globservert.sin_port        = htons((SHORT)pgmData[5]);               
      globservert.sin_addr.s_addr = inet_addr(guestIP); 
   
      rc = connect(globsockt, (struct sockaddr *)&globservert, sizeof(globservert));
      tries++;
      }
   while( rc != 0 && tries < 80 );   
   
   // if (connect(globsockt, (struct sockaddr *)&globservert, sizeof(globservert)) < 0)
   if ( rc < 0)
      {
      SENTALREADY = FALSE;
      ATTEMPTINGCONNECT = FALSE;
      _beginthread(canNOTConnect, NULL, BSTACK, NULL);
      soclose(globsockt);
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }
   else
      {
      NOWCONNECTED1 = TRUE;
      _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)4);
      _beginthread(chkKeyDupes, NULL, BSTACK, (PVOID)0);
      }   
   }
      
ATTEMPTINGCONNECT = FALSE;
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID attemptConnect2(PVOID acdat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
INT rval, rv, kb;
INT sopt;



habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

ATTEMPTINGCONNECT = TRUE;
hwndDlg = hwndMainDlg;

kb = 0;

do
   {
   DosSleep(50);
   kb++;
   }
while( !NOWLISTENING && kb < 140 );
   
sock_init();

globsockt = socket(PF_INET, SOCK_STREAM, 0);
setsockopt(globsockt, SOL_SOCKET, SO_REUSEADDR, (CHAR *)&sopt, sizeof(sopt));

if (globsockt < 0)
   {
   WinSetDlgItemText(hwndDlg, 1001, "Couldn't open socket!");
    ATTEMPTINGCONNECT = FALSE;
   WinDestroyMsgQueue(hmqT);
   WinTerminate(habT);
   _endthread();
   }
else
   {
   INT rc, tries;
   struct hostent *hi;  //*
   

    hi = gethostbyname(guestIP);
    bcopy(hi->h_addr, &globservert.sin_addr, hi->h_length); //*
   
   tries = 0;
   do
      {
      if( tries > 0 )
         DosSleep(100);
      memset(&globservert, 0, sizeof(globservert));
      globservert.sin_family      = AF_INET;         
      globservert.sin_port        = htons((SHORT)pgmData[5]);               
      // globservert.sin_addr.s_addr = inet_addr(guestIP); 
      bcopy(hi->h_addr, &globservert.sin_addr, hi->h_length); //*
   
      rc = connect(globsockt, (struct sockaddr *)&globservert, sizeof(globservert));
      tries++;
      }
   while( rc != 0 && tries < 80 );   
   
   // if (connect(globsockt, (struct sockaddr *)&globservert, sizeof(globservert)) < 0)
   if ( rc < 0)
      {
      SENTALREADY = FALSE;
      ATTEMPTINGCONNECT = FALSE;
      _beginthread(canNOTConnect, NULL, BSTACK, NULL);
      soclose(globsockt);
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }
   else
      {
      NOWCONNECTED1 = TRUE;
      _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)4);
      _beginthread(chkKeyDupes, NULL, BSTACK, (PVOID)0);
      }   
   }
      
ATTEMPTINGCONNECT = FALSE;
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID chkKeyDupes(PVOID var)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
INT kv;
      

habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);


do
   {
   DosSleep(250);
   }
while( ( NOWCONNECTED1 && !NOWCONNECTED2)  );   
_beginthread(sendOneMSG, NULL, BSTACK, (PVOID)13);
DosSleep(1000);
_beginthread(sendOneMSG, NULL, BSTACK, (PVOID)14);



WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID sendOneMSG(PVOID mdd)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
INT sock, rval, rv;
INT bytesend;
struct sockaddr_in server;
struct msghdr msg;
struct iovec iov[1];
CHAR onebuf[MSGSIZE];
CHAR typemsg[1024];
INT namelen;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

if( (INT)mdd == 0 )
   {
   strcpy(typemsg, "connectmessage");
   } 

if( (INT)mdd == 1 )
   {
   strcpy(typemsg, "localctmessage");
   }
      
if( (INT)mdd == 2 )
   {
   strcpy(typemsg, "echoonemessage");
   }
      
if( (INT)mdd == 3 )
   {
   strcpy(typemsg, "echotwomessage");
   }
      
if( (INT)mdd == 4 )
   {
   strcpy(typemsg, "attemptconnect");
   }
      
if( (INT)mdd == 5 )
   {
   strcpy(typemsg, "requestfilexmt");
   strcat(typemsg, SFile);
   strcat(typemsg, SFileSize);
   }
      
if( (INT)mdd == 6 )
   {
   do
      {
      if( !FTPSERVERLISTENING )
         DosSleep(100);
      }
   while( !FTPSERVERLISTENING && FTPINPROGRESS );   
   strcpy(typemsg, "acceptfilexmt");
   }
      
if( (INT)mdd == 7 )
   {
   strcpy(typemsg, "rejectfilexmt");
   }
      
if( (INT)mdd == 8 )
   {
   strcpy(typemsg, "receivedpacketok");
   }
      
if( (INT)mdd == 9 )
   {
   strcpy(typemsg, "gotthewakeupok");
   }
      
if( (INT)mdd == 10 )
   {
   strcpy(typemsg, "wakeupthedead!");
   }
      
if( (INT)mdd == 11 )
   {
   strcpy(typemsg, "<<QUITNOWNC>>");
   }
      
if( (INT)mdd == 12 )
   {
   strcpy(typemsg, "abortfilexmit");
   }
      
if( (INT)mdd == 13 )
   {
   strcpy(typemsg, "nchatfilterID");
   }
      
if( (INT)mdd == 14 )
   {
   strcpy(typemsg, "ncfilterRNAME");
   }
      
if( (INT)mdd == 15 )
   {
   strcpy(typemsg, "nchatfilter00");
   }
   
if( (INT)mdd == 16 )
   {
   strcpy(typemsg, "nchatfilter01");
   }
   
if( (INT)mdd != 2 && (INT)mdd != 3 )      
   DosSleep(550);

if( (INT)mdd == 11 )
   {
   strcpy(onebuf, typemsg);
   }
else
   {
   strcpy(onebuf, localIP);
   strcat(onebuf, "<");
   strcat(onebuf, typemsg);
   strcat(onebuf, ">");
   }   
   
if( (INT)mdd == 13 )
   {
   if( registered(ncpw) )
      {
      strcat(onebuf, rkey);   
      strcat(onebuf, rtype);   
      }
   else
      {
      strcat(onebuf, "UNREGISTERED");   
      }   
   }
   
if( (INT)mdd == 14 )
   {
   if( registered(ncpw) )
      {
      strcat(onebuf, rname);
      if( strcmp(rtype, "one") == 0 )  
         strcat(onebuf, " (Main Key)");
      if( strcmp(rtype, "two") == 0 )   
         strcat(onebuf, " (Guest Key)");
      }
   else
      {
      strcat(onebuf, "An UNREGISTERED user");
      }      
   }
   
if( (INT)mdd == 16 )
   {
   CHAR info[260];
   CHAR ftpstr[80];
   
   strcpy(info, "");
   strcpy(ftpstr, "");
   itoa((INT)pgmData[8], ftpstr, 10);
   strcpy(info, ncversion);
   strcat(info, "\xB0"); 
   strcat(info, ftpstr); 
   strcat(info, "\xB0"); 
   strcat(info, localIP); 
   strcat(onebuf, info);
   }
   

if (send(globsockt, onebuf, strlen(onebuf)+1, 0) < 0)
   {
   if( (INT)mdd == 5 )
      {
      STILLWAITING = FALSE;
      msgBox(hwndMainDlg, "Attention!", "File transfer request failed.");
      }
   if( (INT)mdd == 6 )
      {
      STILLWAITING = FALSE;
      soclose(ftpcsock);
      }
   soclose(globsockt);
   WinDestroyMsgQueue(hmqT);
   WinTerminate(habT);
   _endthread();
   }
else
   {
   if( (INT)mdd == 5 )
      {
      STILLWAITING = TRUE;
      _beginthread(requestFTD, NULL, BSTACK, (PVOID)0);
      }
   }   
    
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID canNOTConnect(PVOID var)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
INT kv;
      

habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

for( kv=0;kv<3;kv++ )
   {
   WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "");
   DosSleep(200);
   WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "Could NOT connect!");
   DosSleep(700);
   }
   
makeTBar(); 
WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID NOTConnected(PVOID var)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
INT kv;
      

habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

for( kv=0;kv<1;kv++ )
   {
   DosBeep(1200, 50);
   WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "Message NOT sent.  Connection may be broken!");
   DosSleep(2000);
   }
   
makeTBar(); 

WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID sendMSG(PVOID chkmaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
INT sock, rval, rv;
INT bytesend;
USHORT msgport;
struct sockaddr_in server;
struct msghdr msg;
struct iovec iov[1];
CHAR conaddr[260];
INT namelen;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

hwndDlg = ((PFCBD)chkmaildat)->hwndDlg;

if( strlen(guestIP) == 0 )
   strcpy(conaddr, "0");
else   
   strcpy(conaddr, guestIP);

if( pgmData[4] <= 0 ||  pgmData[5] <= 0 || strlen(conaddr) == 0 || strlen(tmpsendbuf) == 0 )   
// if( strlen(conaddr) == 0 || strlen(tmpsendbuf) == 0 )   
   {
   WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);	  
   WinDestroyMsgQueue(hmqT);
   WinTerminate(habT);
   _endthread();
   }

strcpy(sendbuf, localIP);
strcat(sendbuf, "<");
strcat(sendbuf, nickName);
strcat(sendbuf, ">");
strcat(sendbuf, tmpsendbuf);

if (send(globsockt, sendbuf, strlen(sendbuf)+1, 0) < 0)
   {
   WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);	  
   soclose(globsockt);
   _beginthread(NOTConnected, NULL, BSTACK, NULL);
   WinDestroyMsgQueue(hmqT);
   WinTerminate(habT);
   _endthread();
   }

WinEnableWindow(WinWindowFromID(hwndDlg, 1001), TRUE);	  

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




ULONG getFSize(CHAR *file)
{
FILESTATUS3  fsts3ConfigInfo = {{0}};
ULONG            ulBufSize     = sizeof(FILESTATUS3);
HFILE             hfile      = 0;
ULONG            ulAction  = 0;


DosOpen(file,
             &hfile,
             &ulAction,
             0L,0L,
             OPEN_ACTION_FAIL_IF_NEW |
             OPEN_ACTION_OPEN_IF_EXISTS,
             OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READONLY |
             OPEN_SHARE_DENYNONE, 0L);
             
DosQueryFileInfo(hfile,
                        FIL_STANDARD,
                        &fsts3ConfigInfo,
                        ulBufSize);

DosClose(hfile);

return(fsts3ConfigInfo.cbFile);
}




INT sendFile(HWND hwnd, CHAR *fn)
{
HWND hwndFile;
char pszTitle[]="File Transfer";
char pszOKButton[]="~Send file";
char pszFullFile[]="";
CHAR nbstr[40];
div_t   dvt;
INT packets;
CHAR packetstr[80];
ULONG siz;


memset(&SFileDlg, 0, sizeof(FILEDLG));
if(strlen(DEFULDIR) > 1)
   {
   if( DEFULDIR[strlen(DEFULDIR)-1] != '\\' )
      strcat(DEFULDIR, "\\");
   strcpy(SFileDlg.szFullFile, DEFULDIR);
   }
SFileDlg.cbSize = sizeof(FILEDLG);
SFileDlg.fl = FDS_OPEN_DIALOG | FDS_CENTER | FDS_ENABLEFILELB;
SFileDlg.pfnDlgProc = (PFNWP)sendFileProc;
SFileDlg.pszTitle = pszTitle;
SFileDlg.pszOKButton = pszOKButton;

hwndFile = WinFileDlg(HWND_DESKTOP, hwnd, &SFileDlg);
   
if( hwndFile && SFileDlg.lReturn != DID_OK )
   {
   FTPINPROGRESS = FALSE;
   WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
   strcpy(SFileDlg.szFullFile, "");
   strcpy(SPath, "");
   strcpy(SFile, "");
   strcpy(FQSFile, "");
   return(0);
   }

/*   
if( !registered(ncpw) )
   {
   USHORT usReturn;
   HWND hNewFrame;
   
   
   hNewFrame = OpenABOUT(hwndMainDlg, 0);
   usReturn = (USHORT) WinProcessDlg(hNewFrame);
   }
*/

strcpy(FQSFile, SFileDlg.szFullFile);
strcpy(SFile, FQSFile+strlen(SPath));

siz = getFSize(FQSFile);
dvt = div(siz, FILEXMTSIZE);
if( dvt.rem != 0 )
   packets = dvt.quot + 1;
else   
   packets = dvt.quot;
itoa(packets, packetstr, 10);
packstosend = packets;
strcpy(packstosendstr, packetstr);

ltoa(siz, nbstr, 10);
strcpy(SFileSize, "\xB0");
strcat(SFileSize, "  (");
strcat(SFileSize, nbstr);
strcat(SFileSize, " bytes) ");
strcat(SFileSize, packetstr);

WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, TRUE);
_beginthread(sendOneMSG, NULL, BSTACK, (PVOID)5);

return(1);   
}




MRESULT EXPENTRY sendFileProc(HWND hwndDlg, ULONG msg,
                                                MPARAM mp1, MPARAM mp2 )
{
switch ( msg )
   {
   case WM_INITDLG:
      WinSendDlgItemMsg(hwndDlg, DID_FILENAME_ED,EM_SETTEXTLIMIT,
		  MPFROM2SHORT(MAXSTRING,0),NULL);
      WinSetDlgItemText(hwndDlg, DID_FILENAME_TXT, "Send filename:");
      WinDefFileDlgProc( hwndDlg, msg, mp1, mp2 );
      
      
   case WM_CONTROL:
      switch (SHORT2FROMMP (mp1))
	 {
	 case LN_SELECT:
	    if (SHORT1FROMMP (mp1) == 266)
	       {
	       LONG sel;
	       CHAR ft[] = "File transfer  -  selected file : ";
	       CHAR tb[MAXSTRING];
	       CHAR fna[MAXSTRING];
	       CHAR fqf[MAXSTRING];
	       CHAR num[40];
	       ULONG fs;
	       
	       
                   sel = (LONG)WinSendDlgItemMsg(hwndDlg, 266,
                                                               LM_QUERYSELECTION,
                                                               MPFROMLONG(LIT_FIRST),
                                                               MPFROMLONG(0));
                   if(sel >=0)
                      WinSendDlgItemMsg(hwndDlg, 266,
                                                 LM_QUERYITEMTEXT,
                                                 MPFROM2SHORT(sel, sizeof(fna)), MPFROMP(fna));
	       
	       strcpy(fqf, SFileDlg.szFullFile);
	       if(strlen(fna) > 0)
	          {
	          if(fqf[strlen(fqf)-1] != '\\')
	             strcat(fqf, "\\");
	          strcat(fqf, fna);
	          fs = getFSize(fqf);   
                      ltoa(fs, num, 10);
	          strcpy(tb, ft);
	          strcat(tb, num);
	          strcat(tb, "  bytes");
	          WinSetWindowText(WinWindowFromID(hwndDlg, FID_TITLEBAR), tb);
	          }
	       }
	       break;

	 default:
	    break;
	 }
      return WinDefFileDlgProc( hwndDlg, msg, mp1, mp2 );


   case WM_COMMAND :
      switch( SHORT1FROMMP( mp1 ) )
         {
         case DID_CANCEL :
            WinDismissDlg(hwndDlg, TRUE);
            break;

         case DID_OK :
            strcpy(SPath, SFileDlg.szFullFile);
            // bugem(hwndDlg);
            WinDismissDlg(hwndDlg, TRUE);
	 break;
         }
         break;
   }
return WinDefFileDlgProc( hwndDlg, msg, mp1, mp2 );
}




VOID requestFTD(PVOID n)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

ABORTME = FALSE;
hwndDlg = hwndMainDlg;

if( pgmData[19] )
   {
   DosBeep(900, 50);
   DosBeep(1500, 50);
   DosBeep(1200, 50);
   DosBeep(900, 50);
   }

do
   {
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Waiting for file transfer decision");
   DosSleep(100);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Waiting for file transfer decision .");
   DosSleep(100);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Waiting for file transfer decision ..");
   DosSleep(100);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Waiting for file transfer decision ...");
   DosSleep(100);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Waiting for file transfer decision ....");
   DosSleep(100);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Waiting for file transfer decision .....");
   DosSleep(100);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Waiting for file transfer decision ......");
   DosSleep(100);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Waiting for file transfer decision .......");
   DosSleep(100);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Waiting for file transfer decision ........");
   DosSleep(100);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Waiting for file transfer decision .........");
   DosSleep(100);
   }
while(STILLWAITING && !ABORTME);   

if( ABORTME )
   {
   makeTBar(); 
   WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 
   }
   
WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, FALSE);
WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID flashFileButton()
{
HAB habT;
HMQ hmqT;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

FILENOTIFY = TRUE;
WinEnableWindow(WinWindowFromID(hwndMainDlg, 1008), TRUE);
do
   {
   if( pgmData[15] )
      {
      DosBeep(100, 50);
      WinSetWindowText(WinWindowFromID(hwndMainDlg, 1008), "~Incoming file");
      DosSleep(800);
      WinSetWindowText(WinWindowFromID(hwndMainDlg, 1008), "");
      DosSleep(350);
      }
   else
      {
      WinSetWindowText(WinWindowFromID(hwndMainDlg, 1008), "~Incoming file");
      DosSleep(800);
      WinSetWindowText(WinWindowFromID(hwndMainDlg, 1008), "");
      DosSleep(400);
      }   
   }
while(FILENOTIFY);   
      
WinSetWindowText(WinWindowFromID(hwndMainDlg, 1008), "~Incoming file");

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID handleXmtRequest()
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

hwndDlg = hwndMainDlg;

if( receiveFile(hwndMainDlg) == 1 )
   {
   FTPSERVERLISTENING = FALSE;   
   _beginthread(ftpServer, NULL, BSTACK, NULL);
   _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)6);
   }
else
   {
   FTPINPROGRESS = FALSE;
   WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
   _beginthread(sendOneMSG, NULL, BSTACK, (PVOID)7);
   }   
      
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}





INT receiveFile(HWND hwnd)
{
HWND hwndFile;
char pszOKButton[]="~Accept file";
char pszTitle[]="Do you want to accept this file transfer?";
char pszFullFile[]="";

  
memset(&RFileDlg, 0, sizeof(FILEDLG));
if(strlen(DEFDLDIR) > 1)
   {
   if( DEFDLDIR[strlen(DEFDLDIR)-1] != '\\' )
      strcat(DEFDLDIR, "\\");
   strcpy(RFileDlg.szFullFile, DEFDLDIR);
   }
RFileDlg.cbSize = sizeof(FILEDLG);
RFileDlg.fl = FDS_SAVEAS_DIALOG | FDS_CENTER | FDS_ENABLEFILELB;
RFileDlg.pfnDlgProc = (PFNWP)receiveFileProc;
RFileDlg.pszTitle = NULL;
RFileDlg.pszOKButton = pszOKButton;

hwndFile = WinFileDlg(HWND_DESKTOP, hwnd, &RFileDlg);
   
if( hwndFile && RFileDlg.lReturn != DID_OK )
   {
   strcpy(RFileDlg.szFullFile, "");
   strcpy(RPath, "");
   strcpy(RFile, "");
   strcpy(FQRFile, "");
   return(0);
   }

strcpy(FQRFile, RFileDlg.szFullFile);

return(1);   
}




INT existPath(CHAR *dstr)
{
CHAR dest[260];

if( strlen(dstr) > MAXSTRING )
   return(0);
strcpy(dest, dstr);
if( dest[strlen(dest)-1] == '\\' )
   dest[strlen(dest)-1] = '\0';
if( WinQueryObject(dest) == NULLHANDLE )
   return(0);
else
   return(1);
}




MRESULT EXPENTRY receiveFileProc(HWND hwndDlg, ULONG msg,
                                                MPARAM mp1, MPARAM mp2 )
{
switch ( msg )
   {
   case WM_INITDLG:
      {
      WinSendDlgItemMsg(hwndDlg, DID_FILENAME_ED,EM_SETTEXTLIMIT,
		  MPFROM2SHORT(MAXSTRING,0),NULL);
      WinSetDlgItemText(hwndDlg, FID_TITLEBAR, ftPromptTB);
      WinSetDlgItemText(hwndDlg, DID_FILENAME_ED, RFile);
      }		  
      WinDefFileDlgProc( hwndDlg, msg, mp1, mp2 );

   case WM_COMMAND :
      switch( SHORT1FROMMP( mp1 ) )
         {
         case DID_CANCEL :
            WinDismissDlg(hwndDlg, TRUE);
            break;

         case DID_OK :
            {
            CHAR rfpfqf[MAXSTRING];
            CHAR rfpnam[MAXSTRING];
            
            strcpy(rfpfqf, RFileDlg.szFullFile);
            if( rfpfqf[strlen(rfpfqf)-1] != '\\' )
               strcat(rfpfqf, "\\");
            WinQueryDlgItemText(hwndDlg, 258, sizeof(rfpnam), rfpnam);   
            strcat(rfpfqf, rfpnam);
            if( existFile(rfpfqf) )
               {
               msgBox(hwndDlg, "Attention!", "File aready exists! Rename file to download it.");
               return(0);
               }
            // bugem(hwndDlg);
            WinDismissDlg(hwndDlg, TRUE);
            }
	break;
         }
         break;
   }
return WinDefFileDlgProc( hwndDlg, msg, mp1, mp2 );
}




VOID ftpConnect()
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
INT rval, rv;
INT sopt;
INT divrold;
BOOL ALLBYTESSENT;
HFILE hfile;
ULONG ulAction;

CHAR tn[20];


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

hwndDlg = hwndMainDlg;

ALLBYTESSENT = FALSE;
ABORTME = FALSE;

// DosSleep(100);

sock_init();

ftpcsock = socket(PF_INET, SOCK_STREAM, 0);
setsockopt(ftpcsock, SOL_SOCKET, SO_REUSEADDR, (CHAR *)&sopt, sizeof(sopt));

if (ftpcsock < 0)
   {
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Transfer failed : could not create socket!"); 
   DosSleep(800);
   makeTBar(); 
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg); 
   FTPINPROGRESS = FALSE;
   WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
   WinDestroyMsgQueue(hmqT);
   WinTerminate(habT);
   _endthread();
   }
else
   {
   INT rc, tries;
   
   
   tries = 0;
   do
      {
      memset(&ftpserverc, 0, sizeof(ftpserverc));
      ftpserverc.sin_family      = AF_INET;         
      ftpserverc.sin_port        = htons(pgmData[8]);               
      ftpserverc.sin_addr.s_addr = inet_addr(guestIP); 

      if( tries > 0 ) 
         DosSleep(100);
      rc = connect(ftpcsock, (struct sockaddr *)&ftpserverc, sizeof(ftpserverc));
      tries++;
      }
   while( rc != 0 && tries < 80 );   
   
   if ( rc < 0)
      {
      STILLWAITING = FALSE;
      SENTALREADY = FALSE;
      _beginthread(canNOTConnect, NULL, BSTACK, NULL);
      FTPINPROGRESS = FALSE;
      WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
      soclose(ftpcsock);
      makeTBar(); 
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }
   else
      {
      INT bsend, brcv;
      CHAR onechunk[FILEXMTSIZE+EOSIZE];
      CHAR eofmsg[FILEXMTSIZE+EOSIZE];  // greater than 512
      CHAR confirm[FTPHDRSIZE+1];
      

      if( DosOpen(FQSFile, 
                       &hfile,
                       &ulAction,
                       0L,
                       FILE_NORMAL,
                       OPEN_ACTION_FAIL_IF_NEW | OPEN_ACTION_OPEN_IF_EXISTS,
                       OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE | OPEN_FLAGS_SEQUENTIAL, NULL) != 0  )
         {
         }
      else
         { 
         INT packs;
 
 
         packs = 0;  
         divrold = -1;
         do
            {
            if( ABORTME )
               {
               STILLWAITING = FALSE;
               DosClose(hfile);
               bsend = -1;
               }
            else
               {   
               bsend = readchunk(hfile, onechunk);
               if( bsend == 0 )
                  {
                  DosClose(hfile);
                  onechunk[0] = 'E';
                  onechunk[1] = '_';
                  onechunk[2] = 'O';
                  onechunk[3] = 'F';
                  onechunk[4] = '_';
                  onechunk[5] = 'F';
                  onechunk[6] = '\0';
                  if( send(ftpcsock, onechunk, 7, 0) >= 0 )
                     {
                     CHAR readout[20];
                     
                     strcpy(readout, "Pct. sent : 100%");
                     WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), readout);
                     DosSleep(2000);
                     ALLBYTESSENT = TRUE;
                     }
                  }
               else
                  {
                  div_t  divr;
                  CHAR pctstr[40];
                  CHAR readout[20];
                  

                  onechunk[bsend] = '@';
                  onechunk[bsend+1] = ')';
                  onechunk[bsend+2] = '+';
                  onechunk[bsend+3] = '~';
                  onechunk[bsend+4] = '(';
                  onechunk[bsend+5] = '@';
                  onechunk[bsend+6] = '\0';
                  STILLWAITING = FALSE;
                  if (send(ftpcsock, onechunk, bsend+EOSIZE, 0) < 0)
                     {
                     bsend = 0;
                     }
                  else
                     {
                     packs++;
                     divr = div(packs*100, packstosend);
                     if( divr.quot > divrold )
                        { 
                        itoa(divr.quot, pctstr, 10);
                        strcpy(readout, "Pct. sent : ");
                        strcat(readout, pctstr);
                        strcat(readout, "%");
                        WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), readout);
                        }
                     divrold = divr.quot;   
                     if( recv(ftpcsock, confirm, sizeof(confirm), 0) < 0 )
                        bsend = 0;
                     }
                  }
               }   
            }
         while( bsend > 0 );
               
         WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
         DosClose(hfile);
         }
      }   
   }


DosClose(hfile);
STILLWAITING = FALSE;
FTPINPROGRESS = FALSE;
WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
if( ALLBYTESSENT )
   {
   if( pgmData[29] )
      {
      DosBeep(1100, 50);
      DosBeep(1500, 50);
      DosBeep(2000, 50);
      DosBeep(1000, 50);
      } 
   WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "File was successfully sent!"); 
   }
else   
   {
   if( pgmData[30] )
      {
      DosBeep(100, 50);
      DosBeep(150, 50);
      DosBeep(200, 50);
      DosBeep(100, 50);
      }
   if( ABORTME )
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "File was ABORTED!"); 
   else
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "File was NOT successfully sent!"); 
   }
DosSleep(3000);      
makeTBar(); 
WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 
soclose(ftpcsock);
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID ftpServer()
{
HAB habT;
HMQ hmqT;
INT i, sopt;
HWND hwndDlg;
ULONG len, pos;
ULONG fgndcolor;
HFILE hfilew;
APIRET apiret;
ULONG ulAction, ulBufferSize, ulBytesWritten, newP;
BOOL ALLBYTESRECEIVED;
INT endoffile;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

hwndDlg = hwndMainDlg;

WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, TRUE);
WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Attempting file transfer ..."); 
ABORTME = FALSE;
ALLBYTESRECEIVED = FALSE;
sopt = 1;
sock_init();

ftpsock = socket(PF_INET, SOCK_STREAM, 0);
setsockopt(ftpsock, SOL_SOCKET, SO_REUSEADDR, (CHAR *)&sopt, sizeof(sopt));

if (ftpsock < 0)
   {
   FTPINPROGRESS = FALSE;
   WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, FALSE);
   WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Transfer failed : could not create socket!"); 
   DosSleep(800);
   makeTBar(); 
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg); 
   soclose(ftpsock);
   WinDestroyMsgQueue(hmqT);
   WinTerminate(habT);
   _endthread();
   }
else
   {
   int namelen;


   memset(&ftpserver, 0, sizeof(ftpserver));
   ftpserver.sin_family = AF_INET;
   ftpserver.sin_addr.s_addr = inet_addr(localIP);
   ftpserver.sin_port = htons(pgmData[8]);
      
   namelen = sizeof(ftpserver);
      
   if (bind(ftpsock, (struct sockaddr *)&ftpserver, sizeof(ftpserver)) < 0)
      {
      FTPINPROGRESS = FALSE;
      WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, FALSE);
      WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
      WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Transfer failed : could not bind to socket!"); 
      DosSleep(800);
      makeTBar(); 
      WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg); 
      soclose(ftpsock);
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }

   if (listen(ftpsock, 1) != 0)
      {
      FTPINPROGRESS = FALSE;
      WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, FALSE);
      WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
      WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Transfer failed : could not listen on socket!"); 
      DosSleep(800);
      makeTBar(); 
      WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg); 
      soclose(ftpsock);   
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }
   else
      FTPSERVERLISTENING = TRUE;   
      
   memset(&ftpclient, 0, sizeof(ftpclient));
   if ((ftpnsock = accept(ftpsock, (struct sockaddr *)&ftpclient, &namelen)) == -1)
      {
      FTPINPROGRESS = FALSE;
      WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, FALSE);
      WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
      WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Transfer failed : Failed to accept connection!"); 
      DosSleep(800);
      makeTBar(); 
      WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg); 
      }
   else
      {
      INT packs, divrold;
      
       
      FTPINPROGRESS = TRUE; 
      setsockopt(ftpnsock, SOL_SOCKET, SO_REUSEADDR, (CHAR *)&sopt, sizeof(sopt));
      strcpy(guestIP, inet_ntoa(ftpclient.sin_addr));
      apiret = DosOpen(FQRFile,
		       &hfilew,
		       &ulAction,
		       0L,
		       FILE_NORMAL,
		       OPEN_ACTION_CREATE_IF_NEW  | OPEN_ACTION_FAIL_IF_EXISTS,
		       OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYWRITE | OPEN_FLAGS_SEQUENTIAL, NULL);
      divrold = -1;		       
      packs = 0;		       
      if( apiret == 0 )
         {
         do
            {
            INT lnum, br;
            CHAR partchunk[FILEXMTSIZE+EOSIZE];
            CHAR wholechunk[FILEXMTSIZE+EOSIZE];
            CHAR confirm[FTPHDRSIZE+1] = "[OKCHUNK]";


            memset(&wholechunk, 0, sizeof(wholechunk));
            memset(&partchunk, 0, sizeof(partchunk));
            endoffile = 1;
            lnum = 0;
            br = 0;
             
            do
               {                
               br = recv(ftpnsock, partchunk, sizeof(partchunk), 0);
               getmsgchunk(lnum, br, wholechunk, partchunk);
               lnum += br;
               endoffile = checkchunk(wholechunk, lnum);
               }
            while( endoffile == 1 && br > 0 );   
               
            if( (lnum-EOSIZE) > 0 )
               {
               APIRET ret;
               
               
               ret = 0;
               if( endoffile == 0 )
                  ret = DosWrite(hfilew, &wholechunk, lnum-EOSIZE, &ulBytesWritten);
               if( ret != 0 )
                  endoffile = -1; 
               else
                  {
                  div_t  divr;
                  float pctg;
                  CHAR pctstr[40];
                  CHAR readout[20];
                  
                  if( endoffile != -1 && endoffile != -2 )
                     {
                     if( send(ftpnsock, confirm, sizeof(confirm), 0) < 0 )
                        endoffile = -1;
                     packs++;
                     divr = div(packs*100, packstorcv);
                     if( divr.quot > divrold )
                        { 
                        itoa(divr.quot, pctstr, 10);
                        strcpy(readout, "Pct. received : ");
                        strcat(readout, pctstr);
                        strcat(readout, "%");
                        WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), readout);
                        }
                     divrold = divr.quot;   
                     }
                  else
                     {
                     if( endoffile == -2 )
                        {
                        CHAR readout[20];
                        
                        strcpy(readout, "Pct. received : 100%");
                        WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), readout);
                        ALLBYTESRECEIVED = TRUE;
                        DosSleep(2000);
                        }
                     }      
                  }   
               }
            else
               {
               if( endoffile == -2 )
                  {
                  CHAR readout[20];
                        
                  strcpy(readout, "Pct. received : 100%");
                  WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), readout);
                  ALLBYTESRECEIVED = TRUE;
                  DosSleep(2000);
                  }
               else   
                  endoffile = -1;      
               }
            if( ABORTME )
               {
               if( endoffile != -2 )
                  {
                  endoffile = -3;
                  DosClose(hfilew);
                  DosDelete(FQRFile);
                  }
               }   
            }
         while( endoffile == 0 );   
         DosClose(hfilew);
         }
      else
         {
         msgBox(hwndMainDlg, "Attention!", "Could NOT open file may already exist!");
         }   
      DosClose(hfilew);
      }      
   DosClose(hfilew);
   }

DosClose(hfilew);
soclose(ftpnsock);
soclose(ftpsock);

FTPINPROGRESS = FALSE; 
WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, FALSE);
WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, TRUE);
if( ALLBYTESRECEIVED )
   {
   if( endoffile == -2 )
      {
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "File successfully received!"); 
      if( pgmData[22] )
         {
         DosBeep(1100, 50);
         DosBeep(1500, 50);
         DosBeep(2000, 50);
         DosBeep(1000, 50);
         }
      }
   else
      {   
      DosDelete(FQRFile);
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "File was NOT received successfully !"); 
      if( pgmData[23] )
         {
         DosBeep(100, 50);
         DosBeep(150, 50);
         DosBeep(200, 50);
         DosBeep(100, 50);
         }
      }
   }
else
   {
   if( endoffile == -3 )
      {
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "File transfer ABORTED!"); 
      if( pgmData[23] )
         {
         DosBeep(100, 100);
         DosBeep(150, 150);
         DosBeep(200, 150);
         DosBeep(100, 100);
         }
      }
   else
      {   
      DosDelete(FQRFile);
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "File was NOT received successfully!"); 
      if( pgmData[23] )
         {
         DosBeep(100, 50);
         DosBeep(150, 50);
         DosBeep(200, 50);
         DosBeep(100, 50);
         }
      }
   }   
DosSleep(3000);
makeTBar();
WinSetDlgItemText(hwndMainF, FID_TITLEBAR, tbarmsg); 
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




INT getmsgchunk(INT sp, INT brd, CHAR *tmp, CHAR *dStr)
{
INT cw, iter;
BOOL ENDRCV;


for( iter=0;iter<brd;iter++ )
   {
   tmp[sp] = dStr[iter];
   sp++;
   }
   
return(sp);
}




INT checkchunk(CHAR *chunk, INT blen)
{
INT cw, iter;
BOOL ENDRCV;
INT ret;
CHAR regchunk[] = "[REGCHUNK]";
CHAR eofchunk[] = "[EOFCHUNK]";

if( blen >= 7 )
   {
   if(chunk[blen-1] == '\0' && chunk[blen-2] == '@' && chunk[blen-3] == '(' && chunk[blen-4] == '~' && 
      chunk[blen-5] == '+' && chunk[blen-6] == ')' && chunk[blen-7] == '@' )
      return(0);
   
   if(chunk[blen-1] == '\0' && chunk[blen-2] == 'F' && chunk[blen-3] == '_' && chunk[blen-4] == 'F' && 
      chunk[blen-5] == 'O' && chunk[blen-6] == '_' && chunk[blen-7] == 'E' )
      return(-2);
   }
else
   return(-1);      
        
return(1);
}





INT writechunk(CHAR *chunk, INT bytes)
{
HFILE hfile;
APIRET apiret;
ULONG ulAction, ulBufferSize, ulBytesWritten, newP;

ulBufferSize = bytes;
apiret = DosOpen(FQRFile,
		 &hfile,
		 &ulAction,
		 ulBufferSize,
		 FILE_NORMAL,
		 OPEN_ACTION_CREATE_IF_NEW  | OPEN_ACTION_OPEN_IF_EXISTS,
		 OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYWRITE | OPEN_FLAGS_SEQUENTIAL, NULL);

if( apiret != 0 )
   {
   DosClose(hfile);
   return(-1);
   }
   		 
DosSetFilePtr(hfile, 0, FILE_END, &newP);
   
DosWrite(hfile, &chunk, ulBufferSize, &ulBytesWritten);
DosClose(hfile);
return(ulBytesWritten);
}




INT readchunk(HFILE hfile, CHAR *chunkbuf)
{
ULONG ulBytesRead;


if( DosRead(hfile, (PVOID)chunkbuf,
                 FILEXMTSIZE, &ulBytesRead) )
   {
   return(0);
   }

return(ulBytesRead);
}




VOID runArgs(PVOID n)
{
HAB habT;
HMQ hmqT;
INT marg;

habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);


marg  = (INT)n;

DosSleep(4000);
switch(marg)
   {
   case 1:
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(1002, 0), 0);
      break;
      
   case 2:
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(1006, 0), 0);
      break;
      
   case 3:
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(263, 0), 0);
      break;
      
   default:
      break;   
   }

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




BOOL chkCommand(SHORT mp1)
{
switch(mp1)
   {
   case ID_MAIN2SENDFILE :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(275, 0), 0);
      }
      return(TRUE);
         
   case ID_MAIN2ABORTTRANSFER :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(282, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN2DISCONNECT :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(IDM_CLOSECONNECTION, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN2LISTEN :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(IDM_CONNECT, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN2CONNECT :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(IDM_WINDOWSTYLE, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN2WAKEUP :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(279, 0), 0);
      }
      return(TRUE);
      
   case ID_RPINFO :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(268, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN2UPLOADDIR :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(265, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN2DOWNLOADDIR :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(284, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN2WORDWRAP :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(264, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN2PASTE :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(262, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN2CLEAR :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(280, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN2GETCURIP :
      {
      USHORT usReturn;
      HWND hNewFrame;
      
      hNewFrame = OpenSTATS(hwndMainDlg, 0);
      usReturn = (USHORT) WinProcessDlg(hNewFrame);
      }
      return(TRUE);
      
   case ID_MAIN1WORDWRAP :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(274, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN1COPY :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(261, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN1CLEAR :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(281, 0), 0);
      }
      return(TRUE);
      
   case ID_MAIN1PHRASES :
      {
      WinSendMsg(hwndMainDlg, WM_COMMAND, MPFROM2SHORT(276, 0), 0);
      }
      return(TRUE);
      
   default :
      break;
   }
return(FALSE);   
}   





MRESULT EXPENTRY newMLE1Proc(HWND hwndWnd, ULONG ulMsg,
                                                MPARAM mp1, MPARAM mp2 )
{
PFNWP oldmle1WinProc;


oldmle1WinProc = (PFNWP) WinQueryWindowPtr(hwndWnd, 0);
switch(ulMsg)
   {
   case WM_CONTEXTMENU :
      {
      POINTL ptlMouse;

      WinQueryPointerPos(HWND_DESKTOP, &ptlMouse);
      WinPopupMenu(HWND_DESKTOP,
		   WinQueryWindow(hwndWnd, QW_OWNER),
		   hwndMLENEW1Popup,
		   ptlMouse.x, ptlMouse.y,
		   0,
		   PU_HCONSTRAIN |
		   PU_VCONSTRAIN |
		   PU_KEYBOARD |
		   PU_MOUSEBUTTON2 |
		   PU_MOUSEBUTTON1 );   
      WinSetPresParam(hwndMLENEW1Popup, 
                               PP_FONTNAMESIZE,
      		       sizeof(PPAttrValue2)+1,
      		       &PPAttrValue2);
      }
      break;

   case WM_PRESPARAMCHANGED :
            {
            WinQueryPresParam(hwndWnd, PP_FONTNAMESIZE, 0, NULL,
                                         FACESIZE+64,
                                         &PPAttrValue2,
                                         QPF_NOINHERIT);

            WinQueryPresParam(hwndWnd, PP_BACKGROUNDCOLOR, 0, &attra,
			     sizeof(pgmData[25]), &pgmData[25], QPF_NOINHERIT);
            WinQueryPresParam(hwndWnd, PP_FOREGROUNDCOLOR, 0, &attrb,
			     sizeof(pgmData[26]), &pgmData[26], QPF_NOINHERIT);
            saveNCSet();
            }
            break;   
      
      
   case WM_BEGINDRAG:
	{
	PDRAGINFO pdrginfo ;
	DRAGITEM drgitem, *pdrgitem ;
	DRAGIMAGE drgimage ;
	HWND hwndTarget;
	CHAR szFullPathName[MAXSTRING] ;
	CHAR szFullDocName[MAXSTRING] ;
	CHAR fileName[MAXSTRING] ;
	HPOINTER  standard;
	CHAR cwd[MAXSTRING];
            HFILE     hFile;
            PBYTE     pText;
            ULONG     ulTemp;
            ULONG wwstate;
	
	
	if( WinQueryDlgItemTextLength(WinQueryWindow(hwndWnd, QW_PARENT), 1000) <= 0 )
	   break;
	standard = WinLoadPointer(HWND_DESKTOP, 0L, ID_POINTER1);
	strcpy(szFullPathName, "");
	strcpy(szFullDocName, "");
	_getcwd(cwd, MAXSTRING);
	if( cwd != NULL )
	   {
	   strcpy(szFullPathName, cwd);
	   if( szFullPathName[strlen(szFullPathName)-1] != '\\' )
	      {
	      strcat(szFullPathName, "\\");
	      strcat(szFullPathName, "\0");
	      }
	   }
	strcpy(szFullDocName, szFullPathName);
	strcpy(fileName, "TEMP1.TXT");
	strcat(szFullDocName, fileName);
	
            if (!DosOpen(szFullDocName, &hFile, &ulTemp, 0L, FILE_ARCHIVED, 
                              FILE_TRUNCATE | FILE_CREATE,
                              OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYREADWRITE, 0L)) 
               {
               LONG ap, offs;
               ULONG sellen; 
               
               
               offs = (LONG)WinSendDlgItemMsg(hwndMainDlg, 1000,
                                                              MLM_QUERYSEL ,
                                                              MPFROMLONG(MLFQS_MINSEL), 0);

               sellen = (ULONG)WinSendDlgItemMsg(hwndMainDlg, 1000,
                                                                  MLM_QUERYSEL, MPFROMLONG(MLFQS_MAXSEL), 0) -
                                                                  (ULONG)WinSendDlgItemMsg(hwndMainDlg, 1000,
                                                                  MLM_QUERYSEL, MPFROMLONG(MLFQS_MINSEL), 0);
                                                                  
               if( sellen > 0 ) 
                   MLEGetItemText(hwndMainDlg, 1000, offs, sellen, &pText); 
               else   
                  MLEGetItemText(hwndMainDlg, 1000, 0, -1, &pText); 
               if (pText) 
                  {
                  DosWrite(hFile, (PSZ)pText, strlen(pText), &ulTemp);
                  free(pText);
                  }
               DosClose(hFile);                   
               }
	
	pdrginfo = DrgAllocDraginfo( 1L) ;
	pdrginfo -> hwndSource = hwndWnd;

	drgitem.hwndItem = hwndWnd;
	drgitem.ulItemID = 100L ;
	drgitem.hstrType = DrgAddStrHandle( DRT_TEXT) ;
	drgitem.hstrRMF = DrgAddStrHandle( "(DRM_OS2FILE)x(DRF_TEXT,DRF_UNKNOWN)" ) ;
	drgitem.hstrContainerName = DrgAddStrHandle( szFullPathName) ;
	drgitem.hstrSourceName = DrgAddStrHandle( fileName) ;
	drgitem.hstrTargetName = NULLHANDLE ;
	drgitem.cxOffset = 0 ;
	drgitem.cyOffset = 0 ;
	drgitem.fsControl = DC_REMOVEABLEMEDIA ;
	drgitem.fsSupportedOps = DO_COPYABLE;

	pdrgitem = (PDRAGITEM)( pdrginfo + 1) ;

	if( !DrgSetDragitem( pdrginfo, &drgitem, sizeof( DRAGITEM), 0L))
		WinAlarm( HWND_DESKTOP, WA_ERROR) ;


	drgimage.cb = sizeof( DRAGIMAGE) ;
	drgimage.cptl = 0 ;
	drgimage.hImage = standard;
	drgimage.sizlStretch.cx = 0L ;
	drgimage.sizlStretch.cy = 0L ;
	drgimage.fl = DRG_ICON ;
	drgimage.cxOffset = 0 ;
	drgimage.cyOffset = 0 ;
	DrgDrag(hwndWnd,
		pdrginfo,
		&drgimage,
		1L,
		VK_ENDDRAG,
		NULL) ;
	}
	break;

   default :
      break;
   }
return( *oldmle1WinProc ) (hwndWnd, ulMsg, mp1, mp2);
}




MRESULT EXPENTRY newMLE2Proc(HWND hwndWnd, ULONG ulMsg,
                                                MPARAM mp1, MPARAM mp2 )
{
PFNWP oldmle2WinProc;


oldmle2WinProc = (PFNWP) WinQueryWindowPtr(hwndWnd, 0);
switch(ulMsg)
   {
   case WM_CONTEXTMENU :
      {
      POINTL ptlMouse;
      CHAR bstatus[20];
      

      WinQueryPointerPos(HWND_DESKTOP, &ptlMouse);
      WinPopupMenu(HWND_DESKTOP,
		   WinQueryWindow(hwndWnd, QW_OWNER),
		   hwndMLENEW2Popup,
		   ptlMouse.x, ptlMouse.y,
		   0,
		   PU_HCONSTRAIN |
		   PU_VCONSTRAIN |
		   PU_KEYBOARD |
		   PU_MOUSEBUTTON2 |
		   PU_MOUSEBUTTON1 );  
      WinSetPresParam(hwndMLENEW2Popup, 
                               PP_FONTNAMESIZE,
      		       sizeof(PPAttrValue1)+1,
      		       &PPAttrValue2);
      if( checkConnectionOnceNT() == 1 )
         {
         if( !FTPINPROGRESS ) 
            {
            if( STILLWAITING )
               WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2SENDFILE, FALSE);
            else   
               WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2SENDFILE, TRUE);
            
            if( WinIsMenuItemEnabled(WinWindowFromID(hwndMainF, FID_MENU), 282) )
               WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2ABORTTRANSFER, TRUE);
            else   
               WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2ABORTTRANSFER, FALSE);
            }
         else
            {
            WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2SENDFILE, FALSE);
            if( FILENOTIFY )
               WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2ABORTTRANSFER, FALSE);
            else   
               WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2ABORTTRANSFER, TRUE);
            }
         }
      else
         {
         WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2SENDFILE, FALSE);
         WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2ABORTTRANSFER, FALSE);
         }         

      WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);
      if( strcmp(bstatus, "Listen OFF") == 0 )
         {
         WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2DISCONNECT, FALSE);
         WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2LISTEN, TRUE);
         }
      else
         {
         WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2DISCONNECT, TRUE);
         WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2LISTEN, FALSE);
         }   

      if( strcmp(bstatus, "Connected!") == 0 )
         {
         WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2CONNECT, FALSE);
         WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2WAKEUP, TRUE);
         WinEnableMenuItem(hwndMLENEW2Popup, ID_RPINFO, TRUE);
         }
      else
         {
         WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2CONNECT, TRUE);
         WinEnableMenuItem(hwndMLENEW2Popup, ID_MAIN2WAKEUP, FALSE);
         WinEnableMenuItem(hwndMLENEW2Popup, ID_RPINFO, FALSE);
         }   
      }
      break;

   case WM_CHAR :
      if( CHARMSG(&ulMsg)->chr == '\x0d' )
         {
         _beginthread(pressOK, NULL, BSTACK, NULL);
         return(0);
         }
         break;
      break;
   
   case DM_DRAGOVER :
      {
      PDRAGINFO pdrginfo;
      PDRAGITEM pdrgitem;
      CHAR btext[20];
      BOOL YESDROP;
      

      YESDROP = TRUE;
      
      if( checkConnectionOnceNT() == 1 )
         {
         if( !FTPINPROGRESS ) 
            {
            if( STILLWAITING )
               YESDROP = FALSE;
            }
         else
            YESDROP = FALSE;
         }
      else
         YESDROP = FALSE;

      if( !YESDROP )
         {
         break;
         }
         
      WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(btext), btext);
      if( strcmp(btext, "Connected!") != 0 )
         {
         break;
         }
      
      pdrginfo = (PDRAGINFO) PVOIDFROMMP(mp1);
      
      if( !DrgAccessDraginfo(pdrginfo) )
	 {
	 DrgFreeDraginfo(pdrginfo) ;
	 break;
	 }

      pdrgitem = DrgQueryDragitemPtr(pdrginfo, 0L);

      if( DrgVerifyTrueType(pdrgitem, DRT_UNKNOWN) )
         {
         DrgFreeDraginfo(pdrginfo) ;
         break;
         }  
	 
      if( !DrgVerifyRMF(pdrgitem, (PSZ)"DRM_OS2FILE", NULL) )
	 {
	 DrgFreeDraginfo(pdrginfo) ;
	 break;
	 }
	 
      if( (DrgQueryDragitemCount(pdrginfo)) != 1 )
	 {
	 DrgFreeDraginfo(pdrginfo) ;
	 break;
	 }
	 
      DrgFreeDraginfo(pdrginfo);
      
      return MPFROM2SHORT(DOR_DROP, DO_COPY);
      }
      break;   
   
   case WM_PRESPARAMCHANGED :
      {
      WinQueryPresParam(hwndWnd, PP_FONTNAMESIZE, 0, NULL,
                                    FACESIZE+64,
                                    &PPAttrValue1,
                                    QPF_NOINHERIT);
      WinQueryPresParam(hwndWnd, PP_BACKGROUNDCOLOR, 0, &attra,
			    sizeof(pgmData[27]), &pgmData[27], QPF_NOINHERIT);
      WinQueryPresParam(hwndWnd, PP_FOREGROUNDCOLOR, 0, &attrb,
			    sizeof(pgmData[28]), &pgmData[28], QPF_NOINHERIT);
      saveNCSet();
      }
      break;
      
   case DM_DROP :
      {
      PDRAGINFO pdrginfo = (PDRAGINFO)mp1;
      PDRAGITEM pdrgitem;
      USHORT usReturn;
      HWND hNewFrame;

          
      if( !DrgAccessDraginfo(pdrginfo) )
	 {
	 DrgFreeDraginfo(pdrginfo) ;
	 break;
	 }
	 
      pdrgitem = DrgQueryDragitemPtr(pdrginfo, 0L);

      DrgQueryStrName(pdrgitem->hstrContainerName,
		      sizeof(szCont), szCont);
		      
      DrgQueryStrName(pdrgitem->hstrSourceName,
		      sizeof(szFN), szFN);
		      
      DrgFreeDraginfo(pdrginfo);
      
      strcpy(FQSFile, szCont);
      if( FQSFile[strlen(FQSFile)-1] != '\\' )
          strcat(FQSFile, "\\");
      strcat(FQSFile, szFN);
      strcpy(SFile, szFN);
      
      SENDPASTE = 0;
      
      if( WinGetKeyState(HWND_DESKTOP, VK_CTRL)&0x8000 ) 
         {
         _beginthread(pasteDroppedFile, NULL, BSTACK, (PVOID)0);
         }
      else
         {
         if( pgmData[39] )
            {    
            hNewFrame = OpenCPC(hwndMainDlg, 0);
            usReturn = (USHORT) WinProcessDlg(hNewFrame);

            switch(SENDPASTE)
               {
               case 0:
                  break;
               
               case 1:
                  WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, FALSE);
                  WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, TRUE);
                  _beginthread(sendDroppedFile, NULL, BSTACK, (PVOID)0);
                  break;
               
               case 2:
                  _beginthread(pasteDroppedFile, NULL, BSTACK, (PVOID)0);
                  break;
                  
               default:
                  break;   
               }
            }
         else
            {
            WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 275, FALSE);
            WinEnableMenuItem(WinWindowFromID(hwndMainF, FID_MENU), 282, TRUE);
            _beginthread(sendDroppedFile, NULL, BSTACK, (PVOID)0);
            }      
         }
      }
      break;


   default :
      break;
   }
return( *oldmle2WinProc ) (hwndWnd, ulMsg, mp1, mp2);
}




VOID pasteDroppedFile(PVOID n)
{
ULONG siz;
HAB habT;
HMQ hmqT;
FILE *hanv;
ULONG pos;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

tstr[0] = '\0';
siz = getFSize(FQSFile);
if( siz > 0 && siz < MAXDROPSIZE )
   {
   if ((hanv = fopen(FQSFile, "r+b" )) != NULL)
      {
      fread(&tstr, siz, 1, hanv);   
      fclose(hanv);
      tstr[siz] = '\0';
      WinSetDlgItemText(hwndMainDlg, 1001, ""); 
      // WinSetDlgItemText(hwndMainDlg, 1001, tstr); 
      // WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwndMainDlg, 1001));
      // pos = WinQueryWindowTextLength(WinWindowFromID(hwndMainDlg, 1001));
      WinSendMsg(WinWindowFromID(hwndMainDlg, 1001),
                        MLM_SETSEL,
                        MPFROMP(0),
                        MPFROMP(0));  
      MLEInsertText(hwndMainDlg, 1001, -1, tstr);        
      WinSendMsg(WinWindowFromID(hwndMainDlg, 1001),
                        MLM_SETSEL,
                        MPFROMP(siz),
                        MPFROMP(siz));  
      }
   else
      msgBox(hwndMainDlg, "Error!", "Could not open the file.");
   }
else
   msgBox(hwndMainDlg, "Error!", "File size must be less than 5k.");
  
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID sendDroppedFile(PVOID n)
{
CHAR nbstr[40];
div_t   dvt;
INT packets;
CHAR packetstr[80];
ULONG siz;



siz = getFSize(FQSFile);
dvt = div(siz, FILEXMTSIZE);
if( dvt.rem != 0 )
   packets = dvt.quot + 1;
else   
   packets = dvt.quot;
itoa(packets, packetstr, 10);
packstosend = packets;
strcpy(packstosendstr, packetstr);

ltoa(siz, nbstr, 10);
strcpy(SFileSize, "\xB0");
strcat(SFileSize, "  (");
strcat(SFileSize, nbstr);
strcat(SFileSize, " bytes) ");
strcat(SFileSize, packetstr);

_beginthread(sendOneMSG, NULL, BSTACK, (PVOID)5);
}



                                              
VOID pressOK(PVOID prdat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
HWND hwndWnd;
ULONG len, pos, forecolor;
static CBD senddat;
INT n;
CHAR tbuf[MSGSIZE];


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

hwndDlg = hwndMainDlg;
hwndWnd = WinWindowFromID(hwndMainDlg, 1001);
	
if( WinQueryWindowTextLength(hwndWnd) == 0 )
   {
   WinEnableWindow(hwndWnd, TRUE);	  
      {
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }
   }
   
WinQueryWindowText(hwndWnd, sizeof(tmpsendbuf), tmpsendbuf);
len = (ULONG)WinSendDlgItemMsg(WinQueryWindow(hwndWnd, QW_OWNER), 
                                                1000,
                                                MLM_QUERYFORMATTEXTLENGTH ,
                                                MPFROMLONG(0), 
                                                MPFROMLONG(-1));
                                                
if( len > 0 )
   {                                                         
   strcpy(sendbuf, "\x0d\x0d\x0a<");
   }
else
   {                                                         
   strcpy(sendbuf, "<");
   }
strcat(sendbuf, nickName);
strcat(sendbuf, ">");
if( strlen(tmpsendbuf) > 0  )
   {  
   strcat(sendbuf, tmpsendbuf);
   WinSetWindowText(hwndWnd, "");
	 
   if( strcmp(localIP, guestIP) == 0 && pgmData[4] == pgmData[5] )
      {
      WinEnableWindow(hwndWnd, TRUE);	  
      }
   else   
      { 
      senddat.hwndDlg = WinQueryWindow(hwndWnd, QW_OWNER);
      _beginthread(sendMSG, NULL, BSTACK, (PVOID)&senddat);
      WinSetWindowText(hwndWnd, "");
      }
             
   strcpy(tbuf, sendbuf);   
   n = 0;
   do
      {
      n++;
      }
   while( tbuf[n] != '>' );
   strinsert(tbuf+n+1, ' ');
           
   pos = MLEInsertText(WinQueryWindow(hwndWnd, QW_OWNER), 1000, len, tbuf);
   WinSendMsg(hwndWnd,
 	         MLM_SETSEL,
                     MPFROMP(0),
	         MPFROMP(0));
   pos = WinQueryWindowTextLength(WinWindowFromID(WinQueryWindow(hwndWnd, QW_OWNER), 1000));
   WinSendMsg(WinWindowFromID(WinQueryWindow(hwndWnd, QW_OWNER), 1000),
	         MLM_SETSEL,
	         MPFROMP(pos),
                     MPFROMP(pos));
   }		       
      
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID makeTBar(VOID)
{
CHAR nctbur[] = "(UNREGISTERED) NetChat for OS/2";
CHAR nctb[] = "NetChat for OS/2";
CHAR noacct[] = "No acct. settings";
CHAR spacer[] = "   ";
CHAR tbarlm[260];
CHAR cip[40];
CHAR acct[40];

if( registered(ncpw) )
   strcpy(tbarmsg, nctb);
else
   strcpy(tbarmsg, nctbur);
strcat(tbarmsg, spacer);
strcat(tbarmsg, "R:");
itoa(pgmData[4], cip, 10);
strcat(tbarmsg, cip);
strcat(tbarmsg, spacer);
strcat(tbarmsg, "T:");
itoa(pgmData[5], cip, 10);
strcat(tbarmsg, cip);

itoa(pgmData[8], cip, 10);
strcat(tbarmsg, spacer);
strcat(tbarmsg, "F:");
strcat(tbarmsg, cip);

strcat(tbarmsg, spacer);
strcat(tbarmsg, "(");
if( pgmData[9] == 0  )
   strcat(tbarmsg, "I");
else   
   strcat(tbarmsg, "N");
strcat(tbarmsg, ")");
   
if( strlen(mailServer) > 0 )
   {
   strcat(tbarmsg, spacer);
   strcat(tbarmsg, mailServer);
   }
else   
   {
   strcat(tbarmsg, spacer);
   strcat(tbarmsg, noacct);
   }

}




VOID saveNCSet(VOID)
{
PrfWriteProfileData(hini, "NetChat", "WINPOS", 
                    &pgmData, sizeof(pgmData));
PrfWriteProfileString(hini, "NetChat",
                      "MAILSERVER", mailServer);
PrfWriteProfileString(hini, "NetChat",
                      "USERNAME", userName);
PrfWriteProfileString(hini, "NetChat",
                      "NICKNAME", nickName);
PrfWriteProfileString(hini, "NetChat",
                      "MPW", passWord);
PrfWriteProfileString(hini, "NetChat",
                      "MAILSERVER2", mailServer2);
PrfWriteProfileString(hini, "NetChat",
                      "USERNAME2", userName2);
PrfWriteProfileString(hini, "NetChat",
                      "MPW2", passWord2);
PrfWriteProfileString(hini, "NetChat",
                      "RTNAME", rtname);
PrfWriteProfileString(hini, "NetChat",
                      "RTEMA", rtema);
PrfWriteProfileString(hini, "NetChat",
                      "DEFDLDIR", DEFDLDIR);
PrfWriteProfileString(hini, "NetChat",
                      "DEFULDIR", DEFULDIR);
PrfWriteProfileString(hini, "NetChat",
                      "ENTRY1FONT", PPAttrValue1);
PrfWriteProfileString(hini, "NetChat",
                      "ENTRY2FONT", PPAttrValue2);
PrfWriteProfileString(hini, "NetChat",
                      "NCHATPW", ncpw);
}



VOID queryNCSet(VOID)
{
ULONG rSize;

if ( (hini = PrfOpenProfile(WinQueryAnchorBlock(0) , INIFILE)) != NULLHANDLE )
   {
   PrfQueryProfileSize(hini, "NetChat", "WINPOS", &rSize);
   if ( rSize == (sizeof(pgmData)) )
      {
      PrfQueryProfileData(hini, "NetChat", "WINPOS", &pgmData, &rSize);
      PrfQueryProfileString(hini, "NetChat", "MAILSERVER",
                            "", mailServer, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "USERNAME",
                            "", userName, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "NICKNAME",
                            "", nickName, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "MPW",
                            "", passWord, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "MAILSERVER2",
                            "", mailServer2, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "USERNAME2",
                            "", userName2, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "RTNAME",
                            "", rtname, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "RTEMA",
                            "", rtema, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "MPW2",
                            "", passWord2, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "DEFDLDIR",
                            "", DEFDLDIR, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "DEFULDIR",
                            "", DEFULDIR, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "ENTRY1FONT",
                            "", PPAttrValue1, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "ENTRY2FONT",
                            "", PPAttrValue2, CCHMAXPATH );
      PrfQueryProfileString(hini, "NetChat", "NCHATPW",
                            "", ncpw, CNAMESIZE);
      }
   else
      {
      strcpy(mailServer, "");
      strcpy(userName, "");
      strcpy(nickName, "");
      strcpy(passWord, "");
      strcpy(mailServer2, "");
      strcpy(userName2, "");
      strcpy(passWord2, "");
      strcpy(DEFDLDIR, "");
      strcpy(DEFULDIR, "");
      strcpy(PPAttrValue1, "");
      strcpy(ncpw, "");
      pgmData[0] = 50;
      pgmData[1] = 50;
      pgmData[2] = 550;
      pgmData[3] = 350;
      pgmData[4] = 6667; /* Receiving port */
      pgmData[5] = 6667; /* transmitting port */
      pgmData[6] = 10;    /* check mail interval in seconds */
      pgmData[7] = 3;      /* mode to use AFTER sending hailing message */
      pgmData[8] = 21;      /* Default FTPPORT */
      pgmData[9] = 0;      /* Force using Internet IP if available = 0  Lan = 1 */
      pgmData[10] = 80;  /* x axis for Phrases position */      
      pgmData[11] = 70;  /* y axis for Phrases position */    
      pgmData[12] = 400;  /* width */    
      pgmData[13] = 400;  /* height */    
      pgmData[14] = 0;  /* Start Phrase list at startup */    
      pgmData[15] = 1;  /* Beep : Incoming mail */    
      pgmData[16] = 1;  /* Beep : Connected! */    
      pgmData[17] = 1;  /* Beep : Wake up */    
      pgmData[18] = 1;  /* Beep : Echo */    
      pgmData[19] = 1;  /* Beep : Waiting ..... */    
      pgmData[20] = 1;  /* Beep : Sending Hail */    
      pgmData[21] = 1;  /* Beep : Receiving Hail */    
      pgmData[22] = 1;  /* Beep : File received OK */    
      pgmData[23] = 1;  /* Beep : File NOT received OK */    
      pgmData[24] = 1;  /* Beep : Transfer rejected */    
      pgmData[25] = -1;  /* Remote bkgnd color */    
      pgmData[26] = -1;  /* Remote fgnd color */    
      pgmData[27] = -1;  /* Local bkgnd color */    
      pgmData[28] = -1;  /* Local fgnd color */    
      pgmData[29] = 1;  /* Beep : File Sent OK */    
      pgmData[30] = 1;  /* Beep : File NOT Sent OK  */    
      pgmData[31] = -1;  /* Unhide when Hailed */    
      pgmData[32] = 0;  /* minimize at start */    
      pgmData[33] = 1;  /* auto-synch ports */    
      pgmData[34] = 1;  /* revert to original  ports */    
      pgmData[35] = 6667;  /* default R  port */    
      pgmData[36] = 6667;  /* default T  port */    
      pgmData[37] = 21;  /* default F  port */    
      pgmData[38] = 0;  /* use IBM's sendmail */    
      pgmData[39] = 1;  /* Prompt for paste or send */    
      pgmData[40] = 1;  /* Prompt CLOSE */    
      }
   }   
else
   {
   strcpy(mailServer, "");
   strcpy(userName, "");
   strcpy(nickName, "");
   strcpy(passWord, "");
   strcpy(mailServer2, "");
   strcpy(userName2, "");
   strcpy(passWord2, "");
   strcpy(DEFDLDIR, "");
   strcpy(DEFULDIR, "");
   strcpy(PPAttrValue1, "");
   strcpy(ncpw, "");
   pgmData[0] = 50;
   pgmData[1] = 50;
   pgmData[2] = 550;
   pgmData[3] = 350;
   pgmData[4] = 6667; /* Receiving port */
   pgmData[5] = 6667; /* transmitting port */
   pgmData[6] = 10; /* check mail interval in seconds */
   pgmData[7] = 3;      /* mode to use AFTER sending hailing message */
   pgmData[8] = 21;      /* Default FTPPORT */
   pgmData[9] = 0;      /* Force using Internet IP if available = 0  Lan = 1 */
   pgmData[10] = 80;  /* x axis for Phrases position */      
   pgmData[11] = 70;  /* y axis for Phrases position */    
   pgmData[12] = 400;  /* width */    
   pgmData[13] = 400;  /* height */    
   pgmData[14] = 1;  /* Start Phrase list at startup */    
   pgmData[15] = 1;  /* Beep : Incoming mail */    
   pgmData[16] = 1;  /* Beep : Connected! */    
   pgmData[17] = 1;  /* Beep : Wake up */    
   pgmData[18] = 1;  /* Beep : Echo */    
   pgmData[19] = 1;  /* Beep : Waiting ..... */    
   pgmData[20] = 1;  /* Beep : Sending Hail */    
   pgmData[21] = 1;  /* Beep : Receiving Hail */    
   pgmData[22] = 1;  /* Beep : File received OK */    
   pgmData[23] = 1;  /* Beep : File NOT received OK */    
   pgmData[24] = 1;  /* Beep : Transfer rejected */    
   pgmData[25] = -1;  /* Remote bkgnd color */    
   pgmData[26] = -1;  /* Remote fgnd color */    
   pgmData[27] = -1;  /* Local bkgnd color */    
   pgmData[28] = -1;  /* Local fgnd color */    
   pgmData[29] =  1;  /* Beep : File Sent OK */    
   pgmData[30] = 1;  /*Beep : File NOT Sent OK   */    
   pgmData[31] = -1;  /* Unhide when Hailed */    
   pgmData[32] = 0;  /* minimize at start */    
   pgmData[33] = 1;  /* auto-synch ports */    
   pgmData[34] = 1;  /* revert to original  ports */    
   pgmData[35] = 6667;  /* default R  port */    
   pgmData[36] = 6667;  /* default T  port */    
   pgmData[37] = 21;  /* default F  port */    
   pgmData[38] = 0;  /* use IBM's sendmail */    
   pgmData[39] = 1;  /* Prompt for paste or send */    
   pgmData[40] = 1;  /* Prompt CLOSE */    
   }
}




MRESULT EXPENTRY NewListProc(HWND hwndWnd, ULONG ulMsg,
                                            MPARAM mp1, MPARAM mp2 )
{
PFNWP moldWinProc;

moldWinProc = (PFNWP) WinQueryWindowPtr(hwndWnd, 0);
switch(ulMsg)
   {
   case WM_CONTEXTMENU :
      {
      POINTL ptlMouse;

      WinQueryPointerPos(HWND_DESKTOP, &ptlMouse);
      WinPopupMenu(HWND_DESKTOP,
		   WinQueryWindow(hwndWnd, QW_OWNER),
		   hwndMLBPopup,
		   ptlMouse.x, ptlMouse.y,
		   0,
		   PU_HCONSTRAIN |
		   PU_VCONSTRAIN |
		   PU_KEYBOARD |
		   PU_MOUSEBUTTON2 |
		   PU_MOUSEBUTTON1 );  
      }
      break;

   default :
      break;
   }
return( *moldWinProc ) (hwndWnd, ulMsg, mp1, mp2);
}





MRESULT EXPENTRY newNoteProc( HWND hwndWnd, ULONG ulMsg,
			      MPARAM mp1, MPARAM mp2 )
{
PFNWP oldNoteProc;

oldNoteProc = (PFNWP) WinQueryWindowPtr(hwndWnd, 0);
switch(ulMsg)
   {
   case WM_CHAR :
      if( CHARMSG(&ulMsg)->chr == '\x0d' )
	 {
	 return(0);
	 }
      if( !(CHARMSG(&ulMsg)->fs & KC_KEYUP) )
	 break;
      break;

   default :
      break;
   }
return( *oldNoteProc ) (hwndWnd, ulMsg, mp1, mp2);
}





MRESULT EXPENTRY newPhrProc(HWND hwndWnd, ULONG ulMsg,
                                            MPARAM mp1, MPARAM mp2 )
{
PFNWP poldWinProc;

poldWinProc = (PFNWP) WinQueryWindowPtr(hwndWnd, 0);
switch(ulMsg)
   {
   case WM_CONTEXTMENU :
      {
      POINTL ptlMouse;
       
      WinQueryPointerPos(HWND_DESKTOP, &ptlMouse);
      WinPopupMenu(HWND_DESKTOP,
                           // hwndPhrDlg,
		   WinQueryWindow(hwndWnd, QW_OWNER),
		   hwndMLPPopup,
		   ptlMouse.x, ptlMouse.y,
		   0,
		   PU_HCONSTRAIN |
		   PU_VCONSTRAIN |
		   PU_KEYBOARD |
		   PU_MOUSEBUTTON2 |
		   PU_MOUSEBUTTON1 );  
      }
      break;

   default :
      break;
   }
return( *poldWinProc ) (hwndWnd, ulMsg, mp1, mp2);
}




VOID phrmenuChoice(HWND hwndDlg, HWND hwndFrame, HWND hwndPopup, ULONG msg, MPARAM mp1, MPARAM mp2)
{
switch (SHORT1FROMMP(mp1))
   { 
   case ID_PHRADDREC :
      {
      USHORT usReturn;
      HWND hNewFrame;
      
      
      hNewFrame = OpenADDPHR(hwndDlg, 0);
      usReturn = (USHORT) WinProcessDlg(hNewFrame);
      if( PHRTMP.index == 1 )
         {
         addPHRRecord(PHRDATAFILE, PHRTMP.phrase, hwndDlg); 
         zeroPHRTMP();
         }
      }
      break;
         
   case ID_PHREDITREC :
      {
      USHORT usReturn;
      HWND hNewFrame;
      PEDITPHRFORMINFO pEditPHRFormInfo = malloc(sizeof(EDITPHRFORMINFO));
      
      
      editPHRRecord(PHRDATAFILE, hwndDlg);
      pEditPHRFormInfo->hwnd = hwndDlg;
      hNewFrame = OpenEDITPHR(hwndDlg, pEditPHRFormInfo);
      usReturn = (USHORT) WinProcessDlg(hNewFrame);
      }
      break;
         
   case ID_PHRDELETEREC :
      {
      deletePHRRecord(PHRDATAFILE, hwndDlg);
      }
      break;
   }
}   




VOID mailSendStatus(PVOID chkmdat)
{
HAB habT;
HMQ hmqT;
HWND hwndDlg;
INT sint = 400;
INT it = 6;
INT mode, kv;


habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

hwndDlg = ((PFCBD)chkmdat)->hwndDlg;
mode = ((PFCBD)chkmdat)->interval;

if( mode == 0 )
   {
   if( pgmData[20] )
      DosBeep(900, 100);   
   for( kv=0;kv<it;kv++ )
      {
      WinSetDlgItemText(hwndDlg, FID_TITLEBAR, "");
      DosSleep(sint);
      WinSetDlgItemText(hwndDlg, FID_TITLEBAR, "Server did not accept the data to be sent!");
      DosSleep(sint);
      }
   }

if( mode == 1 )
   {
   CHAR mm[300];
   
   
   strcpy(mm, "Hail successfully sent to : ");
   strcat(mm, mmtoname);
   if( pgmData[20] )
      DosBeep(900, 100);   
   for( kv=0;kv<it;kv++ )
      {
      WinSetDlgItemText(hwndDlg, FID_TITLEBAR, "");
      DosSleep(sint);
      WinSetDlgItemText(hwndDlg, FID_TITLEBAR, mm);
      DosSleep(sint);
      }
   }

if( mode == 2 )
   {
   it = 3;
   for( kv=0;kv<it;kv++ )
      {
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "");
      DosSleep(sint);
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "You are now connected!");
      if( pgmData[16] )
         {
         DosBeep(1500, 50);
         DosBeep(1200, 50);
         DosBeep(900, 50);
         DosBeep(1500, 50);
         DosBeep(1200, 50);
         DosBeep(900, 50);
         DosSleep(sint); 
         }
      else
         DosSleep(sint+300);   
      }
   }

if( mode == 3 )
   {
   it = 1;
   for( kv=0;kv<it;kv++ )
      {
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "");
      DosSleep(sint);
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "You are still connected!");
      if( pgmData[18] )
         DosBeep(1500, 50);
      DosSleep(sint*2);
      }
   }

if( mode == 4 )
   {
   DosSleep(800);
   it = 3;
   for( kv=0;kv<it;kv++ )
      {
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "");
      DosSleep(sint);
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "File transfer rejected!");
      if( pgmData[24] )
         DosBeep(1500, 50);
      DosSleep(sint);
      }
   }

if( mode == 5 )
   {
   it = 1;
   for( kv=0;kv<it;kv++ )
      {
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "");
      DosSleep(sint);
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "Wake up was received!");
      if( pgmData[17] )
         DosBeep(1500, 50);
      DosSleep(sint);
      }
   DosSleep(1600);
   }

if( mode == 6 )
   {
   DosSleep(800);
   it = 3;
   for( kv=0;kv<it;kv++ )
      {
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "");
      DosSleep(sint);
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "Wake up and pay attention!");
      if( pgmData[17] )
         {
         DosBeep(1500, 50);
         DosBeep(500, 50);
         DosBeep(100, 50);
         DosBeep(500, 50);
         DosBeep(1500, 50);
         DosSleep(sint);
         }
      else   
         DosSleep(sint+250);
      }
   }

if( mode == 7 )
   {
   it = 1;
   for( kv=0;kv<it;kv++ )
      {
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "");
      DosSleep(sint);
      WinSetDlgItemText(hwndMainF, FID_TITLEBAR, "Receive port already in use!");
      if( pgmData[17] )
         DosBeep(1500, 50);
      DosSleep(sint);
      }
   DosSleep(1600);
   }

makeTBar();
WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);

WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}






BOOL menuChoice(SHORT mp1, HWND hwndDlg)
{
switch (mp1)
   { 
   case ID_NCADDREC :
      {
      USHORT usReturn;
      HWND hNewFrame;

      hNewFrame = OpenNEWREC(hwndDlg, 0);
      usReturn = (USHORT) WinProcessDlg(hNewFrame);
      if( ncTmpr.indx == 1 )
         {
         addRecord(ncDataFile, ncTmpr.ncName, ncTmpr.ncURL, ncTmpr.ncNote, hwndDlg); 
         zeroNCTmpr();
         }
      }
      return(TRUE);
         
   case ID_NCEDITREC :
      {
      USHORT usReturn;
      HWND hNewFrame;
      PEDITRECFORMINFO pEditrecFormInfo = malloc(sizeof(EDITRECFORMINFO));
      
      editRecord(ncDataFile, hwndDlg);
      pEditrecFormInfo->hwnd = hwndDlg;
      hNewFrame = OpenEDITREC(hwndDlg, pEditrecFormInfo);
      usReturn = (USHORT) WinProcessDlg(hNewFrame);
      }
      return(TRUE);
         
   case ID_NCDELETEREC :
      deleteRecord(ncDataFile, hwndDlg);
      return(TRUE);
         
   case ID_NCSELECTREC :
      DosBeep(3100, 100);
      return(TRUE);
      
   default :
      break;   
   }
return(FALSE); 
}   




INT savePHRData(CHAR *fname)
{
FILE *hanv;

if ((hanv = fopen( fname, "w+b" )) == NULL)
   {
   return(-1);
   }
else
   {
   fwrite(&PHR[0], sizeof(struct PHRdata)*PHRNUMRECS, 1, hanv);
   fclose(hanv);
   }   
return(1);
}




INT loadPHRData(CHAR *fname)
{
FILE *hanv;
INT i = 0;

if ((hanv = fopen( fname, "r+b" )) == NULL)
   {
   return(-1);
   }

fread(&PHR[0], sizeof(struct PHRdata)*PHRNUMRECS, 1, hanv);   
   
fclose(hanv);
return(1);
}




VOID zeroPHRLBoxHandle(HWND hwndDlg)
{
INT j;

for( j=0;j<PHRNUMRECS;j++ )
   {
   WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_SETITEMHANDLE,
                    MPFROMSHORT(j), MPFROMLONG((LONG)-1)); 
   }
}




INT loadPHRLBox(HWND hwndDlg, CHAR *fname)
{
INT i, pos;

if( !loadPHRData(fname) )
   return(-1);

zeroPHRLBoxHandle(hwndDlg);

WinSendMsg (WinWindowFromID(hwndDlg, 1000),LM_DELETEALL,0,0);
   
for( i=0;i<PHRNUMRECS;i++ )
   {
   if( PHR[i].index >= 0 && PHR[i].index <= PHRNUMRECS )   
      {
      CHAR header[81];
      INT slen;
      
      slen = strlen(PHR[i].phrase);
      if( slen > 80 )
         {
         strncpy(header, PHR[i].phrase, 80);
         header[80] = '\0';
         }
      else
         strcpy(header, PHR[i].phrase);   
      pos = WinInsertLboxItem(WinWindowFromID(hwndDlg, 1000), LIT_SORTASCENDING, PHR[i].phrase);
      WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_SETITEMHANDLE,
                       MPFROMSHORT(pos), MPFROMLONG((LONG)PHR[i].index)); 
      }                 
   }
   
WinSendMsg (WinWindowFromID(hwndDlg, 1000),LM_SELECTITEM,(MPARAM)0,MPFROMSHORT(TRUE));
return(1);   
}



INT addPHRRecord(CHAR *fname, CHAR *phrase, HWND hwndDlg)
{
INT h;
LONG recpos;
CHAR header[81];
INT slen;

      
slen = strlen(phrase);
if( slen > 80 )
   {
   strncpy(header, phrase, 80);
   header[80] = '\0';
   }
else
   strcpy(header, phrase);   

recpos = WinInsertLboxItem(WinWindowFromID(hwndDlg, 1000), LIT_SORTASCENDING, header);
WinSendMsg (WinWindowFromID(hwndDlg, 1000),LM_SELECTITEM,(MPARAM)recpos,MPFROMSHORT(TRUE));

if( PHR[0].index == -1 )
   {
   PHR[0].index = 0;
   WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_SETITEMHANDLE,
                    MPFROMSHORT(recpos), MPFROMLONG((LONG)PHR[0].index)); 
   strcpy(PHR[0].phrase, phrase);   
   if( !savePHRData(fname) )
      return(-1); 
   }
else
   {   
   h = 0;
   do
      {
      h++;
      }
   while( h < PHRNUMRECS && PHR[h].index != -1 );
   if( h <= PHRNUMRECS )
      {
      PHR[h].index = h;
      WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_SETITEMHANDLE,
                       MPFROMSHORT(recpos), MPFROMLONG((LONG)PHR[h].index)); 
      strcpy(PHR[h].phrase, phrase);   
      if( !savePHRData(fname) )
         return(-1);
      }
   else
      return(-1);   
   }
return(1);
}




INT deletePHRRecord(CHAR *fname, HWND hwndDlg)
{
INT chosen;
INT handle;


chosen = (LONG)WinSendDlgItemMsg(hwndDlg, 1000,
                                                 LM_QUERYSELECTION,
                                                 MPFROMLONG(LIT_FIRST),
                                                 MPFROMLONG(0));

handle = (LONG)WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_QUERYITEMHANDLE,
                    MPFROMSHORT(chosen), 0); 

PHR[handle].index = -1;

savePHRData(fname);

zeroPHRData();

loadPHRLBox(hwndDlg, fname);

return(1);
}




INT editPHRRecord(CHAR *fname, HWND hwndDlg)
{
INT chosen;
INT handle;


zeroPHRTMP();
chosen = (LONG)WinSendDlgItemMsg(hwndDlg, 1000,
                                                 LM_QUERYSELECTION,
                                                 MPFROMLONG(LIT_FIRST),
                                                 MPFROMLONG(0));

handle = (LONG)WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_QUERYITEMHANDLE,
                    MPFROMSHORT(chosen), 0); 

PHRTMP.index = PHR[handle].index;
strcpy(PHRTMP.phrase, PHR[handle].phrase);

return(chosen);
}




VOID zeroPHRData(VOID)
{
INT j;

for( j=0;j<PHRNUMRECS;j++ )
   {
   PHR[j].index = -1;
   PHR[j].phrase[0] = '\0';
   }
}




VOID zeroPHRTMP(VOID)
{
PHRTMP.index = -1;
PHRTMP.phrase[0] = '\0';
}



INT editRecord(CHAR *fname, HWND hwndDlg)
{
INT chosen;
INT handle;


zeroNCTmpr();
chosen = (LONG)WinSendDlgItemMsg(hwndDlg, 1000,
                                                 LM_QUERYSELECTION,
                                                 MPFROMLONG(LIT_FIRST),
                                                 MPFROMLONG(0));

handle = (LONG)WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_QUERYITEMHANDLE,
                    MPFROMSHORT(chosen), 0); 


ncTmpr.indx = ncData[handle].indx;
strcpy(ncTmpr.ncName, ncData[handle].ncName);
strcpy(ncTmpr.ncURL, ncData[handle].ncURL);
strcpy(ncTmpr.ncNote, ncData[handle].ncNote);

return(chosen);
}




INT deleteRecord(CHAR *fname, HWND hwndDlg)
{
INT chosen;
INT handle;


chosen = (LONG)WinSendDlgItemMsg(hwndDlg, 1000,
                                                 LM_QUERYSELECTION,
                                                 MPFROMLONG(LIT_FIRST),
                                                 MPFROMLONG(0));

handle = (LONG)WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_QUERYITEMHANDLE,
                    MPFROMSHORT(chosen), 0); 

ncData[handle].indx = -1;

saveNCData(fname);

zeroNCData();

loadNCLBox(hwndDlg, fname);

return(1);
}




INT addRecord(CHAR *fname, CHAR *ncName, CHAR *ncURL, CHAR *ncNote, HWND hwndDlg)
{
INT h;
LONG recpos;

recpos = WinInsertLboxItem(WinWindowFromID(hwndDlg, 1000), LIT_SORTASCENDING, ncName);
WinSendMsg (WinWindowFromID(hwndDlg, 1000),LM_SELECTITEM,(MPARAM)recpos,MPFROMSHORT(TRUE));


if( ncData[0].indx == -1 )
   {
   ncData[0].indx = 0;
   WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_SETITEMHANDLE,
                    MPFROMSHORT(recpos), MPFROMLONG((LONG)ncData[0].indx)); 
   strcpy(ncData[0].ncName, ncName);   
   strcpy(ncData[0].ncURL, ncURL);   
   strcpy(ncData[0].ncNote, ncNote);   
   if( !saveNCData(fname) )
      return(-1); 
   }
else
   {   
   h = 0;
   do
      {
      h++;
      }
   while( h < RECNUM && ncData[h].indx != -1 );
   if( h <= RECNUM )
      {
      ncData[h].indx = h;
      WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_SETITEMHANDLE,
                       MPFROMSHORT(recpos), MPFROMLONG((LONG)ncData[h].indx)); 
      strcpy(ncData[h].ncName, ncName);   
      strcpy(ncData[h].ncURL, ncURL);   
      strcpy(ncData[h].ncNote, ncNote);   
      if( !saveNCData(fname) )
         return(-1);
      }
   else
      return(-1);   
   }
return(1);
}




INT saveNCData(CHAR *fname)
{
FILE *hanv;

if ((hanv = fopen( fname, "w+b" )) == NULL)
   {
   return(-1);
   }
else
   {
   fwrite(&ncData[0], sizeof(struct NCDATA)*RECNUM, 1, hanv);
   fclose(hanv);
   }   
return(1);
}




INT loadNCData(CHAR *fname)
{
FILE *hanv;
INT i = 0;

if ((hanv = fopen( fname, "r+b" )) == NULL)
   {
   return(-1);
   }

fread(&ncData[0], sizeof(struct NCDATA)*RECNUM, 1, hanv);   
   
fclose(hanv);
return(1);
}




INT loadNCLBox(HWND hwndDlg, CHAR *fname)
{
INT i, pos;

if( !loadNCData(fname) )
   return(-1);

zeroLBoxHandle(hwndDlg);

WinSendMsg (WinWindowFromID(hwndDlg, 1000),LM_DELETEALL,0,0);
   
for( i=0;i<RECNUM;i++ )
   {
   if( ncData[i].indx >= 0 && ncData[i].indx <= RECNUM )   
      {
      pos = WinInsertLboxItem(WinWindowFromID(hwndDlg, 1000), LIT_SORTASCENDING, ncData[i].ncName);
      WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_SETITEMHANDLE,
                       MPFROMSHORT(pos), MPFROMLONG((LONG)ncData[i].indx)); 
      }                 
   }
   
WinSendMsg (WinWindowFromID(hwndDlg, 1000),LM_SELECTITEM,(MPARAM)0,MPFROMSHORT(TRUE));

return(1);   
}




VOID zeroNCTmpr(VOID)
{
ncTmpr.indx = -1;
ncTmpr.ncName[0] = '\0';
ncTmpr.ncURL[0] = '\0';
ncTmpr.ncNote[0] = '\0';
}




VOID zeroNCData(VOID)
{
INT j;

for( j=0;j<RECNUM;j++ )
   {
   ncData[j].indx = -1;
   ncData[j].ncName[0] = '\0';
   ncData[j].ncURL[0] = '\0';
   ncData[j].ncNote[0] = '\0';
   }
}




VOID zeropvdat(VOID)
{
INT j;

for( j=0;j<RECNUM;j++ )
   {
   pvdat[j].INDATE[0] = '\0';
   pvdat[j].INSUBJECT[0] = '\0';
   pvdat[j].INFROM[0] = '\0';
   pvdat[j].REPTO[0] = '\0';
   }
}




VOID zeroLBoxHandle(HWND hwndDlg)
{
INT j;

for( j=0;j<RECNUM;j++ )
   {
   WinSendMsg(WinWindowFromID(hwndDlg, 1000), LM_SETITEMHANDLE,
                    MPFROMSHORT(j), MPFROMLONG((LONG)-1)); 
   }
}




void strdelc(char *s, char c)
{
while ( *s )
   {
   if ( *s == c )
      strcpy( s, s+1 );
   else
      s++;
   }
}




int strndel(char *s, int n)
{
int len;

len = strlen(s);
if( len < n )
   return(0);
strcpy(s, s+n);
return(1);
}




char * strinsert(char *s, char insert)
{
char *sptr;

sptr = (char*)calloc(strlen(s)+1, sizeof(char));

if( sptr == NULL )
   return(NULL);

strcpy(sptr, s);
*s = insert;
strcpy(s+1, sptr);
free(sptr);
return(s);
}




VOID chkForMail(PVOID chkmaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
struct hostent *hp;    
struct sockaddr_in server;
char * host;
CHAR sendbuf[bsize];
CHAR receivebuf[bsize];
CHAR receivebufA[bsize];
CHAR rcvbuf[64];
CHAR serverbuf[260];
CHAR mailserverbuf[260];
CHAR userbuf[260];
CHAR passwordbuf[260];
CHAR statbuf[260];
CHAR quitbuf[] = "QUIT\x0d\x0a";
CHAR termn[] = "\x0d\x0a";
CHAR mrreport[260];
INT sock, rval, rv;
INT ina;
INT len;
INT mailreceiveport = 110;
INT retn;
INT ig, ih;
INT socks[1];
ULONG fgndcolor;
CHAR conon[30];
// INT dontblock;
BOOL FSTTIME;
CHAR tmbuf[bsize];



habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

STOPME = 0;
PAUSEAC = 0;
hwndDlg = ((PFCBD)chkmaildat)->hwndDlg;

TINTERVAL = pgmData[6]*1000;
DosCreateEventSem(NULL, &hev, 0L, FALSE);

fgndcolor = CLR_RED;   
WinSetPresParam(WinWindowFromID(hwndDlg, 1006), 
                PP_FOREGROUNDCOLORINDEX,
                sizeof(ULONG),     
                &fgndcolor);     

do
   {
   queryNCSet();
   if( strlen(mailServer) > 0 && strlen(userName) > 0 && strlen(passWord) > 0 )
      {
      INT kh;
      BOOL dn;
      CHAR uname[260];
      
      
      strcpy(serverbuf, mailServer);
      
      dn = FALSE;
      kh = 0;
      do
         {
         if( userName[kh] != '@' )
            {
            uname[kh] = userName[kh];
            }
         else
            dn = TRUE;
         kh++;      
         }
      while( !dn && (kh < strlen(userName)) );

      if( dn )
         {
         uname[kh-1] = '\0';   
         strcpy(userbuf, "USER ");
         strcat(userbuf, uname);
         }
      else
         {
         fgndcolor = CLR_BLACK;   
         WinSetPresParam(WinWindowFromID(hwndDlg, 1006), 
                              PP_FOREGROUNDCOLORINDEX,
                              sizeof(ULONG),     
                              &fgndcolor);     
         WinQueryDlgItemText(hwndDlg, 1002, sizeof(conon), conon);
         if( strcmp(conon, "Listen OFF") == 0  || pgmData[7] < 3 )
            {
            WinEnableWindow(WinWindowFromID(hwndDlg, 1006), TRUE);
            WinSetDlgItemText(hwndDlg, 1006, "Monitor OFF");
            }
         DosBeep(1250, 50);
         msgBox(hwndMainDlg, "Improper or NO setting for e-mail address.", "Attention!");
         WinDestroyMsgQueue(hmqT);
         WinTerminate(habT);
         _endthread();
         return;
         }   
         
      strcat(userbuf, termn);
      strcpy(passwordbuf, "PASS ");
      strcat(passwordbuf, passWord);
      strcat(passwordbuf, termn);
      strcpy(statbuf, "STAT");
      strcat(statbuf, termn);
      }
   else
      {
      fgndcolor = CLR_BLACK;   
      WinSetPresParam(WinWindowFromID(hwndDlg, 1006), 
                              PP_FOREGROUNDCOLORINDEX,
                              sizeof(ULONG),     
                              &fgndcolor);     
      WinQueryDlgItemText(hwndDlg, 1002, sizeof(conon), conon);
      if( strcmp(conon, "Listen OFF") == 0  || pgmData[7] < 3 )
         {
         WinEnableWindow(WinWindowFromID(hwndDlg, 1006), TRUE);
         WinSetDlgItemText(hwndDlg, 1006, "Monitor OFF");
         }
      DosBeep(1250, 50);
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }   

   sock_init();

   sock = socket(AF_INET, SOCK_STREAM, 0);

   // dontblock = 1;
   // ioctl(sock, FIONBIO, (char *) &dontblock, sizeof(dontblock));

   if (sock < 0)
      {
      soclose(sock);   
      fgndcolor = CLR_BLACK;   
      WinSetPresParam(WinWindowFromID(hwndDlg, 1006), 
                              PP_FOREGROUNDCOLORINDEX,
                              sizeof(ULONG),     
                              &fgndcolor);     
      DosBeep(1250, 50);
      WinQueryDlgItemText(hwndDlg, 1002, sizeof(conon), conon);
      if( strcmp(conon, "Listen OFF") == 0  || pgmData[7] < 3 )
         {
         WinEnableWindow(WinWindowFromID(hwndDlg, 1006), TRUE);
         WinSetDlgItemText(hwndDlg, 1006, "Monitor OFF");
         }
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }
   else
      {
      hp = gethostbyname(serverbuf);
      if (!hp) 
         {
         fgndcolor = CLR_BLACK;   
         WinSetPresParam(WinWindowFromID(hwndDlg, 1006), 
                                 PP_FOREGROUNDCOLORINDEX,
                                 sizeof(ULONG),     
                                 &fgndcolor);     
         DosBeep(1250, 50);
         soclose(sock);   
         WinQueryDlgItemText(hwndDlg, 1002, sizeof(conon), conon);
         if( strcmp(conon, "Listen OFF") == 0  || pgmData[7] < 3 )
            {
            WinEnableWindow(WinWindowFromID(hwndDlg, 1006), TRUE);
            WinSetDlgItemText(hwndDlg, 1006, "Monitor OFF");
            }
         WinDestroyMsgQueue(hmqT);
         WinTerminate(habT);
         _endthread();
         } 
      else  
         {   
         memset(&server, 0, sizeof(server));
         bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
         server.sin_port = htons(mailreceiveport);
         server.sin_family = AF_INET;
        
         if(connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
            {
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            }
         else 
            {
            memset(&receivebuf, 0, sizeof(receivebuf));
            // rval = recv(sock, receivebuf, bsize, 0); 

            FSTTIME = TRUE;
            do
               {
               memset(&tmbuf, 0, sizeof(tmbuf));
               rval = recv(sock, tmbuf, sizeof(tmbuf), 0);
               if( rval > 0 && !FSTTIME )
                  {
                  strcat(receivebuf, tmbuf);
                  }
               if( rval > 0 && FSTTIME )
                  {
                  FSTTIME = FALSE;
                  strcpy(receivebuf, tmbuf);
                  }
               }
            while( rval > 0 && tmbuf[rval-2] != '\x0d' && tmbuf[rval-1] != '\x0a' );

            // msgBox(hwndDlg, "receivebuf 01", receivebuf);

            if (rval <= 0)
               {
               send(sock, quitbuf, strlen(quitbuf), 0);
               soclose(sock);   
               }
            }

         if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
            {
            CHAR er[260];
         
      
            socks[0] = sock;
            select(socks, 1, 0, 0, 2000);
         
            memset(&receivebuf, 0, sizeof(receivebuf));
            rv = send(sock, userbuf, strlen(userbuf), 0);
            rval = recv(sock, receivebuf, bsize, 0); 
                     
            if (rval <= 0)
               {
               send(sock, quitbuf, strlen(quitbuf), 0);
               soclose(sock);   
               }
            }
         else           
            msgBox(hwndDlg, "Server error!", receivebuf);

         if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
            {
            memset(&receivebuf, 0, sizeof(receivebuf));
            send(sock, passwordbuf, strlen(passwordbuf), 0);
            rval = recv(sock, receivebuf, bsize, 0); 
            if (rval <= 0)
               {
               send(sock, quitbuf, strlen(quitbuf), 0);
               soclose(sock);   
               }
            }
         else           
            msgBox(hwndDlg, "User name error!", receivebuf);
         
         if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
            {
            CHAR tmsg[260];
            CHAR tbyte[260];
            INT gf, bf;
         
            memset(&receivebuf, 0, sizeof(receivebuf));
            send(sock, statbuf, strlen(statbuf), 0);
            rval = recv(sock, receivebuf, bsize, 0); 
            if (rval <= 0)
               {
               send(sock, quitbuf, strlen(quitbuf), 0);
               soclose(sock);   
               }
            }
         else
            {
            if( strstr(receivebuf, "Password") != NULL || strstr(receivebuf, "password") != NULL )
               {
               WinSetDlgItemText(hwndMainF, FID_TITLEBAR, receivebuf);
               DosBeep(2400, 50);
               DosSleep(3000);
               makeTBar();
               WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
               }
            }
            
         if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
            { 
            INT vnum, vb, index, highestindex;
            CHAR listc[260];
            CHAR num[80];
            CHAR TTnum[80];
      
            strndel(receivebuf, 4);
            if( receivebuf[0] == '0' )
               {
               // ************  DO NOTHING - NO MESSAGES
               }
            else
               {  
               // ************  Get number of messages and check them 
               vb = 0;
               do
                  {
                  num[vb] = receivebuf[vb];
                  vb++;
                  }
               while( receivebuf[vb] != ' ' );   
               num[vb] = '\0';

               vnum = atoi (&num[0]);
         
               zeropvdat();
               highestindex = -1;
               for( vb=0;vb<vnum;vb++ )
                  {
                  INT lnum, newlnum, totrec;
            
                  itoa(vb+1,num,10);
                  strcpy(listc, "TOP ");
                  strcat(listc, num);
                  strcat(listc, " 3");
                  strcat(listc, termn);
            
                  memset(&receivebuf, 0, sizeof(receivebuf));
                  memset(&receivebufA, 0, sizeof(receivebufA));
                  send(sock, listc, strlen(listc), 0);
            
                  lnum = 0;
                  totrec = 0;
                  do
                     {
                     newlnum = lnum;
                     rval = recv(sock, receivebufA, sizeof(receivebufA), 0); 
                     lnum = getStr2(newlnum, receivebuf, receivebufA);
                     }
                  while( lnum != -1 ); 

                  index = saveCodeHeaderData(receivebuf);   
                  if( index >= 0 )
                     highestindex = index;
                     
                  if( index >= 0 )
                     {
                     itoa(vb+1,TTnum,10);
                     strcpy(listc, "DELE ");
                     strcat(listc, TTnum);
                     strcat(listc, termn);
                     memset(&receivebufA, 0, sizeof(receivebufA));
                     send(sock, listc, strlen(listc), 0);
                     rval = recv(sock, receivebufA, bsize, 0); 
                     if( strnicmp(receivebufA, "+OK", 3) != 0 )
                        {
                        DosSleep(500);
                        memset(&receivebufA, 0, sizeof(receivebufA));
                        send(sock, listc, strlen(listc), 0);
                        rval = recv(sock, receivebufA, bsize, 0); 
                        if( strnicmp(receivebufA, "+OK", 3) != 0 )
                           {
                           msgBox(hwndDlg, "Attention!", "Could not delete message on the server.");
                           }
                        }
                     }  
                  }   
               if( highestindex >= 0 )
                  {
                  USHORT usReturn;
                  HWND hNewFrame;
                  PHAILNOTEFORMINFO pHAILNOTEFormInfo = malloc(sizeof(HAILNOTEFORMINFO));
      
                  
                  reverselist(highestindex);
                  send(sock, quitbuf, strlen(quitbuf), 0);
                  soclose(sock);   
                  pHAILNOTEFormInfo->hwnd = hwndDlg;
                  pHAILNOTEFormInfo->index = highestindex+1;
                  hNewFrame = OpenHAILNOTE(hwndDlg, pHAILNOTEFormInfo);
                  usReturn = (USHORT) WinProcessDlg(hNewFrame);
                  savetolog(highestindex); 
                  }        
               }
            }
         }
      send(sock, quitbuf, strlen(quitbuf), 0);
      soclose(sock);   
      }
   DosWaitEventSem(hev, TINTERVAL);
   memset(&receivebuf, 0, sizeof(receivebuf));
   }
while( !STOPME );

fgndcolor = CLR_BLACK;   
WinSetPresParam(WinWindowFromID(hwndDlg, 1006), 
                        PP_FOREGROUNDCOLORINDEX,
                        sizeof(ULONG),     
                        &fgndcolor);     
WinQueryDlgItemText(hwndDlg, 1002, sizeof(conon), conon);
if( strcmp(conon, "Listen OFF") == 0 || pgmData[7] < 3 )
   {
   WinEnableWindow(WinWindowFromID(hwndDlg, 1006), TRUE);
   WinSetDlgItemText(hwndDlg, 1006, "Monitor OFF");
   }
DosBeep(1250, 50);
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




INT reverselist(INT num)
{
INT i, z;


num++;
if( num > RECNUM )
   num = RECNUM;

for( z=0;z<num-1;z++ )
   {
   strcpy(onerec.INDATE, pvdat[num-1].INDATE);
   strcpy(onerec.INFROM, pvdat[num-1].INFROM);
   strcpy(onerec.REPTO, pvdat[num-1].REPTO);
   strcpy(onerec.INSUBJECT, pvdat[num-1].INSUBJECT);
   strcpy(onerec.INPORTS, pvdat[num-1].INPORTS);
   strcpy(onerec.INNOTE, pvdat[num-1].INNOTE);
   for( i=num-1;i>0+z;i-- )
         {
         strcpy(pvdat[i].INDATE, pvdat[i-1].INDATE);
         strcpy(pvdat[i].INFROM, pvdat[i-1].INFROM);
         strcpy(pvdat[i].REPTO, pvdat[i-1].REPTO);
         strcpy(pvdat[i].INSUBJECT, pvdat[i-1].INSUBJECT);
         strcpy(pvdat[i].INPORTS, pvdat[i-1].INPORTS);
         strcpy(pvdat[i].INNOTE, pvdat[i-1].INNOTE);
         }
   strcpy(pvdat[0+z].INDATE, onerec.INDATE);
   strcpy(pvdat[0+z].INFROM, onerec.INFROM);
   strcpy(pvdat[0+z].REPTO, onerec.REPTO);
   strcpy(pvdat[0+z].INSUBJECT, onerec.INSUBJECT);
   strcpy(pvdat[0+z].INPORTS, onerec.INPORTS);
   strcpy(pvdat[0+z].INNOTE, onerec.INNOTE);
   }      
return(1);   
}




VOID zeroLog(VOID)
{
INT i;

for( i=0;i<LOGNUM;i++ )
   {
   logdat[i].INDATE[0] = '\0';
   logdat[i].INFROM[0] = '\0';
   logdat[i].REPTO[0] = '\0';
   logdat[i].INSUBJECT[0] = '\0';
   logdat[i].INPORTS[0] = '\0';
   logdat[i].INNOTE[0] = '\0';
   }
}




INT makeNewLog(FILE *hand)
{
hand = fopen(nclog, "w+b" );
if( hand == NULL )
   return(-1);
else
   {
   fwrite(pvdat, sizeof(pvdat), 1, hand);
   fclose(hand);
   return(1);
   }   
}




INT replaceLog(FILE *hand)
{
hand = fopen(nclog, "w+b" );
if( hand == NULL )
   return(-1);
else
   {
   fwrite(logdat, sizeof(logdat), 1, hand);
   fclose(hand);
   return(1);
   }   
}




INT savetolog(INT num)
{
FILE *han;
FILE *pvhan;
CHAR smarker[] = "\5e";
CHAR emarker[] = "\7e";
CHAR newLine[] = "\n";
CHAR space[] = "     ";
INT i, j;


han = fopen(nclog, "r+b" );
if( han == NULL )
   {
   if( makeNewLog(han) == -1 )
      return(-1);
   else   
      return(1);      
   }
else
   {
   INT slen, w;
   INT newtot, tmptot;

   
   zeroLog();
   fread(&logdat, sizeof(logdat), 1, han);
   fclose(han);

   j = 0;
   do
      {
      slen = strlen(logdat[j].INDATE);
      if( slen > 0 )
         j++;
      }
   while( slen > 0 );

   newtot = num+1+j ;
   tmptot = num+1+j ;

   if( newtot <= LOGNUM )
      {
      for( i=j;i>0;i-- )
         {
         strcpy(logdat[(i-1)+num+1].INDATE, logdat[i-1].INDATE);
         strcpy(logdat[(i-1)+num+1].INFROM, logdat[i-1].INFROM);
         strcpy(logdat[(i-1)+num+1].REPTO, logdat[i-1].REPTO);
         strcpy(logdat[(i-1)+num+1].INSUBJECT, logdat[i-1].INSUBJECT);
         strcpy(logdat[(i-1)+num+1].INPORTS, logdat[i-1].INPORTS);
         strcpy(logdat[(i-1)+num+1].INNOTE, logdat[i-1].INNOTE);
         }
         
      for( i=0;i<(num+1);i++ )
         {
         strcpy(logdat[i].INDATE, pvdat[i].INDATE);
         strcpy(logdat[i].INFROM, pvdat[i].INFROM);
         strcpy(logdat[i].REPTO, pvdat[i].REPTO);
         strcpy(logdat[i].INSUBJECT, pvdat[i].INSUBJECT);
         strcpy(logdat[i].INPORTS, pvdat[i].INPORTS);
         strcpy(logdat[i].INNOTE, pvdat[i].INNOTE);
         }  
         
      if( replaceLog(han) == -1 )
         return(-1);
      else   
         return(1);
      }   
   else
      {
      INT dif;
      
      dif = newtot - LOGNUM;
      for( i=j-dif;i>0;i-- )
         {
         strcpy(logdat[(i-1)+num+1].INDATE, logdat[i-1].INDATE);
         strcpy(logdat[(i-1)+num+1].INFROM, logdat[i-1].INFROM);
         strcpy(logdat[(i-1)+num+1].REPTO, logdat[i-1].REPTO);
         strcpy(logdat[(i-1)+num+1].INSUBJECT, logdat[i-1].INSUBJECT);
         strcpy(logdat[(i-1)+num+1].INPORTS, logdat[i-1].INPORTS);
         strcpy(logdat[(i-1)+num+1].INNOTE, logdat[i-1].INNOTE);
         }
         
      for( i=0;i<(num+1);i++ )
         {
         strcpy(logdat[i].INDATE, pvdat[i].INDATE);
         strcpy(logdat[i].INFROM, pvdat[i].INFROM);
         strcpy(logdat[i].REPTO, pvdat[i].REPTO);
         strcpy(logdat[i].INSUBJECT, pvdat[i].INSUBJECT);
         strcpy(logdat[i].INPORTS, pvdat[i].INPORTS);
         strcpy(logdat[i].INNOTE, pvdat[i].INNOTE);
         }  
         
      if( replaceLog(han) == -1 )
         return(-1);
      else   
         return(1);
      }
   }
}




INT loadLogList(HWND hwnd)
{
FILE *han;


han = fopen(nclog, "r" );
if( han )
   {
   fread(&logdat, sizeof(logdat), 1, han);
   fclose(han);
   return(1);
   }
else
   {
   return(-1); 
   }
}




INT getStr2(INT cz, CHAR *tmp, CHAR *dStr)
{
INT cw;
BOOL ENDRCV;


ENDRCV = FALSE;
cw = 0;
do
   {
   tmp[cz] = dStr[cw];
   if( tmp[cz] == '\x0a' && tmp[cz-1] == '\x0d' && tmp[cz-2] == '\x2e' && tmp[cz-3] == '\x0a' && tmp[cz-4] == '\x0d' )
      {
      tmp[cz+1] = '\0';
      ENDRCV = TRUE;
      }
   cz++;   
   cw++;   
   }
while( (cz < bsize-4) && (dStr[cw] != '\0') && (ENDRCV == FALSE) );

if( ENDRCV )
   return(-1);
if( (cz >= bsize-5) )
   {
   if( tmp[cz-3] != '\x0d' && tmp[cz-2] != '\x0a' && tmp[cz-1] != '\x2e' )
      {
      tmp[cz] = '\0';
      strcat(tmp, "\x0d\x0a\0");
      }
   else
      tmp[cz] = '\0';
   return(-1);
   }
return(cz);
}




INT saveCodeHeaderData(CHAR *buf)
{
CHAR indata[bsize];
INT nx, index, sz;
CHAR indate[] = "Date: ";
CHAR infrom[] = "From: ";
CHAR repto[] = "Reply-To: ";
CHAR insubject[] = "Subject: ";
CHAR code[] = "Subject: &&$~NETCHATMSG~$&&";
CHAR inports[] = "NC%Ports: ";
CHAR innote[] = "NHC%Note: ";
CHAR *res1;
CHAR *res2;
CHAR *res3;
CHAR *res4;
CHAR *res5;
CHAR *res6;
CHAR *resh;


index = -1;
for( nx=0;nx<RECNUM;nx++ )
   {
   if( strlen(pvdat[nx].INFROM) > 0 )
      index = nx;
   }
index++;
   
sz = strlen(buf);
resh = NULL;
strcpy(indata, buf);
if(strlen(indata) > strlen(code) )
   resh = strstr(indata, code);
else
   return(-1);   
if( resh != NULL )
   {
   resh = NULL;
   if( sz <= bsize )
      {
      strcpy(indata, buf);
      res1 = NULL;
      res1 = strstr(indata, indate);
      if( res1 != NULL )
         {
         nx = 0;
         do
            {
            pvdat[index].INDATE[nx] = res1[nx+strlen(indate)];
            nx++;
            }
         while(res1[nx+strlen(indate)] != '\x0a');
         pvdat[index].INDATE[nx-1] = '\0';
         }
      else
         strcpy(pvdat[index].INDATE, "Unknown");   
      
      res2 = NULL;
      res2 = strstr(indata, infrom);
      if( res2 != NULL )
         {
         nx = 0;
         do
            {
            pvdat[index].INFROM[nx] = res2[nx+strlen(infrom)];
            nx++;
            }
         while(res2[nx+strlen(infrom)] != '\x0a');
         pvdat[index].INFROM[nx-1] = '\0';
         }
      else
         strcpy(pvdat[index].INFROM, "Unknown");   
      
      res3 = NULL;
      res3 = strstr(indata, repto);
      if( res3 != NULL )
         {
         nx = 0;
         do
            {
            pvdat[index].REPTO[nx] = res3[nx+strlen(repto)];
            nx++;
            }
         while(res3[nx+strlen(repto)] != '\x0a');
         pvdat[index].REPTO[nx-1] = '\0';
         }
      else
         strcpy(pvdat[index].REPTO, "No Reply-To address");   
      
      res4 = NULL;
      res4 = strstr(indata, insubject);
      if( res4 != NULL )
         {
         nx = 0;
         do
            {
            pvdat[index].INSUBJECT[nx] = res4[nx+strlen(insubject)];
            nx++;
            }
         while(res4[nx+strlen(insubject)] != '\x0a');
         pvdat[index].INSUBJECT[nx-1] = '\0';
         }
      else
         strcpy(pvdat[index].INSUBJECT, "Unknown");   
         
      res5 = NULL;
      res5 = strstr(indata, inports);
      if( res5 != NULL )
         {
         nx = 0;
         do
            {
            pvdat[index].INPORTS[nx] = res5[nx+strlen(inports)];
            nx++;
            }
         while(res5[nx+strlen(inports)] != '\x0a');
         pvdat[index].INPORTS[nx-1] = '\0';
         }
      else
         strcpy(pvdat[index].INPORTS, "Unknown");   
      
      res6 = NULL;
      res6 = strstr(indata, innote);
      if( res6 != NULL )
         {
         nx = 0;
         do
            {
            pvdat[index].INNOTE[nx] = res6[nx+strlen(innote)];
            nx++;
            }
         while( res6[nx+strlen(innote)] != '\x0a' );
         pvdat[index].INNOTE[nx-1] = '\0';
         }
      else
         {
         strcpy(pvdat[index].INNOTE, "No note sent");   
         }
         
      return(index);   
      }
   else
      {
      return(-1);      
      }
   }
else
   return(-1);   
}





INT getIPaddr(CHAR *locaddr)
{
BOOL  FOUNDINTERNETIP;
int			s, i;
struct ifconf	ifc;
struct ifreq	*ifr;
struct in_addr	inaddr;
struct hostent	*host;



FOUNDINTERNETIP = FALSE;
if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
   {
   // printf ("Error opening socket: %u\n", sock_errno());
    return(1);
    }

ifc.ifc_len = sizeof(ipbuf);
ifc.ifc_buf = ipbuf;
if (ioctl (s, SIOCGIFCONF, (char *) &ifc, sizeof(ifc)) < 0)
   {
   // printf("Error on ioctl(): %u\n", sock_errno());
   soclose(s);
   return(1);
   }

i = ifc.ifc_len / sizeof(struct ifreq);
for (ifr = ifc.ifc_req; i; i--, ifr++)
   {
   if (((struct sockaddr *) &ifr->ifr_addr)->sa_family == AF_INET)
      {
      if( pgmData[9] == 0 && (stricmp(ifr->ifr_name, "ppp0") == 0 || stricmp(ifr->ifr_name, "sl0") == 0) )
         {
         inaddr = ((struct sockaddr_in *) &ifr->ifr_addr)->sin_addr;
         host = gethostbyaddr ((char *) &inaddr, sizeof(inaddr), AF_INET);
         sprintf(locaddr, "%s", inet_ntoa(inaddr));
         }
      if( pgmData[9] == 1 && stricmp(ifr->ifr_name, "lan0") == 0 )
         {
         inaddr = ((struct sockaddr_in *) &ifr->ifr_addr)->sin_addr;
         host = gethostbyaddr ((char *) &inaddr, sizeof(inaddr), AF_INET);
         sprintf(locaddr, "%s", inet_ntoa(inaddr));
         }
      }
   }   

soclose(s);
FOUNDINTERNETIP = TRUE;

return(1);
}





/*
INT getIPaddr(CHAR *locaddr, CHAR *tmpfn)
{
CHAR nsexe[] = "cmd.exe";
CHAR nscom[] = "/C netstat.exe -a > ";
CHAR whcom[40];
HFILE fhan;
APIRET rc;
ULONG act, rd, local;
INT i, k, op;
CHAR fline[512] = "";
CHAR schStr[] = "interface 10";
CHAR schStrN[] = "interface 0";
BOOL  FOUNDINTERNETIP;
CHAR *res;


DosDelete(tmpfn);

FOUNDINTERNETIP = FALSE;

strcpy(whcom, nscom);
strcat(whcom, tmpfn);
callPgm(nsexe, whcom, PROG_WINDOWABLEVIO, SWP_HIDE, NULL, NULL);

i = 0;
op=0;
do
   {
   DosSleep(10);
   rc = DosOpen(tmpfn,
                      &fhan,
                      &act,
                      0L,
                      0L,
                      OPEN_ACTION_FAIL_IF_NEW |
                      OPEN_ACTION_OPEN_IF_EXISTS,
                      OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READONLY | OPEN_SHARE_DENYWRITE, 0L);
   op++;                   
   }
while( rc != 0  && op < 800 );
                    
if (rc != 0 )
   {
   DosClose(fhan);
   }
else
   {
   do
      {
      fline[0] = '\0';    
      k = 0;
      do
         {
         DosRead(fhan, fline+k, sizeof(fline[0]), &rd);
         if( fline[k] != '\n' )
            k++;
         }
      while( rd > 0 && fline[k] != '\n' );
      fline[k] = '\0';     
      
      res = NULL;
      if( pgmData[9] == 0 )
         res = strstr(fline, schStr);
      else   
         res = strstr(fline, schStrN);
      if( res != NULL )
         {
         INT g, s;
         
         strndel(fline, 4);
         s = 0;
         g = 0;
         do
            {
            if( fline[s] == ' ' )
               g = s;
            s++;   
            }
         while(fline[s] == ' ');   
         strndel(fline, g+1);
         s = 0;
         g = 0;
         do
            {
            if( fline[s] == ' ' )
               g = s;
            }
         while(fline[s++] != ' ');   
         fline[g] = '\0';   
         FOUNDINTERNETIP = TRUE;
         }
      }
   while(rd != 0 && !FOUNDINTERNETIP);
   }
DosClose(fhan);
DosDelete(tmpfn);

if( FOUNDINTERNETIP )    
   strcpy(locaddr, fline);
else
   chkhost(locaddr);

return(1);
}





VOID chkhost(CHAR *locaddr)
{
struct in_addr in;
ULONG ip_addr=0;
ULONG local_ip;
CHAR *lad;


ip_addr = gethostid();
local_ip = lswap(ip_addr);
in.s_addr = local_ip;
lad = inet_ntoa(in);
strcpy(locaddr, lad);
}
*/





VOID sendEMail(PVOID chkmaildat)
{
HAB habT;
HMQ hmqT;
INT i;
HWND hwndDlg;
INT handle;
struct hostent *hp;    
struct sockaddr_in server;
char * host;
CHAR tmbuf[bsize];
CHAR sendbuf[bsize];
CHAR receivebuf[bsize];
CHAR receivebufM[bsize];
CHAR rcvbuf[64];
CHAR serverbuf[260];
// CHAR userbuf[260];
CHAR passwordbuf[260];
CHAR statbuf[260];
CHAR listbuf[260];
CHAR mfName[] = "hail.tmp";
CHAR quitbuf[] = "QUIT\x0d\x0a";
CHAR helobuf[260];
CHAR mfrom[260];
CHAR mto[260];
CHAR rto[260];
CHAR msub[260];
CHAR data[] = "DATA\x0d\x0a";
CHAR termn[] = "\x0d\x0a";
CHAR eomsg[] = "\x0d\x0a\x0d\x0a\x2e\x0d\x0a";
INT sock, rval, rv;
INT ina;
INT len;
INT mailreceiveport = 25;
// INT mailreceiveport = 110;
INT retn;
FILE *Hanv;
// INT dontblock;
BOOL FSTTIME;



habT = WinInitialize(0);
hmqT = WinCreateMsgQueue(habT, 0);
WinCancelShutdown(hmqT, TRUE);

hwndDlg = ((PFCBD)chkmaildat)->hwndDlg;
handle = ((PFCBD)chkmaildat)->interval;

/*
if( !registered(ncpw) )
   {
   USHORT usReturn;
   HWND hNewFrame;
   
   
   hNewFrame = OpenABOUT(hwndMainDlg, 0);
   usReturn = (USHORT) WinProcessDlg(hNewFrame);
   }
*/

WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), FALSE);

WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Initiating Hail message.");

strcpy(helobuf, "HELO ");
strcat(helobuf, mailServer2);
strcat(helobuf, termn);


strcpy(mfrom, "MAIL FROM:");
strcat(mfrom, "<");
strcat(mfrom, userName2);
strcat(mfrom, ">");
strcat(mfrom, termn);

if( strlen(rtema) > 0 && strlen(rtname) > 0 )
   {
   strcpy(rto, "Reply-To:");
   strcat(rto, "<");
   strcat(rto, rtema);
   strcat(rto, ">");
   strcat(rto, " (");
   strcat(rto, rtname);
   strcat(rto, ")");
   strcat(rto, termn);
   }
else
   {   
   strcpy(rto, "");
   }


strcpy(mto, "RCPT TO:");
strcat(mto, "<");
strcat(mto, ncData[handle].ncURL);
strcat(mto, ">");
strcat(mto, termn);

strcpy(serverbuf, mailServer2);
strcpy(passwordbuf, "PASS ");
strcat(passwordbuf, passWord2);
strcat(passwordbuf, termn);
strcpy(statbuf, "STAT");
strcat(statbuf, termn);
strcpy(listbuf, "LIST");
strcat(listbuf, termn);
strcpy(mmtoname, ncData[handle].ncName);



if( pgmData[38] == 1 )
   {
   CHAR cip[40];
   CHAR wmsg[1024];
   FILE *hanx;
   CHAR bstatus[40];
   INT tries;
         
   
  
   tries = 0;
   do
      {
      DosSleep(100);
      WinQueryDlgItemText(hwndMainDlg, 1002, sizeof(bstatus), bstatus);
      tries++;
      }
   while( !NOWLISTENING && tries < 100);    

   
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Querying data .....");
   getIPaddr(localIP);
   strcpy(msub, "Subject: ");
   strcat(msub, cphrase);
   strcat(msub, localIP);     
         
   strcat(msub, "\x0d\x0a");               
   strcat(msub, rto);               
           
   strcat(msub, "\x0d\x0a");               
   strcat(msub, "NC%Ports: ");               

   strcat(msub, "R:");               
   itoa(pgmData[4], cip, 10);
   strcat(msub, cip);               
   strcat(msub, " ");
                          
   strcat(msub, "T:");               
   itoa(pgmData[5], cip, 10);
   strcat(msub, cip);               
   strcat(msub, " ");
                           
   strcat(msub, "F:");               
   itoa(pgmData[8], cip, 10);
   strcat(msub, cip); 
   strcat(msub, "\x0d\x0a");               
   strdelc(NCHNote, '\x0a');
   strcat( NCHNote, "\x0d\x0a");
   strcat(msub, "NHC%Note: ");               
   strcat(msub, NCHNote);               
            
   strcat(msub, eomsg);
   
   if ((hanx = fopen("mess$.txt", "wb" )) != NULL)
      {
      fwrite(&msub, strlen(msub)+1, 1, hanx);   
      fclose(hanx);
      }
   else
      {
      WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
      msgBox(hwndDlg, "Attention!", "Could not create temporary file!");
      makeTBar();
      WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      return;
      }   
   
   strcpy(wmsg, "sendmail -af mess$.txt");
   strcat(wmsg, " -f ");
   strcat(wmsg, userName2);
   strcat(wmsg, " -t ");
   strcat(wmsg, ncData[handle].ncURL);
   WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Attempting to send Hailing message .....");
   system(wmsg);      
   msdat.hwndDlg = hwndDlg;
   msdat.interval = 1;
   _beginthread(mailSendStatus, NULL, BSTACK, (PVOID)&msdat);
   remove("mess$.txt");
   }
else
   {   
   sock_init();

   sock = socket(AF_INET, SOCK_STREAM, 0);

   // dontblock = 1;
   // ioctl(sock, FIONBIO, (char *) &dontblock, sizeof(dontblock));

   if (sock < 0)
      {
      WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
      errorMsgInt(sock_errno(), "Can't open socket! Error code : ");
      // msgBox(hwndDlg, "Attention!", "Couldn't open socket!");
      makeTBar();
      WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
      soclose(sock);   
      WinDestroyMsgQueue(hmqT);
      WinTerminate(habT);
      _endthread();
      }
   else
      {
      hp = gethostbyname(serverbuf);
      if (!hp) 
         {
         WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
         errorMsgInt(sock_errno(), "Can't get host name! Error code : ");
         // msgBox(hwndDlg, "Attention!", "Can't get host name!");
         makeTBar();
         WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
         soclose(sock);   
         WinDestroyMsgQueue(hmqT);
         WinTerminate(habT);
         _endthread();
         } 
      else 
         {
         memset(&server, 0, sizeof(server));
         bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
         // server.sin_addr.s_addr = inet_addr(hp->h_addr);
         server.sin_port = htons(mailreceiveport);
         server.sin_family = AF_INET;
        
         WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Connecting with mail server.");
      
         if(connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
            {
            WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
            // msgBox(hwndDlg, "Attention!", "Can't connect to servers mail port!");
            errorMsgInt(sock_errno(), "Cannot connect to port! Error code : ");
            makeTBar();
            WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            WinDestroyMsgQueue(hmqT);
            WinTerminate(habT);
            _endthread();
            }
         else 
            {
            memset(&receivebuf, 0, sizeof(receivebuf));
            
            // rval = recv(sock, receivebuf, bsize, 0); 

            FSTTIME = TRUE;
            do
               {
               memset(&tmbuf, 0, sizeof(tmbuf));
               rval = recv(sock, tmbuf, sizeof(tmbuf), 0);
               if( rval > 0 && !FSTTIME )
                  {
                  strcat(receivebuf, tmbuf);
                  }
               if( rval > 0 && FSTTIME )
                  {
                  FSTTIME = FALSE;
                  strcpy(receivebuf, tmbuf);
                  }
               }
            while( rval > 0 && tmbuf[rval-2] != '\x0d' && tmbuf[rval-1] != '\x0a' );

            // msgBox(hwndDlg, "receivebuf 01", receivebuf);
            // msgBox(hwndDlg, "Just connected!", receivebuf);
            if (rval < 0)
               {
               msgBox(hwndDlg, "Attention!", "Connect error!");
               makeTBar();
               WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
               soclose(sock);   
               WinDestroyMsgQueue(hmqT);
               WinTerminate(habT);
               _endthread();
               }
            }
         memset(&receivebuf, 0, sizeof(receivebuf));
         rv = send(sock, helobuf, strlen(helobuf), 0);
         rval = recv(sock, receivebuf, sizeof(receivebuf), 0); 
         // msgBox(hwndDlg, "receivebuf 02", receivebuf);

      
         // msgBox(hwndDlg, "After connect ...", receivebuf);
         // if( strlen(receivebuf) > 2  && strnicmp(receivebuf, "+OK", 3) == 0 )
         // debugMsgStr(receivebuf, "receivebuf");
   
         //*********   FROM :  **************
         if( strlen(receivebuf) > 3  && strnicmp(receivebuf, "250 ", 4) == 0 )
            {
            memset(&receivebuf, 0, sizeof(receivebuf));
            rv = send(sock, mfrom, strlen(mfrom), 0);
            rval = recv(sock, receivebuf, sizeof(receivebuf), 0); 
            }
         else
            {
            if( strlen(receivebuf) > 3  && strnicmp(receivebuf, "220 ", 4) == 0 )
               {
               memset(&receivebuf, 0, sizeof(receivebuf));
               rv = send(sock, helobuf, strlen(helobuf), 0);
               rval = recv(sock, receivebuf, sizeof(receivebuf), 0); 
               if( strlen(receivebuf) > 3  && strnicmp(receivebuf, "250 ", 4) == 0 )
                  {
                  memset(&receivebuf, 0, sizeof(receivebuf));
                  rv = send(sock, mfrom, strlen(mfrom), 0);
                  rval = recv(sock, receivebuf, sizeof(receivebuf), 0); 
                  }
               else
                  {
                  WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
                  msgBox(hwndDlg, "Attention! Server error #1!", receivebuf);
                  // msgBox(hwndDlg, "Attention!", "Connect error! Sender's address not recognized by server.");
                  makeTBar();
                  WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
                  send(sock, quitbuf, strlen(quitbuf), 0);
                  soclose(sock);   
                  WinDestroyMsgQueue(hmqT);
                  WinTerminate(habT);
                  _endthread();
                  }
               }
            else
               {   
               WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
               msgBox(hwndDlg, "Attention! Server error #2!", receivebuf);
               // msgBox(hwndDlg, "Attention!", "Connect error! Sender's address not recognized by server.");
               makeTBar();
               WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
               send(sock, quitbuf, strlen(quitbuf), 0);
               soclose(sock);   
               WinDestroyMsgQueue(hmqT);
               WinTerminate(habT);
               _endthread();
               }
            }   


         // msgBox(hwndDlg, "After mfrom ...", receivebuf);
         // debugMsgStr(receivebuf, "receivebuf");
      
         //*********   TO :  **************
         if( strlen(receivebuf) > 3  && strnicmp(receivebuf, "250 ", 4) == 0 )
            {
            memset(&receivebuf, 0, sizeof(receivebuf));
            rv = send(sock, mto, strlen(mto), 0);
            rval = recv(sock, receivebuf, sizeof(receivebuf), 0); 
            }
         else
            {
            WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
            msgBox(hwndDlg, "Attention! Server error #3!", receivebuf);
            // msgBox(hwndDlg, "Attention!", "Connect error! Destination address not recognized by server.");
            makeTBar();
            WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            WinDestroyMsgQueue(hmqT);
            WinTerminate(habT);
            _endthread();
            }   
      
         WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), "Sending Hail message to server.");
      
         //*********   SENDING DATA :  **************
         if( strlen(receivebuf) > 3  && strnicmp(receivebuf, "250 ", 4) == 0 )
            {
            memset(&receivebuf, 0, sizeof(receivebuf));
            rv = send(sock, data, strlen(data), 0);
            rval = recv(sock, receivebuf, sizeof(receivebuf), 0); 
            }
         else   
            {
            WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
            msgBox(hwndDlg, "Attention! Server error #4!", receivebuf);
            // msgBox(hwndDlg, "Attention!", "Server did not recognize the DATA command.");
            makeTBar();
            WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
            send(sock, quitbuf, strlen(quitbuf), 0);
            soclose(sock);   
            WinDestroyMsgQueue(hmqT);
            WinTerminate(habT);
            _endthread();
            }   
      
         if( strlen(receivebuf) > 3  && strnicmp(receivebuf, "354 ", 4) == 0 )
            {
            CHAR cip[40];
         
            getIPaddr(localIP);
            strcpy(msub, "Subject: ");
            strcat(msub, cphrase);
            strcat(msub, localIP);     
         
            strcat(msub, "\x0d\x0a");               
            strcat(msub, rto);               
            
            strcat(msub, "\x0d\x0a");               
            strcat(msub, "NC%Ports: ");               

            strcat(msub, "R:");               
            itoa(pgmData[4], cip, 10);
            strcat(msub, cip);               
            strcat(msub, " ");
                           
            strcat(msub, "T:");               
            itoa(pgmData[5], cip, 10);
            strcat(msub, cip);               
            strcat(msub, " ");
                           
            strcat(msub, "F:");               
            itoa(pgmData[8], cip, 10);
            strcat(msub, cip); 
            strcat(msub, "\x0d\x0a");               
            strdelc(NCHNote, '\x0a');
            strcat( NCHNote, "\x0d\x0a");
            strcat(msub, "NHC%Note: ");               
            strcat(msub, NCHNote);               
            
            strcat(msub, eomsg);
         
            strcpy(receivebufM, msub);               
            memset(&receivebuf, 0, sizeof(receivebuf));
            rv = send(sock, receivebufM, strlen(receivebufM), 0);
            rval = recv(sock, receivebuf, sizeof(receivebuf), 0); 
            if( rval <= 0 )
               {
               WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
               msdat.hwndDlg = hwndDlg;
               msdat.interval = 0;
               _beginthread(mailSendStatus, NULL, BSTACK, (PVOID)&msdat);
               }
            else
               {   
               if( pgmData[7] < 2 )
                  WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
               msdat.hwndDlg = hwndDlg;
               msdat.interval = 1;
               _beginthread(mailSendStatus, NULL, BSTACK, (PVOID)&msdat);
               }
            //************  Get answer or confirmation of sent mail **************
            }
         else
            {
            msgBox(hwndDlg, "Attention! Server error #5!", receivebuf);
            WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
            msdat.hwndDlg = hwndDlg;
            msdat.interval = 0;
            _beginthread(mailSendStatus, NULL, BSTACK, (PVOID)&msdat);
            }
         }
      memset(&receivebuf, 0, sizeof(receivebuf));
      send(sock, quitbuf, strlen(quitbuf), 0);
      rval = recv(sock, receivebuf, bsize, 0); 
      if (rval <= 0)
         {
         makeTBar();
         WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
         send(sock, quitbuf, strlen(quitbuf), 0);
         soclose(sock);   
         WinDestroyMsgQueue(hmqT);
         WinTerminate(habT);
         _endthread();
         }
      soclose(sock);   
      }
   }
   
if( pgmData[7] < 3 )
   WinEnableWindow(WinWindowFromID(WinWindowFromID(hwndDlg, FID_CLIENT), 1007), TRUE);
makeTBar();
WinSetWindowText(WinWindowFromID(hwndMainF, FID_TITLEBAR), tbarmsg);
WinDestroyMsgQueue(hmqT);
WinTerminate(habT);
_endthread();
}




VOID callPgm(PSZ PgmName, PSZ PgmInputs, SHORT PgmType,
	         ULONG swapStuff, PSZ startDir,  PSZ title )
{
PROGDETAILS  pDetails;

pDetails.Length          = sizeof(PROGDETAILS);
pDetails.progt.progc     = PgmType;
pDetails.progt.fbVisible = SHE_VISIBLE;
pDetails.pszTitle        = title;
pDetails.pszExecutable   = PgmName;
pDetails.pszParameters   = PgmInputs;
pDetails.pszStartupDir   = startDir;
pDetails.pszIcon         = "";
pDetails.pszEnvironment  = NULL;
pDetails.pszEnvironment  = "";
pDetails.swpInitial.fl   = swapStuff; 
pDetails.swpInitial.cy   = 0;    
pDetails.swpInitial.cx   = 0;    
pDetails.swpInitial.y    = 0;    
pDetails.swpInitial.x    = 0;    
pDetails.swpInitial.hwndInsertBehind = HWND_TOP;
pDetails.swpInitial.hwnd             = NULLHANDLE;
pDetails.swpInitial.ulReserved1      = 0;
pDetails.swpInitial.ulReserved2      = 0;

WinStartApp( NULLHANDLE, &pDetails, PgmInputs, NULL, 1);
}



BOOL registered(CHAR *pw)
{
if(stricmp(pw, rname) == 0 && KEYISTHERE )
   return(TRUE);
return(FALSE);
}




VOID bugem(HWND hwndDlg)
{
if( !registered(ncpw) )
   {
   INT k;
   
   for( k=0;k<5;k++ )
      {
      WinSetWindowText(WinWindowFromID(hwndDlg, FID_TITLEBAR), "Registered versions don't do this!");
      DosBeep(1200, 50);
      DosSleep(550);
      WinSetWindowText(WinWindowFromID(hwndDlg, FID_TITLEBAR), "");
      DosSleep(550);
      }
   }
}





VOID msgBox(HWND hwnd, CHAR *title, CHAR *message)
{
WinMessageBox(HWND_DESKTOP,
                     hwnd,
                     message,
                     title,
                     0,
                     MB_OK | MB_ICONEXCLAMATION );
}




INT msgBoxOKCANCEL(HWND hwndDlg, CHAR *title, CHAR *msg)
{
if ( WinMessageBox(HWND_DESKTOP,
                          hwndDlg,
                          msg,
                          title,
                          0,
                          MB_ICONEXCLAMATION | MB_OKCANCEL) == MBID_CANCEL )
   {
   return(0);
   }
else
   return(1);
}





VOID ncRunning(VOID)
{
SWCNTRL sw;
USHORT numTasks, bufSize;
PSWBLOCK pswb;
PVOID bm;
HWND wt[100];   
INT i, k;


numTasks = WinQuerySwitchList(0, NULL, 0);
bufSize = sizeof(SWBLOCK) * numTasks;
DosAllocMem(&bm, bufSize, PAG_READ | PAG_WRITE | PAG_COMMIT);
pswb = bm;
WinQuerySwitchList(0, pswb, bufSize);

for( k=0;k<100;k++ )
   {
   if( (WinIsWindow(0, wt[k])) == PMERR_INVALID_HWND )
      wt[k] = NULLHANDLE;
   }
      
for( i=0;i<numTasks;i++)
   {
   sw = *(PSWCNTRL) ((CHAR*)&(pswb[i].aswentry[0].swctl) - sizeof(ULONG)*i);
   if( sw.hwnd != NULLHANDLE )
      {
      if( strcmp(sw.szSwtitle, "NetChat for OS/2") == 0 )
         {
         DosFreeMem(bm);
         exit(0);
         }
      }   
   }
DosFreeMem(bm);
}   


INT readKey(VOID)
{
CHAR waste;
CHAR fn[20];
FILE *hanv;
INT v;
ULONG siz;
 

if( existFile("main.key") == 0 )
   {
   if( existFile("guest.key") == 0 )
      return(0);
   else
      {
      strcpy(fn, "guest.key");
      }   
   }
else
   {
   strcpy(fn, "main.key");
   }    

siz = getFSize(fn);
if( siz != 2564 )
   return(0);

if ((hanv = fopen( fn, "rb" )) == NULL)
   {
   fclose(hanv);
   return(0);
   }

strcpy(rname, "");
strcpy(rkey, "");
strcpy(rtype, "");

for( v=0;v<2564;v++ )
   {
   switch(v)
      {
      case 69 :
         {
         fread(&rtype[0], sizeof(CHAR), 1, hanv);   
         }
         break;
         
      case 1269 :
         {
         fread(&rtype[1], sizeof(CHAR), 1, hanv);   
         }
         break;
         
      case 2069 :
         {
         fread(&rtype[2], sizeof(CHAR), 1, hanv);   
         }
         break;
         
      // *****************************************   
      // *****************************************   
         
      case 2545 :
         fread(&rname[0], sizeof(CHAR), 1, hanv);   
         break;
         
      case 542 :
         fread(&rname[1], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2455 :
         fread(&rname[2], sizeof(CHAR), 1, hanv);   
         break;
         
      case 25 :
         fread(&rname[3], sizeof(CHAR), 1, hanv);   
         break;
         
      case 925 :
         fread(&rname[4], sizeof(CHAR), 1, hanv);   
         break;
         
      case 845 :
         fread(&rname[5], sizeof(CHAR), 1, hanv);   
         break;
         
      case 805 :
         fread(&rname[6], sizeof(CHAR), 1, hanv);   
         break;
         
      case 1795 :
         fread(&rname[7], sizeof(CHAR), 1, hanv);   
         break;
         
      case 115 :
         fread(&rname[8], sizeof(CHAR), 1, hanv);   
         break;
         
      case 511 :
         fread(&rname[9], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2005 :
         fread(&rname[10], sizeof(CHAR), 1, hanv);   
         break;
         
      case 770 :
         fread(&rname[11], sizeof(CHAR), 1, hanv);   
         break;
         
      case 1216 :
         fread(&rname[12], sizeof(CHAR), 1, hanv);   
         break;
         
      case 67 :
         fread(&rname[13], sizeof(CHAR), 1, hanv);   
         break;
         
      case 904 :
         fread(&rname[14], sizeof(CHAR), 1, hanv);   
         break;
         
      case 789 :
         fread(&rname[15], sizeof(CHAR), 1, hanv);   
         break;
         
      case 932 :
         fread(&rname[16], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2430 :
         fread(&rname[17], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2222 :
         fread(&rname[18], sizeof(CHAR), 1, hanv);   
         break;
         
      case 200 :
         fread(&rname[19], sizeof(CHAR), 1, hanv);   
         break;
         
      case 1020 :
         fread(&rname[20], sizeof(CHAR), 1, hanv);   
         break;
         
      case 20 :
         fread(&rname[21], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2000 :
         fread(&rname[22], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2010 :
         fread(&rname[23], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2210 :
         fread(&rname[24], sizeof(CHAR), 1, hanv);   
         break;
         
      case 28 :
         fread(&rname[25], sizeof(CHAR), 1, hanv);   
         break;
         
      case 640 :
         fread(&rname[26], sizeof(CHAR), 1, hanv);   
         break;
         
      case 460 :
         fread(&rname[27], sizeof(CHAR), 1, hanv);   
         break;
         
      case 1409 :
         fread(&rname[28], sizeof(CHAR), 1, hanv);   
         break;
         
      case 975 :
         fread(&rname[29], sizeof(CHAR), 1, hanv);   
         break;
         
      case 673 :
         fread(&rname[30], sizeof(CHAR), 1, hanv);   
         break;
         
      case 439 :
         fread(&rname[31], sizeof(CHAR), 1, hanv);   
         break;
         
      case 218 :
         fread(&rname[32], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2557 :
         fread(&rname[33], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2121 :
         fread(&rname[34], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2001 :
         fread(&rname[35], sizeof(CHAR), 1, hanv);   
         break;
         
      case 378 :
         fread(&rname[36], sizeof(CHAR), 1, hanv);   
         break;
         
      case 499 :
         fread(&rname[37], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2344 :
         fread(&rname[38], sizeof(CHAR), 1, hanv);   
         break;
         
      case 400 :
         fread(&rname[39], sizeof(CHAR), 1, hanv);   
         break;
         
      // *****************************************   
      // *****************************************   
         
      case 47 :
         fread(&rkey[0], sizeof(CHAR), 1, hanv);   
         break;
         
      case 347 :
         fread(&rkey[1], sizeof(CHAR), 1, hanv);   
         break;
         
      case 1357 :
         fread(&rkey[2], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2519 :
         fread(&rkey[3], sizeof(CHAR), 1, hanv);   
         break;
         
      case 1212 :
         fread(&rkey[4], sizeof(CHAR), 1, hanv);   
         break;
         
      case 253 :
         fread(&rkey[5], sizeof(CHAR), 1, hanv);   
         break;
         
      case 2201 :
         fread(&rkey[6], sizeof(CHAR), 1, hanv);   
         break;
         
      case 333 :
         fread(&rkey[7], sizeof(CHAR), 1, hanv);   
         break;
         
      case 451 :
         fread(&rkey[8], sizeof(CHAR), 1, hanv);   
         break;
         
      case 670 :
         fread(&rkey[9], sizeof(CHAR), 1, hanv);   
         break;
         
      case 1402 :
         fread(&rkey[10], sizeof(CHAR), 1, hanv);   
         break;
         
      case 1299 :
         fread(&rkey[11], sizeof(CHAR), 1, hanv);   
         break;
         
      case 991 :
         fread(&rkey[12], sizeof(CHAR), 1, hanv);   
         break;
      
      default :
         fread(&waste, sizeof(CHAR), 1, hanv);   
         break;
      }
   }
fclose(hanv);

return(1);
}



BOOL saveToDTFile(CHAR *buf, CHAR *fn)  
{                                        
PVOID iobuf;
ULONG ulBufferSize, ulSize, ulAction, ulBytesWritten, ulLines ;
LONG lOffset = 0L ;
HFILE hfile ;
APIRET apiret ;
HWND hwndMLE;


ulBufferSize = strlen(buf)+2;

if( DosAllocMem((PPVOID)&iobuf, ulBufferSize, PAG_WRITE | PAG_COMMIT))
   {
   WinAlarm( HWND_DESKTOP, WA_ERROR) ;
   return FALSE ;
   }

WinSendMsg( hwndMLE, MLM_SETIMPORTEXPORT,          /* these two messages set up the transfer */
               MPFROMP(iobuf), MPFROMLONG(ulSize)) ;     /* of the MLE text to the iobuf             */
WinSendMsg(hwndMLE, MLM_EXPORT, MPFROMP((PIPT)&lOffset), MPFROMP(&ulSize)) ;

apiret = DosOpen(fn, &hfile,
                      &ulAction,
                      ulBufferSize,
                      FILE_NORMAL,
                      OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                      OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYWRITE | OPEN_FLAGS_SEQUENTIAL, NULL);
if( apiret )                       
   {
   WinAlarm( HWND_DESKTOP, WA_ERROR) ;
   DosFreeMem(iobuf) ;
   return FALSE ;
   }

apiret = DosWrite(hfile, buf, ulBufferSize, &ulBytesWritten);
   
if( apiret )
   {
   WinAlarm(HWND_DESKTOP, WA_ERROR) ;
   DosClose(hfile) ;
   DosFreeMem(iobuf) ;
   return(FALSE);
   }
DosClose( hfile) ;
DosFreeMem(iobuf) ;
return(TRUE);
}


VOID openFolder(CHAR *fold)
{
WinOpenObject(WinQueryObject(fold), 1, TRUE);
}




VOID errorMsgInt(INT num, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Error! ";

strcat(dMsg, varName),
itoa(num, str, 10);
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}







VOID msgOK(CHAR *title, CHAR *message)
{
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              message,
              title,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}


VOID debugMsgStr(CHAR *str, CHAR *varName)
{
CHAR dMsg[255] = "Debug Message string ... ";

strcat(dMsg, varName),
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}




VOID debugMsgInt(INT num, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message Int ... ";

strcat(dMsg, varName),
itoa(num, str, 10);
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}




VOID debugMsgULong(ULONG num, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message ULong ... ";

strcat(dMsg, varName),
ultoa(num, str, 10);
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}


VOID debugMsgLong(LONG num, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message Long ... ";

strcat(dMsg, varName),
ltoa(num, str, 10);
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}


VOID debugMsgCH(CHAR ch, CHAR *varName)
{
CHAR str[255] = "";
CHAR dMsg[255] = "Debug Message char ... ";

strcat(dMsg, varName),
str[0] = ch;
str[1] = '\0';
WinMessageBox(HWND_DESKTOP,
              HWND_DESKTOP,
              str,
              dMsg,
              0,
              MB_OK | MB_ICONEXCLAMATION );
}


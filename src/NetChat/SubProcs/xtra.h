/* XTRA.H */

#define INCL_WIN
#define INCL_DOS
#define INCL_WINWORKPLACE
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <process.h>
#include <types.h>
#include <direct.h>
#include <sys\stat.h>
#include <netinet\in.h>
#include <sys\socket.h>
#include <netdb.h>
#include <sys\ioctl.h>
#include <net\if.h>

#include <sys\ioctl.h>
#include <net\route.h>
#include <net\if.h>
#include <net\if_arp.h>
 

#define MAXDROPSIZE 5000
#define CNAMESIZE     40
#define MAXSTRING    1024
#define MSGSIZE        4096
#define BSTACK        524288
// #define BSTACK        262144
#define bsize            4096
#define RECNUM        100
#define LOGNUM        100
#define NAMESIZE      260
#define NOTESIZE      500
#define FILEXMTSIZE  8192
#define FTPHDRSIZE   10
#define PHRTXTLIMIT  500
#define PHRNUMRECS  100
#define EOSIZE           7
#define PHRDATAFILE  "phr.dat"
#define WM_COMMANDUSER    5505

typedef struct CData
   {
   HWND hwndF;
   HWND hwndDlg;
   CHAR dTopFold[260];
   CHAR ftitle[260];
   INT interval;
   }CBD;
typedef CBD FAR *PFCBD;

struct PHRdata
   {
   INT index;
   CHAR phrase[500];
   }PHR[PHRNUMRECS];

struct PHRdata PHRTMP;

typedef struct INETData
   {
   CHAR INDATE[80];
   CHAR INSUBJECT[1024];
   CHAR INFROM[1024];
   CHAR REPTO[1024];
   CHAR INPORTS[40];
   CHAR INNOTE[1024];
   }INETD;
typedef INETD FAR *PFINETD;

struct NCTMPR
   {
   SHORT indx;
   CHAR ncName[NAMESIZE];
   CHAR ncURL[NAMESIZE];
   CHAR ncNote[NOTESIZE];
   }ncTmpr;

struct NCDATA
   {
   SHORT indx;
   CHAR ncName[NAMESIZE];
   CHAR ncURL[NAMESIZE];
   CHAR ncNote[NOTESIZE];
   }ncData[RECNUM];

extern CHAR passWord[];
extern CHAR userName[];
extern CHAR nickName[];
extern CHAR mailServer[];
extern CHAR passWord2[];
extern CHAR userName2[];
extern CHAR rtname[];
extern CHAR rtema[];
extern CHAR mailServer2[];
extern CHAR hailingAddr[];
extern CHAR hailingName[];
extern CHAR appName[];
extern CHAR nclog[];
extern CHAR ncDataFile[];
extern CHAR INIFILE[];
extern CHAR cphrase[];
extern INT STOPME;
extern INT PAUSEAC;
extern HEV hev;
extern CHAR guestIP[260];
extern CHAR eochunk[];
extern CHAR eofile[];
extern CHAR tmpFileName[];
extern CHAR ncversion[];
extern CHAR NCHNote[1024];
extern CHAR eoNCHMSG[];

CHAR tstr[MAXDROPSIZE];
CHAR	ipbuf[10240];
CBD haildat, msdat;
INETD pvdat[RECNUM];
INETD logdat[LOGNUM];
INETD onerec;
INT globsock, globsockt, globnsock, ftpsock, ftpnsock, ftpcsock;
struct sockaddr_in globserver, globservert, globclient, ftpserver, ftpclient, ftpserverc;
BOOL CLOSESERVER;
BOOL WASCONNECTED;
INT mmm;
HWND hwndMainDlg, hwndMainF;
INT rcvthread, sendthread, activen;
BOOL SERVERON;
HWND hwndMLBPopup, hwndMLPPopup;
HWND hwndMLENEW1Popup, hwndMLENEW2Popup;
PFNWP moldWinProc, poldWinProc;
PFNWP oldmle2WinProc;
PFNWP oldmle1WinProc;
PFNWP oldNoteProc;
LONG pgmData[60];
HINI hini;
INT TINTERVAL;
CHAR sendbuf[MSGSIZE];
CHAR tmpsendbuf[MSGSIZE];
CHAR rcvbuf[MSGSIZE];
CHAR tmprcvbuf[MSGSIZE];
CHAR hnipaddr[260];
CHAR logpaddr[260];
CHAR tbarmsg[260];
BOOL SENTALREADY;
CHAR SFile[MAXSTRING];
CHAR FQSFile[MAXSTRING];
CHAR SPath[MAXSTRING];
CHAR RFile[MAXSTRING];
CHAR FQRFile[MAXSTRING];
CHAR RPath[MAXSTRING];
FILEDLG SFileDlg;
FILEDLG RFileDlg;
CHAR transfile[MAXSTRING];
CHAR SFileSize[40];
BOOL STILLWAITING;
INT numPackets;
INT packstorcv;
CHAR packstorcvstr[80];
INT numPacketsx;
INT packstosend;
CHAR packstosendstr[80];
INT FTPPORT;
CHAR DEFDLDIR[260];
CHAR DEFULDIR[260];
CHAR localIP[260];
CHAR ncpw[40];
BOOL FILENOTIFY;
BOOL NOWCONNECTED1;
BOOL NOWCONNECTED2;
BOOL FTPINPROGRESS;
BOOL LISTENWASOFF;
BOOL MLISTENWASOFF;
BOOL ABORTME;
HWND hNewPHRFrame;
PSWP pswp;
CHAR szCont[MAXSTRING];
CHAR szFN[MAXSTRING];
CHAR szFQFN[MAXSTRING];
CHAR ftPromptTB[MAXSTRING];
char rfppszTitle[MAXSTRING];
CHAR rfpfqf[MAXSTRING];
CHAR  PPAttrValue1[FACESIZE+64];
CHAR  PPAttrValue2[FACESIZE+64];
ULONG attra , attrb;
INT argcnt;
BOOL NOWLISTENING;
BOOL argL;
BOOL argM;
BOOL argMC;
BOOL ABORTED;
CHAR rname[21];
CHAR rkey[14];
CHAR rtype[4];
BOOL KEYISTHERE;
BOOL ATTEMPTINGCONNECT;
CHAR rpVersion[40];
CHAR rpFTPPort[40];
CHAR rpIPAddress[40];
BOOL STARTMIN;
CHAR mmtoname[NAMESIZE];
CHAR grport[6];
CHAR gsport[6];
CHAR gfport[6];
CBD cdat;
BOOL  FTPSERVERLISTENING;
UINT SENDPASTE;


extern ULONG MLEGetItemText(HWND hwndDlg, ULONG ulID, LONG lIptPosition,
                                           LONG lBoundary, PBYTE *ppText);
extern ULONG MLEInsertText(HWND hwndDlg, ULONG ulID, LONG iptPosition, PBYTE pText);

MRESULT EXPENTRY sendFileProc(HWND hwndDlg, ULONG msg,
                                                MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY receiveFileProc(HWND hwndDlg, ULONG msg,
                                                MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY newMLE1Proc(HWND hwndWnd, ULONG ulMsg,
                                                MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY newMLE2Proc(HWND hwndWnd, ULONG ulMsg,
                                                MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY NewListProc(HWND hwndWnd, ULONG ulMsg,
                                                MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY newPhrProc(HWND hwndWnd, ULONG ulMsg,
                                            MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY newNoteProc(HWND hwndWnd, ULONG ulMsg,
                                            MPARAM mp1, MPARAM mp2 );
VOID saveNCSet(VOID);
VOID queryNCSet(VOID);
VOID _Optlink mailSendStatus(PVOID chkmdat);
VOID _Optlink sendEMail(PVOID chkmaildat);
VOID _Optlink chkForMail(PVOID chkmaildat);
void strdelc(char *s, char c);
int strndel(char *s, int n);
char * strinsert(char *s, char insert);
VOID zeroNCData(VOID);
VOID zeroNCTmpr(VOID);
VOID zeroLBoxHandle(HWND hwndDlg);
INT loadNCData(CHAR *fname);
INT getStr2(INT cz, CHAR *tmp, CHAR *dStr);
INT saveCodeHeaderData(CHAR *buf);
INT saveNCData(CHAR *fname);
INT editRecord(CHAR *fname, HWND hwndDlg);
INT addRecord(CHAR *fname, CHAR *ncName, CHAR *ncURL, CHAR *ncNote, HWND hwndDlg);
INT deleteRecord(CHAR *fname, HWND hwndDlg);
INT loadNCLBox(HWND hwndDlg, CHAR *fname);
BOOL menuChoice(SHORT mp1, HWND hwndDlg);
VOID phrmenuChoice(HWND hwndDlg, HWND hwndFrame, HWND hwndPopup, ULONG msg, MPARAM mp1, MPARAM mp2);
VOID msgBox(HWND hwnd, CHAR *title, CHAR *message);
VOID zeropvdat(VOID);
INT loadLogList(HWND hwnd);
VOID zeroLog(VOID);
INT savetolog(INT num);
INT makeNewLog(FILE *hand);
INT replaceLog(FILE *hand);
INT reverselist(INT num);
VOID _Optlink msgServer(PVOID chkmaildat);
VOID _Optlink sendMSG(PVOID chkmaildat);
VOID _Optlink sendQuitMSG(PVOID chkmaildat);
VOID _Optlink sendOneMSG(PVOID mdd);
VOID _Optlink listenLoop(PVOID hwndm);
VOID _Optlink canNOTConnect(PVOID var);
VOID _Optlink NOTConnected(PVOID var);
VOID makeTBar(VOID);
INT getmsgstr(INT sp, INT brd, CHAR *tmp, CHAR *dStr);
VOID _Optlink attemptConnect(PVOID acdat);
VOID _Optlink attemptConnect2(PVOID acdat);
INT sendFile(HWND hwnd, CHAR *fn);
INT receiveFile(HWND hwnd);
VOID _Optlink handleXmtRequest();
VOID _Optlink flashFileButton();
VOID _Optlink ftpServer();
VOID _Optlink ftpConnect();
INT getmsgchunk(INT sp, INT brd, CHAR *tmp, CHAR *dStr);
INT checkchunk(CHAR *chunk, INT blen);
INT readchunk(HFILE hfile, CHAR *chunkbuf);
INT writechunk(CHAR *chunk, INT bytes);
VOID _Optlink requestFTD(PVOID n);
ULONG getFSize(CHAR *file);
INT getIPaddr(CHAR *locaddr);
INT existFile(CHAR *fileStr);
VOID _Optlink pressOK();
INT listenToLoop(HWND hwndD);
INT savePHRData(CHAR *fname);
INT loadPHRData(CHAR *fname);
INT loadPHRLBox(HWND hwndDlg, CHAR *fname);
VOID zeroPHRLBoxHandle(HWND hwndDlg);
INT addPHRRecord(CHAR *fname, CHAR *phrase, HWND hwndDlg);
INT editPHRRecord(CHAR *fname, HWND hwndDlg);
INT deletePHRRecord(CHAR *fname, HWND hwndDlg);
VOID zeroPHRData(VOID);
VOID zeroPHRTMP(VOID);
VOID _Optlink sendDroppedFile(PVOID n);
VOID _Optlink pasteDroppedFile(PVOID n);
INT checkConnectionOnceNT(VOID);
INT existPath(CHAR *dstr);
BOOL chkCommand(SHORT mp1);
VOID runArgs(PVOID n);
VOID callPgm(PSZ PgmName, PSZ PgmInputs, SHORT PgmType,
	         ULONG swapStuff, PSZ startDir,  PSZ title );
BOOL registered(CHAR *pw);
VOID bugem(HWND hwndDlg);
VOID ncRunning(VOID);
INT readKey(VOID);
VOID _Optlink chkKeyDupes(PVOID var);
VOID _Optlink showRPInfo(PVOID n);
BOOL saveToDTFile(CHAR *buf, CHAR *fn);  
VOID openFolder(CHAR *fold);
INT msgBoxOKCANCEL(HWND hwndDlg, CHAR *title, CHAR *msg);
VOID errorMsgInt(INT num, CHAR *varName);


VOID msgOK(CHAR *title, CHAR *message);
VOID debugMsgCH(CHAR ch, CHAR *varName);
VOID debugMsgStr(CHAR *str, CHAR *varName);
VOID debugMsgULong(ULONG num, CHAR *varName);
VOID debugMsgInt(INT num, CHAR *varName);




























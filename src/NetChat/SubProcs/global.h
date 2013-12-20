/* global.h */

CHAR INIFILE[1024] = "NETCHAT.INI";
HBITMAP hbmcopy, hbmpaste;
CHAR ncDataFile[] = "nc.dat";
CHAR passWord[CCHMAXPATH];
CHAR userName[CCHMAXPATH];
CHAR mailServer[CCHMAXPATH];
CHAR passWord2[CCHMAXPATH];
CHAR userName2[CCHMAXPATH];
CHAR mailServer2[CCHMAXPATH];
CHAR rtname[CCHMAXPATH];
CHAR rtema[CCHMAXPATH];
CHAR nickName[CCHMAXPATH];
CHAR hailingAddr[CCHMAXPATH];
CHAR hailingName[CCHMAXPATH];
CHAR appName[] = "NetChat for OS/2";
INT STOPME;
INT PAUSEAC;
HEV hev;
CHAR cphrase[] = "&&$~NETCHATMSG~$&&";
CHAR nclog[] = "netchat.log";
CHAR guestIP[260];
CHAR eochunk[] = "@)+~(@";
CHAR eofile[] = "E_OF_F";
CHAR tmpFileName[] = "nchat.$_$";
CHAR ncversion[] = "NetChat ver. 1.36";
CHAR NCHNote[1024];
CHAR eoNCHMSG[] = "&&NCEND&&";
HWND hwndHelp;
HELPINIT hinit;



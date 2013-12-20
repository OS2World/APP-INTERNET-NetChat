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



INT pgmData[20];
HINI hini;
ULONG rSize;
extern CHAR INIFILE[];

INT createKeys(HWND hwndDlg, CHAR *name, CHAR *regcode);
INT saveToFile(HWND hwndDlg);

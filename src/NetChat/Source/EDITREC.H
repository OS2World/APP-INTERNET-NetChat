/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.29f                                   */
/*                                                                            */
/* File Name : EDITREC.H                                                      */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Gary L. Robinson                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

#ifndef EDITRECWINDOW_H
#define EDITRECWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenEDITREC(HWND hwndOwner, PVOID pInfo);

typedef struct _EDITRECFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* Code sections - Window structure members */

   HWND hwnd;
   /* ##END Window structure members */
} EDITRECFORMINFO;
typedef EDITRECFORMINFO * PEDITRECFORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif
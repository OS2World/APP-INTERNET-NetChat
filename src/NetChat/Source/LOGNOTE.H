/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : LOGNOTE.H                                                      */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Gary L. Robinson                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

#ifndef LOGNOTEWINDOW_H
#define LOGNOTEWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenLOGNOTE(HWND hwndOwner, PVOID pInfo);

typedef struct _LOGNOTEFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* Code sections - Window structure members */

   HWND hwnd;
   INT index;
   /* ##END Window structure members */
} LOGNOTEFORMINFO;
typedef LOGNOTEFORMINFO * PLOGNOTEFORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif
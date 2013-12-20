/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : HAILNOTE.H                                                     */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Gary L. Robinson                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

#ifndef HAILNOTEWINDOW_H
#define HAILNOTEWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenHAILNOTE(HWND hwndOwner, PVOID pInfo);

typedef struct _HAILNOTEFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* Code sections - Window structure members */

   HWND hwnd;
   INT index;
   /* ##END Window structure members */
} HAILNOTEFORMINFO;
typedef HAILNOTEFORMINFO * PHAILNOTEFORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif
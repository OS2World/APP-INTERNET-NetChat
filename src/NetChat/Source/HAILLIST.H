/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.29f                                   */
/*                                                                            */
/* File Name : HAILLIST.H                                                     */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Gary L. Robinson                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

#ifndef HAILLISTWINDOW_H
#define HAILLISTWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenHAILLIST(HWND hwndOwner, PVOID pInfo);

typedef struct _HAILLISTFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* Code sections - Window structure members */

   INT mode;
   HWND hwnd;
   /* ##END Window structure members */
} HAILLISTFORMINFO;
typedef HAILLISTFORMINFO * PHAILLISTFORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif
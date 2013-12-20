/******************************************************************************/
/*                                                                            */
/* Program: NETCHAT.EXE                                                       */
/*                                                                            */
/* Description: NetChat for OS/2 ver. 1.30                                    */
/*                                                                            */
/* File Name : PHRLIST.H                                                      */
/*                                                                            */
/* Author : GARY L. ROBINSON                                                  */
/*                                                                            */
/* Copyright 1997 Gary L. Robinson                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5013754                          */
/*                                                                            */
/******************************************************************************/

#ifndef PHRLISTWINDOW_H
#define PHRLISTWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenPHRLIST(HWND hwndOwner, PVOID pInfo);

typedef struct _PHRLISTFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* ##END Window structure members */
} PHRLISTFORMINFO;
typedef PHRLISTFORMINFO * PPHRLISTFORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif
# PROGRAM - Makefile (MAKEKEYS.MAK) 
#
#       Makefile variables from Build Options 
#
CFLAGS=/c /O /Gm /Ss /W3 /Tl- -I. -I..\SUBPROCS -IG:\VISPROC
LFLAGS=/ST:32768 /A:16 /NOI /NOE /NOD
L_ADDITIONAL_LIBS=OS2386.LIB DDE4MBS.LIB 
L_ADDITIONAL_OBJS=
COMPILER=ICC
LINKER=LINK386
#
#       Additional definitions 
#
SUBPROCS=..\\SUBPROCS\\
EXCL=!
OBJECTS= \
          Main.OBJ \
          xtra.OBJ 

ALL: ..\NCHATREG.EXE 
#
#       Statements to compile the classes
#
Main.OBJ:  Main.C Main.H Main.RCH  MAIN.H 
    $(COMPILER) $(CFLAGS) Main.C
xtra.OBJ:  $(SUBPROCS)xtra.c 
    $(COMPILER) $(CFLAGS) $(SUBPROCS)xtra.c
#
#       Statements to compile resources for the classes
#
MAKEKEYS.RES:  MAKEKEYS.RC \
               Main.RCH Main.RC 
    RC -r MAKEKEYS.RC
#
#       Statements to link the EXE file
#
..\NCHATREG.EXE:  $(OBJECTS) MAKEKEYS.DEF MAKEKEYS.RES MAKEKEYS.MAK 
    $(LINKER) @<<
           $(LFLAGS) $(L_ADDITIONAL_OBJS)  +
          Main.OBJ +
          xtra.OBJ ,
          ..\NCHATREG.EXE,, $(L_ADDITIONAL_LIBS), MAKEKEYS.DEF 
<<
    RC MAKEKEYS.RES ..\NCHATREG.EXE

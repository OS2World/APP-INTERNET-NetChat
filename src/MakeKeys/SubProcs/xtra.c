/* xtra.c  */

#include <xtra.h>



INT createKeys(HWND hwndDlg, CHAR *name, CHAR *regcode)
{
INT k;
FILE *mainkey, *guestkey;
CHAR mkey[] = "main.key";
CHAR gkey[] = "guest.key";
CHAR tone[] = "one";
CHAR ttwo[] = "two";


if( strlen(name) < 1 )
   return(0);
   
if( strlen(regcode) != 13 )
   return(0);
   
if ((mainkey = fopen( mkey, "w+b" )) == NULL)
   {
   fclose(mainkey);
   fclose(guestkey);
   return(-1);
   }

if ((guestkey = fopen( gkey, "w+b" )) == NULL)
   {
   fclose(mainkey);
   fclose(guestkey);
   return(-1);
   }


for( k=0;k<2564;k++ )
   {
   INT rn;
   
   switch( k )
      {
      case 69 :
         {
         fwrite(&tone[0], sizeof(CHAR), 1, mainkey);
         fwrite(&ttwo[0], sizeof(CHAR), 1, guestkey);
         }
         break;
         
      case 1269 :
         {
         fwrite(&tone[1], sizeof(CHAR), 1, mainkey);
         fwrite(&ttwo[1], sizeof(CHAR), 1, guestkey);
         }
         break;
         
      case 2069 :
         {
         fwrite(&tone[2], sizeof(CHAR), 1, mainkey);
         fwrite(&ttwo[2], sizeof(CHAR), 1, guestkey);
         }
         break;
         
      case 2545 :
         fwrite(&name[0], sizeof(CHAR), 1, mainkey);
         fwrite(&name[0], sizeof(CHAR), 1, guestkey);
         break;
         
      case 542 :
         fwrite(&name[1], sizeof(CHAR), 1, mainkey);
         fwrite(&name[1], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2455 :
         fwrite(&name[2], sizeof(CHAR), 1, mainkey);
         fwrite(&name[2], sizeof(CHAR), 1, guestkey);
         break;
         
      case 25 :
         fwrite(&name[3], sizeof(CHAR), 1, mainkey);
         fwrite(&name[3], sizeof(CHAR), 1, guestkey);
         break;
         
      case 925 :
         fwrite(&name[4], sizeof(CHAR), 1, mainkey);
         fwrite(&name[4], sizeof(CHAR), 1, guestkey);
         break;
         
      case 845 :
         fwrite(&name[5], sizeof(CHAR), 1, mainkey);
         fwrite(&name[5], sizeof(CHAR), 1, guestkey);
         break;
         
      case 805 :
         fwrite(&name[6], sizeof(CHAR), 1, mainkey);
         fwrite(&name[6], sizeof(CHAR), 1, guestkey);
         break;
         
      case 1795 :
         fwrite(&name[7], sizeof(CHAR), 1, mainkey);
         fwrite(&name[7], sizeof(CHAR), 1, guestkey);
         break;
         
      case 115 :
         fwrite(&name[8], sizeof(CHAR), 1, mainkey);
         fwrite(&name[8], sizeof(CHAR), 1, guestkey);
         break;
         
      case 511 :
         fwrite(&name[9], sizeof(CHAR), 1, mainkey);
         fwrite(&name[9], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2005 :
         fwrite(&name[10], sizeof(CHAR), 1, mainkey);
         fwrite(&name[10], sizeof(CHAR), 1, guestkey);
         break;
         
      case 770 :
         fwrite(&name[11], sizeof(CHAR), 1, mainkey);
         fwrite(&name[11], sizeof(CHAR), 1, guestkey);
         break;
         
      case 1216 :
         fwrite(&name[12], sizeof(CHAR), 1, mainkey);
         fwrite(&name[12], sizeof(CHAR), 1, guestkey);
         break;
         
      case 67 :
         fwrite(&name[13], sizeof(CHAR), 1, mainkey);
         fwrite(&name[13], sizeof(CHAR), 1, guestkey);
         break;
         
      case 904 :
         fwrite(&name[14], sizeof(CHAR), 1, mainkey);
         fwrite(&name[14], sizeof(CHAR), 1, guestkey);
         break;
         
      case 789 :
         fwrite(&name[15], sizeof(CHAR), 1, mainkey);
         fwrite(&name[15], sizeof(CHAR), 1, guestkey);
         break;
         
      case 932 :
         fwrite(&name[16], sizeof(CHAR), 1, mainkey);
         fwrite(&name[16], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2430 :
         fwrite(&name[17], sizeof(CHAR), 1, mainkey);
         fwrite(&name[17], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2222 :
         fwrite(&name[18], sizeof(CHAR), 1, mainkey);
         fwrite(&name[18], sizeof(CHAR), 1, guestkey);
         break;
         
      case 200 :
         fwrite(&name[19], sizeof(CHAR), 1, mainkey);
         fwrite(&name[19], sizeof(CHAR), 1, guestkey);
         break;
         
      case 1020 :
         fwrite(&name[20], sizeof(CHAR), 1, mainkey);
         fwrite(&name[20], sizeof(CHAR), 1, guestkey);
         break;
         
      case 20 :
         fwrite(&name[21], sizeof(CHAR), 1, mainkey);
         fwrite(&name[21], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2000 :
         fwrite(&name[22], sizeof(CHAR), 1, mainkey);
         fwrite(&name[22], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2010 :
         fwrite(&name[23], sizeof(CHAR), 1, mainkey);
         fwrite(&name[23], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2210 :
         fwrite(&name[24], sizeof(CHAR), 1, mainkey);
         fwrite(&name[24], sizeof(CHAR), 1, guestkey);
         break;
         
      case 28 :
         fwrite(&name[25], sizeof(CHAR), 1, mainkey);
         fwrite(&name[25], sizeof(CHAR), 1, guestkey);
         break;
         
      case 640 :
         fwrite(&name[26], sizeof(CHAR), 1, mainkey);
         fwrite(&name[26], sizeof(CHAR), 1, guestkey);
         break;
         
      case 460 :
         fwrite(&name[27], sizeof(CHAR), 1, mainkey);
         fwrite(&name[27], sizeof(CHAR), 1, guestkey);
         break;
         
      case 1409 :
         fwrite(&name[28], sizeof(CHAR), 1, mainkey);
         fwrite(&name[28], sizeof(CHAR), 1, guestkey);
         break;
         
      case 975 :
         fwrite(&name[29], sizeof(CHAR), 1, mainkey);
         fwrite(&name[29], sizeof(CHAR), 1, guestkey);
         break;
         
      case 673 :
         fwrite(&name[30], sizeof(CHAR), 1, mainkey);
         fwrite(&name[30], sizeof(CHAR), 1, guestkey);
         break;
         
      case 439 :
         fwrite(&name[31], sizeof(CHAR), 1, mainkey);
         fwrite(&name[31], sizeof(CHAR), 1, guestkey);
         break;
         
      case 218 :
         fwrite(&name[32], sizeof(CHAR), 1, mainkey);
         fwrite(&name[32], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2557 :
         fwrite(&name[33], sizeof(CHAR), 1, mainkey);
         fwrite(&name[33], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2121 :
         fwrite(&name[34], sizeof(CHAR), 1, mainkey);
         fwrite(&name[34], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2001 :
         fwrite(&name[35], sizeof(CHAR), 1, mainkey);
         fwrite(&name[35], sizeof(CHAR), 1, guestkey);
         break;
         
      case 378 :
         fwrite(&name[36], sizeof(CHAR), 1, mainkey);
         fwrite(&name[36], sizeof(CHAR), 1, guestkey);
         break;
         
      case 499 :
         fwrite(&name[37], sizeof(CHAR), 1, mainkey);
         fwrite(&name[37], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2344 :
         fwrite(&name[38], sizeof(CHAR), 1, mainkey);
         fwrite(&name[38], sizeof(CHAR), 1, guestkey);
         break;
         
      case 400 :
         fwrite(&name[39], sizeof(CHAR), 1, mainkey);
         fwrite(&name[39], sizeof(CHAR), 1, guestkey);
         break;
         
      // *****************************************   
      // *****************************************   
      // *****************************************   
         
      case 47 :
         fwrite(&regcode[0], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[0], sizeof(CHAR), 1, guestkey);
         break;
         
      case 347 :
         fwrite(&regcode[1], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[1], sizeof(CHAR), 1, guestkey);
         break;
         
      case 1357 :
         fwrite(&regcode[2], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[2], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2519 :
         fwrite(&regcode[3], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[3], sizeof(CHAR), 1, guestkey);
         break;
         
      case 1212 :
         fwrite(&regcode[4], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[4], sizeof(CHAR), 1, guestkey);
         break;
         
      case 253 :
         fwrite(&regcode[5], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[5], sizeof(CHAR), 1, guestkey);
         break;
         
      case 2201 :
         fwrite(&regcode[6], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[6], sizeof(CHAR), 1, guestkey);
         break;
         
      case 333 :
         fwrite(&regcode[7], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[7], sizeof(CHAR), 1, guestkey);
         break;
         
      case 451 :
         fwrite(&regcode[8], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[8], sizeof(CHAR), 1, guestkey);
         break;
         
      case 670 :
         fwrite(&regcode[9], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[9], sizeof(CHAR), 1, guestkey);
         break;
         
      case 1402 :
         fwrite(&regcode[10], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[10], sizeof(CHAR), 1, guestkey);
         break;
         
      case 1299 :
         fwrite(&regcode[11], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[11], sizeof(CHAR), 1, guestkey);
         break;
         
      case 991 :
         fwrite(&regcode[12], sizeof(CHAR), 1, mainkey);
         fwrite(&regcode[12], sizeof(CHAR), 1, guestkey);
         break;
         
      default :
         rn = rand();
         fwrite(&rn, sizeof(CHAR), 1, mainkey);
         fwrite(&rn, sizeof(CHAR), 1, guestkey);
         break;   
      }
   }
fclose(mainkey);
fclose(guestkey);

return(1);
}




INT saveToFile(HWND hwndDlg)
{
CHAR custaddr[500];


WinQueryDlgItemText(hwndDlg, 1006, sizeof(custaddr), custaddr);
return(1);
}


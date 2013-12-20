NetChat for OS/2 ver. 1.36
***************************
2012-Open Source under the GNU GPL V2 License.
***********************************************



******************************************
******* What is NetChat for OS/2 ***********
******************************************
NetChat for OS/2 is a small and fast personal
communication tool for OS/2.  It is designed to
hook 2 people up directly (without using the 
IRC channels, servers, IP servers, etc.) for a
ONE on ONE personal text mode chat.

NetChat for OS/2 utilizes a "Hailing feature" to
accomplish this.  The hailing feature uses a 
built in seamless e-mail facility to send your
current IP address to another NetChat user
in a specially coded e-mail letter.  The other
user (who is checked into the net and has 
NetChat running in Monitor ON mode) will 
receive the message and prompt him to 
connect or not connect.  

The NetChat Monitor ON mode checks your 
mail box (at user set intervals) for NetChat 
Hailing messages.  If it detects a NetChat 
hailing message(s) it downloads them, deletes 
them from the server, and prompts you to 
see if you want to attempt a connection.  

If you decline to connect at that time NetChat
will save the hailing message(s) in Hail log.
The Hail log can be used to connect with also -
assuming the message is not so old that the
person hasn't logged off the internet, turned off
NetChat, or logged off and back on with a new 
IP address.

Once NetChat gets an IP address from the NetChat
Hailing message then it can directly connect you
with the other party.  The ONLY use of the e-mail
system is to initially exchange an IP address.






******************************************
*********** Installing NetChat **************
******************************************
Copy NETCHAT.EXE to a directory (folder) of
it's own and put a program object or a shadow 
object on your Desktop or launchpad.  NetChat
will create (during use) several data files and
it's own .INI file.






******************************************
*********** Setting Up NetChat *************
******************************************
NetChat has 3 sets of configurations - 3 menu
items under the main menu item Configure.

1. Internet Account settings :
    A. Domain name -- This is usually the base
        domain of your internet provider.  Most
        often that means everything to the right
        of the '@' symbol in your e-mail address.
        Eg., bigdude@monkey.com
        The Domain name would be : monkey.com
        *** We did run into a problem during testing
        with at least one user, though, that was
        an I.B.M. Advantis subscriber.  He could
        NOT get NetChat working when he entered
        ibm.net as the Domain name.  After some 
        trial and error he fond out he could make it
        work by entering www.ibm.net   **********
        
   B. User name :
       This is everything to the left of the '@' symbol
       in you e-mail address.  
       Eg., bigdude@monkey.com
       The User name would be : bigdude
      
   C. Nickname :
       This could be your real first name or anything
       you like.  This name will be used in the actual
       chat window to indentify you and your messages.   

   D. Password :
       This is your password for your ISP.  It is necessary
       to have so NetChat can monitor you mail account
       for NetChat Hailing messages.
       
2. Misc. settings :  (This page is in a state of flux with this 
   beta - much more will be added later)
   A. Monitor mail interval :  Set to how often you want NetChat
       to check your mail box for NetChat Hailing messages when
       you are in Monitor ON mode.
       
   B.  Force NetChat to use machine (network) IP  :
       This should NOT be checked UNLESS you are on a local
       network AND want to have two copies of NetChat use the
       local machine IP's to connect.  Even then it may NOT work ...
       
   C.  Default upload/download directories :
       Set these if you want the download/upload dialog to default
       to a certain directory when the first are activated.        
   
2. Port settings :  
   A.  For most casual users the port settings do NOT have to be set
        or changed.  Generally it is safe to use any port for transmitting
        and receiving messages in the 6667-6675 range.  Actually it is 
        safe to use almost ANY port but it is possible that you might have
        other programs or system facilities that use certain ports.  if you
        don't understand ports and or how they are used then don't mess
        with these settings.  The generally used port for file transfer (FTP)
        is port 21.
        However, if you might want to run your FTP program AT THE SAME
        TIME that you want to do a file transfer with NetChat you can change the
        file transfer port to another setting -- preferrably up in the 6670 and
        higher range.  The Person on the other end would have to set his to
        the same setting.
        Also, if you wanted to have multiple sessions of NetChat going at the 
        same time -- you could set one on 6667 (both transmit and receive) and
        others on 6668, 6669, etc.
        Port settings and your Domain name are reported in the titlebar.
        ********* NetChat does NOT support multiple sessions UNLESS you
        put a copy of NETCHAT.EXE in a separate folder and set it up as a
        separate entity of it's own - with it's own .INI and data files.

        ******* YOU MUST BE ON THE SAME RECEIVE AND TRANSMIT PORT AS
        THE PERSON YOU WANT TO COMMUNICATE WITH.  IT IS THEREFORE
        RECOMMENDED TO GENERALLY LEAVE THESE BOTH ON 6667. ********






       
******************************************
************** Quick Start *****************
******************************************
To get up and running fast just fill in all the 
Settings described above.

Then, if you want to test and make sure your
Domain name is working correctly with NetChat 
(as well as a few other things) do the following :

1. Select Hailing on the main menu bar and then 
    select Hailing list.
    
2. When the Hailing list dialog appears put the
    mouse cursor over the center of it and 
    Right click it once to get the popup menu.
    
3.  Select Add record.  In the Add a new record
    dialog put YOUR name in the first entry area
    and YOUR e-mail address in the second area.
    The third area is for small notes.  It's not
    necessary to put anything there.
    
4.  Add other entries for anyone else you want to
    try and connect with that already has NetChat.
    
5.  To test and see if it's working :
     A.  Log onto the Internet
     B.  Start NetChat (if it's not already running)
     C.  Shut down any programs that AUTOMATICALLY
         download your mail.
     D.  Press the Monitor OFF button once (it will
          go to Monitor ON mode and turn Red)
     E.  Press the Hail BUTTON on the right of the 
         button bar.
     F.  Select YOURSELF in the list box and either
         double-click or Press ENTER.  (You
         should also see the Listen OFF button go
         to Listen ON mode at this time and turn
         Yellow)
         
NetChat should report (in the titlebar) in a few 
seconds or so that a Hailing message has been 
successfully sent.

Depending on whether you kept the default setting of 10
seconds for the mail monitoring setting NetChat will detect
the Hailing message and Notify you in a few seconds or so.

When it does (assuming all is working well) look and see if
it is reporting your correct current IP address - assuming you
know it.  Hit the cancel button.  No need to try and connect 
with yourself.  

If all this works OK then you can now send a Hailing message 
to someone else on the net using NetChat and try to connect.

When a person receives a Hailing message (and NetChat is 
running and the Monitor OFF/ON button is in Monitor ON mode)
you will be prompted by a dialog and a beep.  You will see
who is calling, their IP address, and you can select either to 
Connect or not to.  Whether you connect or decline the hailing
message will be saved to the hailing log.

If you decide to connect, NetChat goes through a connect process.
If it is successful you will be notified in the titlebar AND the 
Listen ON button (Yellow) will turn to a Connected! button (RED).

**** If you ever download a Hailing message into your regular
mail program DON'T panic.  Just look at the HEADER of the 
message (there is no body) and copy the IP address out of
it -- right after the characters : &&$~NETCHATMSG~$&&
in the subject : area.  Then take the IP address and do the 
Manual Connect as noted directly below.



ALTERNATIVE METHOD OF CONNECTING (Manual Connect) :
You don't have to use the hailing message system at all to 
connect with NetChat.  It is merely included as a convenience.
If you exchange an IP address through a regular e-mail letter,
over the phone, or through ESP -- that is all you really need.
If you get the IP address and want to connect to your other
party (who is using NetChat) then :

1. Press the Listen OFF button and put NetChat in listen ON mode

2. Select the File menu item and then select Manual Connect

3. In the manual connect dialog type in the IP address of the person
    you want to connect to.  If he is logged in, running NetChat, AND
    HE IS IN LISTENING ON MODE then you will connect.
  
4. When you do connect you will be beeped and flashed 3 times in the
    titlebar.  The Listen ON button on the button bar turns to Red and
    says "Connected!"
         
Connections sometimes take 2-5 seconds to complete under normal
circumstances.    

********** ONCE CONNECTED .....  *****************************
Once connected you type text in the BOTTOM white area and Press 
ENTER to send it.  Both your text AND the other person's will show 
in the upper entry area (CYAN).     

The session can be TERMINATED by simply pressing on the Red "Connected!"
button (formerly, Listen ON/OFF).  It will break the connection and put the
button into Connect OFF mode.

        
        
        


******************************************
************** Using NetChat **************
******************************************
To summarize, NetChat can connect you in
basically 2 ways.  Either exchange an IP
address and use Manual Connect OR use the
built in Hailing function (Hail button) to do the 
work for you.

OTHER FEATURES  .....

FILE TRANSFER :
NetChat can also transfer files.  To transfer
a file while connected simply select the File
menu item and then select "Send file".

You will see a standard "File open" type dialog 
box where you can select a file to be sent.

Select one and Press Send File.

NetChat will prompt the person at the other end
by ENABLING the "Incoming file" button on the
Button bar and by flashing and beeping.

The person on the receiving end then presses the
button and either accepts or rejects the file
transfer.  They are presented with a "File open"
type dialog, also to deal with.

The status of the file transfer is noted
in the title bar.  Be a little patient as the process
is negotiated to begin the transfer.  The user is
shown the progress and the completion of the 
download in the titlebar also.

File transfers can be aborted during the process.  
Select the File menu item and then select Abort
file transfer.  This menu item is normally greyed out
EXCEPT during a file transfer.


FAVORITE PHRASES :
Favorite phrases gives you a sizeable windowed
list box to keep up to 100 favorite phrases in
for quick "no typing" access.  Each phrase can be
up to 500 characters long.

The Phrase window has a popup menu (right click on
it once) to allow Adding, editing, and deleting Phrases.

When you Add a phrase, Up to the first 80 characters 
will ACTUALLY show in the list box list.

While connected, and running the Phrases window just
double-click on a phrase and it will be automatically
sent.  (or select and Press ENTER)


HAILING LOG :
This log keeps a rotating list of the LAST 100 Hailing
messages you received -- whether you connected
with them or NOT.  The Hailing log dialog can be used
to connect to some one also -- IF the hailing log
entry is not so old that the person hasn't logged off
the internet AND if they are still at the same IP address.


COPY & PASTE, WORD WRAP, ETC. :
The Edit menu item has sub-menu's supporting copy and
pasting.  The Copy Remote menuitem copies ALL the text
in the remote entry area (upper, CYAN) to the system 
clipboard.  The Paste Local menu item pastes ANYTHING 
that is in the system clipboard (text) into the local entry
area (bottom, WHITE).  There are also menu items to 
clear each area and/or set the Word Wrap state for either.


MISC. FILE MENU ITEMS :
Under the File menu is also items that put you in listen mode
and one to disconnect you.  This mimics the EXACT same 
function that is accomplished by clicking on the Listen ON/OFF
button the button bar.  Manual Connect menu item is described
above in the Quick Start section.  The Wake Up menu item is
a function that, while connected, you can select and beep the
guy on the other end 3 times to literally get their attention.


BUTTON BAR ..... :
The Listen ON/OFF button is toggable.  Select it once and it will
go to Listen ON state.  In this state NetChat is actually monitoring
the port (6667 or whatever you have set it on) for any messages
at your specific IP address.  YOU MUST BE IN LISTENING ON MODE
to be able to connect.  If you aren't listening -- you can NOT 
connect.  When you get a Hailing message NetChat automatically
puts itself into Listening ON mode and when you ACTUALLY connect
the Listen ON mode (Yellow) goes to Connected! mode (Red).

The Echo button is simply a button to test the connection.  At any
time while connected just press the Echo button and IF the connection
is OK you will get 1 beep and a message flashed in the titlebar.  This
message has mad a round trip from your machine to the other and
back.  It is also useful to see how FAST the connection is.  If the
connection is broken -- nothing happens.  Be patient, though.  A slow
connection might take several seconds for the message to go there 
and back.

The copy and paste buttos are slightly different than the menu item
counterparts.  The paste button is actually the same as the menu item
but the copy button ONLY copies SELECTED text in the upper (CYAN)
area into the system clipboard.  The paste button pastes ALL the clipboard
text contents into the bottom (WHITE) area.

The Incoming File button is normally greyed out AND only comes to life
when someone tries to send you a file.  It will beep and flash to let you
know.  Select it AND THEN decide to accept or reject the incoming file 
transfer request.  Sending files is done through the Send File menu item
under the File menu item.

The Monitor ON/OFF button toggles back and forth to turn the monitoring on
and off for Hailing messages.

The Hail button is pressed to initiate calling (Hailing) someone.  It pops up
a window with a list box of our Hailing list entries.  To add, edit, or delete
Hailing list entries select Hailing on the menu bar and then select hailing
list.  Right click on the list for a popup menu.  All this can ALSO be done on
the dialog box that pops up when you select the Hail BUTTON.    Double
clicking on an entry in the dialog box (the one initiated from the Hail BUTTON)
will send the Hailing message.  



  



******************************************
********* Known problems & bugs **********
******************************************
Like any software that does much NetChat is NOT
perfect.  Sometimes you may experiece slight
difficulties in connecting.  This may be because
of problems with your provider and/or other 
internet difficulties.  It may also be because
NetChat has a lot going on under the hood.

One Known problem is if you are on a Local
Network while you are hooked into the Internet.
I.B.M. has a bug -- or perhaps just a bad design
choice - in their TCP/IP.  NetChat needs the
correct current IP that you are using on the 
Internet interface to connect you to another
person.  I.B.M.'s TCP/IP , however, causes 
some of the socket calls to get your Default
interface IP -- which if you are on a network
will result in NetChat getting your computers
Network IP instead of the internet IP.

There is some code written in NetChat to try
and work around this problem but it doesn't
always seem to be successful.

There are 2 other ways to resolve this.  one
way is to take the network down and reboot.  
For most people this is NOT an option.

The other is to get the LATEST TCP/IP fixes 
from I.B.M. or one of their sites.  Warp 4.0
already has the fixes needed.  I am not sure
if fix pack #26 for Warp 3.0 has the TCP/IP
fixes needed.  (easy way to tell is to just
start the "Dial Other Provider" dialer and see
if there is a check box on Page 2 of the 
settings for an entry for "Primary Interface".
If it's there then you are OK)

That said, here is the I.B.M. work-around IF
you have this problem.

You have to use the "Dial Other Provider" dialer
that comes with Warp.  Select "modify entry"
and on Page 2 of the settings (Connect Info tab)
check the Primary Interface check box.

Now when you dial in Warp's TCP/IP will make 
your internet software (including NetChat) see your
Internet IP address instead of your network address.
That will be effective ONLY while you are dialed in
with this dialer (and the box is checked).  When you
log off the internet the network is once again the 
primary interface.

It is also possible that other dialers may already 
support this feature - or will soon.





******************************************
************** FINAL NOTES ***************
******************************************

This is still a work in progress.

The Settings dialogs are definitely "Under construction".

The documentation above will hopefully be expanded
upon and be somewhat better by release time.  I hope.

P.S.  I HATE HATE HATE HATE writing documentation :)


/*-----------------------------------------------------
Name: packet.h
Date: 2015.05.09
Auth: kala13x (a.k.a 7th Ghost / kala13x)
Desc: Get and dump packets in file
-----------------------------------------------------*/


#include "stdinc.h"


/*---------------------------------------------
| Log tcp packets in file
---------------------------------------------*/
void log_tcp(short dump, unsigned char* buf, int size);


/*---------------------------------------------
| Log udp packets in file
---------------------------------------------*/
void log_udp(short dump, unsigned char* buf, int size);
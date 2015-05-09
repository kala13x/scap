/*---------------------------------------------------------------------------

 sCap is simple application for scaning and capturing incomming packets
 useing sockets.

 Copyright (c) 2015 Sun Dro (a.k.a. 7th Ghost / kala13x)
 Web: http://off-sec.com/ ; E-Mail: kala0x13@gmail.com

 This is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3 of the License, or (at your option) any later version.

 This software is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

---------------------------------------------------------------------------*/


#include "stdinc.h"
#include "info.h"
#include "slog.h"


/*---------------------------------------------
| Structure of packets
---------------------------------------------*/
typedef struct {
	int tcp;
	int udp; 
	int icmp;
	int igmp; 
	int total;
	int other;
} ScapPackets;


/*---------------------------------------------
| Initialise sCap packets
---------------------------------------------*/
void init_scap_packets(ScapPackets * scap) 
{
	scap->tcp = 0;
	scap->udp = 0;
	scap->icmp = 0;
	scap->igmp = 0;
	scap->total = 0;
	scap->other = 0;
}


/*---------------------------------------------
| Main function
---------------------------------------------*/
int main(int argc, char **argv)
{
	/* Used variables */
	ScapPackets scap;

	/* Initialise scap */
	init_scap_packets(&scap);
    init_slog("scap", 2);

    /* Todo */
    slog(0, "[LIVE] TODO");

    return 0;
}
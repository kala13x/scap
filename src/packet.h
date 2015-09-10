/*
 * src/packet.h
 * Copyleft (C) 2015  Sun Dro (a.k.a 7th Ghost)
 *
 * Get and dump packets in file.
 */


#include "stdinc.h"


/*
 * log_tcp - Log TCP packet header in file. Function takes packet buffer, 
 * parses it and dumps parsed header information in file. First argument 
 * is dump flag, if first argument is 1, function will dump packet 
 * payload in log file otherwise it wont. Second argument buf is packet 
 * buffer recieved from socket and third argument size is packet size. 
 */
void log_tcp(short dump, unsigned char* buf, int size);


/*
 * log_udp - Log UDP packet header in file. Function takes packet buffer, 
 * parses it and dumps parsed header information in file. First argument 
 * is  dump flag, if first argument is 1, function will hexdump packet 
 * payload in log file, otherwise it wont. Second argument buf is packet 
 * buffer recieved from socket and third argument size is packet size. 
 */
void log_udp(short dump, unsigned char* buf, int size);
/*
 * packet.h
 * Copyleft (C) 2015  Sun Dro (a.k.a 7th Ghost)
 *
 * Get and dump packets in file
 */


#include "stdinc.h"


/*
 * Log TCP Packet header in file. Function takes packet buffer, parses
 * it and dumps parsed header information in file.
 *
 * First argument is dump flag, if first argument is 1, function will
 * dump packet payload in log file, otherwise it wont. Second argument
 * is packet buffer recieved from socket, third argument is packet size. 
 */
void log_tcp(short dump, unsigned char* buf, int size);


/*
 * Log UDP Packet header in file. Function takes packet buffer, parses
 * it and dumps parsed header information in file.
 *
 * First argument is dump flag, if first argument is 1, function will
 * dump packet payload in log file, otherwise it wont. Second argument
 * is packet buffer recieved from socket, third argument is packet size. 
 */
void log_udp(short dump, unsigned char* buf, int size);
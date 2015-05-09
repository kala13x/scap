/*-----------------------------------------------------
Name: packet.c
Date: 2015.05.09
Auth: kala13x (a.k.a 7th Ghost / kala13x)
Desc: Get and dump packets in file
-----------------------------------------------------*/


#include "stdinc.h"
#include "slog.h"


/*---------------------------------------------
| Log tcp packets in file
---------------------------------------------*/
void log_tcp(unsigned char* buf, int size)
{
    /* Used variables */
    unsigned short iph_len;
    struct iphdr *iph = (struct iphdr *)buf;
     
    /* Get TCP packet header */
    iph_len = iph->ihl * 4;
    struct tcphdr* tcph= (struct tcphdr*)(buf + iph_len);
             
    /* Log TCP packet header in file */
    slog_to_file("[LIVE] Captured TCP Packet");          
    slog_to_file("[TCP] Source Port          : %u", ntohs(tcph->source));
    slog_to_file("[TCP] Destination Port     : %u", ntohs(tcph->dest));
    slog_to_file("[TCP] Sequence Number      : %u", ntohl(tcph->seq));
    slog_to_file("[TCP] Acknowledge Number   : %u", ntohl(tcph->ack_seq));
    slog_to_file("[TCP] Header Length        : %d DWORDS or %d BYTES" , 
                        (unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
    slog_to_file("[TCP] Urgent Flag          : %d", (unsigned int)tcph->urg);
    slog_to_file("[TCP] Acknowledgement Flag : %d", (unsigned int)tcph->ack);
    slog_to_file("[TCP] Push Flag            : %d", (unsigned int)tcph->psh);
    slog_to_file("[TCP] Reset Flag           : %d", (unsigned int)tcph->rst);
    slog_to_file("[TCP] Synchronise Flag     : %d", (unsigned int)tcph->syn);
    slog_to_file("[TCP] Finish Flag          : %d", (unsigned int)tcph->fin);
    slog_to_file("[TCP] Window               : %d", ntohs(tcph->window));
    slog_to_file("[TCP] Checksum             : %d", ntohs(tcph->check));
    slog_to_file("[TCP] Urgent Pointer       : %d", tcph->urg_ptr);
}


/*---------------------------------------------
| Log udp packets in file
---------------------------------------------*/
void log_udp(unsigned char* buf, int size)
{
    /* Used variables */
    unsigned short iph_len;
    struct iphdr *iph = (struct iphdr *)buf;

    /* Get UDP packet heaer */
    iph_len = iph->ihl * 4;
    struct udphdr* udph = (struct udphdr*)(buf + iph_len);
     
    /* Log TCP packet header in file */
    slog_to_file("[LIVE] Captured UDP Packet");               
    slog_to_file("[UDP] Source Port      : %d", ntohs(udph->source));
    slog_to_file("[UDP] Destination Port : %d", ntohs(udph->dest));
    slog_to_file("[UDP] Length           : %d", ntohs(udph->len));
    slog_to_file("[UDP] Checksum         : %d", ntohs(udph->check));
}
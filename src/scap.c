/*
 * sCap is simple application for scanning and capturing incoming packets
 * without libcap. sCap uses system sockets to recieve and dump traffic.
 *
 *  Copyright (c) 2015 Sun Dro (a.k.a. 7th Ghost)
 *  Web: http://off-sec.com/ ; E-Mail: kala0x13@gmail.com
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */


#include "stdinc.h"
#include "packet.h"
#include "errex.h"
#include "info.h"
#include "../slog/slog.h"

/* Max size of buffer */
#define MAXMSG 65536


/* Structure of packets */
typedef struct {
    int tcp;
    int udp; 
    int icmp;
    int igmp; 
    int total;
    int other;
} ScapPackets;


/* Structure of flags */
typedef struct {
    /* dump header info in file */
    short info;
    
    /* dump data in file */
    short data;
    
    /* flags for export in PCAP */
    short should_export_pcap;
    FILE * file_export_pcap;
    
    /* flags for filter for source ip */
    short should_filter_ip_src;
    struct in_addr ip_src;
    
    /* flags for filter for destination ip */
    short should_filter_ip_dst;
    struct in_addr ip_dst;
    
    /* flags for source port */
    short should_filter_port_src;
    unsigned int port_src;
    
    /* flags for destination port */
    short should_filter_port_dst;
    unsigned int port_dst;
    
    /* flags for TTL filter */
    short should_filter_ttl_min;
    unsigned int ttl_min;
    short should_filter_ttl_max;
    unsigned int ttl_max;
    
    /* flags for fragment number */
    short should_filter_frag_min;
    unsigned int frag_min;
    short should_filter_frag_max;
    unsigned int frag_max;
    
    /* flags for filter protocols */
    short should_filter_protocol;
    short should_filter_tcp;
    short should_filter_udp;
    short should_filter_icmp;
    short should_filter_igmp;
    
} ScapFlags;


/* Initialize sCap packets */
void init_scap_packets(ScapPackets * scap) 
{
    scap->tcp = 0;
    scap->udp = 0;
    scap->icmp = 0;
    scap->igmp = 0;
    scap->total = 0;
    scap->other = 0;
}


/* Initialize sCap flags */
void init_scap_flags(ScapFlags * scfl) 
{
    scfl->info = 0;
    scfl->data = 0;
    scfl->should_export_pcap = 0;
    scfl->should_filter_ip_src = 0;
    scfl->should_filter_ip_dst = 0;
    scfl->should_filter_ttl_min = 0;
    scfl->should_filter_ttl_max = 0;
    scfl->should_filter_frag_min = 0;
    scfl->should_filter_frag_max = 0;
    scfl->should_filter_protocol = 0;
    scfl->should_filter_tcp = 0;
    scfl->should_filter_udp = 0;
    scfl->should_filter_icmp = 0;
    scfl->should_filter_igmp = 0;
}


/*
 * Read signal. Function handles illegal signals and 
 * intertupts program if there is something wrong.
 */
void sig_handler(int sig) 
{
    /* Handle signals */
    if (sig == SIGILL || sig == SIGSEGV) 
        slog(0, SLOG_ERROR, "Can not process data");

    if (sig == SIGPIPE)
        slog(0, SLOG_ERROR, "Broken Pipe");

    if (sig == SIGINT) 
        slog(0, SLOG_LIVE, "Cleanup on exit");

    exit(-1);
}


/* 
 * create_socket - Function creates and returns raw socket.
 */
int create_socket()
{
    /* Used variables */
    int sock;

    /* Create raw socket */
    sock = socket(AF_INET , SOCK_RAW , IPPROTO_TCP);
    if (sock < 0)
        exit_prog(1, "Can not create raw socket (requires root)");
    
    return sock;
}


/*
 * write_packet_pcap - Write the packet in to the pcap file
 * wont work with multi-threading because of several fwrite calls
 */
void write_packet_pcap(ScapFlags * scfl,
                       unsigned char* buf,
                       int size)
{
    struct timeval current_time;
    uint32_t var_32bits;
    
    gettimeofday(&current_time, NULL);
    
    /* timestamp in seconds */
    var_32bits = (uint32_t) current_time.tv_sec;
    fwrite(&var_32bits, sizeof(var_32bits), 1, scfl->file_export_pcap);
    
    /* microseconds */
    var_32bits = (uint32_t) current_time.tv_usec;
    fwrite(&var_32bits, sizeof(var_32bits), 1, scfl->file_export_pcap);
    
    /* captured packet length */
    var_32bits = (uint32_t) size;
    fwrite(&var_32bits, sizeof(var_32bits), 1, scfl->file_export_pcap);
    
    /* original packet length */
    fwrite(&var_32bits, sizeof(var_32bits), 1, scfl->file_export_pcap);
    
    /* packet data */
    fwrite(buf, size, 1, scfl->file_export_pcap);
}


/*
 * read_scap_packet - Fucntion reads incomming 
 * packets and starts packet parsing and hexdump.
 */
void read_scap_packet(ScapPackets * scap, 
                    ScapFlags * scfl,
                    unsigned char* buf, 
                    int size)
{
    /* Used variables */
    struct iphdr* iph = (struct iphdr*)buf;
    char* out_line;
    unsigned short iph_len;
    struct tcphdr* tcph;
    struct udphdr* udph;

    if (scfl->should_filter_ip_src) {
        if ((scfl->ip_src).s_addr != iph->saddr) {
            return;
        }
    }

    if (scfl->should_filter_ip_dst) {
        if ((scfl->ip_dst).s_addr != iph->daddr) {
            return;
        }
    }

    if (scfl->should_filter_ttl_min) {
        if (iph->ttl < scfl->ttl_min) {
            return;
        }
    }

    if (scfl->should_filter_ttl_max) {
        if (iph->ttl > scfl->ttl_max) {
            return;
        }
    }

    if (scfl->should_filter_frag_min) {
        if (iph->frag_off < scfl->frag_min) {
            return;
        }
    }

    if (scfl->should_filter_frag_max) {
        if (iph->frag_off > scfl->frag_max) {
            return;
        }
    }

    iph_len = iph->ihl * 4;

    /* Get IP header */
    switch (iph->protocol)
    {
        case 1:
            if (scfl->should_filter_protocol && !scfl->should_filter_icmp) {
                return;
            }

            ++scap->icmp;
            break;

        case 2:
            if (scfl->should_filter_protocol && !scfl->should_filter_igmp) {
                return;
            }

            ++scap->igmp;
            break;

        case 6:
            if (scfl->should_filter_protocol && !scfl->should_filter_tcp) {
                return;
            }

            ++scap->tcp;

            tcph = (struct tcphdr*)(buf + iph_len);

            if (scfl->should_filter_port_src && ntohs(tcph->source) != scfl->port_src) {
                return;
            }

            if (scfl->should_filter_port_dst && ntohs(tcph->dest) != scfl->port_dst) {
                return;
            }

            if (scfl->info || scfl->data) 
                log_tcp(scfl->data, buf, size);
            break;

        case 17:
            if (scfl->should_filter_protocol && !scfl->should_filter_udp) {
                return;
            }

            ++scap->udp;

            udph = (struct udphdr*)(buf + iph_len);

            if (scfl->should_filter_port_src && ntohs(udph->source) != scfl->port_src) {
                return;
            }

            if (scfl->should_filter_port_dst && ntohs(udph->dest) != scfl->port_dst) {
                return;
            }

            if (scfl->info || scfl->data) 
                log_udp(scfl->data, buf, size);
            break;

        default:
            if (scfl->should_filter_protocol) {
                return;
            }

            ++scap->other;
            break;
    }

    /* Total packet counter */
    ++scap->total;

    /* Return status in slog format */
    out_line = ret_slog("[LIVE] TCP: %d   UDP: %d   ICMP: %d   IGMP: %d   Other: %d   Total: %d",
        scap->tcp, scap->udp, scap->icmp, scap->igmp, scap->other, scap->total);

    /* Print status */
    printf("%s\r", out_line);
    
    if (scfl->should_export_pcap && scfl->file_export_pcap != NULL)
    {
        write_packet_pcap(scfl, buf, size);
    }
}


/* 
 * Insert the PCAP File header 
 * Definition of the header is in the link:
 * http://xml2rfc.tools.ietf.org/cgi-bin/xml2rfc.cgi?url=https://raw.githubusercontent.com/pcapng/pcapng/master/draft-gharris-opsawg-pcap.xml&modeAsFormat=html/ascii&type=ascii
 */
void init_pcap_file(FILE *pcap_file)
{
    uint32_t magic_number = 0xA1B2C3D4;
    fwrite(&magic_number, sizeof(magic_number), 1, pcap_file);
    
    uint16_t major_version = 2;
    fwrite(&major_version, sizeof(major_version), 1, pcap_file);
    
    uint16_t minor_version = 4;
    fwrite(&minor_version, sizeof(minor_version), 1, pcap_file);
    
    uint32_t reserved = 0;
    fwrite(&reserved, sizeof(reserved), 1, pcap_file);
    fwrite(&reserved, sizeof(reserved), 1, pcap_file);
    
    /* we can use the upper limit, instead of the size of the largest packet */
    uint32_t snap_len = MAXMSG;
    fwrite(&snap_len, sizeof(snap_len), 1, pcap_file);
    
    uint32_t link_type = 0;
    fwrite(&link_type, sizeof(link_type), 1, pcap_file);
}

/* Parse cli arguments */
static int parse_arguments(int argc, char *argv[], ScapFlags * scfl)
{
    int c;
    int sscanf_result;
    while ( (c = getopt(argc, argv, "i1:d1:h1:o:s:t:p:q:l:m:f:g:")) != -1) {
        switch (c) {
        /* dump header info in file */
        case 'i':
            scfl->info = 1;
            break;
        
        /* dump data in file */
        case 'd':
            scfl->data = 1;
            break;
        
        /* file output in pcap */
        case 'o':
            scfl->should_export_pcap = 1;
            if (strlen(optarg) == 0) {
                printf("Invalid filename for export.\n");
                return -1;
            }
            
            scfl->file_export_pcap = fopen(optarg, "wb");
            
            if (scfl->file_export_pcap == NULL) {
                printf("Could not open the file '%s' to export.\n", optarg);
                return -1;
            }
            
            init_pcap_file(scfl->file_export_pcap);
            
            break;
        
        /* source Ip address */
        case 's':
            scfl->should_filter_ip_src = 1;
            if (inet_aton(optarg, &(scfl->ip_src)) == 0) {
                printf("Invalid IP for source address.\n");
                return -1;
            }
            break;
        
        /* destination Ip address */
        case 't':
            scfl->should_filter_ip_dst = 1;
            if (inet_aton(optarg, &(scfl->ip_dst)) == 0) {
                printf("Invalid IP for destination address.\n");
                return -1;
            }
            break;
        
        /* source port */
        case 'p':
            scfl->should_filter_port_src = 1;
            sscanf_result = sscanf(optarg, "%u", &(scfl->port_src));
            if (sscanf_result != 1) {
                printf("Invalid port for source.\n");
                return -1;
            }
            
            /* since port is TCP/UDP only, need filter for TCP/UDP only */
            scfl->should_filter_protocol = 1;
            scfl->should_filter_tcp = 1;
            scfl->should_filter_udp = 1;
            
            break;
        
        /* destination port */
        case 'q':
            scfl->should_filter_port_dst = 1;
            sscanf_result = sscanf(optarg, "%u", &(scfl->port_dst));
            if (sscanf_result != 1) {
                printf("Invalid port for destination.\n");
                return -1;
            }
            
            /* since port is TCP/UDP only, need filter for TCP/UDP only */
            scfl->should_filter_protocol = 1;
            scfl->should_filter_tcp = 1;
            scfl->should_filter_udp = 1;
            
            break;
        
        /* ttl min */
        case 'l':
            scfl->should_filter_ttl_min = 1;
            sscanf_result = sscanf(optarg, "%u", &(scfl->ttl_min));
            if (sscanf_result != 1) {
                printf("Invalid TTL min.\n");
                return -1;
            }
            break;
            
        /* ttl max */
        case 'm':
            scfl->should_filter_ttl_max = 1;
            sscanf_result = sscanf(optarg, "%u", &(scfl->ttl_max));
            if (sscanf_result != 1) {
                printf("Invalid TTL max.\n");
                return -1;
            }
            break;
        
        /* frag min */
        case 'f':
            scfl->should_filter_frag_min = 1;
            sscanf_result = sscanf(optarg, "%u", &(scfl->frag_min));
            if (sscanf_result != 1) {
                printf("Invalid minimum fragment number.\n");
                return -1;
            }
            break;
            
        /* frag max */
        case 'g':
            scfl->should_filter_frag_max = 1;
            sscanf_result = sscanf(optarg, "%u", &(scfl->frag_max));
            if (sscanf_result != 1) {
                printf("Invalid maximum fragment number.\n");
                return -1;
            }
            break;
        
        /* help */    
        case 'h':
        default:
            usage(argv[0]);
            return -1;
        }
    }

    return 0;
}


int main(int argc, char **argv)
{
    /* Used variables */
    ScapFlags scfl;
    ScapPackets scap;
    unsigned char buf[MAXMSG];
    struct sockaddr addr;
    int sock, data, size;

    /* Read signals */
    signal(SIGPIPE, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGSEGV, sig_handler);
    signal(SIGILL , sig_handler);

    /* Greet */
    greet("sCap");

    /* Initialise scap */
    init_scap_packets(&scap);
    init_scap_flags(&scfl);
    init_slog("scap", "config.cfg", 2);

    /* Parse Commandline Arguments */
    if (parse_arguments(argc, argv, &scfl)) 
        return 0;

    /* Create raw socket */
    sock = create_socket();

    /* Main loop (never ends) */
    while(1)
    {
        /* Get packet size */
        size = sizeof addr;

        /* Get packet */
        data = recvfrom(sock, buf, sizeof(buf), 0, &addr, (socklen_t *)&size);
        if(data < 0)
        {
            slog(0, SLOG_ERROR, "Can not get packets");
            break;
        }
        else read_scap_packet(&scap, &scfl, buf, data);
    }

    /* Close socket */
    close(sock);

    if (scfl.should_export_pcap && scfl.file_export_pcap != NULL)
    {
        fclose(scfl.file_export_pcap);
    }

    return 0;
}

sCap - Version: 1.0.2 Snapshot Build 17
----

sCap is open source commandline application project which makes you able to scan, capture and dump incoming tcp/udp/icmp traffic. Software is written for educational purposes and is distributed in the hope that it will be useful for anyone interested in this field.

###Usage
```
scap [-i] [-d] [-h]
options are:
 -i         # dump header info in file
 -d         # dump data in file
 -h         # print help and usage
```

With option -i, you can capture incomming traffic and log ip/udp/tcp/icmp headers in file. If you add option -d, sCap will capture this headers and also it will dump incomming traffic data in file. Without those arguments, sCap only counts numbers of incoming packets.

###Installation
Compilation of this project is possible with Makefile (just type 'make' in terminal).
```
git clone https://github.com/kala13x/scap.git
cd  scap
make
sudo make install
```
###How to use
sCap requires root access because of binding raw socket. When you launch sCap it only counts numbers of packets, but at the some time you can tail log file to see dumped data. 

###Example of log file output
```
2015.05.09-20:30:38 - [LIVE] Captured IP Header
2015.05.09-20:30:38 - [IP] Version : 4
2015.05.09-20:30:38 - [IP] Header Length : 5 DWORDS or 20 Bytes
2015.05.09-20:30:38 - [IP] Type Of Service : 40
2015.05.09-20:30:38 - [IP] Total Length : 83 Bytes(Size of Packet)
2015.05.09-20:30:38 - [IP] Identification : 4923
2015.05.09-20:30:38 - [IP] TTL : 53
2015.05.09-20:30:38 - [IP] Protocol : 6
2015.05.09-20:30:38 - [IP] Checksum : 46234
2015.05.09-20:30:38 - [IP] Source IP : 192.30.252.87
2015.05.09-20:30:38 - [IP] Destination IP : 192.168.0.137

2015.05.09-20:30:38 - [LIVE] Captured TCP Packet
2015.05.09-20:30:38 - [TCP] Source Port : 443
2015.05.09-20:30:38 - [TCP] Destination Port : 41324
2015.05.09-20:30:38 - [TCP] Sequence Number : 472573572
2015.05.09-20:30:38 - [TCP] Acknowledge Number : 2250858137
2015.05.09-20:30:38 - [TCP] Header Length : 8 DWORDS or 32 BYTES
2015.05.09-20:30:38 - [TCP] Urgent Flag : 0
2015.05.09-20:30:38 - [TCP] Acknowledgement Flag : 1
2015.05.09-20:30:38 - [TCP] Push Flag : 1
2015.05.09-20:30:38 - [TCP] Reset Flag : 0
2015.05.09-20:30:38 - [TCP] Synchronise Flag : 0
2015.05.09-20:30:38 - [TCP] Finish Flag : 0
2015.05.09-20:30:38 - [TCP] Window : 31
2015.05.09-20:30:38 - [TCP] Checksum : 12061
2015.05.09-20:30:38 - [TCP] Urgent Pointer : 0

2015.05.09-20:30:38 - [IP] Header
45 28 00 53 13 3B 40 00 35 06 B4 9A C0 1E FC 57 E     (.S.;@.5......W
C0 A8 00 89                                           ....

2015.05.09-20:30:38 - [TCP] Header
01 BB A1 6C 1C 2A E6 84 86 29 5E 99 80 18 00 1F       ...l.*...)^.�...
2F 1D 00 00 01 01 08 0A 40 9D 7A BE 01 4C CD 9C       /.......@.z..L..

2015.05.09-20:30:38 - [DATA] Payload
```

###Feel free to fork
You can fork, modify and change the code unther the GNU GPL 3 license. The project contains LICENSE file to see full license description.

###Get more info from blog
- Offencive-Security Georgia [http://off-sec.com/](http://off-sec.com)

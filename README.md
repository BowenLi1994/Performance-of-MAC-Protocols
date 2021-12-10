<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>
# Performance of MAC Protocols 

## Purpose
Purpose
1. Implement simulation programs to evaluate MAC protocols including Aloha, Slotted Aloha, and CSMA 1-persistent.
2. Get better understanding of the MAC protocols

##Description

In this assignment, you will write programs to study the performance of MAC protocols. The first program is a traffic generator that generates synthetic random traffic and store the traffic in a file. The first line of the traffic file contains a number telling the total number of packets in the file. After that, the traffic file contains line: of the formats
                                                  **pkt_id src_node dst_node pkt_size time**

and are sorted based on the time. Each line represents a packet of size pkt_size in bits from $s r c_{-}$node to dst_node that is ready to be sent at time time. The pkt_id must be unique for each packet in the file. The traffic generator should execute with the following parameters
                                **./traffic_generator num_node pkt_size offered_load num_pkts_per_node [seed]**

We will assume that our wireless system operates at a speed of 1 Mbps. The first parameter num_node is the number of stations in the system that can send and receive packets. The value of this parameter is from 2 to 200 . The second parameter pkt_size is the packet size in bits. The value of this parameter is from 100 to 2000. The third parameter the overall offered_load. It value is from 0.01 to 10 . The last parameter is the number of packets sent from each station in the traffic file. All stations will send the same number of packets with exactly the same characteristics.

The unit time is set to be 1 μs. The time starts from 0 (and only have integer values). A time value of 10000 means time 10000μs from the beginning. When generating the traffic, all stations should have the same probability to send packets throughout the time. For each packet sent from a station, the destination should be uniform randomly selected from the all nodes other than the source (all other nodes have equal probability to be the destination). For each station, since the unit time is 1μs and the bit rate is 1 Mbps (each bit will take 1 μs time to send) 
the average interpacket gap (in the unit of μs) for each station can be computed from the offered_load by solving the following:
                               


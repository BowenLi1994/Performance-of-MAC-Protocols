//
//  main.c
//  MAC ver1
//
//  Created by Bowen Li on 10/30/17.
//  Copyright © 2017 Bowen Li. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

struct packet {
  int pkt_id;
  int scr_node;
  int dst_node;
  int pkt_size;
  int time;
  int cls_flag;
  int new_time;
  int slot_time;
};
struct packet_temp{
  char pkt_id[5];
  char scr_node[5];
  char dst_node[5];
  char pkt_size[5];
  char time[5];
};
void convert_int (char *strLine,struct packet * packet_out) {
  struct packet_temp packet_out_temp;
  sscanf( strLine, "%s %s %s %s %s",packet_out_temp.pkt_id,packet_out_temp.scr_node,packet_out_temp.dst_node,packet_out_temp.pkt_size,packet_out_temp.time);
  packet_out->pkt_id=atoi(packet_out_temp.pkt_id);
  packet_out->scr_node=atoi(packet_out_temp.scr_node);
  packet_out->dst_node=atoi(packet_out_temp.dst_node);
  packet_out->pkt_size=atoi(packet_out_temp.pkt_size);
  packet_out->time=atoi(packet_out_temp.time);
  packet_out->new_time=packet_out->time;
  packet_out->cls_flag=0;
  if(packet_out->time % packet_out->pkt_size == 0){
    packet_out->slot_time = packet_out->time;
  }else{
    packet_out->slot_time = (packet_out->time / packet_out->pkt_size + 1) *  packet_out->pkt_size; //compute the slot id
  }
}

void ALOHA(struct packet *packet_out,int no){
    //channel=0, free,chnnel=1,busy
    int channel=0;
    int channel_begin=0;
    int channel_end=0;
    int temp=0;
    for(int i=0;i<no-1;i++){
        //when channel is free, sending the frame
        if(channel==0){
            printf("Time: %d, Packet %d: %d %d %d %d start sending\n",packet_out[i].time,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].time);
            channel=1;
            channel_begin=packet_out[i].time;
            channel_end=channel_begin+99;
            //if the time gap between next packer is higher than 100, this packet can be sent sucessfully, or cannot
            if(packet_out[i+1].time>channel_end){
                temp++;
                printf("Time: %d, Packet %d: %d %d %d %d finish sending: successfully transmitted\n",packet_out[i].time+99,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].time);
                channel=0;
            }
            else{
                channel_end=packet_out[i].time+99;
                printf("Time: %d, Packet %d: %d %d %d %d finish sending: failed\n",packet_out[i].time+99,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].time);
            }
        }
        //when the channel is busy
        else {
            //this channel can be sent
            if(packet_out[i].time>=channel_end){
                channel=0;
                channel_begin=packet_out[i].time;
                channel_end=channel_begin+99;
                //go back
                i=i-1;
            }
            else{
                channel_end=packet_out[i].time+99;
                printf("Time: %d, Packet %d: %d %d %d %d start sending: collision\n",packet_out[i].time,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].time);
                 printf("Time: %d, Packet %d: %d %d %d %d finish sending: failed\n",packet_out[i].time+99,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].time);

            }

        }
    }
    printf("Time: %d, Packet %d: %d %d %d %d start sending\n",packet_out[no-1].time,packet_out[no-1].pkt_id,packet_out[no-1].scr_node,packet_out[no-1].dst_node,packet_out[no-1].pkt_size,packet_out[no-1].time);
    printf("Time: %d, Packet %d: %d %d %d %d finish sending: successfully transmitted\n",packet_out[no-1].time+99,packet_out[no-1].pkt_id,packet_out[no-1].scr_node,packet_out[no-1].dst_node,packet_out[no-1].pkt_size,packet_out[no-1].time);
    printf("%d packets succefully transmitted.\n",temp);
    printf("%d packets failed transmission due to collision.\n",no-temp);
    float throughput=(float)(temp*100)/(float)(packet_out[no-1].time+99);
    printf("throughput %.0f kps\n",throughput*1000);


}
void SLOTTED_ALOHA(struct packet *packet_out,int no){
    //channel=0, free,chnnel=1,busy
    //slotted aloha with slot time 100
    //slotted id starting with 0
    int channel=0;
    int channel_begin=0;
    int channel_end=0;
    int temp=0;
    for(int i=0;i<no-1;i++){
        //when channel is free, sending the frame
        if(channel==0){
            printf("Time: %d, Packet %d: %d %d %d %d start sending\n",packet_out[i].slot_time,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].slot_time);
            channel=1;
            channel_begin=packet_out[i].slot_time;
            channel_end=channel_begin+99;
            //if the time gap between next packer is higher than 100, this packet can be sent sucessfully, or cannot
            if(packet_out[i+1].slot_time>channel_end){
                temp++;
                printf("Time: %d, Packet %d: %d %d %d %d finish sending: successfully transmitted\n",packet_out[i].slot_time+99,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].slot_time);
                channel=0;
            }
            else{
                channel_end=packet_out[i].slot_time+99;
                printf("Time: %d, Packet %d: %d %d %d %d finish sending: failed\n",packet_out[i].slot_time+99,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].slot_time);
            }
        }
        //when the channel is busy
        else {
            //this channel can be sent
            if(packet_out[i].slot_time>=channel_end){
                channel=0;
                channel_begin=packet_out[i].slot_time;
                channel_end=channel_begin+99;
                //go back
                i=i-1;
            }
            else{
                channel_end=packet_out[i].slot_time+99;
                printf("Time: %d, Packet %d: %d %d %d %d start sending: collision\n",packet_out[i].slot_time,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].slot_time);
                 printf("Time: %d, Packet %d: %d %d %d %d finish sending: failed\n",packet_out[i].slot_time+99,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].slot_time);

            }

        }
    }
    printf("Time: %d, Packet %d: %d %d %d %d start sending\n",packet_out[no-1].slot_time,packet_out[no-1].pkt_id,packet_out[no-1].scr_node,packet_out[no-1].dst_node,packet_out[no-1].pkt_size,packet_out[no-1].slot_time);
    printf("Time: %d, Packet %d: %d %d %d %d finish sending: successfully transmitted\n",packet_out[no-1].slot_time+99,packet_out[no-1].pkt_id,packet_out[no-1].scr_node,packet_out[no-1].dst_node,packet_out[no-1].pkt_size,packet_out[no-1].slot_time);
    printf("%d packets succefully transmitted.\n",temp);
    printf("%d packets failed transmission due to collision.\n",no-temp);
    float throughput=(float)(temp*100)/(float)(packet_out[no-1].slot_time+99);
    printf("throughput %.0f kps\n",throughput*1000);

}
void CSMA_1(struct packet *packet_out,int no){
    printf("%d\n",packet_out[1].time);
    int channel=0;
    int temp=0;
    int channel_end=0;
    for(int i=0;i<no;i++){
        if(channel==0){
            printf("Time: %d, Packet %d: %d %d %d %d start sending\n",packet_out[i].new_time,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].time);
            printf("Time: %d, Packet %d: %d %d %d %d finish sending: successfully transmitted\n",packet_out[i].new_time+99,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].time);
            channel=1;
            channel_end=packet_out[i].new_time+99;
            temp++;
        }
        else{
            if(packet_out[i].time>channel_end){
                channel=0;
                i=i-1;
            }
            else{
                printf("Time: %d, Packet %d: %d %d %d %d wait for idle\n",packet_out[i].time,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].time);
                if(packet_out[i+1].time<=channel_end||packet_out[i].cls_flag==1){
                    packet_out[i+1].cls_flag=1;
                    printf("Time: %d, Packet %d: %d %d %d %d start sending:collison \n",channel_end +1,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].time);
                    printf("Time: %d, Packet %d: %d %d %d %d finish sending:failed \n",channel_end +100,packet_out[i].pkt_id,packet_out[i].scr_node,packet_out[i].dst_node,packet_out[i].pkt_size,packet_out[i].time);

                    if(packet_out[i+1].time>channel_end){
                        channel_end=channel_end+100;
                        packet_out[i+1].cls_flag=0;
                    }
                }
                else{
                    packet_out[i].new_time=channel_end+1;
                    channel=0;
                    i=i-1;
                }
            }
        }
    }

    printf("%d packets succefully transmitted.\n",temp);
    printf("%d packets failed transmission due to collision.\n",no-temp);
    float throughput=(float)(temp*100)/(float)(packet_out[no-1].time+99);
    printf("throughput %.0f kps\n",throughput*1000);
}

int main(int argc, char *argv[]) {
    int packet_num;
    int temp_no=0;
    //int method_no;
    struct packet packte_out[1001];
    char strLine[1024];
    FILE *fp = fopen("data", "rb");
    if( fp == NULL){
        printf("Error at opening files!\n");
        return 0;
    }
     fgets(strLine,1024,fp);
     packet_num = atoi(strLine);
    while (!feof(fp))
    {
        fgets(strLine,1024,fp);
        convert_int(strLine,&packte_out[temp_no]);
        temp_no++;
    }
    if(argc < 2){
      std::cout << "Must input one of the following simulator method: aloha, slotted_aloha, csma_1 " << std::endl;
      exit(1);
    }
    std::string method(argv[1]);
    if(method == "aloha"){
      ALOHA(packte_out, packet_num);
    }else if(method == "slotted_aloha"){
      SLOTTED_ALOHA(packte_out, packet_num);
    }else if(method == "csma_1"){
      CSMA_1(packte_out, packet_num);
    }else{
      std::cout << "Wrong simulator method " << std::endl;
    }

    // printf("Input the protocol you want to use:\n1.ALOHA\n2.Slotted ALOHA\n3.CSMA 1-persistent\n0.Exit\n");
    // do{
    //     scanf("%d",&method_no);
    // switch(method_no){
    //     case 1:
    //         ALOHA(packte_out, packet_num);
    //         break;
    //     case 2:
    //         SLOTTED_ALOHA(packte_out, packet_num);
    //         break;
    //     case 3:
    //         CSMA_1(packte_out, packet_num);
    //         break;
    //       }
    // }while(method_no!=0);
    return 0;
}

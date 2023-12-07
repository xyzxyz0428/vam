/*
    Simple udp client
*/
#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h> // for close
#include "raw-its.h"


#define SERVER "141.30.187.201"
#define BUFLEN 512  //Max length of buffer
#define PORT1 8888  //The port on which to send data
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main()
{
    struct sockaddr_in si_other;
    socklen_t s, i, slen=sizeof(si_other);
    
	int input_yawRateValue;
    	int input_curvatureValue;
	int input_vruEnvironment;
    	int j=0; 
	
	struct RAWexternedata buf[2];
    
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT1);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    
    while(1)
    {   
		scanf("%d,%d,%d", &input_yawRateValue,&input_curvatureValue,&input_vruEnvironment);
		struct RAWexternedata datatest={
				input_yawRateValue,
				input_curvatureValue,
				input_vruEnvironment};
		struct RAWexternedata message[2]={datatest};
		
		
        //send the message
        if (sendto(s, message, sizeof(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
        
       printf("send from PC1 to RSU: j=%d\nyawRateValue=%d, curvatureValue=%d, vruEnvironment=%d\n",
               j,
               (int)message[0].yawRateValue,
               (int)message[0].curvatureValue,
               (int)message[0].vruEnvironment);
       
       
      // sleep(1);
       j++; 
      //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(message, 0, sizeof(message));
        
        //try to receive some data, this is a blocking call
        if (recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            die("recvfrom()");
        }
        printf("receive the Backdata :\nyawRateValue=%d, curvatureValue=%d, vruEnvironment=%d\n\n",
               (int)buf[0].yawRateValue,
               (int)buf[0].curvatureValue,
               (int)buf[0].vruEnvironment);
        memset(buf,0,sizeof(buf)); 
  
      }
    
 
    close(s);
    return 0;
}

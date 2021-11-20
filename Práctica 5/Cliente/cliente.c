#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Records.h"

#define PORT 8080

   typedef struct
   {
        int32_t SOF;
        int32_t SENSOR;
        int8_t Data_Size;
        int32_t DATA;
        int32_t CS;
   }adpd;

int main(int argc, char const *argv[])
{
    int sock = 0, valread = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char Buffer[1024];
    char cs = 0;
	adpd ad;

	ad.SOF = 0xAA;
	ad.SENSOR = 0x64;
	ad.Data_Size = 2;
	ad.DATA = SLOTA_AFE_WINDOW;

	cs = ad.SOF + ad.SENSOR + ad.Data_Size + ad.DATA;
	cs = ~cs;//Calculo del CS

	ad.CS = cs;

	memcpy(Buffer, &ad, sizeof(adpd));

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.101.7", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock ,  Buffer, sizeof(adpd) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer);
    return 0;
}

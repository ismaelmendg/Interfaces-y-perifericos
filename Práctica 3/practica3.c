#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#define gpio21E fd = open("/sys/class/gpio/gpio21/value", O_WRONLY); write(fd,"1",1); close(fd);
#define gpio21A fd = open("/sys/class/gpio/gpio21/value", O_WRONLY); write(fd, "0",1); close(fd); 
#define gpio20E fd = open("/sys/class/gpio/gpio20/value", O_WRONLY); write(fd,"1",1); close(fd);
#define gpio20A fd = open("/sys/class/gpio/gpio20/value", O_WRONLY); write(fd, "0",1); close(fd);
#define gpio16E fd = open("/sys/class/gpio/gpio16/value", O_WRONLY); write(fd, "1",1); close(fd);
#define gpio16A fd = open("/sys/class/gpio/gpio16/value", O_WRONLY); write(fd, "0",1); close(fd);
#define gpio12E fd = open("/sys/class/gpio/gpio12/value", O_WRONLY); write(fd, "1",1); close(fd);
#define gpio12A fd = open("/sys/class/gpio/gpio12/value", O_WRONLY); write(fd, "0",1); close(fd);
#define gpio26E fd = open("/sys/class/gpio/gpio26/value", O_WRONLY); write(fd, "1",1); close(fd);
#define gpio26A fd = open("/sys/class/gpio/gpio26/value", O_WRONLY); write(fd, "0",1); close(fd);
#define readsw1 fd = open("/sys/class/gpio/gpio24/value", O_RDONLY); read(fd, sw1,1); close(fd);
#define readsw2 fd = open("/sys/class/gpio/gpio23/value", O_RDONLY); read(fd, sw2,1); close(fd);
#define ReadB1  fd = open("/sys/class/gpio/gpio25/value", O_RDONLY); read(fd,b1,1); close(fd);
#define ReadB2  fd = open("/sys/class/gpio/gpio22/value", O_RDONLY); read(fd,b2,1); close(fd);
#define ReadB3  fd = open("/sys/class/gpio/gpio27/value", O_RDONLY); read(fd,b3,1); close(fd);
#define ReadB4  fd = open("/sys/class/gpio/gpio17/value", O_RDONLY); read(fd,b4,1); close(fd);

int main(){

    u_int8_t sw1[2];
    u_int8_t sw2[2];
    u_int8_t sw = 0;
    double x=0;
    u_int8_t b1[2];
    u_int8_t b2[2];
    u_int8_t b3[2];
    u_int8_t b4[2];
    u_int32_t vacio[]={0};
    FILE *fl;
    FILE *fr;

    int fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, "21",2);//LED1
    write(fd, "20",2);//LED2
    write(fd, "16",2);//LED3
    write(fd, "12",2);//LED4
    write(fd, "23",2);//SW2
    write(fd, "24",2);//SW1
    write(fd, "25",2);//B1
    write(fd, "22",2);//B2
    write(fd, "27",2);//B3
    write(fd, "17",2);//B4
    write(fd, "26",2);//LED_INTER
    close(fd);

    fd = open("/sys/class/gpio/gpio26/direction", O_WRONLY);//LED_INTER
    write(fd,"out", 3);
    close(fd);
    fd = open("/sys/class/gpio/gpio21/direction", O_WRONLY);//LED1
    write(fd,"out", 3);
    close(fd);
    fd = open("/sys/class/gpio/gpio20/direction", O_WRONLY);//LED2
    write(fd,"out", 3);
    close(fd);
    fd = open("/sys/class/gpio/gpio16/direction", O_WRONLY);//LED3
    write(fd,"out", 3);
    close(fd);
    fd = open("/sys/class/gpio/gpio12/direction", O_WRONLY);//LED4
    write(fd,"out", 3);
    close(fd);
    fd = open("/sys/class/gpio/gpio23/direction", O_WRONLY);//SW2
    write(fd,"in", 2);
    close(fd);
    fd = open("/sys/class/gpio/gpio24/direction", O_WRONLY);//SW1
    write(fd,"in", 2);
    close(fd);
    fd = open("/sys/class/gpio/gpio25/direction", O_WRONLY);//B1
    write(fd,"in", 2);
    close(fd);
    fd = open("/sys/class/gpio/gpio22/direction", O_WRONLY);//B2
    write(fd,"in", 2);
    close(fd);
    fd = open("/sys/class/gpio/gpio27/direction", O_WRONLY);//B3
    write(fd,"in", 2);
    close(fd);
    fd = open("/sys/class/gpio/gpio17/direction", O_WRONLY);//B4
    write(fd,"in", 2);
    close(fd);

while(1){

    readsw1
    readsw2
    if(sw1[0] == '0' && sw2[0] == '0'){sw = 2;}
    if(sw1[0] == '1' && sw2[0] == '1'){sw = 2;}
    if(sw1[0] == '0' && sw2[0] == '1'){sw = 1;}
    if(sw1[0] == '1' && sw2[0] == '0'){sw = 0;}

    switch(sw){

    case 0:
	fl = fopen("record.txt","w");
	fwrite(vacio,sizeof(int),sizeof(vacio),fl);
	fclose(fl);
        while(sw1[0]=='1'){

    fl = fopen("record.txt", "a");

	readsw1
	ReadB1
        ReadB2
        ReadB3
        ReadB4

        if(b1[0] == '1'){ gpio21E fputc('1', fl); }else{gpio21A
        fputc('0', fl); }

	if(b2[0] == '1'){ gpio20E fputc('2', fl); }else{gpio20A
        fputc('0', fl); }

	if(b3[0] == '1'){ gpio16E fputc('3', fl); }else{gpio16A
        fputc('0', fl); }

	if(b4[0] == '1'){ gpio12E fputc('4', fl); }else{gpio12A
        fputc('0', fl); }

	fclose(fl);}
	break;

      case 1:
   fr = fopen("record.txt", "r");
	while(!feof(fr)){

	x = fgetc(fr);
	if(x == '1'){gpio21E}else{gpio21A}
        if(x == '2'){gpio20E}else{gpio20A}
        if(x == '3'){gpio16E}else{gpio16A}
        if(x == '4'){gpio12E}else{gpio12A}
	readsw2
	if(sw2[0]=='0'){break;}else{}

}//Fin while

	fclose(fr);
        break;

	case 2:
		gpio21A gpio20A gpio16A gpio12A
	break;
}//Fin switch
}//Fin while principal
	return 1;
}//Fin main


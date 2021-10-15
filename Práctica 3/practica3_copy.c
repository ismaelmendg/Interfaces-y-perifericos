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

double time_diff(struct timeval x, struct timeval y){
	double x_ms, y_ms;
	x_ms = (double)x.tv_sec * 1000000 + (double)x.tv_usec;
	y_ms = (double)y.tv_sec * 1000000 + (double)y.tv_usec;
return y_ms - x_ms;
}

int main(){

    struct timeval start, end, start1, end1, start2, end2, start3, end3, start4, end4,start_1, end_1,start_2, end_2,start_3, end_3,start_4, end_4;
    u_int8_t sw1[2];
    u_int8_t sw2[2];
    u_int8_t sw = 0;
    double x=0,x1=0, y1=0,x2=0, y2=0,x3=0, y3=0,x4=0, y4=0;
    u_int8_t b1[2];
    u_int8_t b2[2];
    u_int8_t b3[2];
    u_int8_t b4[2];
    u_int32_t vacio[]={0};
    u_int8_t i_1=0, i_2=0, i_3=0, i_4=0;
    u_int8_t tiempo=0;
    u_int32_t size=0;
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

    fl = fopen("record.txt", "a");

	ReadB1
        ReadB2
        ReadB3
        ReadB4

	if(b1[0] == '1'){
                if(i_1 == 0){
		gettimeofday(&end1, NULL);
		y1 = time_diff(start1,end1);
		printf("y1 = %6.0fus\n",y1);
		fputc('5',fl);///5 es el cero de LED1
		fputc(y1,fl);  y1 =0;
		gettimeofday(&start, NULL);
		gpio21E fputc('1', fl);
		i_1 = 1;
	}}

	if(b1[0]=='0'){
		if(i_1 == 1){
		gettimeofday(&start1, NULL);
		gettimeofday(&end,NULL);
		x1 = time_diff(start, end);
		printf("x1 = %6.0fus\n",x1);
		gpio21A
		fputc(x1, fl);
		x1 = 0; i_1 = 0;
	}}
///////////////////////////////////////////////////////////////
        if(b2[0] == '1'){
                if(i_2 == 0){
                gettimeofday(&end2, NULL);
                y2 = time_diff(start2,end2);
                printf("y2 = %6.0fus\n",y2);
                fputc('6',fl);///6 es el cero de LED2
                fputc(y2,fl);  y2 =0;

                gettimeofday(&start_2, NULL);
                gpio20E fputc('2', fl);
                i_2 = 1;
        }}

        if(b2[0]=='0'){
                if(i_2 == 1){
                gettimeofday(&start2,NULL);
                gettimeofday(&end_2,NULL);  
                x2 = time_diff(start_2, end_2);
                printf("x2 = %6.0fus\n",x2);
                gpio20A
                fputc(x2, fl);
                x2 = 0; i_2 = 0;
        }}
///////////////////////////////////////////////////////////////
        if(b3[0] == '1'){
                if(i_3 == 0){
                gettimeofday(&end3, NULL);
                y3 = time_diff(start3,end3);
                printf("y3 = %6.0fus\n",y3);
                fputc('7',fl);///7 es el cero de LED3
                fputc(y3,fl);  y3 =0;
                gettimeofday(&start_3, NULL);
                gpio16E fputc('3', fl);
                i_3 = 1;
        }}

        if(b3[0]=='0'){
                if(i_3 == 1){
                gettimeofday(&start3,NULL);
                gettimeofday(&end_3,NULL); 
                x3 = time_diff(start_3, end_3);
                printf("x3 = %6.0fus\n",x3);
                gpio16A
                fputc(x3, fl);
                x3 = 0; i_3 = 0;
        }}
///////////////////////////////////////////////////////////////
        if(b4[0] == '1'){
                if(i_4 == 0){
                gettimeofday(&end4, NULL);
                y4 = time_diff(start4,end4);
                printf("y4 = %6.0fus\n",y4);
                fputc('8',fl);///8 es el cero de LED4
                fputc(y4,fl);  y4 =0;

                gettimeofday(&start_4, NULL);
                gpio12E fputc('4', fl);
                i_4 = 1;
        }}

        if(b4[0]=='0'){
                if(i_4 == 1){
                gettimeofday(&start4,NULL);
                gettimeofday(&end_4,NULL); 
                x4 = time_diff(start_4, end_4);
                printf("x4 = %6.0fus\n",x4);
                gpio12A
                fputc(x4, fl);
                x4 = 0; i_4 = 0;
        }}

	fclose(fl);
	break;

      case 1:
   fr = fopen("record.txt", "r");
	while(!feof(fr)){

	x = fgetc(fr);
	if(x == '1'){gpio21E }else{gpio21A}
        if(x == '2'){gpio20E }else{gpio20A}
        if(x == '3'){gpio16E }else{gpio16A}
        if(x == '4'){gpio12E }else{gpio12A}
	readsw2
	if(sw2[0]=='0'){break;}else{}
	usleep(10000);
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


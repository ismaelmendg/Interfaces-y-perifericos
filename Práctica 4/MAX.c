#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define CONFIG_MODE 0x09 
#define CONFIG_SpO2 0x0A
#define LED_RED     0x0C
#define LED_IR      0x0D
#define CONFIG_FIFO 0x08
#define FIFO_WR_PTR 0x04
#define OVF_COUNTER 0x05
#define FIFO_RD_PTR 0x06
#define FIFO_DATA   0x07
#define INTERRUPT_ENABLE 0x02
#define PIN_INT PD_6
#define PIN_ANALOG PED_2
#define PPG_RDY 0x80
#define REG_INTR_STATUS_1 0x00
#define activeLEDs 2

u_int8_t max30102_Buffer[6];
unsigned long intensidad_red;
unsigned long intensidad_ir;
//boolean intensidad_preparada = false;
float prev_w_red = 0;
float prev_w_ir = 0;
float alpha = 0.999215;
float IntRed;
float IntIr;
int ecg_analog;
float ecg_out, BUFFER_LENGHT;

/*struct filtroDC
{
	float w;
	float y;
}

struct filtroDC removedorDC(float x, float prev_w, float  alpha)
{
	struct filtroDC result;
	result.w = x + alpha * prev_w;
	result.y = result.w - prev_w;
	return result;
}*/

void config()
{
	int dir;
	printf("config Init\n");
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x57);
	
		wiringPiI2CWriteReg8(dir, INTERRUPT_ENABLE, 0x40);	
		wiringPiI2CWriteReg8(dir, CONFIG_MODE, 0x3);
		wiringPiI2CWriteReg8(dir, CONFIG_SpO2, 0x6F);
		wiringPiI2CWriteReg8(dir, LED_RED, 0x3F);
		wiringPiI2CWriteReg8(dir, LED_IR, 0x3F);		
		wiringPiI2CWriteReg8(dir, CONFIG_FIFO, 0x60);		
		
}
/*
void read(void)
{
	int dir = 0;
	int numberOffSamples = 0;
	int bytesLeftToRead = 0;
	printf("config Init\n");
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x57);
	
	char readPointer = wiringPiI2CReadReg8(dir, FIFO_RD_PTR);
	char writePointer = wiringPiI2CReadReg8(dir, FIFO_WR_PTR);
					printf("%d\n", readPointer);
					printf("%d\n", writePointer);
	if(readPointer != writePointer)
	{
		numberOffSamples = writePointer - readPointer;
		if(numberOffSamples < 0) numberOffSamples += 32;
		
		bytesLeftToRead = numberOffSamples + activeLEDs *3;
		
		wiringPiI2CWrite(dir, FIFO_DATA);

			while(bytesLeftToRead > 0)
			{
				int toGet = bytesLeftToRead;
				if(toGet > BUFFER_LENGHT)
				{
					toGet = BUFFER_LENGHT -(BUFFER_LENGHT %(activeLEDs*3));
				}	
				bytesLeftToRead -= toGet;
			while(toGet > 0)
			{
				u_int32_t temp[32];
				u_int32_t tempLong;
				
				temp[3] = 0;
				temp[2] = wiringPiI2CReadReg8(dir, FIFO_DATA);
				temp[1] = wiringPiI2CReadReg8(dir, FIFO_DATA);
				temp[0] = wiringPiI2CReadReg8(dir, FIFO_DATA);
				
				memcpy(&tempLong, temp, sizeof(tempLong));
				printf("%d\n", tempLong);
				tempLong &= 0x3FFFF;
				
				if(activeLEDs > 1)
				{
				temp[3] = 0;
				temp[2] = wiringPiI2CReadReg8(dir, FIFO_DATA);
				temp[1] = wiringPiI2CReadReg8(dir, FIFO_DATA);
				temp[0] = wiringPiI2CReadReg8(dir, FIFO_DATA);
				
				memcpy(&tempLong, temp, sizeof(tempLong));
				printf("%d\n", tempLong);
				tempLong &= 0x3FFFF;	
				}	
			}	
			}
	}
}

void read()
{
	int dir;
	printf("config Init\n");
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x57);
	while(1)
	{
	//if(intensidad_preparada)
	//{
		//intensidad_preparada = false;
		max30102_Buffer = wiringPiI2CReadReg8(dir, REG_INTR_STATUS_1);
		
		//if(max30102_Buffer[0]&PPG_RDY && wiringPiI2CReadReg8(dir, FIFO_DATA))
		//
		while(i<7)
		{
				i++;
				max30102_Buffer[i] = wiringPiI2CReadReg8(dir, FIFO_DATA);
		}	
		
			intensidad_red = max30102_Buffer[0] & 0x3;
			intensidad_red = max30102_Buffer[1] | intensidad_red << 8;
			intensidad_red = max30102_Buffer[2] | intensidad_red << 8;
			intensidad_ir = max30102_Buffer[3] & 0x3;
			intensidad_ir = max30102_Buffer[4] | intensidad_ir << 8;
			intensidad_ir = max30102_Buffer[5] | intensidad_ir << 8;
			intensidad_red = (float)intensidad_red;
			intensidad_ir = (float)intensidad_ir;
			struct filtroDC red;
			red = removedorDC(intensidad_red, prev_w_red , alpha);
			prev_w_red = red.w;
			struct filtroDC ir;
			ir = removedorDC(intensidad_ir, prev_w_ir , alpha);
			prev_w_ir = ir.w;
			IntIr=-1.0*((ir.y*16384.0)/262143.0);
            IntRed=-1.0*((red.y*16384.0)/262143.0);
			printf("%f.4\n", IntIr);
			printf("%f.4\n",IntRed);
			
	}
}*/

void read()
{
  u_int32_t un_temp;
  u_int8_t uch_temp;
  int *pun_ir_led=0;
  int *pun_red_led=0;
  
  	int dir;
	printf("config Init\n");
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x57);
  
  wiringPiI2CWrite(dir, FIFO_DATA);
while(1){
  un_temp=wiringPiI2CReadReg8(dir, FIFO_DATA);
  un_temp<<=16;
  *pun_red_led+=un_temp;
  un_temp=wiringPiI2CReadReg8(dir, FIFO_DATA);
  un_temp<<=8;
  *pun_red_led+=un_temp;
  un_temp=wiringPiI2CReadReg8(dir, FIFO_DATA);
  *pun_red_led+=un_temp;
  un_temp=wiringPiI2CReadReg8(dir, FIFO_DATA);
  un_temp<<=16;
  *pun_ir_led+=un_temp;
  un_temp=wiringPiI2CReadReg8(dir, FIFO_DATA);
  un_temp<<=8;
  *pun_ir_led+=un_temp;
  un_temp=wiringPiI2CReadReg8(dir, FIFO_DATA);
  *pun_ir_led+=un_temp;

  *pun_red_led&=0x03FFFF;  //Mask MSB [23:18]
  *pun_ir_led&=0x03FFFF;  //Mask MSB [23:18]
  
  				printf("%d\n", pun_red_led);
				printf("%d\n", pun_ir_led);
}
}
int main(void)
{
	config();
	read();

}
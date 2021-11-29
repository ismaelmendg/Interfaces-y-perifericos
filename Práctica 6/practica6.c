#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include <errno.h>
#define PORT 8080
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define STATUS           0x00
#define INT_MASK         0x01
#define GPIO_DRIV        0x02
#define BG_STATUS        0x04
#define FIFO_THRESH      0x06
#define DEVID            0x08
#define I2CS_ID          0x09 
#define CLK_RATIO        0x0A
#define GPIO_CTRL         0x0B
#define SLAVE_ADDRESS_KEY 0x0D
#define SW_RESET         0x0F
#define MODE             0x10
#define SLOT_EN          0x11
#define FSAMPLE          0x12
#define PD_LED_SELECT    0x14
#define NUM_AVG          0x15
#define BG_MEAS_A       0x16
#define INT_SEQ_A        0x17
#define SLOTA_CH1_OFFSET 0x18
#define SLOTA_CH2_OFFSET 0x19
#define SLOTA_CH3_OFFSET 0x1A
#define SLOTA_CH4_OFFSET 0x1B
#define BG_MEAS_B        0x1C
#define INT_SEQ_B        0x1D
#define SLOTB_CH1_OFFSET 0x1E
#define SLOTB_CH2_OFFSET 0x1F
#define SLOTB_CH3_OFFSET 0x20
#define SLOTB_CH4_OFFSET 0x21 
#define ILED3_COARSE     0x22
#define ILED1_COARSE     0x23
#define ILED2_COARSE     0x24
#define ILED_FINE        0x25
#define SLOTA_LED_PULSE  0x30
#define SLOTA_NUMPULSES 0x31
#define LED_DISABLE      0x34
#define SLOTB_LED_PULSE  0x35
#define SLOTB_NUMPULSES  0x36
#define ALT_PWR_DN       0x37
#define EXT_SYNC_STARTUP 0x38
#define SLOTA_AFE_WINDOW 0x39
#define SLOTB_AFE_WINDOW 0x3B
#define AFE_PWR_CFG1     0x3C 
#define SLOTA_FLOAT_LED  0x3E
#define SLOTB_FLOAT_LED  0x3F
#define SLOTA_TIA_CFG    0x42
#define SLOTA_AFE_CFG    0x43
#define SLOTB_TIA_CFG    0x44
#define SLOTB_AFE_CFG    0x45
#define SAMPLE_CLK      0x4B
#define CLK32M_ADJUST   0x4D
#define EXT_SYNC_SEL    0x4F
#define CLK32M_CAL_EN   0x50
#define AFE_PWR_CFG2    0x54
#define TIA_INDEP_GAIN  0x55
#define Math             0x58
#define FLT_CONFIG_B    0x59
#define FLT_LED_FIRE    0x5A
#define FLT_CONFIG_A    0x5E
#define DATA_ACCESS_CTL 0x5F
#define FIFO_ACCESS     0x60
#define SLOTA_PD1_16BIT 0x64
#define SLOTA_PD2_16BIT 0x65
#define SLOTA_PD3_16BIT 0x66
#define SLOTA_PD4_16BIT 0x67
#define SLOTB_PD1_16BIT 0x68
#define SLOTB_PD2_16BIT 0x69
#define SLOTB_PD3_16BIT 0x6A
#define SLOTB_PD4_16BIT 0x6B
#define A_PD1_LOW        0x70
#define A_PD2_LOW        0x71
#define A_PD3_LOW        0x72
#define A_PD4_LOW        0x73
#define A_PD1_HIGH       0x74
#define A_PD2_HIGH       0x75
#define A_PD3_HIGH       0x76
#define A_PD4_HIGH       0x77
#define B_PD1_LOW        0x78
#define B_PD2_LOW        0x79
#define B_PD3_LOW        0x7A
#define B_PD4_LOW        0x7B
#define B_PD1_HIGH       0x7C
#define B_PD2_HIGH       0x7D
#define B_PD3_HIGH       0x7E
#define B_PD4_HIGH       0x7F
#define N 8

int storage_socketID[5] = {0};
int32_t x = 0, var = 0;
pthread_mutex_t socketMutex;

void config(void)
{
	int dir;
	printf("config Init\n");
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x64);
	
	wiringPiI2CWriteReg16(dir,SAMPLE_CLK, 0x8000);
	wiringPiI2CReadReg16(dir, SAMPLE_CLK);
	
	wiringPiI2CWriteReg16(dir, MODE, 0x0100);
	wiringPiI2CReadReg16(dir, MODE);
	
////////////Registros de control LED	
	wiringPiI2CWriteReg16(dir, PD_LED_SELECT, 0x5005);//PDET1 a canal 3 - PDET2 a canla 4 en intervalo A y B
    wiringPiI2CReadReg16(dir, PD_LED_SELECT);
	
	wiringPiI2CWriteReg16(dir, ILED1_COARSE, 0x4620);//Velocidad de respuesta media - COARSE = 151.3
	wiringPiI2CReadReg16(dir, ILED1_COARSE);
	
	wiringPiI2CWriteReg16(dir, ILED2_COARSE, 0x0000);//Controlador LED 2 bajo consumo
	wiringPiI2CReadReg16(dir, ILED2_COARSE);
	
	wiringPiI2CWriteReg16(dir, ILED3_COARSE, 0x0000);//Controlador LED 3 bajo consumo
	wiringPiI2CReadReg16(dir, ILED3_COARSE);
	
	wiringPiI2CWriteReg16(dir, ILED_FINE , 0x1A00);//Ajuste de 27 - LED_peak = 151.3*1.302 = 196.99mA
	wiringPiI2CReadReg16(dir, ILED_FINE);
	
	wiringPiI2CWriteReg16(dir, SLOTA_LED_PULSE, 0x2007);
	wiringPiI2CReadReg16(dir, SLOTA_LED_PULSE);
	
	wiringPiI2CWriteReg16(dir, SLOTA_NUMPULSES, 0x1902);//Periodo de 19us con 2 pulsos por periodo
	wiringPiI2CReadReg16(dir, SLOTA_NUMPULSES);
	
	wiringPiI2CWriteReg16(dir, SLOTB_LED_PULSE, 0x2007);
	wiringPiI2CReadReg16(dir, SLOTB_LED_PULSE);
	
	wiringPiI2CWriteReg16(dir, SLOTB_NUMPULSES, 0x1902);//Periodo de 19us con 2 pulsos por periodo
	wiringPiI2CReadReg16(dir, SLOTB_NUMPULSES);
	
////////////SET  SLOT
	wiringPiI2CWriteReg16(dir, SLOT_EN, 0xA930);//SLOT A y B habilitados con los 4 canales a 32 bits y FIFO promediada 
	wiringPiI2CReadReg16(dir, SLOT_EN);
	
	wiringPiI2CWriteReg16(dir, Math, 0x8000);
	wiringPiI2CReadReg16(dir, Math);
	
	wiringPiI2CWriteReg16(dir, SLOTA_TIA_CFG, 0x351C);//Ganancia de 200, voltaje de 1.27v
	wiringPiI2CReadReg16(dir, SLOTA_TIA_CFG);
	
	wiringPiI2CWriteReg16(dir, SLOTA_AFE_CFG, 0xA5AD);//modo de ruta completa analógica (TIA→BPF→EN T→ADC)
	wiringPiI2CReadReg16(dir, SLOTA_AFE_CFG);
	
	wiringPiI2CWriteReg16(dir, SLOTB_TIA_CFG, 0x351C);//Ganancia de 200, voltaje de 1.27v
	wiringPiI2CReadReg16(dir, SLOTB_TIA_CFG);
	
	wiringPiI2CWriteReg16(dir, SLOTB_AFE_CFG, 0xA5AD);//modo de ruta completa analógica (TIA→BPF→EN T→ADC)
	wiringPiI2CReadReg16(dir, SLOTB_AFE_CFG);
	
///////////SET OPERATION MODE
	wiringPiI2CWriteReg16(dir, DATA_ACCESS_CTL, 0x0100);//Encender el reloj de 32MHz
	wiringPiI2CReadReg16(dir, DATA_ACCESS_CTL);
	
	wiringPiI2CWriteReg16(dir, MODE, 0x0200);	
}

int rotar(int x, char n)
{
	unsigned char maso = 0x01;
	int32_t masl = 0x8000;
	unsigned char temp = 0;
	int32_t i = 0;

	while(i != n)
	{
		i++;
		
		temp = x & maso;
		x = x >> 1;
		
		if(temp == 1)
		{
			x = x | masl;
		}
	}
	
	return x;
}
//////////////////////////////////////////////////////////////////////////////////////

void *SendMessages (void *ptr)
{

	int dir;
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x64);	
	
	int32_t valor = 0, i = 0;
	char CS = 0;
    int32_t buffer[1024] = {0};	
	char Buffer_server[20];	
	
    while (1)
    {

	pthread_mutex_lock(&socketMutex);

	if(storage_socketID[x-1] != var){

	read( storage_socketID[x-1], buffer, 1024);

	while(i != 4)
	{
		CS = CS + buffer[i];
		i++;
	}
	
	CS = CS | buffer[4];//OR de CS obtenido con el calculado por datos de entrada

	if(CS == 0xFF){//Verificación CS
		printf("CS correcto\n");
		if(buffer[0] == 0xAA)//Verificación de SOF
		{
			if(buffer[1] == 0x64)//Verificación de sensor
			{
				if(buffer[2] == 2){//Lectura de registro pedido por el cliente
					valor = wiringPiI2CReadReg16(dir, buffer[3]);
					printf("ID5 %d\r\n", buffer[3]);
				}else
				{
					printf("Longitud de dato invalido\n");
				}
			}else
			{
				printf("verificacion sensor erronea\n");
			}
		}else
		{
			printf("Verificacion SOF erronea\n");
		}
	}else
	{
		printf("CS incorrecto\n");
		printf("SOF = %X\n", buffer[0]);
		printf("SENSOR = %X\n", buffer[1]);
		printf("DATA_SIZE= %X\n", buffer[2]);
		printf("REGISTRO: %X\n", buffer[3]);
		printf("CS = %X\n", buffer[4]);
	}
	
	valor = rotar(valor, N);//Rotación de bits para correcta interpretación
	sprintf(Buffer_server, "%x", valor);//Formateamos el valor a hexadecimal

	send(storage_socketID[x-1], Buffer_server, strlen(Buffer_server),0);
	
	var = storage_socketID[x-1];
	}
		pthread_mutex_unlock(&socketMutex);

	}
}

int main(int argc, char *argv[])
{	 

	int dir;
	wiringPiSetup();
	dir = wiringPiI2CSetup(0x64);
	
	config();
	
    int32_t server_fd; 
    struct sockaddr_in address;
    int32_t opt = 1;
    int32_t addrlen = sizeof(address);
	int32_t iPthRc, newScoketConnectionFD;
	char hello[1] = "1";
	
	pthread_t tid[1];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        return 1;
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        return -1;
    }
	
	iPthRc = pthread_create(&tid[0],&attr, SendMessages, argv[1]);
    if (iPthRc < 0)
      {
        printf("There was an error trying to create the pthread, iPthRc:%d\n", iPthRc);
        exit(1);
      }
	while(1){  
	
	  newScoketConnectionFD = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen);
					   
			if (newScoketConnectionFD < 0)
		{
			printf("There was an error traying to accept in the socket, errno:%d\n", errno);
			continue;
		}	

        pthread_mutex_lock(&socketMutex);

		storage_socketID[x] = newScoketConnectionFD;

		send(storage_socketID[x], hello, strlen(hello), 0);

		x++;

		pthread_mutex_unlock(&socketMutex);

	}
}	
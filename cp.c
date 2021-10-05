#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define long 100

int main(int argc, char *argv[]){

  char buffer[long];
  char nuevo[long];
  char co[]="_copy.c";
  char original[20];
  sprintf(original,"%s", argv[1]);//Enviar cadena de argv[1] a "original"
 
  FILE *fc = fopen(original, "rb");//lectura de bit
	if(!fc){ printf("\nError\n");
        }//comprobar se haya abierto el archivo

    fread(&buffer, sizeof(buffer), 1, fc);//Leer lo que hay en el archivo por bits

   for(int i=0; i < sizeof(original); i++){//ciclo para copiar el nombre del archivo
	if(original[i]== '.'){
           break;
         }        

         nuevo[i] =  original[i];//variable "nuevo" para guardar el nombre del archivo

}
      strcat(nuevo, co);//unir "nuevo" con "co(_copy.c)"

  FILE  *fp = fopen(nuevo, "w");//Escritura
 
      fwrite(&buffer, strlen(buffer), 1, fp);//Escritura del archivo nuevo, usamos strlen para ver el tamaño del archivo y evitar escribir basura  
      fclose(fp);
      fclose(fc);

  return 1;
}

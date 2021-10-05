#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define long 100

int main(int argc, char *argv[]){

  char* buffer;
  char nuevo[long];
  char co[]="_copy.c";
  char original[20];
  int  size;
  sprintf(original,"%s", argv[1]);//Enviar cadena de argv[1] a "original"
 
  FILE *fc = fopen(original, "rb");//lectura de bit
	if(!fc){ printf("\nError\n");
        }//comprobar se haya abierto el archivo

		fseek(fc, 0L, SEEK_END);
		size=ftell(fc);//obtnemos el tamaño en caracteres del archivo y guardamos en variable size
		fseek(fc, 0, SEEK_SET);
                buffer = (char*)malloc(size*sizeof(char)+1);//tamaño de memoria dinamica

    fread(buffer, size, 1, fc);//Leer lo que hay en el archivo por bits

   for(int i=0; i < sizeof(original); i++){//ciclo para copiar el nombre del archivo
	if(original[i]== '.'){
           break;
         }

         nuevo[i] =  original[i];//variable "nuevo" para guardar el nombre del archivo

}
      strcat(nuevo, co);//unir "nuevo" con "co(_copy.c)"

  FILE  *fp = fopen(nuevo, "w");//Escritura
 
      fwrite(buffer, size, 1, fp);//Escritura del archivo nuevo 
      fclose(fp);
      fclose(fc);

  return 1;
}

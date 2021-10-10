#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cadena 100
#define co  "_copy.c"

int main(int argc, char *argv[]){

  char* buffer;
  char* nuevo;//[100];
  char* original;//[20];
  int  size = 0, i = 0;
  original = (char*)malloc(sizeof(char)+1);
  sprintf(original,"%s", argv[1]);//Pasar el valor recibido en argv[1] como una cadena en  variable original

  FILE *fc = fopen(original, "rb");
	if(fc == NULL){ printf("\nError\n"); exit(0); }else{}//comprobar se haya abierto el archivo

		fseek(fc, 0L, SEEK_END);
		size=ftell(fc);//obtnemos el tamaño en caracteres del archivo y guardamos en variable size
		fseek(fc, 0, SEEK_SET);
                buffer = (char*)malloc(size*sizeof(char)+1);//tamaño de memoria dinamica

    fread(buffer, size, 1, fc);//Leer lo que hay en el archivo por bits
	if(fc == NULL){ printf("\nError\n"); exit(0); }else{}
	nuevo = (char*)malloc(sizeof(char)+1);
     while(original[i] != '.'){

	nuevo[i] = original[i];
	i++;
}

      strcat(nuevo, co);//unir "nuevo" con "co(_copy.c)"

  FILE  *fp = fopen(nuevo, "w");//Escritura
 	if(fp == NULL){ printf("\nError\n");}else{}
      fwrite(buffer, size, 1, fp);//Escritura del archivo nuevo, usamos strlen para ver el tamaño del archivo y evitar escribir basura  
      fclose(fp);
      fclose(fc);

  return 1;
}

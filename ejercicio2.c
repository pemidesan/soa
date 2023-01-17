#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

	char command[100];
	char ruta[100];
	int valor1, valor2;

	printf("\t######## Ejercicio 2 de C ########");
	printf("\n\nIntroduzca en la ruta donde desea buscar los ficheros: ");
	scanf("%s", &ruta);
	printf("\nIntroduzca el tamanio minimo en kilobytes de los ficheros a buscar: ");
	scanf("%d", &valor1);
	printf("\nIntroduzca el tamanio maximo en kilobytes de los ficheros a buscar: ");
	scanf("%d", &valor2);
	
	printf("\nLos archivos comprendidos entre %d y %d son: \n\n", valor1, valor2);
	sprintf(command,"find %s -size +%dk -and -size -%dk",ruta, valor1, valor2);
	system(command);
	
	return 0;
}

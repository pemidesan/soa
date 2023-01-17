#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main () {
char command[100];
char ruta[50];
int user=0;

system("clear");
printf("Ejercicio 3 de C\n");
printf("¿En qué directorio quieres hacer la búsqueda?: ");
scanf("%s",ruta);
printf("¿Cuál es el UID de usuario: ");
scanf("%d", &user);

sprintf(command,"find %s -uid %d",ruta,user);
system(command);

return 0;
}
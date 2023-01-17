/*Escribe un programa en C bajo Linux que busque dentro de un directorio 
cuya ruta es proporcionada en la línea de comandos los ficheros que sean 
propiedad de un usuario cuyo ID se pase también como un argumento del programa.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int validar_parametros(int argc, char *argv[], char *cadena, int *uid_user) {
    char error[150];
    int retorno=0;   
    sprintf(error, "Todo Ok");
    if (argc != 3) {
        sprintf(error,"Número de parámetros incorrectos. \n Uso: %s <ruta> <uid_use\n", argv[0]);        
        retorno = 1;
    } else {
        char *puntero1;
        long id_user = strtol(argv[2], &puntero1, 10);
        if (*puntero1 !='\0') {
            sprintf(error,"Formato de tamaño incorrectos. Introduzca números enteros (tamaño expresado en bytes)");
            retorno = 2;            
        } else {
            *uid_user = (int)id_user;
        }
    }
    strcpy(cadena, error);
    return retorno;
}
int main(int argc, char *argv[]) {
    int retorno = 0;
    char cadena[150];
    int uid_user;
    DIR *dirp;
    struct dirent *direntp;

    if (validar_parametros(argc, argv, cadena, &uid_user) == 0) {
        //printf("%s, %d", argv[1], uid_user);
        dirp = opendir(argv[1]);
        if (dirp == NULL) {
            printf("Error. No se pudo abrir el directorio\n");
            retorno = 1;
        } else {
            while ((direntp = readdir(dirp)) != NULL) {
                struct stat buf;
                stat(direntp->d_name, &buf);
                if(buf.st_uid == uid_user && direntp->d_type == DT_REG) {
                    printf("Fichero %s con uid propietario %d\n", direntp->d_name, buf.st_uid);
                }
            }
            close(direntp);
        }
    } else {
        printf("%s", cadena);
    }

}
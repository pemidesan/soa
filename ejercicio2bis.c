/*
    Escribe un programa en C bajo Linux que busque dentro de un directorio
    cuya ruta es proporcionada en la linea de comandos todos los ficheros
    cuyo tamaño esté comprendido entre dos valores que se pasen también como
    argumentos del programa.
*/

//0: parámetros correctos
//1: número de parámetros incorrectos
//2: formato de parámetros incorrectos

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


int validar_parametros(int argc, char *argv[], char *cadena, long *lim_inferior, long *lim_superior) {
    char error[150];
    int retorno=0;   
    sprintf(error, "Todo Ok");
    if (argc != 4) {
        sprintf(error,"Número de parámetros incorrectos. \n Uso: %s <ruta> <lim_inf> <lim_sup>\n", argv[0]);        
        retorno = 1;
    } else {
        char *puntero1, *puntero2;
        long l_inf = strtol(argv[2], &puntero1, 10);
        long l_sup = strtol(argv[3], &puntero2, 10);
        if (*puntero1 !='\0' || *puntero2 != '\0') {
            sprintf(error,"Formato de tamaño incorrectos. Introduzca números enteros (tamaño expresado en bytes)");
            retorno = 2;            
        } else if (l_inf >l_sup) {
            sprintf(error, "Límite inferior debe ser menor o igual que límite superior");
            retorno = 3;
        } else {
            *lim_inferior = l_inf;            
            *lim_superior = l_sup;
        }
    }
    strcpy(cadena, error);
    return retorno;
}

int main(int argc, char *argv[]) {
    int retorno;
    long limite_inferior=0, limite_superior=0;
    char error[150];
    DIR *dirp;
    struct dirent *direntp;

    retorno = validar_parametros(argc, argv, error, &limite_inferior, &limite_superior);
    if (retorno == 0) {
        dirp = opendir(argv[1]);
        if (dirp == NULL) {
            printf("Error. No se pudo abrir el directorio\n");
            retorno = 2;
            exit(2);
        } else {
            while ((direntp = readdir(dirp)) != NULL) {
                struct stat buf;
                stat(direntp->d_name,&buf);
                if (buf.st_size >= limite_inferior && buf.st_size <= limite_superior && direntp->d_type == DT_REG) {
                    //printf("encontrada coincidencia %s", direntp->d_name);
                    printf("Fichero encontrado --> Nombre: %s, Tamaño en bytes: %d (%d <= %d <= %d)\n", direntp->d_name, buf.st_size, limite_inferior, buf.st_size, limite_superior);
                } 
            }
        }
      close(dirp);
    } else {
        printf(error);
    }
    return retorno;
}

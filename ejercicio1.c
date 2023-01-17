/*
Programa en C bajo Linux que cree un fichero de texto plano que liste el nombre, el tamaño y la fecha
de la última modificación de todos los ficheros que haya en un directorio cuya ruta es proporcionada
en la linea de comandos. No debe entrar en los subdirectorios.
----------------------------------------------------------------------------------------------------------
El programa crea un fichero llamado listado.csv con los datos solicitados y adicionalmente indica el tipo
de fichero que es, un directorio, un fichero normal, un enlace simbólico u otros.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void tipo_fichero(unsigned char tipo, char *cadena) {
    strcpy(cadena, "OTROS");
    if (tipo == DT_REG)
    {
        strcpy(cadena, "ARCHIVO");
    }
    if (tipo == DT_DIR)
    {
        strcpy(cadena, "DIRECTORIO");
    }
    if (tipo == DT_LNK)
    {
        strcpy(cadena, "ENLACE SIMBÓLICO");
    }
}

int main(int argc, char *argv[]) {
    DIR *dirp;
    struct dirent *direntp;
    FILE *fichero;

    if (argc != 2)
    {
        // no he puesto dos argumentos.
        printf("Error. Parámetros incorrectos\n");
        printf("Uso: %s <directorio>\n", argv[0]);
        exit(1);
    }
    else
    { // dos argumentos.
        dirp = opendir(argv[1]);
        if (dirp == NULL) {
            printf("Error. No se pudo abrir el directorio\n");
            exit(2);
        }
        else {
            fichero = fopen("listado.csv", "wt");
            if (fichero != NULL) {
                fprintf(fichero, "Tipo,Nombre Fichero,Tamaño(Bytes),Última Modif.\n");
                while ((direntp = readdir(dirp)) != NULL) {
                    struct stat buf;
                    stat(direntp->d_name, &buf);
                    char cadena_tipo_fichero[20];
                    tipo_fichero(direntp->d_type, cadena_tipo_fichero);
                    fprintf(fichero, "%s,%s,%d,%s\n", cadena_tipo_fichero, direntp->d_name, buf.st_size, ctime(&buf.st_mtime));
                }
                closedir(dirp);
                close(fichero);
                exit(0);
            }
            else {
                printf("Error en la creación de fichero de salida");
            }
        }
    }
}
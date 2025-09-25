#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    int i;

    // Si no se especifican archivos, salir con código 0
    if (argc == 1) {
        return 0;
    }

    // Procesar cada archivo
    for (i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }

        // Leer e imprimir contenido línea por línea
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
            printf("%s", buffer);
        }

        fclose(fp);
    }

    return 0;
}
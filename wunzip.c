#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int count;
    int character;
    int i, j;

    // Verificar argumentos
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    // Procesar todos los archivos
    for (i = 1; i < argc; i++) {
        fp = fopen(argv[i], "rb");  // Modo binario para leer
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        // Leer pares de (entero de 4 bytes, carácter)
        while (fread(&count, sizeof(int), 1, fp) == 1) {
            character = fgetc(fp);
            if (character == EOF) {
                break;
            }

            // Imprimir el carácter 'count' veces
            for (j = 0; j < count; j++) {
                putchar(character);
            }
        }

        fclose(fp);
    }

    return 0;
}
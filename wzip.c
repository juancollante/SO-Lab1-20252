#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int current_char, prev_char = -1;
    int count = 0;
    int i;

    // Verificar argumentos
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    // Procesar todos los archivos
    for (i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        // Leer carácter por carácter
        while ((current_char = fgetc(fp)) != EOF) {
            if (current_char == prev_char) {
                // Mismo carácter, incrementar contador
                count++;
            } else {
                // Carácter diferente o primer carácter
                if (prev_char != -1) {
                    // Escribir la secuencia anterior (4 bytes entero + 1 char)
                    fwrite(&count, sizeof(int), 1, stdout);
                    fputc(prev_char, stdout);
                }
                prev_char = current_char;
                count = 1;
            }
        }

        fclose(fp);
    }

    // Escribir la última secuencia si existe
    if (prev_char != -1) {
        fwrite(&count, sizeof(int), 1, stdout);
        fputc(prev_char, stdout);
    }

    return 0;
}
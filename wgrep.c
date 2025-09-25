#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fp;
    char *searchterm;
    int i;

    // Verificar argumentos mínimos
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    searchterm = argv[1];

    // Si no hay archivos, leer desde stdin
    if (argc == 2) {
        while ((read = getline(&line, &len, stdin)) != -1) {
            if (strstr(line, searchterm) != NULL) {
                printf("%s", line);
            }
        }
    } else {
        // Procesar cada archivo
        for (i = 2; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }

            // Leer líneas del archivo
            while ((read = getline(&line, &len, fp)) != -1) {
                if (strstr(line, searchterm) != NULL) {
                    printf("%s", line);
                }
            }

            fclose(fp);
        }
    }

    // Liberar memoria
    if (line) {
        free(line);
    }

    return 0;
}
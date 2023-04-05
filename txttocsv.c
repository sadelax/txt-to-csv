#include <stdio.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 10

int main() {
    char csv_file[50] = "holaaa.csv";
    char file_name[50] = "cocteles.txt";

    char data[MAX_ROWS][100];
    char table[MAX_ROWS][MAX_COLS][100];

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo %s\n", file_name);
        return 1;
    }

    int row_count = 0;
    while (fgets(data[row_count], 100, fp) != NULL && row_count < MAX_ROWS) {
        row_count++;
    }
    fclose(fp);

    int col_count = 0;
    for (int i = 0; i < row_count; i++) {
        char *token = strtok(data[i], ",");
        int j = 0;
        while (token != NULL && j < MAX_COLS) {
            strcpy(table[i][j], token);
            token = strtok(NULL, ",");
            j++;
            if (j > col_count) {
                col_count = j;
            }
        }
    }

    fp = fopen(csv_file, "w");
    if (fp == NULL) {
        printf("No se pudo crear el archivo %s\n", csv_file);
        return 1;
    }

    // escribir encabezados de columna
    fprintf(fp, "Columna 1");
    for (int i = 2; i <= col_count; i++) {
        fprintf(fp, ", Columna %d", i);
    }
    fprintf(fp, "\n");

    // escribir datos de la tabla
    for (int i = 0; i < row_count; i++) {
        fprintf(fp, "%s", table[i][0]);
        for (int j = 1; j < col_count; j++) {
            fprintf(fp, ", %s", table[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("Archivo generado exitosamente!\n");
    return 0;
}

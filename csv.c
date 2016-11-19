#include "csv.h"

#define LINEBUF 1024

/** Creates an int matrix from the content of a CSV file
  * @fileName - the name of csv the file to be read
  * @lineNum - the number of lines in the file
  * @colNum - the number of columns in the file
  */
double ** getMatFromCsvFile(char * fileName, int lineNum, int colNum) {
    char buffer[LINEBUF];
    char * record;
    char * line;

    double ** mat = (double **) malloc(lineNum * sizeof(double*));
    int i;
    for (i = 0; i < lineNum; i++) {
        mat[i] = (double *) malloc(colNum * sizeof(double));
    }

    FILE * fstream = fopen(fileName, "r");

    if (fstream == NULL) {
        return NULL;
    }

    int lineN=0;
    while ((line = fgets(buffer, sizeof(buffer), fstream)) != NULL) {
        int col = 0;
        record = strtok(line, ",");
        while (record != NULL) {
            mat[lineN][col] = atof(record);
            col++;
            record = strtok(NULL, ",");
        }
        lineN++;
    }


    return mat;
}

/** Gets the line count from any text file
  * @fileName - name of file to be read
  */
int countLines(char * fileName) {
    char buffer[LINEBUF];
    char * line;
    FILE * fstream = fopen(fileName, "r");
    int lines = 0;

    while ((line = fgets(buffer, sizeof(buffer), fstream)) != NULL) {
        lines ++;
    }

    return lines;
}

/** Frees an in-memory matrix
  * @mat - the pointer to the matrix
  * @lineNum - number of lines in the matrix
  */
void freeMatrix(double ** mat, int lineNum) {
    int i;

    for(i = 0; i < lineNum; i++) {
        free(mat[i]);
    }

    free(mat);
}
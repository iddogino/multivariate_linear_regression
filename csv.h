#include <string.h>
#include <stdio.h>
#include <stdlib.h>

double ** getMatFromCsvFile(char * fileName, int lineNum, int colNum);
int countLines(char * fileName);
void freeMatrix(double ** mat, int lineNum);
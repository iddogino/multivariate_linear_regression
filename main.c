#include <stdio.h>
#include <math.h>
#include "csv.h"

#define REQ_ARGS 4
#define FILE_NAME_ARG 1
#define ALPHA_ARG 2
#define FEARURE_NUMBER_ARG 3
#define EPSILON 0.000000001
#define MAX_ITR 1000000

//Helper functions (implemented after main)
int closeToZero(double a, double epsilon);
double getD(int j, double ** trainingSet, int numOfFeatures, int numOfTuples, double alpha, double * theta);
double getH(double * x, double * theta, int numOfFeatures);
int closeToZeroArray(double arr[], double epsilon);

//Input - file to read, alpha (learning rate), # of features
int main(int argc, char ** argv) {

    double xxx[2] = {1.0,1.0};
    double ttt[3] = {5.0,0.5,0.5};
    printf("=> %f\n",getH(xxx, ttt, 2));
    //Input check
    if (argc < REQ_ARGS) {
        printf("At least %d are required for this program\n", REQ_ARGS);
        return -1;
    }

    //Get Input
    char * fileName = argv[FILE_NAME_ARG];
    double alpha = atof(argv[ALPHA_ARG]);
    int numOfFeatures = atoi(argv[FEARURE_NUMBER_ARG]);

    //Get file length
    int numOfTuples = countLines(fileName);
    printf("File has %d lines\n", numOfTuples);

    //Load training data from CSV file
    double ** trainingSet = getMatFromCsvFile(fileName, numOfTuples, numOfFeatures+1); //Loading n features + 1 result (x_1, x_2, ... x_n, y)

    //Initialize params
    double theta[numOfFeatures + 1];
    double delta[numOfFeatures + 1];
    int steps = 0;

    for(int i = 0; i < numOfFeatures+1; i++) {
        theta[i] = 0.0;
        delta[i] = 0.0;
    }


    //Descend...
    do {
        int j = 0;
        for (j = 0; j < numOfFeatures+1; j++) {
            delta[j] = getD(j, trainingSet, numOfFeatures, numOfTuples, alpha, theta);
        }
        for (j = 0; j < numOfFeatures+1; j++) {
            theta[j] += delta[j];
        }
        steps++;
        printf("Step = %d\n", steps);
            //Output result
        printf("y = %f", theta[0]);

        int i;
        for (i = 1; i < numOfFeatures+1; i++) {
            printf(" + %f*x%d", theta[i], i);
        }

        printf("\n");
        
    } while ((!closeToZeroArray(delta, EPSILON)) && steps < MAX_ITR);

    freeMatrix(trainingSet, numOfTuples);


    //Output result
    printf("y = %f", theta[0]);

    int i;
    for (i = 1; i < numOfFeatures+1; i++) {
        printf(" + %f*x%d", theta[i], i);
    }

    printf("\n");

    return 0;
}

double getD(int j, double ** trainingSet, int numOfFeatures, int numOfTuples, double alpha, double * theta) {
    int i = 0;
    double d = 0.0;

    for (i=0; i<numOfTuples; i++) {
        double x_i_j;

        if (j == 0)
            x_i_j = 1;
        else
            x_i_j = trainingSet[i][j-1];


        d += (getH(trainingSet[i], theta, numOfFeatures) - trainingSet[i][numOfFeatures]) * x_i_j; // (h_t(x_i) - y_i) * x_i_j
    }

    return -1 * alpha * d / numOfFeatures;
}

double getH(double * x, double * theta, int numOfFeatures) {
    double h = 0.0;
    int i;

    h += theta[0];

    for (i=1; i < numOfFeatures+1; i++) {
        h += theta[i]*x[i-1]; //Theta starts at 1 because of x_0 =1; we're also skipping last feature in x as it's the result.
    }
    return h;
}

//Return true (e.g. 1) iff every number in the array is close to 0
int closeToZeroArray(double arr[], double epsilon) {
    int r = 1;
    int i;

    for (i = 0; i < sizeof(*arr)/sizeof(double); i++) {
        if (fabs(0.0 - arr[i]) > epsilon) {
            r = 0;
        }
    }
    return r;
}

//Return true iff a is close to 0
int closeToZero(double a, double epsilon) {
    if (fabs(0.0 - a) < epsilon)
        return 1;
    return 0;
}
/**
 * MODULE: layer
 * FILE: layer.c
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 8/7/2024
 * DESCRIPTION: This module is the implementation of a layer.
 * CC: BY SA
 */

#include "layer.h"
#include <stdlib.h>
#include <math.h>

/**
 * FUNCTION: errorLayer
 * INPUT: error message
 * REQUIREMENTS: None
 * MODIFIES: Finish the program.
 */
void errorLayer(char error[]) {
    printf("\n\n\nERROR in the module layer: %s\n", error);
    while (true)
        exit(-1);
}

/**
 * FUNCTION: newLayer
 * INPUT: 
 *      The number neurons of the previous layer (n),
 *      the number neurons of this layer (m) and the activate
 *      function (relu, sigmoide, tan_h) (are constants).
 * REQUIREMENTS: 
 *      n, m <= MAX_NEURONS
 *      The activate function have to exist.
 * OUTPUT: A layer.
 */
void newLayer(Layer *l, unsigned char n, unsigned char m, unsigned char actv_func) {
    if (n > MAX_NEURONS || m > MAX_NEURONS) {
        errorLayer("The layer cannot have more neurons than allowed.");
    }
    else if (actv_func != relu && actv_func != sigmoide && actv_func != tan_h) {
        errorLayer("The activate function doesn't exist.");
    }

    l->n_neurons = m;
    l->n_neurons_previous_layer = n;
    l->actv_func = actv_func;
    newRandomNormMatrix(&(l->w), (unsigned short) (n), (unsigned short) (m));
    newRandomNormMatrix(&(l->b), 1, (unsigned short) (m));
}

float funcRelu(float x) {
    if (x <= 0) {
        return 0;
    }
    else {
        return x;
    }
}

float derivRelu(float x) {
    if (x <= 0) {
        return 0;
    }
    else {
        return 1.0;
    }
}

float funcSigmoide(float x) {
    return 1.0 / (1.0 + exp(-x));
}

float derivSigmoide(float x) {
    float aux1, aux2;
    
    aux1 = exp(-x);
    aux2 = 1.0 + aux1;
    return aux1 / (aux2*aux2);
}

float funcTanh(float x) {
    return tanh(x);
}

float derivTanh(float x) {
    float aux1, aux2, aux3;

    aux1 = exp(x);
    aux2 = exp(-x);
    aux3 = (aux1 - aux2) / (aux1 + aux2);
    return 1.0 - (aux3*aux3);
}

/**
 * FUNCTION: activateFunction
 * INPUT: A matrix (m) and a layer.
 * REQUIREMENTS: Obviously the matrix and the layer must have been created.
 * OUTPUT: If f(x) is the activate function:
 *      The matrix with others values, because now m = f(m).
 */
void activateFunction(Matrix *m, Matrix m1, Layer l) {
    newRandomMatrix(m, m1.size_row, m1.size_col);
    switch (l.actv_func) {
        case relu:
            for (int i = 0; i < numberRows(m1); i++) {
                for (int j = 0; j < numberColumns(m1); j++) {
                    FastMCMatrix(m, i, j, funcRelu(FastCCMatrix(m1, i, j)));
                }
            }
            break;
        case sigmoide:
            for (int i = 0; i < numberRows(m1); i++) {
                for (int j = 0; j < numberColumns(m1); j++) {
                    FastMCMatrix(m, i, j, funcSigmoide(FastCCMatrix(m1, i, j)));
                }
            }
            break;
        case tan_h:
            for (int i = 0; i < numberRows(m1); i++) {
                for (int j = 0; j < numberColumns(m1); j++) {
                    FastMCMatrix(m, i, j, funcTanh(FastCCMatrix(m1, i, j)));
                }
            }
            break;
        default:
            break;
    }
}

/**
 * FUNCTION: derivActivateFunction
 * INPUT: A matrix (m) and a layer.
 * REQUIREMENTS: Obviously the matrix and the layer must have been created.
 * OUTPUT: If f'(x) is the derivate of activate function:
 *      he matrix with others values, because now m = f'(m).
 */
void derivActivateFunction(Matrix *m, Matrix m1, Layer l) {
    newRandomMatrix(m, m1.size_row, m1.size_col);
    switch (l.actv_func) {
        case relu:
            for (int i = 0; i < numberRows(m1); i++) {
                for (int j = 0; j < numberColumns(m1); j++) {
                    FastMCMatrix(m, i, j, derivRelu(FastCCMatrix(m1, i, j)));
                }
            }
            break;
        case sigmoide:
            for (int i = 0; i < numberRows(m1); i++) {
                for (int j = 0; j < numberColumns(m1); j++) {
                    FastMCMatrix(m, i, j, derivSigmoide(FastCCMatrix(m1, i, j)));
                }
            }
            break;
        case tan_h:
            for (int i = 0; i < numberRows(m1); i++) {
                for (int j = 0; j < numberColumns(m1); j++) {
                    FastMCMatrix(m, i, j, derivTanh(FastCCMatrix(m1, i, j)));
                }
            }
            break;
        default:
            break;
    }
}

/**
 * FUNCTION: optimizeWeights
 * INPUT: A layer, a matrix (dC/dw, size N(neurons in this layer)xM(length data))
 *      and learning rate (float).
 * REQUIREMENTS: Obiously, all created and defined.
 * MODIFIES: The weights (w) of the layer.
 *      w = w - dC/dw * lr
 */
void optimizeWeights(Layer *l, Matrix dC_dw, float lr) {
    Matrix aux1, aux2;

    multiplyNumberAndMatrix(&aux1, dC_dw, lr);
    subtractMatrix(&aux2, l->w, aux1);
    l->w = aux2;
}

/**
 * FUNCTION: optimizeBias
 * INPUT: A layer, a matrix (dC/db, size 1xN) and 
 *      learning rate (float).
 * REQUIREMENTS: Obiously, all created and defined.
 * MODIFIES: The bias (w) of the layer.
 *      b = b - dC/db * lr
 */
void optimizeBias(Layer *l, Matrix dC_db, float lr) {
    Matrix aux1, aux2;

    meanMatrix(&aux1, dC_db);
    multiplyNumberAndMatrix(&aux2, aux1, lr);
    subtractMatrix(&aux1, l->b, aux2);
    l->b = aux1;
}

/**
 * FUNCTION: getActivateFunction
 * INPUT: A layer.
 * REQUIREMENTS: Obviously the layer must have been created.
 * OUTPUT: The activate function (unsigned char) and the name
 *      activate function (char[]).
 */
void getActivateFunction(unsigned char *func, char name_func[], Layer l) {
    *func = l.actv_func;
    switch (l.actv_func) {
        case relu:
            name_func = "relu";
            break;
        case sigmoide:
            name_func = "sigmoide";
            break;
        case tan_h:
            name_func = "tan_h";
            break;
        default:
            name_func = "undefined";
            break;
    }
}

/**
 * FUNCTION: getNumberNeurons
 * INPUT: A layer.
 * REQUIREMENTS: Obviously the layer must have been created.
 * OUTPUT: The number of neurons of the layer.
 */
unsigned char getNumberNeuronsLayer(Layer l) {
    return l.n_neurons;
}

/**
 * FUNCTION: getNumberNeuronsPreviousLayer
 * INPUT: A layer.
 * REQUIREMENTS: Obviously the layer must have been created.
 * OUTPUT: The number of neurons of the previously layer.
 */
unsigned char getNumberNeuronsPreviousLayer(Layer l) {
    return l.n_neurons_previous_layer;
}

/**
 * FUNCTION: getWeights
 * INPUT: A layer.
 * REQUIREMENTS: Obviously the layer must have been created.
 * OUTPUT: The weight matrix of the layer.
 */
void getWeights(Matrix *w, Layer l) {
    *w = l.w;
}

/**
 * FUNCTION: getBias
 * INPUT: A layer.
 * REQUIREMENTS: Obviously the layer must have been created.
 * OUTPUT: The bias matrix of the layer.
 */
void getBias(Matrix *b, Layer l) {
    *b = l.b;
}

/**
 * FUNCTION: writeLayer
 * INPUT: The pointer to file (binary of floats) and a layer.
 * REQUIREMENTS: Obviously the layer must have been created and
 *      the file has to be open.
 * MODIFIES: Write the layer in the file.
 *      And the boolean, error.
 */
void writeLayer(FILE *f, bool *error, Layer l) {
    float a, b, c;

    a = (float) (l.n_neurons);
    b = (float) (l.n_neurons_previous_layer);
    c = (float) (l.actv_func);

    if (fwrite(&a, sizeof(float), 1, f) != 1 || fwrite(&b, sizeof(float), 1, f) != 1 || fwrite(&c, sizeof(float), 1, f) != 1) {
        *error = true;
    }
    else {
        writeMatrix(f, error, l.w);
        if (*error == false) {
            writeMatrix(f, error, l.b);
        }
    }
}

/**
 * FUNCTION: readLayer
 * INPUT: The pointer to file (binary of floats) and a layer.
 * REQUIREMENTS: Obviously the layer must have been created and
 *      the file has to be open.
 * MODIFIES: Read the layer of the file.
 *      And the boolean is the error.
 */
void readLayer(FILE *f, Layer *l, bool *error) {
    float a, b, c;

    if (fread(&a, sizeof(float), 1, f) != 1 || fread(&b, sizeof(float), 1, f) != 1 || fread(&c, sizeof(float), 1, f) != 1) {
        *error = true;
    }
    else {
        l->n_neurons = (unsigned char) (a);
        l->n_neurons_previous_layer = (unsigned char) (b);
        l->actv_func = (unsigned char) (c);

        readMatrix(&l->w, f, error);
        if (!*error) {
            readMatrix(&l->b, f, error);
        }
    }
}
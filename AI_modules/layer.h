#ifndef _LAYER_H
#define _LAYER_H

/**
 * MODULE: layer
 * FILE: layer.h
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 8/7/2024
 * DESCRIPTION: This module is the implementation of a layer.
 * CC: BY SA
 */

#include "matrix.h"

#define relu 1
#define sigmoide 2
#define tan_h 3
#define MAX_NEURONS MAX_COLUMNS

typedef struct {
    Matrix w;
    Matrix b;
    unsigned char actv_func;
    unsigned char n_neurons_previous_layer;
    unsigned char n_neurons;
} Layer;

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
void newLayer(Layer *, unsigned char, unsigned char, unsigned char);

/**
 * FUNCTION: activateFunction
 * INPUT: A matrix (m) and a layer.
 * REQUIREMENTS: Obviously the matrix and the layer must have been created.
 * OUTPUT: If f(x) is the activate function:
 *      The matrix with others values, because now m = f(m).
 */
void activateFunction(Matrix *, Matrix, Layer);

/**
 * FUNCTION: derivActivateFunction
 * INPUT: A matrix (m) and a layer.
 * REQUIREMENTS: Obviously the matrix and the layer must have been created.
 * OUTPUT: If f'(x) is the derivate of activate function:
 *      he matrix with others values, because now m = f'(m).
 */
void derivActivateFunction(Matrix *, Matrix, Layer);

/**
 * FUNCTION: optimizeWeights
 * INPUT: A layer, a matrix (dC/dw, size N(neurons in this layer)xM(length data))
 *      and learning rate (float).
 * REQUIREMENTS: Obiously, all created and defined.
 * MODIFIES: The weights (w) of the layer.
 *      w = w - dC/dw * lr
 */
void optimizeWeights(Layer *, Matrix, float);

/**
 * FUNCTION: optimizeBias
 * INPUT: A layer, a matrix (dC/db, size 1xN) and 
 *      learning rate (float).
 * REQUIREMENTS: Obiously, all created and defined.
 * MODIFIES: The bias (w) of the layer.
 *      b = b - dC/db * lr
 */
void optimizeBias(Layer *, Matrix, float);

/**
 * FUNCTION: getActivateFunction
 * INPUT: A layer.
 * REQUIREMENTS: Obviously the layer must have been created.
 * OUTPUT: The activate function (unsigned char) and the name
 *      activate function (char[]).
 */
void getActivateFunction(unsigned char *, char[], Layer);

/**
 * FUNCTION: getNumberNeurons
 * INPUT: A layer.
 * REQUIREMENTS: Obviously the layer must have been created.
 * OUTPUT: The number of neurons of the layer.
 */
unsigned char getNumberNeuronsLayer(Layer);

/**
 * FUNCTION: getNumberNeuronsPreviousLayer
 * INPUT: A layer.
 * REQUIREMENTS: Obviously the layer must have been created.
 * OUTPUT: The number of neurons of the previously layer.
 */
unsigned char getNumberNeuronsPreviousLayer(Layer);

/**
 * FUNCTION: getWeights
 * INPUT: A layer.
 * REQUIREMENTS: Obviously the layer must have been created.
 * OUTPUT: The weight matrix of the layer.
 */
void getWeights(Matrix *, Layer);

/**
 * FUNCTION: getBias
 * INPUT: A layer.
 * REQUIREMENTS: Obviously the layer must have been created.
 * OUTPUT: The bias matrix of the layer.
 */
void getBias(Matrix *, Layer);

/**
 * FUNCTION: writeLayer
 * INPUT: The pointer to file (binary of floats) and a layer.
 * REQUIREMENTS: Obviously the layer must have been created and
 *      the file has to be open.
 * MODIFIES: Write the layer in the file.
 *      And the boolean, error.
 */
void writeLayer(FILE *, bool *, Layer);

/**
 * FUNCTION: readLayer
 * INPUT: The pointer to file (binary of floats) and a layer.
 * REQUIREMENTS: Obviously the layer must have been created and
 *      the file has to be open.
 * MODIFIES: Read the layer of the file.
 *      And the boolean is the error.
 */
void readLayer(FILE *, Layer *, bool *);

#endif
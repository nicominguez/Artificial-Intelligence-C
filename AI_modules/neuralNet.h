#ifndef _NEURAL_NET_H
#define _NEURAL_NET_H

/**
 * MODULE: neuralNet
 * FILE: neuralNet.c
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens on 30/7/2024
 * DESCRIPTION: This module can build a neural network.
 * CC: BY SA
 */

#include "dynamicListLayer.h"

#define MAX_DESCRIPTION 8000
#define OVERFITTING 0.8 // (0, 1) 80% of the data is used for training.

typedef struct {
    dynamicListLayer layers;
    unsigned char n_layers;
    unsigned char n_inputs, n_outputs;
    char description[MAX_DESCRIPTION];
} NeuralNet;

/**
 * FUNCTION: newNeuralNet
 * INPUT: 
 *      The array of the number of neurons per layer. It's length is the
 *      number of the layers. Example:
 *          If there are 3 layers and the first has 5 neurons, the second
 *          layer has 2 neurons and the last layer has 1 neuron, this array
 *          is: {5, 2, 1}. {input layer, hidden layer, output layer}.
 *      The array of the activate function per layer. It's length is the
 *      number of the layers - 1, because the input layer hasn't activate
 *      function. Example:
 *          If there are 3 layers and the first don't use activate function, the 
 *          second use the sigmoide and the last use the relu, this array
 *          is: {sigmoide, relu}
 *          First layer -> None
 *          Second layer -> Sigmoide
 *          Third layer -> Relu
 *          relu, sigmoide and tanh are constants.
 *      The array of characters, which is the description.
 * REQUIREMENTS: 
 *      The length the last array <= MAX_DESCRIPTION
 *      The number of neurons per layer <= MAX_NEURONS
 *      The description must have '\0'.
 * OUTPUT:
 *      A neural network (NeuralNet).
 */
void newNeuralNet(NeuralNet *, unsigned char[], unsigned char[],
                char[MAX_DESCRIPTION], unsigned char);

/**
 * FUNCTION: trainNeuralNet
 * INPUT:
 *      A NeuralNet, which obiously has had to be created.
 *      The first matrix is the input matrix.
 *      The second matrix is the output matrix.
 *      Clarification:
 *          The input matrix whose dimensions are (MxN),
 *          M, rows, is the number of data tuples and
 *          N, columns, is the number of values (floats) in a tuple so
 *          if there are 3 neurons in input layer, N = 3.
 *          Example: There are 2 neurons in the input layer and
 *          there are 5 data tuples, so the input matrix is:
 *              2.453 1.784 (Fist tuple)
 *              -4.12 6.438 (Second tuple)
 *              1.546 -3.65 (...)
 *              0.236 -0.836 (...)
 *              1.345 6.367 (M tuple)
 *              
 *              M = 5 and N = 2
 * 
 *          The output matrix whose dimensions are (MxH),
 *          M, rows, is the number of data tuples and
 *          H, columns, is the number of values (floats) in a
 *          tuple so if there 3 neurons in output layer, N = 3.
 *          Example: There are 1 neuron in the output layer and there are
 *          3 data tuples, so the output matrix is:
 *              -1.456
 *              0.657
 *              2.125
 *              
 *              M = 3 and H = 1
 *      
 *      The number of epochs (unsigned int)
 *      The learning rate (float) (Recommended: [0.5, 0.0001]. For example: 0.0025))
 *      The stop overfitting (bool).
 * REQUIREMENTS: 
 *      0 < learning rate <= 1
 *      number of rows (input) > 10
 *      number of rows (input) = number of rows (output)
 * OUTPUT:
 *      initMSE (float).
 *      endMSE (float).
 *      minMSE (float).
 *      number of epochs completed (unsigned int).
 * MODIFIES: The neural network.
 */
void trainNeuralNet(NeuralNet *, float *init_MSE, float *end_MSE, float *min_MSE,
                    unsigned int *n_epoch_completed, Matrix, Matrix, unsigned int,
                    float, bool);

/**
 * FUNCTION: predict
 * INPUT: A input matrix and a neural network.
 * REQUIREMENTS: Obiously the input matrix and the neural
 *      network have had to be created. And the number of
 *      columns of the input matrix must be equal to the number of 
 *      neurons in the input layer.
 * OUTPUT: The output matrix.
 */
void predict(Matrix *, Matrix, NeuralNet);

/**
 * FUNCTION: getLayers
 * INPUT: A neural network.
 * REQUIREMENTS: Obviously the neural network has to exist.
 * OUTPUT: The array of the numbers of neurons per layer.
 */
void getLayers(unsigned char[], NeuralNet);

/**
 * FUNCTION: getNumberLayers
 * INPUT: A neural network.
 * REQUIREMENTS: Obviously the neural network has to exist.
 * OUTPUT: The number of layers in the neural network.
 */
unsigned char getNumberLayers(NeuralNet);

/**
 * FUNCTION: getNumberInputNeurons
 * INPUT: A neural network.
 * REQUIREMENTS: Obviously the neural network has to exist.
 * OUTPUT: The number of inputs neurons in the neural network.
 */
unsigned char getNumberInputNeurons(NeuralNet);

/**
 * FUNCTION: getNumberOutputNeurons
 * INPUT: A neural network.
 * REQUIREMENTS: Obviously the neural network has to exist.
 * OUTPUT: The number of output neurons in the neural network.
 */
unsigned char getNumberOutputNeurons(NeuralNet);

/**
 * FUNCTION: getDescriptionNeuralNet
 * INPUT: A neural network.
 * REQUIREMENTS: Obviously the neural network has to exist.
 * OUTPUT: The description of the neural network.
 */
void getDescriptionNeuralNet(char[MAX_DESCRIPTION], NeuralNet);

/**
 * FUNCTION: freeNeuralNetwork
 * INPUT: net (NeuralNet)
 * REQUIREMENTS: None.
 * MODIFIES: The memory of the neural network is released.
 */
void freeNeuralNetwork(NeuralNet);

/**
 * FUNCTION: saveNeuralNet
 * INPUT: A neural network and a path.
 *      Example of path:
 *          C:\Users\User\Desktop\net1.aic
 * REQUIREMENTS: Obiously a neural network and a path created.
 * OUTPUT: Save the neural network in the path and the boolean is
 *      the error. Error <=> true
 */
bool saveNeuralNet(NeuralNet, char path[]);

/**
 * FUNCTION: openNeuralNet
 * INPUT: A path of a previosly saved neural network.
 *      Example of path:
 *          C:\Users\User\Desktop\net1.aic
 * REQUIREMENTS: Obiously the file has to exits.
 * OUTPUT: Open the neural network in NeuralNetwork and
 *      the boolean is the error. Error <=> True.
 */
bool openNeuralNet(NeuralNet *, char path[]);

#endif
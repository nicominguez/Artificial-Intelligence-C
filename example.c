#include "AI_modules/ai.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// We are going to work within this region, which is a square.
#define SIDE 5
#define LIM_X SIDE
#define LIM_Y SIDE

// In the region, there is a function
float fxy(float x, float y) {
    return 2*x+y;
}

int main() {
    // Firstly, the AI is initialized
    initAI();
    
    // Secondly, the data are prepared.
    unsigned short n_data;
    Matrix input, output;

    n_data = 50;
    newRandomMatrix(&input, n_data, 2); // input (n_data X 2)
    newRandomMatrix(&output, n_data, 1); // output (n_data X 1)
    
    float x, y, z;
    srand(time(NULL));
    for (int i = 0; i < n_data; i++) {
        // Random point in the region (square)
        x = ((float) (rand()) / (float) (RAND_MAX)) * LIM_X;
        y = ((float) (rand()) / (float) (RAND_MAX)) * LIM_Y;


        MCMatrix(&input, i, 0, x);
        MCMatrix(&input, i, 1, y);

        z = fxy(x, y);
        MCMatrix(&output, i, 0, z);
    }

    normalizationMatrix(&input, 0, SIDE); // The input matrix has be normalized in range [0, 1]
    normalizationMatrix(&output, 0, fxy(LIM_X, LIM_Y)); // The output matrix has be normalized in range [0, 1]

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Then, the neural network is created
    NeuralNet net;
    unsigned char n_layers = 5;
    unsigned char neurons_per_layer[5] = {2, 4, 4, 4, 1};
    unsigned char actv_functions[4] = {tan_h, tan_h, tan_h, tan_h};
    char desc[MAX_DESCRIPTION];

    strcat(desc, "NEURAL NETWORK\n\n");
    strcat(desc, "\tIndex:\n");
    strcat(desc, "\t\t1. Structure.\n");
    strcat(desc, "\t\t2. Description.\n");
    strcat(desc, "\t\t3. Training information.\n\n");

    strcat(desc, "1. Structure.\n");
    strcat(desc, "\tThe neural network has 5 layers.\n");
    strcat(desc, "\tThe input layer has 2 neurons, the second, the third layer and the quarter have 4 neurons, and the output layer has 1 neuron.\n");
    strcat(desc, "\nThe activate function used in all layers, except the input layer, is tanh.\n\n");
    
    strcat(desc, "2. Description.\n");
    strcat(desc, "\tThis neural network will the function f(x, y) = 2x + y.\n");
    strcat(desc, "\tNote: The space is a region 5x5 (square). Therefore is a bounded region.\n\n");

    strcat(desc, "3. Training information.\n");
    strcat(desc, "\tThe neural network has been trained with 1000 epochs, a 0.005 learning rate, and without stop_overffiting. \n");

    newNeuralNet(&net, neurons_per_layer, actv_functions, desc, n_layers); // It is created
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Finaly, the neural network is trained
    float init_mse, end_mse, min_mse;
    unsigned int n_epoch_completd;

    trainNeuralNet(&net, &init_mse, &end_mse, &min_mse, &n_epoch_completd, input, output, 1000, 0.005, false);

    printf("Init MSE: %f; End MSE: %f; Min MSE: %f; Number of the epoch completed: %d\n", init_mse, end_mse, min_mse, n_epoch_completd);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Now we predict f(x, y) with x and y random.
    Matrix input_2, prediction;

    newRandomMatrix(&input_2, 1, 2);

    x = 4.251;
    y = 1.9;
    MCMatrix(&input_2, 0, 0, x);
    MCMatrix(&input_2, 0, 1, y);
    
    normalizationMatrix(&input_2, 0, SIDE);
    predict(&prediction, input_2, net);
    denormalizeMatrix(&prediction, 0, fxy(LIM_X, LIM_Y));

    printf("Prediction:");
    showMatrix(prediction);
    printf("Real: %f\n", fxy(x, y));
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Moreover, the neural network can be saved and opened
    saveNeuralNet(net, "net.aic");

    NeuralNet net_2;
    openNeuralNet(&net_2, "net.aic");

    // net and net_2 are the same neural network. For exmple, if we calculate before prediction, this will the same.
    predict(&prediction, input_2, net_2);
    denormalizeMatrix(&prediction, 0, fxy(LIM_X, LIM_Y));

    printf("Prediction:");
    showMatrix(prediction);
    printf("Real: %f\n", fxy(x, y));
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Moreover, if the program continue and the neural network won't use more => free memory
    freeNeuralNetwork(net);
    freeNeuralNetwork(net_2);

    // ...
    
    return 0;
}
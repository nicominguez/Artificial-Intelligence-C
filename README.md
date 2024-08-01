# Artificial-Intelligence-C
This repository alllow the creation of small neural networks in C.

## Table of Contents
1. [General info](#general-info)
2. [Installation](#installation)
3. [Example](#example)

### General info
The "AI_modules", has been created for build small neural networks in C and to understand how a neural network works.
Therefore, the program for creating neural networks is "AI_modules", "ai".
The "example.c" is an example of how to use "AI_modules", "ai". To compile this example, we have "makefile". Moreover, "net.aic"
is the neural network built by "example.c".

### Installation
First, the repository is installed.
```
git clone https://github.com/eloyUA/Artificial-Intelligence-C
```

Then, the example and "AI_modules" are compiled with a makefile, so make need to be installed.
```
cd Artificial-Intelligence-C
mkdir /AI_modules/compilations
make compile
```

Finaly, the executable, "example", has been created.

### Example
Now, a neural network will be build to predict the output of f(x, y) = sin(x) - y. This function is:
![Function](/screenshots/function.png)

First, the AI is inicialized and the data are prepared. If data (input, output) isn't in [0, 1] need be normalized.
![Data](/screenshots/prepare_data.png)

Second, the neural network is built with the number of the layers, number of neurons per layer, activation functions and description.
![Build net](/screenshots/build_net.png)

Then, the neural network is trained with the data.
![Train net](/screenshots/train_net.png)

Finaly, the neural network predict a f(x, y) with random x, y values and the net is saved. To open the network file, "net.aic",
the function "openNeuralNet" must be used.
![Predict function](/screenshots/prediction_net.png)

The output by display.
![Output by display](/screenshots/output_display.png)

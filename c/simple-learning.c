#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUTS 2          // Number of input neurons
#define HIDDEN_NODES 2    // Number of neurons in the hidden layer
#define SAMPLES 4         // Number of training samples

// Structure to represent the neural network
typedef struct {
    double weights1[INPUTS][HIDDEN_NODES]; // Weights between input layer and hidden layer
    double bias1[HIDDEN_NODES];            // Biases for the hidden layer
    double weights2[HIDDEN_NODES];         // Weights between hidden layer and output layer
    double bias2;                          // Bias for the output layer
    double learning_rate;                  // Learning rate for training
} NeuralNetwork;

// Sigmoid activation function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Derivative of the sigmoid function
double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

// Function to initialize the neural network with random weights and biases
void initialize_network(NeuralNetwork *nn) {
    for (int i = 0; i < INPUTS; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) {
            nn->weights1[i][j] = (double)rand() / RAND_MAX * 2.0 - 1.0; // Random between -1 and 1
        }
    }
    for (int j = 0; j < HIDDEN_NODES; j++) {
        nn->bias1[j] = (double)rand() / RAND_MAX * 2.0 - 1.0; // Random between -1 and 1
        nn->weights2[j] = (double)rand() / RAND_MAX * 2.0 - 1.0; // Random between -1 and 1
    }
    nn->bias2 = (double)rand() / RAND_MAX * 2.0 - 1.0; // Random between -1 and 1
    nn->learning_rate = 0.1; // Set learning rate
}

// Function to perform a forward pass through the network
void forward_pass(NeuralNetwork *nn, double inputs[], double hidden[], double *output) {
    // Calculate activations for hidden layer
    for (int j = 0; j < HIDDEN_NODES; j++) {
        hidden[j] = nn->bias1[j];
        for (int i = 0; i < INPUTS; i++) {
            hidden[j] += nn->weights1[i][j] * inputs[i];
        }
        hidden[j] = sigmoid(hidden[j]);
    }

    // Calculate the output of the network
    *output = nn->bias2;
    for (int j = 0; j < HIDDEN_NODES; j++) {
        *output += nn->weights2[j] * hidden[j];
    }
    *output = sigmoid(*output);
}

// Function to perform a backward pass and update the weights and biases
void backward_pass(NeuralNetwork *nn, double inputs[], double hidden[], double output, double expected) {
    // Calculate output layer error and delta
    double output_error = expected - output;
    double output_delta = output_error * sigmoid_derivative(output);

    // Calculate hidden layer errors and deltas
    double hidden_errors[HIDDEN_NODES];
    double hidden_deltas[HIDDEN_NODES];
    for (int j = 0; j < HIDDEN_NODES; j++) {
        hidden_errors[j] = output_delta * nn->weights2[j];
        hidden_deltas[j] = hidden_errors[j] * sigmoid_derivative(hidden[j]);
    }

    // Update weights and bias for the output layer
    for (int j = 0; j < HIDDEN_NODES; j++) {
        nn->weights2[j] += nn->learning_rate * output_delta * hidden[j];
    }
    nn->bias2 += nn->learning_rate * output_delta;

    // Update weights and biases for the hidden layer
    for (int i = 0; i < INPUTS; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) {
            nn->weights1[i][j] += nn->learning_rate * hidden_deltas[j] * inputs[i];
        }
    }
    for (int j = 0; j < HIDDEN_NODES; j++) {
        nn->bias1[j] += nn->learning_rate * hidden_deltas[j];
    }
}

// Function to train the neural network
void train(NeuralNetwork *nn, double inputs[SAMPLES][INPUTS], double outputs[SAMPLES], int epochs) {
    double hidden[HIDDEN_NODES];
    double output;
    for (int epoch = 0; epoch < epochs; epoch++) {
        for (int i = 0; i < SAMPLES; i++) {
            forward_pass(nn, inputs[i], hidden, &output);
            backward_pass(nn, inputs[i], hidden, output, outputs[i]);
        }
    }
}

int main() {
    NeuralNetwork nn;
    initialize_network(&nn);

    // Training data for the XOR problem
    double inputs[SAMPLES][INPUTS] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };

    double xor_outputs[SAMPLES] = {0, 1, 1, 0}; // Expected outputs for XOR

    // Train the network for XOR
    printf("Training for XOR problem:\n");
    train(&nn, inputs, xor_outputs, 10000);

    double hidden[HIDDEN_NODES];
    double output;

    // Test the network with the XOR training data
    for (int i = 0; i < SAMPLES; i++) {
        forward_pass(&nn, inputs[i], hidden, &output);
        printf("Input: (%.0f, %.0f), Predicted Output: %.2f\n", inputs[i][0], inputs[i][1], output);
    }

    // Training data for the XNOR problem
    double xnor_outputs[SAMPLES] = {1, 0, 0, 1}; // Expected outputs for XNOR

    // Train the network for XNOR
    printf("\nTraining for XNOR problem:\n");
    train(&nn, inputs, xnor_outputs, 10000);

    // Test the network with the XNOR training data
    for (int i = 0; i < SAMPLES; i++) {
        forward_pass(&nn, inputs[i], hidden, &output);
        printf("Input: (%.0f, %.0f), Predicted Output: %.2f\n", inputs[i][0], inputs[i][1], output);
    }

    return 0;
}

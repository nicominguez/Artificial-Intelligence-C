/**
 * MODULE: random
 * FILE: random.c
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 7/7/2024
 * DESCRIPTION: This module can generate random numbers
 *      from a normal distribution, an exponential distribution
 *      and an uniform distribution.
 * CC: BY SA
 */

#include "random.h"
#include "dynamicListInt.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846

/**
 * FUNCTION: initRandom
 * INPUT: None
 * REQUIREMENTS: None
 * MODIFIES: The seed.
 */
void initRandom() {
    srand(time(NULL));
}

/**
 * FUNCTION: errorRandom
 * INPUT: error message
 * REQUIREMENTS: None
 * MODIFIES: Finish the program.
 */
void errorRandom(char error[]) {
    printf("\n\n\nERROR in the module random: %s\n", error);
    while (true)
        exit(-1);
}

/**
 * FUNCTION: uniformDistribution
 * INPUT: Two numbers, n (float) and m (float).
 * REQUIREMENTS: n < m
 * OUTPUT: A number of a uniform distribution in the
 *      interval: [n, m]
 */
float uniformDistribution(float n, float m) {
    if (n >= m) {
        errorRandom("n must be less than m");
    }

    return ((float) (rand()) / (float) (RAND_MAX)) * (m - n) + n;
}

/**
 * FUNCTION: uniformDistributionWithException
 * INPUT: m (int), n (int), l (int array), long_l (int).
 * REQUIREMENTS: 
 *      m < n
 *      l don't empty
 *      All number in l must be in [m, n].
 *      l musn't have repeted elements.
 *      Prohibited l = [m, ..., n].
 *          Example:
 *              [1, 5], m=1, n=5
 *              l = {3, 1, 5, 2, 4}
 *              Prohibited.
 * OUTPUT: A number, r, in [m, n] and not in l.
 */
int uniformDistributionWithException(int m, int n, int l[], int long_l) {
    if (m >= n) {
        errorRandom("m >= n");
    }
    else if (long_l <= 0) {
        errorRandom("Long of l is less than 0");
    }
    else {
        // Repeted elements in l
        if (long_l > 1) {
            int i, j;
            bool found;

            i = 0;
            while (i < long_l - 1 && !found) {
                j = i + 1;
                while (j < long_l - 1 && l[j] != l[i]) {
                    j++;
                }
                found = l[j] == l[i];
                i++;
            }

            if (found) {
                errorRandom("l has repets elements.");
            }
        }

        // All elements in l are in [m, n]?
        int i;

        i = 0;
        while (i < long_l - 1 && (l[i] >= m && l[i] <= n)) {
            i++;
        }

        if (l[i] < m || l[i] > n) {
            errorRandom("There is a number in l that isn't in [m, n].");
        }
        else if (long_l == m - n + 1) {
            errorRandom("l is all the interval.");
        }
    }

    int j;
    dynamicListInt dl;

    newDynamicListInt(&dl);
    for (int i = m; i <= n; i++) {
        j = 0;
        while (j < long_l - 1 && i != l[j]) {
            j++;
        }

        if (i != l[j]) {
            appendDynamicListInt(&dl, i);
        }
    }

    int r, aux;
    aux = (int) ((float) (lengthDynamicListInt(dl)) * uniformDistribution(0, 1));
    if (aux == lengthDynamicListInt(dl)) {
        aux--;
    }

    r = consultElemDynamicListInt(dl, aux);
    freeDynamicListInt(&dl);

    return r;
}

/**
 * FUNCTION: normalDistribution
 * INPUT: None
 * REQUIREMENTS: None
 * OUTPUT: A number of a normal distribution.
 * INFORMATION:
 *      http://nuclear.fis.ucm.es/nuevaweb/html/docencia/mas_montecarlol.htm
 */
float normalDistribution() {
    float n1 = uniformDistribution(0, 1);
    float n2 = uniformDistribution(0, 1);
    return sqrt(-2.0*log((double) n1)) * cos(2.0*PI*n2);
}

/**
 * FUNCTION: exponentialDistribution
 * INPUT: lambda
 * REQUIREMENTS: lambda > 0
 * OUTPUT: A number of a exponential distribution.
 * INFORMATION:
 *      http://nuclear.fis.ucm.es/nuevaweb/html/docencia/mas_montecarlol.htm
 */
float exponentialDistribution(float lambda) {
    if (lambda <= 0) {
        errorRandom("lamdba must be greather than 0");
    }
    
    return (-1.0/lambda) * log((double) (1.0 - uniformDistribution(0, 1)));
}
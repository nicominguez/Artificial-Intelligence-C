#ifndef _RANDOM_H
#define _RANDOM_H

/**
 * MODULE: random
 * FILE: random.h
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 7/7/2024
 * DESCRIPTION: This module can generate random numbers
 *      from a normal distribution, an exponential distribution
 *      and an uniform distribution.
 * CC: BY SA
 */

/**
 * FUNCTION: initRandom
 * INPUT: None
 * REQUIREMENTS: None
 * MODIFIES: The seed.
 */
void initRandom();

/**
 * FUNCTION: uniformDistribution
 * INPUT: Two numbers, n (float) and m (float).
 * REQUIREMENTS: n < m
 * OUTPUT: A number of a uniform distribution in the
 *      interval: [n, m]
 */
float uniformDistribution(float, float);

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
int uniformDistributionWithException(int, int, int[], int);

/**
 * FUNCTION: normalDistribution
 * INPUT: None
 * REQUIREMENTS: None
 * OUTPUT: A number of a normal distribution.
 */
float normalDistribution();

/**
 * FUNCTION: exponentialDistribution
 * INPUT: lambda
 * REQUIREMENTS: lambda > 0
 * OUTPUT: A number of a exponential distribution.
 */
float exponentialDistribution(float);

#endif
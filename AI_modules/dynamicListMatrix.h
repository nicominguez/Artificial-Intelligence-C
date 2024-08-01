#ifndef _DYNAMIC_LIST_MATRIX_H
#define _DYNAMIC_LIST_MATRIX_H

/**
 * MODULE: dynamicListMatrix
 * FILE: dynamicListMatrix.h
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 28/7/2024.
 * DESCRIPTION: This module is the implement of the dynamic list/vector/array of int.
 * CC: BY SA
 */

#include "matrix.h"

typedef struct nodeMatrix {
    Matrix element;
    struct nodeMatrix *next;
} nodeMatrix;

typedef struct {
    unsigned long long n_elem;
    nodeMatrix *first, *last;
} dynamicListMatrix;

/**
 * FUNCTION: newDynamicListMatrix
 * INPUT: None.
 * REQUIREMENTS: None.
 * OUTPUT: An empty dynamic list.
 */
void newDynamicListMatrix(dynamicListMatrix *);

/**
 * FUNCTION: appendDynamicListMatrix
 * INPUT: A dynamic list and an element (Matrix).
 * REQUIREMENTS: The length of dynamic list < 2^64
 * MODIFIES: Add the element (Matrix) to the end of the dynamic list.
 */
void appendDynamicListMatrix(dynamicListMatrix *, Matrix);

/**
 * FUNCTION: consultElemDynamicListMatrix
 * INPUT: A dynamic list, and a position (unsigned long long).
 * REQUIREMENTS: 0 <= position < lengthDynamicListMatrix(list).
 * OUTPUT: The element (Matrix) at the position.
 */
void consultElemDynamicListMatrix(Matrix *, dynamicListMatrix, unsigned long long);

/**
 * FUNCTION: lengthDynamicListMatrix
 * INPUT: A dynamic list.
 * REQUIREMENTS: None.
 * OUTPUT: The length of the dynamic list.
 */
unsigned long long lengthDynamicListMatrix(dynamicListMatrix);

/**
 * FUNCTION: freeDynamicListMatrix
 * INPUT: A dynamic list.
 * REQUIREMENTS: None.
 * OUTPUT: The empty dynamic list.
 */
void freeDynamicListMatrix(dynamicListMatrix *);

#endif
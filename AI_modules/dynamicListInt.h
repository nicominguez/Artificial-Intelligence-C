#ifndef _DYNAMIC_LIST_INT_H
#define _DYNAMIC_LIST_INT_H

/**
 * MODULE: dynamicListInt
 * FILE: dynamicListInt.h
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 23/7/2024.
 * DESCRIPTION: This module is the implement of the dynamic list/vector/array of int.
 * CC: BY SA
 */

typedef struct nodeInt {
    int element;
    struct nodeInt *next;
} nodeInt;

typedef struct {
    unsigned long long n_elem;
    nodeInt *first, *last;
} dynamicListInt;

/**
 * FUNCTION: newDynamicListInt
 * INPUT: None.
 * REQUIREMENTS: None.
 * OUTPUT: An empty dynamic list.
 */
void newDynamicListInt(dynamicListInt *);

/**
 * FUNCTION: appendDynamicListInt
 * INPUT: A dynamic list and an element (int).
 * REQUIREMENTS: The length of dynamic list < 2^64
 * MODIFIES: Add the element (int) to the end of the dynamic list.
 */
void appendDynamicListInt(dynamicListInt *, int);

/**
 * FUNCTION: consultElemDynamicListInt
 * INPUT: A dynamic list, and a position (unsigned long long).
 * REQUIREMENTS: 0 <= position < lengthDynamicListInt(list).
 * OUTPUT: The element (int) at the position.
 */
int consultElemDynamicListInt(dynamicListInt, unsigned long long);

/**
 * FUNCTION: lengthDynamicListInt
 * INPUT: A dynamic list.
 * REQUIREMENTS: None.
 * OUTPUT: The length of the dynamic list.
 */
unsigned long long lengthDynamicListInt(dynamicListInt);

/**
 * FUNCTION: freeDynamicListInt
 * INPUT: A dynamic list.
 * REQUIREMENTS: None.
 * OUTPUT: The empty dynamic list.
 */
void freeDynamicListInt(dynamicListInt *);

#endif
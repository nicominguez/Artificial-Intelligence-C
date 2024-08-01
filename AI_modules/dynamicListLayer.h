#ifndef _DYNAMIC_LIST_LAYER_H
#define _DYNAMIC_LIST_LAYER_H

/**
 * MODULE: dynamicListLayer
 * FILE: dynamicListLayer.h
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 28/7/2024.
 * DESCRIPTION: This module is the implement of the dynamic list/vector/array of int.
 * CC: BY SA
 */

#include "layer.h"

typedef struct nodeLayer {
    Layer element;
    struct nodeLayer *next;
} nodeLayer;

typedef struct {
    unsigned long long n_elem;
    nodeLayer *first, *last;
} dynamicListLayer;

/**
 * FUNCTION: newDynamicListLayer
 * INPUT: None.
 * REQUIREMENTS: None.
 * OUTPUT: An empty dynamic list.
 */
void newDynamicListLayer(dynamicListLayer *);

/**
 * FUNCTION: appendDynamicListLayer
 * INPUT: A dynamic list and an element (Layer).
 * REQUIREMENTS: The length of dynamic list < 2^64
 * MODIFIES: Add the element (Layer) to the end of the dynamic list.
 */
void appendDynamicListLayer(dynamicListLayer *, Layer);

/**
 * FUNCTION: consultElemDynamicListLayer
 * INPUT: A dynamic list, and a position (unsigned long long).
 * REQUIREMENTS: 0 <= position < lengthDynamicListLayer(list).
 * OUTPUT: The element (Layer) at the position.
 */
void consultElemDynamicListLayer(Layer *, dynamicListLayer, unsigned long long);

/**
 * FUNCTION: changeElemDynamicListLayer
 * INPUT: A dynamic list, a position (unsigned long long), and an element (Layer).
 * REQUIREMENTS: 0 <= position < lengthDynamicListLayerr(list).
 * MODIFIES: Change the value of the element at the position.
 */
void changeElemDynamicListLayer(dynamicListLayer *, unsigned long long, Layer);

/**
 * FUNCTION: lengthDynamicListLayer
 * INPUT: A dynamic list.
 * REQUIREMENTS: None.
 * OUTPUT: The length of the dynamic list.
 */
unsigned long long lengthDynamicListLayer(dynamicListLayer);

/**
 * FUNCTION: freeDynamicListLayer
 * INPUT: A dynamic list.
 * REQUIREMENTS: None.
 * OUTPUT: The empty dynamic list.
 */
void freeDynamicListLayer(dynamicListLayer *);

#endif
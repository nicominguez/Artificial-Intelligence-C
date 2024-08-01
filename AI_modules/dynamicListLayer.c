/**
 * MODULE: dynamicListLayer
 * FILE: dynamicListLayer.c
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 28/7/2024.
 * DESCRIPTION: This module is the implement of the dynamic list/vector/array of the layer.
 * CC: BY SA
 */

#include "dynamicListLayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * FUNCTION: errorDynamicListLayer
 * INPUT: Error message.
 * REQUIREMENTS: None
 * MODIFIES: Finish the program.
*/
void errorDynamicListLayer(char error[]) {
    printf("\n\n\nERROR in the module dynamicListLayer: %s\n", error);
    while (true) {
        exit(-1);
    }
}

/**
 * FUNCTION: newDynamicListLayer
 * INPUT: None.
 * REQUIREMENTS: None.
 * OUTPUT: An empty dynamic list.
 */
void newDynamicListLayer(dynamicListLayer *l) {
    l->first = NULL;
    l->last = NULL;
    l->n_elem = 0;
}

/**
 * FUNCTION: appendDynamicListLayer
 * INPUT: A dynamic list and an element (Layer).
 * REQUIREMENTS: The length of dynamic list < 2^63 - 1
 * MODIFIES: Add the element (Layer) to the end of the dynamic list.
 */
void appendDynamicListLayer(dynamicListLayer *l, Layer elem) {
    nodeLayer *aux;

    unsigned long long lim = 9223372036854775807; // 2^63 - 1
    aux = malloc(sizeof(nodeLayer));
    if (aux == NULL) {
        errorDynamicListLayer("There isn't more memory to add an element to the list.");
    }
    else if (lengthDynamicListLayer(*l) >= lim) {
        errorDynamicListLayer("The list is too large.");
    }
    
    aux->element = elem;
    aux->next = NULL;
    if (lengthDynamicListLayer(*l) == 0) {
        l->first = aux;
        l->last = aux;
    }
    else {
        (l->last)->next = aux;
        l->last = aux;
    }

    l->n_elem = l->n_elem + 1;
}

/**
 * FUNCTION: searchPosDynamicListLayer
 * INPUT: A dynamic list and a position (unsigned long long).
 * REQUIREMENTS: lengthDynamicListLayer(list) > 1 and 0 < position < lengthDynamicListLayer(list)
 * OUTPUT: current = A pointer to the memory address of the node whose position is pos.
 *      previous = A pointer to the memory address of the previous node whose position is pos.
 */
void searchPosDynamicListLayer(nodeLayer **current, nodeLayer **previous, dynamicListLayer l, unsigned long long pos) {
    if (lengthDynamicListLayer(l) <= 1) {
        errorDynamicListLayer("A position can't be searched in an empty list or with one element.");
    }
    else if (pos <= 0 || pos >= lengthDynamicListLayer(l)) {
        errorDynamicListLayer("The position is out of range. The position can't be searched.");
    }

    unsigned long long count;

    count = 1;
    *current = (l.first)->next;
    *previous = l.first;
    while ((*current)->next != NULL && count != pos) {
        *previous = *current;
        *current = (*current)->next;
        count++;
    }
}

/**
 * FUNCTION: consultElemDynamicListLayer
 * INPUT: A dynamic list, and a position (unsigned long long).
 * REQUIREMENTS: 0 <= position < lengthDynamicListLayer(list) and lengthDynamicListLayer(list) > 0
 * OUTPUT: The element (Layer) at the position.
 */
void consultElemDynamicListLayer(Layer *elem, dynamicListLayer l, unsigned long long pos) {
    if (lengthDynamicListLayer(l) == 0) {
        errorDynamicListLayer("An element can't be consulted in an empty list.");
    }
    else if (pos < 0 || pos >= lengthDynamicListLayer(l)) {
        errorDynamicListLayer("The position is out of range. The element can't be consulted.");
    }

    nodeLayer *current, *previous;
    if (lengthDynamicListLayer(l) == 1 || pos == 0) {
        *elem = (l.first)->element;
    }
    else {
        searchPosDynamicListLayer(&current, &previous, l, pos);
        *elem = current->element;
    }
}

/**
 * FUNCTION: changeElemDynamicListLayer
 * INPUT: A dynamic list, a position (unsigned long long), and an element (Layer).
 * REQUIREMENTS: 0 <= position < lengthDynamicListLayer(list) and lengthDynamicListLayer(list) > 0
 * MODIFIES: Change the value of the element at the position.
 */
void changeElemDynamicListLayer(dynamicListLayer *l, unsigned long long pos, Layer elem) {
    if (lengthDynamicListLayer(*l) == 0) {
        errorDynamicListLayer("An element can't be changed in an empty list.");
    }
    else if (pos < 0 || pos >= lengthDynamicListLayer(*l)) {
        errorDynamicListLayer("The position is out of range. The element can't be changed.");
    }

    nodeLayer *current, *previous;
    if (lengthDynamicListLayer(*l) == 1 || pos == 0) {
        (l->first)->element = elem;
    }
    else {
        searchPosDynamicListLayer(&current, &previous, *l, pos);
        current->element = elem;
    }
}

/**
 * FUNCTION: freeDynamicListLayer
 * INPUT: A dynamic list.
 * REQUIREMENTS: None.
 * OUTPUT: The empty dynamic list.
 */
void freeDynamicListLayer(dynamicListLayer *l) {
    nodeLayer *aux;
    while (lengthDynamicListLayer(*l) > 0) {
        aux = l->first;
        l->first = (l->first)->next;
        free(aux);

        l->n_elem = l->n_elem - 1;
    }
}

/**
 * FUNCTION: lengthDynamicListLayer
 * INPUT: A dynamic list.
 * REQUIREMENTS: None.
 * OUTPUT: The length of the dynamic list.
 */
unsigned long long lengthDynamicListLayer(dynamicListLayer l) {
    return l.n_elem;
}
/**
 * MODULE: dynamicListInt
 * FILE: dynamicListInt.c
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 23/7/2024.
 * DESCRIPTION: This module is the implement of the dynamic list/vector/array.
 * CC: BY SA
 */

#include "dynamicListInt.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * FUNCTION: errorDynamicListInt
 * INPUT: Error message.
 * REQUIREMENTS: None
 * MODIFIES: Finish the program.
*/
void errorDynamicListInt(char error[]) {
    printf("\n\n\nERROR in the module dynamicListInt: %s\n", error);
    while (true) {
        exit(-1);
    }
}

/**
 * FUNCTION: newdynamicListInt
 * INPUT: None.
 * REQUIREMENTS: None.
 * OUTPUT: An empty dynamic list.
 */
void newDynamicListInt(dynamicListInt *l) {
    l->first = NULL;
    l->last = NULL;
    l->n_elem = 0;
}

/**
 * FUNCTION: appendDynamicListInt
 * INPUT: A dynamic list and an element (int).
 * REQUIREMENTS: The length of dynamic list < 2^63 - 1
 * MODIFIES: Add the element (int) to the end of the dynamic list.
 */
void appendDynamicListInt(dynamicListInt *l, int elem) {
    nodeInt *aux;

    unsigned long long lim = 9223372036854775807; // 2^63 - 1
    aux = malloc(sizeof(nodeInt));
    if (aux == NULL) {
        errorDynamicListInt("There isn't more memory to add an element to the list.");
    }
    else if (lengthDynamicListInt(*l) >= lim) {
        errorDynamicListInt("The list is too large.");
    }
    
    aux->element = elem;
    aux->next = NULL;
    if (lengthDynamicListInt(*l) == 0) {
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
 * FUNCTION: searchPosDynamicListInt
 * INPUT: A dynamic list and a position (unsigned long long).
 * REQUIREMENTS: lengthDynamicListInt(list) > 1 and 0 < position < lengthDynamicListInt(list)
 * OUTPUT: current = A pointer to the memory address of the node whose position is pos.
 *      previous = A pointer to the memory address of the previous node whose position is pos.
 */
void searchPosDynamicListInt(nodeInt **current, nodeInt **previous, dynamicListInt l, unsigned long long pos) {
    if (lengthDynamicListInt(l) <= 1) {
        errorDynamicListInt("A position can't be searched in an empty list or with one element.");
    }
    else if (pos <= 0 || pos >= lengthDynamicListInt(l)) {
        errorDynamicListInt("The position is out of range. The position can't be searched.");
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
 * FUNCTION: consultElemDynamicListInt
 * INPUT: A dynamic list, and a position (unsigned long long).
 * REQUIREMENTS: 0 <= position < lengthDynamicListInt(list) and lengthDynamicListInt(list) > 0
 * OUTPUT: The element (int) at the position.
 */
int consultElemDynamicListInt(dynamicListInt l, unsigned long long pos) {
    if (lengthDynamicListInt(l) == 0) {
        errorDynamicListInt("An element can't be consulted in an empty list.");
    }
    else if (pos < 0 || pos >= lengthDynamicListInt(l)) {
        errorDynamicListInt("The position is out of range. The element can't be consulted.");
    }

    int elem;
    nodeInt *current, *previous;
    if (lengthDynamicListInt(l) == 1 || pos == 0) {
        elem = (l.first)->element;
    }
    else {
        searchPosDynamicListInt(&current, &previous, l, pos);
        elem = current->element;
    }

    return elem;
}

/**
 * FUNCTION: freeDynamicListInt
 * INPUT: A dynamic list.
 * REQUIREMENTS: None.
 * OUTPUT: The empty dynamic list.
 */
void freeDynamicListInt(dynamicListInt *l) {
    nodeInt *aux;
    while (lengthDynamicListInt(*l) > 0) {
        aux = l->first;
        l->first = (l->first)->next;
        free(aux);

        l->n_elem = l->n_elem - 1;
    }
}

/**
 * FUNCTION: lengthDynamicListInt
 * INPUT: A dynamic list.
 * REQUIREMENTS: None.
 * OUTPUT: The length of the dynamic list.
 */
unsigned long long lengthDynamicListInt(dynamicListInt l) {
    return l.n_elem;
}
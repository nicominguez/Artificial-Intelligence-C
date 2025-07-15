/**
 * MODULE: dynamicListMatrix
 * FILE: dynamicListMatrix.c
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 28/7/2024.
 * DESCRIPTION: This module is the implement of the dynamic list/vector/array.
 * CC: BY SA
 */

#include "dynamicListMatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * FUNCTION: errorDynamicListMatrix
 * INPUT: Error message.
 * REQUIREMENTS: None
 * MODIFIES: Finish the program.
*/
void errorDynamicListMatrix(char error[]) {
    printf("\n\n\nERROR in the module dynamicListMatrix: %s\n", error);
    while (true) {
        exit(-1);
    }
}

void newDynamicListMatrix(dynamicListMatrix *l) {
    l->first = NULL;
    l->last = NULL;
    l->n_elem = 0;
}

void appendDynamicListMatrix(dynamicListMatrix *l, Matrix elem) {
    nodeMatrix *aux;

    unsigned long long lim = 9223372036854775807; // 2^63 - 1
    aux = malloc(sizeof(nodeMatrix));
    if (aux == NULL) {
        errorDynamicListMatrix(
            "There isn't more memory to add an element to the list.");
    }
    else if (lengthDynamicListMatrix(*l) >= lim) {
        errorDynamicListMatrix("The list is too large.");
    }
    
    aux->element = elem;
    aux->next = NULL;
    if (lengthDynamicListMatrix(*l) == 0) {
        l->first = aux;
        l->last = aux;
    }
    else {
        (l->last)->next = aux;
        l->last = aux;
    }

    l->n_elem = l->n_elem + 1;
}

void searchPosMatrix(nodeMatrix **current, nodeMatrix **previous,
                    dynamicListMatrix l, unsigned long long pos) {
    if (lengthDynamicListMatrix(l) <= 1) {
        errorDynamicListMatrix(
            "A position can't be searched in an empty list or with one element.");
    }
    else if (pos <= 0 || pos >= lengthDynamicListMatrix(l)) {
        errorDynamicListMatrix(
            "The position is out of range. The position can't be searched.");
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

void consultElemDynamicListMatrix(Matrix *elem, dynamicListMatrix l, unsigned long long pos) {
    if (lengthDynamicListMatrix(l) == 0) {
        errorDynamicListMatrix("An element can't be consulted in an empty list.");
    }
    else if (pos < 0 || pos >= lengthDynamicListMatrix(l)) {
        errorDynamicListMatrix(
            "The position is out of range. The element can't be consulted.");
    }

    nodeMatrix *current, *previous;
    if (lengthDynamicListMatrix(l) == 1 || pos == 0) {
        *elem = (l.first)->element;
    }
    else {
        searchPosMatrix(&current, &previous, l, pos);
        *elem = current->element;
    }
}

void freeDynamicListMatrix(dynamicListMatrix *l) {
    nodeMatrix *aux;
    while (lengthDynamicListMatrix(*l) > 0) {
        aux = l->first;
        l->first = (l->first)->next;
        free(aux);

        l->n_elem = l->n_elem - 1;
    }
}

unsigned long long lengthDynamicListMatrix(dynamicListMatrix l) {
    return l.n_elem;
}
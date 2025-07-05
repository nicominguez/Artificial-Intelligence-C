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

void newDynamicListLayer(dynamicListLayer *l) {
    l->first = NULL;
    l->last = NULL;
    l->n_elem = 0;
}

void appendDynamicListLayer(dynamicListLayer *l, Layer elem) {
    nodeLayer *aux;

    unsigned long long lim = 9223372036854775807; // 2^63 - 1
    aux = malloc(sizeof(nodeLayer));
    if (aux == NULL) {
        errorDynamicListLayer(
            "There isn't more memory to add an element to the list.");
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

void searchPosDynamicListLayer(nodeLayer **current, nodeLayer **previous,
                                dynamicListLayer l, unsigned long long pos) {
    if (lengthDynamicListLayer(l) <= 1) {
        errorDynamicListLayer(
            "A position can't be searched in an empty list or with one element.");
    }
    else if (pos <= 0 || pos >= lengthDynamicListLayer(l)) {
        errorDynamicListLayer(
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

void consultElemDynamicListLayer(Layer *elem, dynamicListLayer l, unsigned long long pos) {
    if (lengthDynamicListLayer(l) == 0) {
        errorDynamicListLayer("An element can't be consulted in an empty list.");
    }
    else if (pos < 0 || pos >= lengthDynamicListLayer(l)) {
        errorDynamicListLayer(
            "The position is out of range. The element can't be consulted.");
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

void freeDynamicListLayer(dynamicListLayer *l) {
    nodeLayer *aux;
    while (lengthDynamicListLayer(*l) > 0) {
        aux = l->first;
        l->first = (l->first)->next;
        free(aux);

        l->n_elem = l->n_elem - 1;
    }
}

unsigned long long lengthDynamicListLayer(dynamicListLayer l) {
    return l.n_elem;
}
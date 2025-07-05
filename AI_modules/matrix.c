/**
 * MODULE: matrix
 * FILE: matrix.c
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 7/7/2024
 * DESCRIPTION: This module can operate with matrix of floats.
 * CC: BY SA
 */

#include "matrix.h"
#include "random.h"
#include <math.h>
#include <stdlib.h>

/**
 * FUNCTION: errorMatrix
 * INPUT: error message
 * REQUIREMENTS: None
 * MODIFIES: Finish the program.
 */
void errorMatrix(char error[]) {
    printf("\n\n\nERROR in the module matrix: %s\n", error);
    while (true)
        exit(-1);
}

void newRandomNormMatrix(Matrix *m, unsigned short sr, unsigned short sc) {
    if (sr > MAX_ROWS || sc > MAX_COLUMNS) {
        errorMatrix("The normal matrix can't be created because is very big.");
    }

    for (int i = 0; i < sr; i++) {
        for (int j = 0; j < sc; j++) {
            m->val[i][j] = normalDistribution();
        }
    }
    m->size_row = sr;
    m->size_col = sc;
    m->transpose = false;
}

void newRandomMatrix(Matrix *m, unsigned short sr, unsigned short sc) {
    if (sr > MAX_ROWS || sc > MAX_COLUMNS) {
        errorMatrix("The matrix can't be created because is very big.");
    }
    
    m->size_row = sr;
    m->size_col = sc;
    m->transpose = false;
}

void MCMatrix(Matrix *m, unsigned short r, unsigned short c, float n) {
    if (r >= m->size_row || c >= m->size_col) {
        errorMatrix(
            "The position (r, c) can't be modified because it's out of range.");
    }

    if (m->transpose) {
        m->val[c][r] = n;
    }
    else {
        m->val[r][c] = n;
    }
}

void FastMCMatrix(Matrix *m, unsigned short r, unsigned short c, float n) {
    if (m->transpose) {
        m->val[c][r] = n;
    }
    else {
        m->val[r][c] = n;
    }
}

float CCMatrix(Matrix m, unsigned short r, unsigned short c) {
    if (r >= m.size_row || c >= m.size_col) {
        errorMatrix(
            "The position (r, c) can't be consulted because it's out of range.");
    }

    float n;

    if (m.transpose) {
        n = m.val[c][r];
    }
    else {
        n = m.val[r][c];
    }

    return n;
}

float FastCCMatrix(Matrix m, unsigned short r, unsigned short c) {
    float n;

    if (m.transpose) {
        n = m.val[c][r];
    }
    else {
        n = m.val[r][c];
    }

    return n;
}

unsigned short numberRows(Matrix m) {
    return m.size_row;
}

unsigned short numberColumns(Matrix m) {
    return m.size_col;
}

void transposeMatrix(Matrix *m) {
    unsigned short aux;

    aux = m->size_row;
    m->size_row = m->size_col;
    m->size_col = aux;
    m->transpose = !m->transpose;
}

void addMatrix(Matrix *m, Matrix m1, Matrix m2) {
    bool equal_r, equal_c;

    equal_r = m1.size_row == m2.size_row;
    equal_c = m1.size_col == m2.size_col;

    if (equal_r && equal_c) { // Equals sizes.
        m->size_row = m1.size_row;
        m->size_col = m1.size_col;
        m->transpose = m1.transpose;
        for (int i = 0; i < m1.size_row; i++) {
            for (int j = 0; j < m1.size_col; j++) {
                FastMCMatrix(m, i, j, FastCCMatrix(m1, i, j) + FastCCMatrix(m2, i, j));
            }
        }
    }
    else if (equal_r) { // Equal number of rows
        m->size_row = m1.size_row;
        if (m1.size_col == 1) {
            m->size_col = m2.size_col;
            m->transpose = m2.transpose;
            for (int i = 0; i < m->size_row; i++) {
                for (int j = 0; j < m->size_col; j++) {
                    FastMCMatrix(m, i, j, FastCCMatrix(m1, i, 0) + FastCCMatrix(m2, i, j));
                }
            }
        }
        else if (m2.size_col == 1) { // Equal number of columns
            m->size_col = m1.size_col;
            m->transpose = m1.transpose;
            for (int i = 0; i < m->size_row; i++) {
                for (int j = 0; j < m->size_col; j++) {
                    FastMCMatrix(m, i, j, FastCCMatrix(m1, i, j) + FastCCMatrix(m2, i, 0));
                }
            }
        }
        else {
            errorMatrix("m1 and m2 cannot be added due to their sizes.");
        }
    }
    else if (equal_c) {
        m->size_col = m1.size_col;
        if (m1.size_row == 1) {
            m->size_row = m2.size_row;
            m->transpose = m2.transpose;
            for (int i = 0; i < m->size_row; i++) {
                for (int j = 0; j < m->size_col; j++) {
                    FastMCMatrix(m, i, j, FastCCMatrix(m1, 0, j) + FastCCMatrix(m2, i, j));
                }
            }
        }
        else if (m2.size_row == 1) {
            m->size_row = m1.size_row;
            m->transpose = m1.transpose;
            for (int i = 0; i < m->size_row; i++) {
                for (int j = 0; j < m->size_col; j++) {
                    FastMCMatrix(m, i, j, FastCCMatrix(m1, i, j) + FastCCMatrix(m2, 0, j));
                }
            }
        }
        else {
            errorMatrix("m1 and m2 cannot be added due to their sizes.");
        }
    }
    else {
        errorMatrix("m1 and m2 cannot be added due to their sizes.");
    }
}

void subtractMatrix(Matrix *m, Matrix m1, Matrix m2) {
    if (m1.size_row != m2.size_row || m1.size_col != m2.size_col) {
        errorMatrix("m1 and m2 cannot be subtracted.");
    }

    int i, j;
    m->size_row = m1.size_row;
    m->size_col = m1.size_col;
    m->transpose = m1.transpose;

    for (i = 0; i < m1.size_row; i++) {
        for (j = 0; j < m1.size_col; j++) {
            FastMCMatrix(m, i, j, FastCCMatrix(m1, i, j) - FastCCMatrix(m2, i, j));
        }
    }
}

void multiplyMatrix(Matrix *m, Matrix m1, Matrix m2) {
    if (m1.size_col != m2.size_row) {
        errorMatrix("The m1 and m2 cannot be multiply due to dimensions");
    }

    if (m1.size_row <= MAX_ROWS && m2.size_col <= MAX_COLUMNS) {
        m->transpose = false;
    }
    else if (m1.size_row <= MAX_COLUMNS && m2.size_col <= MAX_ROWS) {
        m->transpose = true;
    }
    else {
        errorMatrix("The m1 and m2 cannot be multiply due to dimensions. (Transpose).");
    }

    float s;
    m->size_row = m1.size_row;
    m->size_col = m2.size_col;
    for (int i = 0; i < m1.size_row; i++) {
        for (int j = 0; j < m2.size_col; j++) {
            s = 0;
            for (int k = 0; k < m1.size_col; k++) {
                s = s + FastCCMatrix(m1, i, k) * FastCCMatrix(m2, k, j);
            }
            FastMCMatrix(m, i, j, s);
        }
    }
}

void multiplyNumbersMatrix(Matrix *m, Matrix m1, Matrix m2) {
    if (m1.size_row != m2.size_row || m1.size_col != m2.size_col) {
        errorMatrix("The matrix m1 and m2 haven't same sizes.");
    }

    m->size_row = m1.size_row;
    m->size_col = m1.size_col;
    m->transpose = m1.transpose;
    for (int i = 0; i < m1.size_row; i++) {
        for (int j = 0; j < m1.size_col; j++) {
            FastMCMatrix(m, i, j, FastCCMatrix(m1, i, j) * FastCCMatrix(m2, i, j));
        }
    }
}

void meanMatrix(Matrix *mean, Matrix m) {
    float s;
    
    mean->size_row = 1;
    mean->size_col = m.size_col;
    mean->transpose = m.transpose;
    for (int i = 0; i < m.size_col; i++) {
        s = 0;
        for (int j = 0; j < m.size_row; j++) {
            s = s + FastCCMatrix(m, j, i);
        }
        FastMCMatrix(mean, 0, i, s / (float) (m.size_row));
    }
}

void multiplyNumberAndMatrix(Matrix *m, Matrix m1, float n) {
    m->size_row = m1.size_row;
    m->size_col = m1.size_col;
    m->transpose = m1.transpose;
    for (int i = 0; i < m1.size_row; i++) {
        for (int j = 0; j < m1.size_col; j++) {
            FastMCMatrix(m, i, j, n * FastCCMatrix(m1, i, j));
        }
    }
}

float MSEMatrix(Matrix m1, Matrix m2) {
    if (m1.size_row != m2.size_row || m1.size_col != m2.size_col) {
        errorMatrix("The m1 and m2 have to be same sizes.");
    }

    float s, p, mean;

    mean = 0;
    for (int i = 0; i < m1.size_row; i++) {
        s = 0;
        for (int j = 0; j < m1.size_col; j++) {
            p = FastCCMatrix(m1, i, j) - FastCCMatrix(m2, i, j);
            s = s + p*p;
        }
        mean = mean + s / (float) (m1.size_col);
    }
    mean = mean / (float) m1.size_row;

    return mean;
}

void derivMSEMatrix(Matrix *m, Matrix m1, Matrix m2) {
    subtractMatrix(m, m1, m2);
}

void minMaxMatrix(float *min, float *max, Matrix m) {
    float aux;

    *min = FastCCMatrix(m, 0, 0);
    *max = FastCCMatrix(m, 0, 0);
    for (int i = 0; i < m.size_row; i++) {
        for (int j = 0; j < m.size_col; j++) {
            aux = FastCCMatrix(m, i, j);
            if (aux < *min) {
                *min = aux;
            }
            
            if (aux > *max) {
                *max = aux;
            }
        }
    }
}

void normalizationMatrix(Matrix *m, float min, float max) {
    float dif;

    dif = max - min;
    for (int i = 0; i < m->size_row; i++) {
        for (int j = 0; j < m->size_col; j++) {
            FastMCMatrix(m, i, j, (FastCCMatrix(*m, i, j) - min) / dif);
        }
    }
}

void denormalizeMatrix(Matrix *m, float min, float max) {
    float dif;

    dif = max - min;
    for (int i = 0; i < m->size_row; i++) {
        for (int j = 0; j < m->size_col; j++) {
            FastMCMatrix(m, i, j, FastCCMatrix(*m, i, j) * dif + min);
        }
    }
}

/**
 * FUNCTION: swapRow
 * INPUT: A matrix, r1 (row) and r2 (row).
 * REQUIREMENTS: 0 <= r1, r2 < numberRows(m).
 * MODIFIES: Swap r1 and r2 of m.
 */
void swapRow(Matrix *m, unsigned short r1, unsigned short r2) {    
    float aux;
    for (int i = 0; i < numberColumns(*m); i++) {
        aux = FastCCMatrix(*m, r1, i);
        FastMCMatrix(m, r1, i, FastCCMatrix(*m, r2, i));
        FastMCMatrix(m, r2, i, aux);
    }
}

/**
 * FUNCTION: numberInArray
 * INPUT: l, length_l and n
 * REQUIREMENTS: length_l > 0
 * OUTPUT: n in l (bool)
 */
bool numberInArray(int l[], int length_l, int n) {
    int j;

    j = 0;
    while (j < length_l - 1 && l[j] != length_l) {
        j++;
    }

    return l[j] == length_l;
}

void suffleRowsMatrix(Matrix *m, Matrix *decisions) {
    if (numberRows(*m) <= 1) {
        errorMatrix(
            "The matrix cannot be suffled because it has fewer that two rows.");
    }

    /**
     * Explained: 
     *      We work with m (MxN), decisions, l, length_l,  r1 and r2.
     *      We have to suffle the rows of m. Therefore:
     *      1. We select two rows. Row 0 and last row.
     *      2. Swap these rows.
     *      3. We select other two rows but this rows cannot be
     *      none that previous rows selected.
     *      4. Swap these rows.
     *      5. Repet 3.
     * 
     * Clarification:
     *      We save the rows selected in l, whose length rise.
     *      decisions is a matrix (Mx2). For each row, save the other row
     *      swaped. Example:
     *                  1 3
     *      decisions = 0 6
     *                  2 7
     *      The row 1 has been swaped with the row 3.
     *      The row 0 has been swaped with the row 7.
     */

    newRandomMatrix(decisions, numberRows(*m) / 2, 2);
    int l[MAX_ROWS], length_l, r1, r2;

    r1 = 0;
    r2 = numberRows(*m) - 1;

    l[0] = 0;
    l[1] = numberRows(*m) - 1;
    length_l = 2;
    for (int i = 0; i < numberRows(*m) / 2 - 1; i++) {
        swapRow(m, r1, r2);
        MCMatrix(decisions, i, 0, r1);
        MCMatrix(decisions, i, 1, r2);
        
        // r is a number that is in [0, numerRows(*m) - 1] and not in l
        r1 = uniformDistributionWithException(0, numberRows(*m) - 1, l, length_l);
        l[length_l] = r1;
        length_l++;
        r2 = uniformDistributionWithException(0, numberRows(*m) - 1, l, length_l);
        l[length_l] = r2;
        length_l++;
    }
    swapRow(m, r1, r2);
    MCMatrix(decisions, numberRows(*m) / 2 - 1, 0, r1);
    MCMatrix(decisions, numberRows(*m) / 2 - 1, 1, r2);
}

void sortRowsMatrix(Matrix *m, Matrix decisions) {
    for (int i = 0; i < numberRows(decisions); i++) {
        swapRow(m, FastCCMatrix(decisions, i, 0), FastCCMatrix(decisions, i, 1));
    }
}

void cutMatrix(Matrix *m1, Matrix *m2, Matrix m, unsigned int n) {
    if (n >= m.size_row) {
        errorMatrix("The number is greather that rows.");
    }
    else if (n == 0) {
        errorMatrix("The number is less that rows.");
    }

    newRandomMatrix(m1, n, m.size_col);
    newRandomMatrix(m2, m.size_row - n, m.size_col);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < numberColumns(m); j++) {
            FastMCMatrix(m1, i, j, FastCCMatrix(m, i, j));
        }
    }

    for (int i = n; i < numberRows(m); i++) {
        for (int j = 0; j < numberColumns(m); j++) {
            FastMCMatrix(m2, i, j, FastCCMatrix(m, i, j));
        }
    }
}

void showMatrix(Matrix m) {
    printf("\n");
    for (int i = 0; i < m.size_row; i++) {
        printf("    ");
        for (int j = 0; j < m.size_col; j++) {
            printf("%f ", CCMatrix(m, i, j));
        }
        printf("\n");
    }
}

void writeMatrix(FILE *f, bool *error, Matrix m) {
    float sr, sc;
    
    sr = (float) (m.size_row);
    sc = (float) (m.size_col);
    if (fwrite(&sr, sizeof(float), 1, f) != 1 ||
        fwrite(&sc, sizeof(float), 1, f) != 1) {

        *error = true;
    }
    else {
        float aux_val;
        int i, j, pcent;

        i = 0;
        j = 0;
        pcent = m.size_row;
        while (i != pcent) {
            aux_val = FastCCMatrix(m, i, j);
            if (fwrite(&aux_val, sizeof(float), 1, f) != 1) {
                pcent = i;
            }
            else {
                j++;
                if (j % m.size_col == 0) {
                    j = 0;
                    i++;
                }
            }
        }
        *error = pcent != m.size_row;
    }
}

void readMatrix(Matrix *m, FILE *f, bool *error) {
    float sr, sc;

    if (fread(&sr, sizeof(float), 1, f) != 1 ||
        fread(&sc, sizeof(float), 1, f) != 1) {
            
        *error = true;
    }
    else {
        m->size_row = (unsigned short) (sr);
        m->size_col = (unsigned short) (sc);
        m->transpose = !(sr <= MAX_ROWS && sc <= MAX_COLUMNS) &&
                        (sr <= MAX_COLUMNS && sc <= MAX_ROWS);
        if (sr <= MAX_ROWS && sc <= MAX_COLUMNS) {
            m->transpose = false;
        }
        else if (sr <= MAX_COLUMNS && sc <= MAX_ROWS) {
            m->transpose = true;
        }
        else {
            *error = true;
        }

        if (!(*error)) {
            float aux_val;
            int i, j, pcent;

            i = 0;
            j = 0;
            pcent = m->size_row;
            while (i != pcent) {
                if (fread(&aux_val, sizeof(float), 1, f) != 1) {
                    pcent = i;
                }
                else {
                    FastMCMatrix(m, i, j, aux_val);
                    j++;
                    if (j % m->size_col == 0) {
                        j = 0;
                        i++;
                    }
                }
            }
            *error = pcent != m->size_row;
        }
    }
}
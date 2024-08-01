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

/**
 * FUNCTION: newRandomNormMatrix
 * INPUT: 
 *      sr: Number of rows (unsigned short).
 *      sc: Number of columns (unsigned short)
 * REQUIREMENTS: 1 <= sr <= MAX_ROWS and 1 <= sc <= MAX_COLUMNS
 * OUTPUT: A random matrix of size srXsc. It's numbers come from a
 *      normal distribution.
 *      Clarification:
 *          a b c d
 *          e f g h
 *          i j k l
 *          m n o p
 *      
 *      In the previous matrix, the position (0, 0) is a.
 *      (row, column).
 */
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

/**
 * FUNCTION: newRandomMatrix
 * INPUT: 
 *      sr: Number of rows (unsigned short).
 *      sc: Number of columns (unsigned short)
 * REQUIREMENTS: 1 <= sr <= MAX_ROWS and 1 <= sc <= MAX_COLUMNS
 * OUTPUT: A random matrix of size srXsc.
 *      Clarification:
 *          a b c d
 *          e f g h
 *          i j k l
 *          m n o p
 *      
 *      In the previous matrix, the position (0, 0) is a.
 *      (row, column).
 * COST: O(1)
 */
void newRandomMatrix(Matrix *m, unsigned short sr, unsigned short sc) {
    if (sr > MAX_ROWS || sc > MAX_COLUMNS) {
        errorMatrix("The matrix can't be created because is very big.");
    }
    
    m->size_row = sr;
    m->size_col = sc;
    m->transpose = false;
}

/**
 * FUNCTION: MCMatrix
 * INPUT: 
 *      r: Row (unsigned short).
 *      c: Column (unsigned short).
 *      n (float).
 * REQUIREMENTS:
 *      0 <= r < number of rows
 *      0 <= c < number of columns
 * OUTPUT: A matrix with the (r, c) component changed to n.
 * COST: O(1)
 */
void MCMatrix(Matrix *m, unsigned short r, unsigned short c, float n) {
    if (r >= m->size_row || c >= m->size_col) {
        errorMatrix("The position (r, c) can't be modified because it's out of range.");
    }

    if (m->transpose) {
        m->val[c][r] = n;
    }
    else {
        m->val[r][c] = n;
    }
}

/**
 * FUNCTION: FastMCMatrix
 * INPUT: 
 *      r: Row (unsigned short).
 *      c: Column (unsigned short).
 *      n (float).
 * REQUIREMENTS:
 *      0 <= r < number of rows
 *      0 <= c < number of columns
 *      WARNING: This function DOESN'T CHECK IT.
 * OUTPUT: A matrix with the (r, c) component changed to n.
 * COST: O(1) MORE FAST
 */
void FastMCMatrix(Matrix *m, unsigned short r, unsigned short c, float n) {
    if (m->transpose) {
        m->val[c][r] = n;
    }
    else {
        m->val[r][c] = n;
    }
}

/**
 * FUNCTION: CCMatrix
 * INPUT: 
 *      m (Matrix).
 *      r: Row (unsigned short).
 *      c: Column (unsigned short).
 * REQUIREMENTS:
 *      0 <= r < number of rows
 *      0 <= c < number of columns
 * OUTPUT: The value of the position (r, c) of the matrix.
 * COST: O(1)
 */
float CCMatrix(Matrix m, unsigned short r, unsigned short c) {
    if (r >= m.size_row || c >= m.size_col) {
        errorMatrix("The position (r, c) can't be consulted because it's out of range.");
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

/**
 * FUNCTION: FastCCMatrix
 * INPUT: 
 *      m (Matrix).
 *      r: Row (unsigned short).
 *      c: Column (unsigned short).
 * REQUIREMENTS:
 *      0 <= r < number of rows
 *      0 <= c < number of columns
 *      WARNING: This function DOESN'T CHECK IT.
 * OUTPUT: The value of the position (r, c) of the matrix.
 * COST: O(1) MORE FAST
 */
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

/**
 * FUNCTION: numberRows
 * INPUT: A matrix.
 * REQUIREMENTS: None
 * OUTPUT: The number of rows.
 * COST: O(1)
 */
unsigned short numberRows(Matrix m) {
    return m.size_row;
}

/**
 * FUNCTION: numberColumns
 * INPUT: A matrix.
 * REQUIREMENTS: None
 * OUTPUT: The number of columns.
 * COST: O(1)
 */
unsigned short numberColumns(Matrix m) {
    return m.size_col;
}

/**
 * FUNCTION: transposeMatrix
 * INPUT: A matrix, m.
 * REQUIREMENTS:
 *      number of the rows <= MAX_COLUMNS
 *      number of the columns <= MAX_ROWS
 * MODIFIES: m = m' (transpose)
 * COST: O(1)
 */
void transposeMatrix(Matrix *m) {
    unsigned short aux;

    aux = m->size_row;
    m->size_row = m->size_col;
    m->size_col = aux;
    m->transpose = !m->transpose;
}

/**
 * FUNCTION: addMatrix
 * INPUT:
 *      m1 (Matrix).
 *      m2 (Matrix).
 * REQUIREMENTS: m1|m2 (MxN) and m2|m1 (MxN) OR
 *      m1|m2 (1xN) and m2|m1 (MxN) OR m1|m2 (Nx1) and
 *      m2|m1 (NxM)
 * OUTPUT: The matrix m, that is m1+m2.
 *      Clarification:
 *          Case 1:
 *              1 2
 *              0 1 is m1|m2 (rows=2, columns=2)
 * 
 *              0 1
 *              1 0 is m2|m1 (rows=2, columns=2)
 * 
 *              1 3
 *              1 1 is m (rows=2, columns=2)
 * 
 *          Case 2:
 *              1 -2 4 is m1|m2 (rows=1, columns=3)
 *              
 *              2 3 1
 *              1 1 3 is m2|m1 (rows=2, columns=3)
 *              
 *              3 1 5
 *              2 -1 7 is m (rows=2, columns=3)
 *          
 *          Case 3:
 *              3
 *              1 is m1|m2 (rows=2, columns=1)
 *              
 *              2 3 1
 *              1 1 3 is m2|m1 (rows=2, columns=3)
 *              
 *              5 6 4
 *              2 2 4 is m (rows=2, columns=3)
 * COST: O(MxN)
 */
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

/**
 * FUNCTION: subtractMatrix
 * INPUT:
 *      m1 (Matrix MxN).
 *      m2 (Matrix MxN).
 * REQUIREMENTS: The sizes equals.
 * OUTPUT: The matrix m, that is m1-m2.
 * COST: O(MxN)
 */
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

/**
 * FUNCTION: multiplyMatrix
 * INPUT:
 *      m1 (Matrix, size MxH).
 *      m2 (Matrix, size HxN).
 * REQUIREMENTS: 
 *      The number columns of m1 must be equal to number rows
 *      of m2.
 * OUTPUT: The matrix m, that is m1*m2, so size of m is MxN
 * COST: O(MXNXH)
 */
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

/**
 * FUNCTION: multiplyNumbersMatrix
 * INPUT:
 *      m1 (Matrix, size MxN).
 *      m2 (Matrix, size MxN).
 * REQUIREMENTS: 
 *      Same sizes.
 * OUTPUT: The matrix m, that is m1*m2, so size of m is MxN
 *      Ej:
 *               1 2 3         1 1 3        1 2 9
 *          m1 = 0 1 1    m2 = 0 1 0    m = 0 1 0
 * COST: O(MxN)
 */
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

/**
 * FUNCTION: meanMatrix
 * INPUT: A matrix m whose size is (MxN).
 * REQUIREMENTS: None.
 * OUTPUT: A matrix mean whose size is (1xN).
 *      Example: 
 *              1 0 3                      
 *          m = 4 5 -1 Size (2x3)   mean = 5/2 5/2 2/2 Size (1x3)
 * COST: O(MxN)
 */
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

/**
 * FUNCTION: multiplyNumberAndMatrix
 * INPUT:
 *      m1 (Matrix, MxN).
 *      n (float).
 * REQUIREMENTS: None.
 * OUTPUT: The matrix m, that is n*m1.
 * COST: O(MxN)
 */
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

/**
 * FUNCTION: MSEMatrix
 * INPUT:
 *      m1 (Matrix MxN).
 *      m2 (Matrix MxN).
 * REQUIREMENTS: The sizes of m1 and m2 must be equals.
 * OUTPUT: MSE (float).
 *      Example:
 *               1 2 5        0 3 6
 *          m1 = 0 1 4   m2 = 2 1 3   MSE(m1, m2) = 8/6
 * COST: O(MxN)
 */
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

/**
 * FUNCTION: derivMSEMatrix
 * INPUT:
 *      m1 (Matrix MxN).
 *      m2 (Matrix MxN).
 * REQUIREMENTS: The sizes of m1 and m2 must be equals.
 * OUTPUT: The matrix m (MxN). 
 *      Example:
 *               1 2 5        0 3 6                     1 -1 -1
 *          m1 = 0 1 4   m2 = 2 1 3   m = MSE(m1, m2) = -2 0 1
 * COST: O(MxN)
 */
void derivMSEMatrix(Matrix *m, Matrix m1, Matrix m2) {
    subtractMatrix(m, m1, m2);
}

/**
 * FUNCTION: minMaxMatrix
 * INPUT: A matrix (MxN).
 * REQUIREMENTS: None.
 * OUTPUT: min (float) and max (float).
 * COST: O(MxN)
 */
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

/**
 * FUNCTION: normalizationMatrix
 * INPUT: A matrix (MxN), min (float) and max (float).
 * REQUIREMENTS: None.
 * OUTPUT: The matrix normalized.
 * COST: O(MxN)
 */
void normalizationMatrix(Matrix *m, float min, float max) {
    float dif;

    dif = max - min;
    for (int i = 0; i < m->size_row; i++) {
        for (int j = 0; j < m->size_col; j++) {
            FastMCMatrix(m, i, j, (FastCCMatrix(*m, i, j) - min) / dif);
        }
    }
}

/**
 * FUNCTION: denormalizeMatrix
 * INPUT: A matrix (MxN), min (float) and max (float).
 * REQUIREMENTS: None.
 * OUTPUT: The matrix denormalized.
 * COST: O(MxN)
 */
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

/**
 * FUNCTION: suffleRowsMatrix
 * INPUT: A matrix (MxN).
 * REQUIREMENTS: The number of rows of the matrix > 1.
 * MODIFIES: The matrix.
 * OUTPUT: Other matrix, decisions.
 * COST: O(Cubic)
 */
void suffleRowsMatrix(Matrix *m, Matrix *decisions) {
    if (numberRows(*m) <= 1) {
        errorMatrix("The matrix cannot be suffled because it has fewer that two rows.");
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

/**
 * FUNCTION: sortRowsMatrix
 * INPUT: A matrix and the decision (Matrix).
 * REQUIREMENTS: 
 *      m (MxN).
 *      decisions (M/2x2)
 * MODIFIES: The matrix.
 * COST: O(M/2)
 */
void sortRowsMatrix(Matrix *m, Matrix decisions) {
    for (int i = 0; i < numberRows(decisions); i++) {
        swapRow(m, FastCCMatrix(decisions, i, 0), FastCCMatrix(decisions, i, 1));
    }
}

/**
 * FUNCTION: cutMatrix
 * INPUT: A matrix, m (MxN) and a number.
 * REQUIREMENTS: 0 < number (n) < M.
 * OUTPUTS: Two matrix whose union of rows is m.
 *      In m1 there are n rows of m and in
 *      m2 there are the remaining rows of m.
 * COST: O(MxN)
 */
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

/**
 * FUNCTION: showMatrix
 * INPUT: A matrix.
 * REQUIREMENTS: None.
 * OUTPUT: Show the matrix.
 */
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

/**
 * FUNCTION: writeMatrix
 * INPUT:
 *      f (FILE binary of floats).
 *      m (Matrix).
 * REQUIREMENTS: None.
 * MODIFIES: The matrix m, is saved in file f.
 *      And the boolean is the error.
 */
void writeMatrix(FILE *f, bool *error, Matrix m) {
    float sr, sc;
    
    sr = (float) (m.size_row);
    sc = (float) (m.size_col);
    if (fwrite(&sr, sizeof(float), 1, f) != 1 || fwrite(&sc, sizeof(float), 1, f) != 1) {
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

/**
 * FUNCTION: readMatrix
 * INPUT:
 *      f (FILE *).
 * REQUIREMENTS: None.
 * MODIFIES: The matrix m, is read from file f.
 *      And the boolean is the error.
 */
void readMatrix(Matrix *m, FILE *f, bool *error) {
    float sr, sc;

    if (fread(&sr, sizeof(float), 1, f) != 1 || fread(&sc, sizeof(float), 1, f) != 1) {
        *error = true;
    }
    else {
        m->size_row = (unsigned short) (sr);
        m->size_col = (unsigned short) (sc);
        m->transpose = !(sr <= MAX_ROWS && sc <= MAX_COLUMNS) && (sr <= MAX_COLUMNS && sc <= MAX_ROWS);
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
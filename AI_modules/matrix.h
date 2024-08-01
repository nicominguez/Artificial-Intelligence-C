#ifndef _MATRIX_H
#define _MATRIX_H

/**
 * MODULE: matrix
 * FILE: matrix.h
 * VERSION: 1.0.0
 * HISTORICAL: Created by Eloy Urriens Arpal on 7/7/2024
 * DESCRIPTION: This module can operate with matrix of floats.
 * CC: BY SA
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_ROWS 100 // MAX 2^16 - 1
#define MAX_COLUMNS 16

typedef struct {
    float val[MAX_ROWS][MAX_COLUMNS];
    unsigned short size_row;
    unsigned short size_col;
    bool transpose;
} Matrix;

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
 * COST: O(sr*sc)
 */
void newRandomNormMatrix(Matrix *, unsigned short, unsigned short);

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
void newRandomMatrix(Matrix *, unsigned short, unsigned short);

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
void MCMatrix(Matrix *, unsigned short, unsigned short, float);

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
void FastMCMatrix(Matrix *, unsigned short, unsigned short, float);

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
float CCMatrix(Matrix, unsigned short, unsigned short);

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
float FastCCMatrix(Matrix, unsigned short, unsigned short);

/**
 * FUNCTION: numberRows
 * INPUT: A matrix.
 * REQUIREMENTS: None
 * OUTPUT: The number of rows.
 * COST: O(1)
 */
unsigned short numberRows(Matrix);

/**
 * FUNCTION: numberColumns
 * INPUT: A matrix.
 * REQUIREMENTS: None
 * OUTPUT: The number of columns.
 * COST: O(1)
 */
unsigned short numberColumns(Matrix);

/**
 * FUNCTION: transposeMatrix
 * INPUT: A matrix, m.
 * REQUIREMENTS:
 *      number of the rows <= MAX_COLUMNS
 *      number of the columns <= MAX_ROWS
 * MODIFIES: m = m' (transpose)
 * COST: O(1)
 */
void transposeMatrix(Matrix *);

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
void addMatrix(Matrix *, Matrix, Matrix);

/**
 * FUNCTION: subtractMatrix
 * INPUT:
 *      m1 (Matrix MxN).
 *      m2 (Matrix MxN).
 * REQUIREMENTS: The sizes equals.
 * OUTPUT: The matrix m, that is m1-m2.
 * COST: O(MxN)
 */
void subtractMatrix(Matrix *, Matrix, Matrix);

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
void multiplyMatrix(Matrix *, Matrix, Matrix);

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
void multiplyNumbersMatrix(Matrix *, Matrix, Matrix);

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
void meanMatrix(Matrix *, Matrix);

/**
 * FUNCTION: multiplyNumberAndMatrix
 * INPUT:
 *      m1 (Matrix, MxN).
 *      n (float).
 * REQUIREMENTS: None.
 * OUTPUT: The matrix m, that is n*m1.
 * COST: O(MxN)
 */
void multiplyNumberAndMatrix(Matrix *, Matrix, float);

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
float MSEMatrix(Matrix, Matrix);

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
void derivMSEMatrix(Matrix *, Matrix, Matrix);

/**
 * FUNCTION: minMaxMatrix
 * INPUT: A matrix (MxN).
 * REQUIREMENTS: None.
 * OUTPUT: min (float) and max (float).
 * COST: O(MxN)
 */
void minMaxMatrix(float *, float *, Matrix);

/**
 * FUNCTION: normalizationMatrix
 * INPUT: A matrix (MxN), min (float) and max (float).
 * REQUIREMENTS: None.
 * OUTPUT: The matrix normalized.
 * COST: O(MxN)
 */
void normalizationMatrix(Matrix *, float, float);

/**
 * FUNCTION: denormalizeMatrix
 * INPUT: A matrix (MxN), min (float) and max (float).
 * REQUIREMENTS: None.
 * OUTPUT: The matrix denormalized.
 * COST: O(MxN)
 */
void denormalizeMatrix(Matrix *, float, float);

/**
 * FUNCTION: suffleRowsMatrix
 * INPUT: A matrix (MxN).
 * REQUIREMENTS: The number of rows of the matrix > 1.
 * MODIFIES: The matrix.
 * OUTPUT: Other matrix, decisions.
 * COST: O(Cubic)
 */
void suffleRowsMatrix(Matrix *m, Matrix *decisions);

/**
 * FUNCTION: sortRowsMatrix
 * INPUT: A matrix and the decision (Matrix).
 * REQUIREMENTS: 
 *      m (MxN).
 *      decisions (M/2x2)
 * MODIFIES: The matrix.
 * COST: O(M/2)
 */
void sortRowsMatrix(Matrix *m, Matrix decisions);

/**
 * FUNCTION: cutMatrix
 * INPUT: A matrix, m (MxN) and a number.
 * REQUIREMENTS: 0 < number (n) < M.
 * OUTPUTS: Two matrix whose union of rows is m.
 *      In m1 there are n rows of m and in
 *      m2 there are the remaining rows of m.
 * COST: O(MxN)
 */
void cutMatrix(Matrix *, Matrix *, Matrix, unsigned int);

/**
 * FUNCTION: showMatrix
 * INPUT: A matrix (MxN).
 * REQUIREMENTS: None.
 * OUTPUT: Show the matrix.
 */
void showMatrix(Matrix);

/**
 * FUNCTION: writeMatrix
 * INPUT:
 *      f (FILE binary of floats).
 *      m (Matrix).
 * REQUIREMENTS: None.
 * MODIFIES: The matrix m, is saved in file f.
 *      And the boolean is the error.
 */
void writeMatrix(FILE *f, bool *, Matrix);

/**
 * FUNCTION: readMatrix
 * INPUT:
 *      f (FILE *).
 * REQUIREMENTS: None.
 * MODIFIES: The matrix m, is read from file f.
 *      And the boolean is the error.
 */
void readMatrix(Matrix *, FILE *f, bool *);

#endif
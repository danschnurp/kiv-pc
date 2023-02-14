#ifndef _MATRIX_H
#define _MATRIX_H
/**
 * @file matrix.h
 */

/**
 * @brief struktura matice
 * - řádky , sloupce
 * - hodnoty
 */
typedef struct {
  int rows, cols;
  int *items;
} matrix;
/**
 * @brief vytvoří matici
 * @param rows počet řádků
 * @param cols počet sloupců
 * @param val hodnota
 * @return matice
 */
matrix *create_matrix(int rows, int cols, int val);
/**
 * @brief uvolní paměť zabranou maticí
 * @param m matice
 */
void free_matrix(matrix **m);
/**
 * @brief vybere hodnotu z matice
 * @param m matice
 * @param rows počet řádků
 * @param cols počet sloupců
 * @return hodnota
 */
int get_item(matrix *m, int row, int col);
/**
 * @brief nastaví hodnotu v matici
 * @param m matice
 * @param rows počet řádků
 * @param cols počet sloupců
 * @param val hodnota
 */
void set_item(matrix *m, int row, int col, int val);
/**
 * @brief vypíše matici (pro testovací účely)
 * @param m matice
 */
void print_matrix(matrix *m);
#endif

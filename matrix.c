/**
 * @file matrix.c
 */
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
/**
 * @brief vytvoří matici
 * @param rows počet řádků
 * @param cols počet sloupců
 * @param val hodnota
 * @return matice
 */
matrix *create_matrix(int rows, int cols, int val) {
  int i;
  matrix *temp = (matrix *) malloc(sizeof(matrix));
  if (!temp) return NULL;
  
  temp->rows = rows;
  temp->cols = cols;
  temp->items = (int *) malloc(rows * cols * sizeof(int));
  if (!temp->items) {
    free(temp);
    return NULL;
  }
  
  for (i = 0; i < rows * cols; i++) 
    ((int *) temp->items)[i] = val;
  
  return temp;
}
/**
 * @brief uvolní paměť zabranou maticí
 * @param m matice
 */
void free_matrix(matrix **m) {
  if (!*m) return;
  
  free((*m)->items);
  free(*m);
  *m = NULL;
}
/**
 * @brief vybere hodnotu z matice
 * @param m matice
 * @param rows počet řádků
 * @param cols počet sloupců
 * @return hodnota
 */
int get_item(matrix *m, int row, int col) {
  if (!m) return 0;
  if (row >= m->rows || row < 0) return 0;
  if (col >= m->cols || col < 0) return 0;
  
  return m->items[row * m->cols + col];
}
/**
 * @brief nastaví hodnotu v matici
 * @param m matice
 * @param rows počet řádků
 * @param cols počet sloupců
 * @param val hodnota
 */
void set_item(matrix *m, int row, int col, int val) {
  if (!m) return;
  if (row >= m->rows || row < 0) return; 
  if (col >= m->cols || col < 0) return;
  
  m->items[row * m->cols + col] = val;
}
/**
 * @brief vypíše matici (pro testovací účely)
 * @param m matice
 */
void print_matrix(matrix *m) {
  int i, j;
  if (!m) return;
  
  for (i = 0; i < m->rows; i++) {
    printf("| ");    
    for (j = 0; j < m->cols; j++)
      printf("%d ", get_item(m, i, j));
    printf("|\n");
  }
}
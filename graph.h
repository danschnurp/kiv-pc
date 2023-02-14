#ifndef _GRAPH_H
#define _GRAPH_H

/**
 *	@file graph.h
 */

#include <stdlib.h>
#include "matrix.h"
#include "transmitter.h"
#include "stack.h"
/**
 * @brief vytvoří graf kolizí
 * @param t pole vysílačů
 * @param amount_transmit počet vysílačů
 * @param par_radius radius vysílačů
 * @return matice sousedů
 */
matrix *crate_graph_collisions(transmitters **t, int amount_transmit, int par_radius);
/**
 * @brief rozhodne zda je možno přiřadit danou frekvenci
 * @param colisions graf kolizí v matici
 * @param result pole vysílačů
 * @param amount_transmit počet vysílačů
 * @param pom aktuální vysílač vytáhnutý ze zásobníku
 * @return 0 když se frekvence vysílačů rovnají nebo 1 když se dá přiřadit
 */
int assignable(matrix *colisions, transmitters **result, int amount_transmit, transmitters *pom);
/**
 * @brief přiřadí frekvenci vysílači
 * @param colisions graf kolizí v matici
 * @param result pole vysílačů
 * @param amount_transmit počet vysílačů
 * @param max_freqs maximální index pole frekvencí
 * @param frequencies pole frekvencí
 * @param i aktuální index v poli vysílačů
 * @return 0 když dojdou frekvence nebo 1 když se obarví celá komponenta grafu
 */
int assign_component(matrix *colisions, transmitters **result, int amount_transmit, int max_freqs, int *frequencies, int i);
/**
 * @brief přiřadí frekcence všem dodaným vysílačům
 * @param colisions graf kolizí v matici
 * @param tr pole vysílačů
 * @param amount_transmit počet vysílačů
 * @param max_freqs maximální index pole frekvencí
 * @param frequencies pole frekvencí
 * @return pole vysílačů s přiřazenými frekvencemi nebo NULL když dojdou frekvence
 */
transmitters** assign_all(matrix *colisions, transmitters **tr, int amount_transmit, int max_freqs, int *frequencies);
#endif
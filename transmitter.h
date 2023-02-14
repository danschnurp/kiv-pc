#ifndef TRANSMITTER_H
#define TRANSMITTER_H

/**
 *	@file transmitter.h
 */

/**
 * @brief struktura souřadnic vysílačů
 * - identifikační číslo
 * - souřadnice x
 * - souřadnice y
 * - frekvence
 * - informace zda byl vysílač v zásobníku (0 = ne, 1 = ano)
 */
typedef struct {
    int id;
    double x;
    double y;
    int freq_id;
    int staged;
}transmitters;
/**
* @brief uvolní paměť stuktury vysílač
* @param tr pole vysílačů
* @param countrer_tr počet vysílačů
 */
void free_transmitters(transmitters ** tr, int countrer_tr);

#endif

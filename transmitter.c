/**
 *	@file transmitter.c
 */

#include <stdlib.h>
#include "transmitter.h"

/**
* @brief uvolní paměť stuktury vysílač
* @param tr pole vysílačů
* @param countrer_tr počet vysílačů
*/
void free_transmitters(transmitters ** tr, int countrer_tr) {
	int i;
    if(!tr) return;
    for(i = 0; i < countrer_tr; i++) {
        free(tr[i]);

    }

}

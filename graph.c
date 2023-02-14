#include "graph.h"

/**
 *	@file graph.c
 */

/** zásobník */
static stack *stck = NULL;
/**
 * @brief vytvoří graf kolizí
 * @param t pole vysílačů
 * @param amount_transmit počet vysílačů
 * @param par_radius radius vysílačů
 * @return matice sousedů
 */
matrix *crate_graph_collisions(transmitters **tr, int amount_transmit, int par_radius) {
    double distance;
	int i;
	int j;
    matrix *graph = create_matrix(amount_transmit,amount_transmit, 0);
    transmitters **tm = tr;
    par_radius = par_radius * 2;
    par_radius = par_radius * par_radius;

    for(i = 0; i < amount_transmit-1; i++) {
        for(j = i+1; j < amount_transmit; j++) {
            distance = (tm[i]->x - tm[j]->x) * (tm[i]->x - tm[j]->x) + (tm[i]->y - tm[j]->y) * (tm[i]->y - tm[j]->y);
            if(par_radius >= distance) {
                set_item(graph, i, j, 1);
                set_item(graph, j, i, 1);
            }
        }
    }
    return graph;
}
/**
 * @brief rozhodne zda je možno přiřadit danou frekvenci
 * @param colisions graf kolizí v matici
 * @param result pole vysílačů
 * @param amount_transmit počet vysílačů
 * @param pom aktuální vysílač vytáhnutý ze zásobníku
 * @return 0 když se frekvence vysílačů rovnají nebo 1 když se dá přiřadit
 */
int assignable(matrix *colisions, transmitters **result, int amount_transmit, transmitters *pom) {
	int j;
    
    for (j = 0; j < amount_transmit; j++) {
        if (get_item(colisions, pom->id, j) == 1) {
            if(result[j]->freq_id == 0 && result[j]->staged == 0) {
                result[j]->staged = 1;
                push(&stck, result[j]);
            }
            if(result[j]->freq_id == pom->freq_id) {
                return 0;
            }


        }
    }
    return  1;
}
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
int assign_component(matrix *colisions, transmitters **result, int amount_transmit, int max_freqs, int *frequencies, int i) {
    transmitters *pom = NULL;
    int freq_num = 0;
    
    push(&stck, result[i]);
    while(stck != NULL) {
        pom = pop(&stck);


        do {
            if (freq_num > max_freqs) {
                return 0;
            }
            pom->freq_id = frequencies[freq_num];

            freq_num++;
        }while (!assignable(colisions, result, amount_transmit, pom));


        result[pom->id] = pom;
        freq_num = 0;

        }
    return 1;
}
/**
 * @brief přiřadí frekcence všem dodaným vysílačům
 * @param colisions graf kolizí v matici
 * @param tr pole vysílačů
 * @param amount_transmit počet vysílačů
 * @param max_freqs maximální index pole frekvencí
 * @param frequencies pole frekvencí
 * @return pole vysílačů s přiřazenými frekvencemi nebo NULL když dojdou frekvence
 */
transmitters** assign_all(matrix *colisions, transmitters **tr, int amount_transmit, int max_freqs, int *frequencies) {
    int i;
    transmitters **result = tr;
    stck = create_stack();
	
    for (i = 0; i < amount_transmit; i++) {
        if (result[i]->freq_id > 0) {
            continue;
        }
        else {
           if(assign_component(colisions, result, amount_transmit, max_freqs, frequencies, i) == 0) {
               free_stack(&stck);
               return NULL;
           }
        }
    }
    free_stack(&stck);
    /** úspěšně přiřazené freq */
    return result;
}

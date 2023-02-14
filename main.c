/**
 * @name Řešení kolizí frekvencí sítě vysílačů
 * @name (Solving Collisions of Frequencies of Transmitters)
 *
 *	@file main.c
 *
 *	V tomto modulu se skládají dohromady všechny části projektu
 *	do jedné výsledné aplikace.
 *	Řeší se zde kontrola vstupních údajů z příkazové řádky a
 *	výpis výsledků
 *
 *	Dialekt: ANSI C
 *
 *	@author Daniel Schnurpfeil
 * 	@version 1.00-2019-11-09
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transmitter.h"
#include "graph.h"

#define LINE_LENGTH 26
/** počet vysílačů */
static int trasniters_count = 0;
/** pole vysílačů */
transmitters **tr = NULL;
/** radius vysílačů */
static int radius = 0;
/** pole frekvencí */
static int *frequencies = 0;
/** počet frekvencí */
static int frequencies_count = 0;

/**
 * void head()
 *
 * @brief Vypíše hlavičku programu do konzole v pořadí v Angličtině:
                - název práce
                - verze a rok
                - název předmětu
                - jméno autora

 *
 */
void head() {
	printf("Solving Collisions of Frequencies of Transmitters\n");
	printf("Version 1.0 - 2019\n");
	printf("Semestral work 'programming in C' \n");
	printf("Author: Daniel Schnurpfeil \n");


}
/**
 * void hepl()
 *
 * @brief Vypíše možnosti zadání argumentu.
 *
*/
void help() {
	printf("Usage:\n freq.exe <filename>\n\n");
	printf("Example:\n freq.exe vysilace-25.txt  \n\n");
}
/**
 * @brief spočte délku pole pro vysílače
 * @param file_name jméno souboru s vysílači a počty frekvencí a vysílačů
 * @param counter_freq počet frekvencí
 * @param counter počet vysílačů
 */
void count_transmitters_frequncies(char* file_name,int *counter_freq,int *counter) {
    int frequencies_sum, frequency1, id;
    double  coord_x, coord_y;
    FILE *file = fopen((file_name), "r");
    char line[LINE_LENGTH + 1] ;


    if (file == NULL) {
        perror("ERR#1: Missing argument!");
    }
    else {
        while (!feof(file)) {
            fgets(line, LINE_LENGTH, file);
            /**  zkontroluje zda se jedná o souřadnice vysílačů */
            if (sscanf(line, "%d %lf %lf", &id, &coord_x, &coord_y) == 3 && !feof(file)) {
                (*counter)++;
            }
            else if(sscanf(line, "%d %d", &frequencies_sum, &frequency1) == 2 && !feof(file)) {
                (*counter_freq)++;
            }

        }
        fclose(file);
    }

}
/**
 * @brief Zkontroluje vstup argumentu z příkazové řádky
 * @arg argc
 *
*/
void check_input(int argc) {
	if (argc < 1) {
        head();
		help();
		printf("ERR#1: Missing argument!\n");
	  }

}

/**
 * @brief Načte data ze souboru a uloží je deklarovaných globálních proměnných.
 * @param file_name Jméno souboru.
 * @return kód (číslo) o úspěchu či neúspěchu
 */
int load_file(char* file_name) {
  int scan_radius, frequencies_sum, frequency1 = 0, id = 0;
  double coord_x = 0,coord_y = 0;

  char line[LINE_LENGTH] ;
  /** neptřebné výpisy */
  char noneeded[] = { "Available frequencies:\n" };
  char noneeded2[] = { "Transmission radius:\n" };
  char noneeded3[] = { "Transmitters:\n" };

  FILE *file = fopen((file_name), "r");

  if (file == NULL) {
		perror("ERR#1: Missing argument!");
		return EXIT_FAILURE;
	}

  else {

        while (!feof(file)) {

            fgets(line, LINE_LENGTH, file);
            /** zjištění zda je na přečtené řádce nepotřebný výpis */
            if(strncmp(line, noneeded, sizeof (noneeded)) == 0 || strncmp(line, noneeded2, sizeof (noneeded2)) == 0
             || strncmp(line, noneeded3, sizeof (noneeded3)) == 0) {
                continue;
            }
            else {

                /** načítání souřadnic */
                if (sscanf(line, "%d %lf %lf", &id, &coord_x, &coord_y) == 3 && !feof(file)) {
                    trasniters_count = id;
                    tr[trasniters_count] = (transmitters *) malloc(sizeof(transmitters));
                    tr[trasniters_count]->x = coord_x;
                    tr[trasniters_count]->y = coord_y;
                    tr[trasniters_count]->id = id;
                    continue;

                }
                /** načírání frekvencí */
                else if (sscanf(line, "%d %d", &frequencies_sum, &frequency1) == 2 && !feof(file)) {
                    frequencies_count = frequencies_sum;
                    frequencies[frequencies_count] = frequency1;
                    continue;
                }
                /** tady se načte radius */
                else if (sscanf(line, "%d", &scan_radius) == 1 && !feof(file)) {
                    radius = scan_radius;
                    continue;

                }

            }
        }
        fclose(file);
	}
  return EXIT_SUCCESS;
}

/**
 * @brief hlavní program
 * @param argc
 * @param argv
 * @return vrátí kód ukončení programu úspěšný nebo neúspěšný
 */
int main(int argc, char* argv[]) {
	char* file_name = argv[1];
    int counter_tr = 0;
    int counter_freq = 0;
    int i = 0;
    matrix *graph = 0;

    check_input(argc);
    count_transmitters_frequncies(file_name, &counter_freq, &counter_tr);
    /** alokace místa v paměti pro pole frekvencí a pole vysílačů */
    frequencies = (int*) malloc(counter_freq *sizeof(int));
    tr = (transmitters **) malloc(counter_tr * sizeof(transmitters *));

    load_file(file_name);

    graph = crate_graph_collisions(tr, counter_tr, radius);

     tr = assign_all(graph, tr, counter_tr, counter_freq, frequencies);

     /** vypíše výsledek nebo hlášku neexistujícího řešení */
     if(tr != NULL) {
         for (i = 0; i <= trasniters_count; i++) {
             printf("%d %d\n", tr[i]->id, tr[i]->freq_id);
         }
     }
     else {
         printf("ERR#3: Non-existent solution!\n");
     }

     /** uvolnění místa v paměti */
    free_transmitters(tr, counter_tr);
    free_matrix(&graph);
    return EXIT_SUCCESS;
}

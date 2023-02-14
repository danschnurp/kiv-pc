#ifndef _STACK_H
#define _STACK_H
/**
 *	@file stack.h
 */

#include <stdio.h>
#include "transmitter.h"


/**
 * @brief struktura zásobník
 * - pole vysílačů
 * - odkaz na sebe (spojový zásobník)
 */
typedef struct {
	transmitters* data;
	struct stack* next;
} stack;
/**
 * @brief vytvoří zásobník vysílačů
 * @return zásobník vysílačů
 */
stack *create_stack();
/**
 * @brief uvolní paměť alokovanou zásobníkem
 * @param s
 */
int free_stack(stack **s);
/**
 * @brief vloží položku do zásobníku
 * @param s
 * @param item položka
 * @return celé číslo nebo nemusí nic, ale radši celé číslo
 */
int push(stack **s, transmitters *item);
/**
 * @brief vytáhne prvek ze zásobníku
 * @param s
 * @return vysílač
 */
transmitters *pop(stack **s);
#endif

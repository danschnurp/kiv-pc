#include <stdlib.h>
#include "stack.h"
#define RET_ERR 0
#define RET_OK 1

/**
 *	@file stack.c
 */

/**
 * @brief vytvoří zásobník vysílačů
 * @return zásobník vysílačů
 */
stack *create_stack() {
  stack *temp = NULL;
  return temp;
}
/**
 * @brief vloží položku do zásobníku
 * @param s
 * @param položka
 * @return celé číslo nebo nemusí nic, ale radši celé číslo
 */
int push(stack **s, transmitters *item) {
    stack *newstck = malloc(sizeof(transmitters));
    if(newstck == NULL) {
        printf("%s\n", "ERR#2: Out of memory!");
        return RET_ERR;
    }
	newstck->data =  item;
    if(*s == NULL) {
        *s = newstck;
        newstck->next = NULL;
    }
    else {
        newstck->next = (struct stack *) *s;
        *s = newstck;
    }
	return RET_OK;
}

/**
 * @brief vytáhne prvek ze zásobníku
 * @param s
 * @return vysílač
 */
transmitters *pop(stack **s) {
	transmitters *item;
	stack *sp;
	if(!s) return NULL;

    item = (*s)->data;
	sp = *s;
    if((*s)->next != NULL) {
        *s = (stack *) (*s)->next;
        free(sp);
    }
    else {
        free(sp);
        *s = NULL;

    }
	return item;
}
/**
 * @brief uvolní paměť alokovanou zásobníkem
 * @param s
 */
int free_stack(stack **s) {
    if(!*s) return RET_ERR;
    while(*s) {
        pop(s);
    }
    return RET_OK;
}
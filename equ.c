#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct equ {
	int coefficient;
	short exponent;
	struct equ *next;
} equ;

void *equAlloc(int coefficient, short exponent){
	equ *out = malloc(sizeof(equ));
	out->coefficient = coefficient;
	out->exponent = exponent;
	out->next = NULL;
	return out;
}

void equAppend(equ *head, equ *new){
	if (head->next == NULL)
		head->next = new;
	else
		equAppend(head->next, new);
}

void equPrint(equ *head){
	printf("(%dX^%d)", head->coefficient, head->exponent);
	if (head->next != NULL){
		printf(" + ");
		equPrint(head->next);
	}else 
		printf("\n");
}

void equFree(equ *head){
	if (head->next != NULL)
		equFree(head->next);
	free(head);
}

float equSubstitue(equ *head, float x){
	float total = 0;
	total += head->coefficient * pow(x, head->exponent); 
	if (head->next != NULL)
		total += equSubstitue(head->next, x);
	return total;
}

equ *differatiate(equ *head){
	equ *out = equAlloc(head->coefficient * head->exponent, head->exponent - 1);
	if (head->next != NULL)
		equAppend(out, differatiate(head->next));
	return out;
}

int main(){
	equ *y = equAlloc(2, 2);
	equ *f = equAlloc(1, 1);
	equAppend(y, f);
	printf("y = ");
	equPrint(y);

	equ *dydx = differatiate(y);
	printf("dy/dx = ");
	equPrint(dydx);

	equFree(y);
	equFree(dydx);
}


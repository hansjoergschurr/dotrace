#include <stdio.h>
#include "dotrace.h"

int square(int a) {
	return a * a;
}

void main(void) {
	int a = 2; 
	printf("%d\n", square(a));
}


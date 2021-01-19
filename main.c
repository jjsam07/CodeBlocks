#include <stdio.h>
#include <stdlib.h>
#define MAX_FACTORS 100	//Number of maximum factors


int factors[MAX_FACTORS];
int idx = 0;
int num = 1;
int quotient;

/*
*	Returns the greatest factor
*	excluding the number (num) itself.
*/
int greatestFactor(int num) {
	int diff;
	for(int i = 1; i < num; i++) {
		diff = num - i;
		if(diff == 1) {
			return num;
		} else if((num % diff) == 0) {
			return diff;
		}
	}
	return num;
}

/*
*	Returns the least factor
*	excluding 1 (one).
*/
int leastFactor(int num) {
	for(int i = 2; i < num; i++) {
		if((num % i) == 0) {
			return i;
		}
	}
	return 1;
}

int primeFactorization(int num) {
	int lf;
	while(num != 1) {
		lf = leastFactor(num);
		if (lf == 1) lf = num;
		printf("%d ", lf);
		num /= lf;
	}
	putc('\n', stdout);
	return 0;
}

int main()
{
	int num;
	printf("Enter a number: ");
	scanf("%d", &num);

	primeFactorization(num);

    return 0;
}

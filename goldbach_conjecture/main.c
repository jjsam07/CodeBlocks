#include <stdio.h>
#include <stdlib.h>
#define START 700
#define FINISH 1100

int isPrime(int num) {
	int i, lf = 1, gf, diff;
	for(i = 2; i < num; i++) {
		if((num % i) == 0) {
			lf = i;
			break;
		} else {
			lf = 1;
		}
	}

	for(i = 1; i < num; i++) {
		diff = num - i;
		if(diff == 1) {
			gf = num;
			break;
		} else if((num % diff) == 0) {
			gf = diff;
			break;
		} else {
			gf = num;
		}
	}

	if ((gf == num) && (lf == 1)) {
		return 0;
	} else {
		return 1;
	}

}

int next_prime(int num) {
	int next = num;
	while(1) {
		next++;
		if (isPrime(next) == 0) {
			return next;
		}
	}
	return 0;
}

int main()
{
	int i, addend, current_prime = 2;

	if (START % 2 != 0) {
		printf("Start with an even number!\n");
		return 0;
	}
	printf("Every even number greater than 2 is the sum of two primes:\n");
    for(i = START; i <= FINISH; i += 2) {
		while(1) {
			addend = i - current_prime;
			if(isPrime(addend) == 0) {
				printf("%d = %d + %d\n", i, current_prime, addend);
				current_prime = 2;
				break;
			}
			current_prime = next_prime(current_prime);
		}
    }
    return 0;
}

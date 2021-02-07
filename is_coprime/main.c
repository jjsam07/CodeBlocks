#include <stdio.h>
#include <stdlib.h>

int nextFactor(int num, int prev_factor) {
	for(int i = prev_factor + 1; i <= num; i++) {
		if((num % i) == 0) {
			return i;
		}
	}
	return prev_factor;
}

int rel_prime(int i, int j) {
	int i_factor = 1, j_factor = 1;

	while(1) {
		j_factor = nextFactor(j, j_factor);
		if (j_factor == nextFactor(j, j_factor)) {
			break;
		}
		if ((i % j_factor) == 0) {
			return 0;
		}
	}

	while(1) {
		i_factor = nextFactor(i, i_factor);
		if (i_factor == nextFactor(i, i_factor)) {
			break;
		}
		if ((j % i_factor) == 0) {
			return 0;
		}
	}

	return 1;
}

int main()
{
	int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    if (num1 <= 0 || num1 <= 0) {
		printf("Number must be positive\n");
		return 0;
    }

    if (num1 == num2) {
		printf("Numbers must be distinct\n");
		return 0;
    }

	if (rel_prime(num1, num2) == 1) {
		printf("%d and %d are relatively prime i.e. coprime\n", num1, num2);
		return 0;
	} else {
		printf("%d and %d are not relatively prime i.e. not coprime\n", num1, num2);
		return 0;
	}

    return 0;
}

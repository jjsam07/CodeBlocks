#include <stdio.h>
#include <stdlib.h>

int prime(int num) {
	int i, lf = 1, gf = 1, diff;
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

int main()
{
	int num;
	printf("Enter a number: ");
	scanf("%d", &num);

	if (num <= 0) {
		printf("Number must be positive\n");
		return 0;
	}

	if(prime(num) == 0) {
		printf("%d is prime\n", num);
	} else {
		printf("%d is not prime\n", num);
	}

    return 0;
}

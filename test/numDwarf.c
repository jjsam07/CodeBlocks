#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num, sum = 1, lf, prevLf, temp;
	float half;
	printf("Enter a number: ");
	scanf("%d", &num);

	if (num <= 0) {
		printf("Number cannot be negative or zero\n");
		return 0;
	}
	half = num / 2;
	temp = num;
	printf("Factors are: 1 ");
	while(num != 1) {
		for(int i = 2; i < num; i++) {
			if((num % i) == 0) {
				lf = i;
				break;
			} else {
				lf = 1;
			}
		}
		if (lf == 1) lf = num;
		num /= lf;
		if (prevLf != lf) {
			printf("%d ", lf);
			sum += lf;
			prevLf = lf;
		}
	}
	putc('\n', stdout);
	printf("Sum of factors: %d\n", sum);
	printf("Half of number: %f\n", half);
	if (sum > half) {
		printf("%d is DWARF\n", temp);
	} else {
		printf("%d is not DWARF\n", temp);
	}
    return 0;
}

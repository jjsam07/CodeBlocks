#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("WHILE LOOP 0\n");
    int start, step, end, i;

    printf("Enter three numbers (START STEP END): ");
    scanf("%d %d %d", &start, &step, &end);

    i = start;

    while(i <= end) {
		printf("%d\n", i);
		i += step;
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("DO WHILE LOOP 1\n");
    int i = 1;

	do {
		printf("%d\n", i);
		i += 2;
    } while(i < 100);

    return 0;
}

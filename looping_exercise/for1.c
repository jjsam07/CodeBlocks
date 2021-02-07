#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("FOR LOOP 1\n");
    int i;

	for(i = 1; i < 100; i += 2) {
		printf("%d\n", i);
    }

    return 0;
}

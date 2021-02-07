#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("WHILE LOOP 1\n");
    int i = 1;

	while(i < 100) {
		printf("%d\n", i);
		i += 2;
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num;
    printf("Input day in numeric form: ");
    scanf("%d", &num);

    if(num == 1) {
		printf("That day is a Monday.\nHave a nice day!\n");
	} else if (num == 2) {
		printf("That day is a Tuesday.\nHave a nice day!\n");
	} else if (num == 3) {
		printf("That day is a Wednesday.\nHave a nice day!\n");
	} else if (num == 4) {
		printf("That day is a Thursday.\nHave a nice day!\n");
	} else if (num == 5) {
		printf("That day is a Friday.\nHave a nice day!\n");
	} else if (num == 6) {
		printf("That day is a Saturday.\nHave a nice day!\n");
	} else if (num == 7) {
		printf("That day is a Sunday.\nHave a nice day!\n");
	} else {
		printf("INVALID INPUT\n");
	}

    return 0;
}

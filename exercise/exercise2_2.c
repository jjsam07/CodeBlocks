#include <stdio.h>
#include <stdlib.h>

int main()
{
	char letter;
    printf("Enter a letter: ");
    scanf("%c", &letter);

    if(letter >= 'a' && letter <= 'z') {
		printf("LOWER CASE\n");
	} else {
		printf("UPPER CASE\n");
	}

    return 0;
}

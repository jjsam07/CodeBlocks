#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a, b, c, temp;
    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b, &c);

	while(1) {
		if (a > b) {
			if (b > c) {
				printf("%d %d %d\n", a, b, c);
				break;
			} else if (b == c) {
				printf("%d %d %d\n", a, b, c);
				break;
			} else {
				temp = b;
				b = c;
				c = temp;
			}
		} else if (a == b) {
			if (b > c) {
				printf("%d %d %d\n", a, b, c);
				break;
			} else if (b == c) {
				printf("%d %d %d\n", a, b, c);
				break;
			} else {
				temp = b;
				b = c;
				c = temp;
			}
		} else {
			temp = a;
			a = b;
			b = temp;
		}
	}
    return 0;
}

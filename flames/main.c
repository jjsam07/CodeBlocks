#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
	char abbr_flames[6] = {'F', 'L', 'A', 'M', 'E', 'S'};
	char *flames[6] = {"Friends", "Lovers", "Angry", "Marriage", "Enemy", "Sweet"};
	char boy[100], girl[100];
	int common_boy = 0, common_girl = 0, result;

	printf("F.L.A.M.E.S\n\n");

    printf("Enter name of boy: ");
    gets(boy);
    printf("Enter name of girl: ");
    gets(girl);

	for(int i = 0; i < strlen(boy); i++) {
		if (isspace(boy[i]) != 0) continue;
		for(int j = 0; j < strlen(girl); j++) {
			if (tolower(boy[i]) == tolower(girl[j])) {
				common_boy++;
				break;
			}
		}
	}

	for(int i = 0; i < strlen(girl); i++) {
		if (isspace(girl[i]) != 0) continue;
		for(int j = 0; j < strlen(boy); j++) {
			if (tolower(girl[i]) == tolower(boy[j])) {
				common_girl++;
				break;
			}
		}
	}

	if (((common_boy + common_girl) % 6) == 0) {
		result = 6;
	} else {
		result = (common_boy + common_girl) % 6;
	}

	printf("\n%c = %s\n", abbr_flames[result-1], flames[result-1]);

    return 0;
}

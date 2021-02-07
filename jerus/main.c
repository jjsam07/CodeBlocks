#include <stdio.h>
#include <stdlib.h>

int reverseBits(unsigned int numOrig);
int main() {
    unsigned int num;
    printf("Enter number (decimal): ");
    scanf("%u", &num);
    reverseBits(num);
    return 0;
}

int reverseBits(unsigned int numOrig) {
    unsigned int numReversed = 0;
    int size = sizeof(numOrig)*8;
    printf("-----Original-----\n");
    printf("Binary: ");
    for(int i = 0; i < size; i++) {
        if (((i % 4) == 0) && (i != 0)) putc(' ', stdout);
        putc((numOrig & (1 << i)) ? '1':'0', stdout);
    }

    putc('\n', stdout);
    printf("Decimal: %u\n", numOrig);
    printf("Octal: %o\n", numOrig);
    printf("Hexadecimal: %X\n", numOrig);
    for(int i = 0; i < size; i++) {
        numReversed |= (numOrig & (0x80000000 >> i)) ? (1 << i):0;
    }
    printf("-----Reversed-----\n");
    printf("Binary: ");

    for(int i = 0; i < size; i++) {
        if (((i % 4) == 0) && (i != 0)) putc(' ', stdout);
        putc((numReversed & (1 << i)) ? '1':'0', stdout);
    }

    putc('\n', stdout);
    printf("Decimal: %u\n", numReversed);
    printf("Octal: %o\n", numReversed);
    printf("Hexadecimal: %X\n", numReversed);
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>

int main()
{

    char character;
    scanf("%c", &character);
    if(islower(character) != 0) {
        printf("%c is lower case\n")
    }
    ...
    char pieces[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                         {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                         {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                         {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    int i, j;
    for(i = 0; i< 8; i++) {
        for(j = 0; j < 8; j++) {
            putc(pieces[i][j], stdout);
        }
        putc('\n', stdout);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    char character0;
    scanf("%c", &character0);
    if (isalnum(character0) != 0) {
        printf("%c is alphanumeric\n", character0);
    }
    if (isalpha(character0) != 0) {
        printf("%c is alphabetic\n", character0);
    }
    if (iscntrl(character0) != 0) {
        printf("%c is control character\n", character0);
    }
    if (isdigit(character0) != 0) {
        printf("%c is decimal digit\n", character0);
    }
    if (isgraph(character0) != 0) {
        printf("%c has graphical representation using locale\n", character0);
    }
    if (islower(character0) != 0) {
        printf("%c is lowercase letter\n", character0);
    }
    if (isprint(character0) != 0) {
        printf("%c is printable\n", character0);
    }
    if (ispunct(character0) != 0) {
        printf("%c is a punctuation character\n", character0);
    }
    if (isspace(character0) != 0) {
        printf("%c is white-space\n", character0);
    }
    if (isupper(character0) != 0) {
        printf("%c is an uppercase letter\n", character0);
    }
    if (isxdigit(character0) != 0) {
        printf("%c is a hexadecimal digit\n", character0);
    }
    printf("%c to lowercase is %c\n", character0, tolower(character0));
    printf("%c to uppercase is %c\n", character0, toupper(character0));
    return 0;
}
*/

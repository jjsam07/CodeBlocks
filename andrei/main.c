#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(){
char b;
scanf("%c", &b);
char a[b];
for (int i = 0; i < b; i++){
    if (isalnum(a) != 0){
        printf("%d", a);
    }
}




 return 0;
}

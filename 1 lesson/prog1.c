#include <stdio.h>
#include <stdlib.h>

int main() {
    char digits[100];
    int k, m;
    printf("Write number, old system and new system\n");

    scanf("%s%d%d", digits, &k,&m);
    char *endptr;
    long long int number = strtol(digits, &endptr, k);
    if (*endptr != '\0') {
        printf("It is not number!");
        return 1;
    }
    lltoa(number, digits, m);

    printf("%s", digits);
    return 0;
}

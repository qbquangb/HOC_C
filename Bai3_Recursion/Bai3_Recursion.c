#include <stdio.h>
int sum(unsigned int n);

int main() {
    int number, result;

    printf("Enter a positive integer: "); // >= 0
    scanf("%d", &number);

    result = sum(number);

    printf("sum = %d", result);
    return 0;
}

int sum(unsigned int n) {
    if (n != 0)
        // sum() function calls itself
        return n + sum(n-1); 
    else
        return n;
}
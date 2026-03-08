/*
Truyền địa chỉ hay con trỏ
*/

#include <stdio.h>
typedef struct Complex
{
    double real;
    double imag;
} complex;

void addNumbers(complex c1, complex c2, complex* result); 

int main()
{
    complex c1, c2, result;

    printf("For first number,\n");
    printf("Enter real part: ");
    scanf("%lf", &c1.real);
    printf("Enter imaginary part: ");
    scanf("%lf", &c1.imag);

    printf("For second number, \n");
    printf("Enter real part: ");
    scanf("%lf", &c2.real);
    printf("Enter imaginary part: ");
    scanf("%lf", &c2.imag);

    addNumbers(c1, c2, &result); 
    printf("\nresult.real = %.2lf\n", result.real);
    printf("result.imag = %.2lf", result.imag);
    
    return 0;
}
void addNumbers(complex c1, complex c2, complex* result) 
{
     result->real = c1.real + c2.real;
     result->imag = c1.imag + c2.imag; 
}

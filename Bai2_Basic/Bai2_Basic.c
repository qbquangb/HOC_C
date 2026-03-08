#include <stdio.h>
#include <math.h>

void clear_input_buffer(void) {
    int ch;
    ch = getchar();
    while (ch != '\n') {
    ch = getchar();
    }
}

int main() {

	char k;
	printf("Nhap ki tu: ");
	fflush(stdout); // đảm bảo prompt được in ra trước khi chờ nhập (thường cần trong một số môi trường)
    clear_input_buffer(); // fflush(stdin);
	scanf("%c", &k);
	printf("\nki tu ban vua nhap %c\n", k);

	double x = 1.23;
	int a = 50, b = 100, c = 200;
	printf("xin chao\n");
	printf("so double x la %.5lf\n", x);
	printf("gia tri cua 3 bien a, b, c la %d %d %d\n", a, b, c);

	printf("Nhap gia tri cho bien a, b, c: ");
	fflush(stdout); // đảm bảo prompt được in ra trước khi chờ nhập (thường cần trong một số môi trường)
    clear_input_buffer(); // fflush(stdin);
	scanf("%d%d%d", &a, &b, &c);
	printf("\ngia tri cua 3 bien a, b, c la %d %d %d\n", a, b, c);

	double r, r2;
	r = (1.0 * a) / b;
	printf("ket qua r = %.10lf\n", r);
	r2 = ((double)a) / b;
	printf("ket qua r2 = %.10lf\n", r2);

	int d = 100, e = 200;
	int f;
	f = d < e; // Tất cả các số khác không là đúng (1), bằng 0 là sai (0)
	printf("gia tri cua f %d\n", f);

	// Logic operator bao gồm &&, ||, !

	double can;
	can = sqrt(16);
	printf("can bac 2 bang %.2lf\n", can);

    // Trong C, 0 là hệ 8, 0x là hệ 16
    int base8_, base16_;
    base8_ = 021; // 17
    base16_ = 0b00010001; // 17
    printf("%d\n", base8_);
    printf("%d\n", base16_);

    short a;
    long b;
    long long c;
    long double d;

    printf("size of short = %d bytes\n", sizeof(a));
    printf("size of long = %d bytes\n", sizeof(b));
    printf("size of long long = %d bytes\n", sizeof(c));
    printf("size of long double= %d bytes\n", sizeof(long double));

	double number, sum = 0;
	// the body of the loop is executed at least once
	do {
	printf("Enter a number: ");
	scanf("%lf", &number);
	sum += number;
	}
	while(number != 0.0);
	printf("Sum = %.2lf",sum);

	return 0;
}
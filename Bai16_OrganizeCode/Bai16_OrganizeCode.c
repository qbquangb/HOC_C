#include "source.h"
#include "math_lib.h"
#include <stdio.h>

void f();

double r = 10.0;
double x = 2.5;
double y = 7.5;

void f() { ++g_counter; }

int main()
{
	printf("Counter: %d\n", g_counter); // Output: Counter: 0
	incrementCounter();
	printf("Counter: %d\n", g_counter); // Output: Counter: 1
	f();
	printf("Counter: %d\n", g_counter); // Output: Counter: 2

	// Sử dụng các hằng số
	printf("PI: %.5lf\n", HSPI); // Output: Pi: 3.14159
	printf("Speed of Sound: %lf\n", HSSPEED_OF_SOUND); // Output: Speed of Sound: 343.2 m/s

	// sử dụng các hàm từ thư viện toán
	printf("Diện tích hình tròn: %lf\n", DienTichHinhTron(r));
	printf("Diện tích hình chữ nhật: %lf\n", DienTichChuNhat(x, y));
	printf("Chu vi hình tròn: %lf\n", ChuViHinhTron(r));

	return 0;
}
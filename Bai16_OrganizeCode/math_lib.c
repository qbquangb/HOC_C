#include "math_lib.h"

// Định nghĩa các hằng số
const double HSPI = 3.14159 ; //HS pi
const double HSSPEED_OF_SOUND = 343.2;	// Tốc độ âm thanh 343.2 m/s

double DienTichHinhTron(double r) {
	return HSPI * r * r;
}

double DienTichChuNhat(double x, double y) {
	return x * y;
}

double ChuViHinhTron(double r) {
	return 2 * HSPI * r;
}
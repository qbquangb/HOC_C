#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {
    size_t n = 10;
    int* arr = malloc(n * sizeof*arr);
    if (arr == NULL) {
        fprintf(stderr, "Cap phat that bai\n");
        return 1;
    }

    for (size_t i = 0; i < n; ++i) arr[i] = (int)i;

    // Muốn tăng kích thước:
    size_t new_n = 20;
    if (new_n <= SIZE_MAX / sizeof *arr) {
        int *tmp = realloc(arr, new_n * sizeof *arr);
        if (tmp == NULL) {
            // realloc thất bại, arr vẫn hợp lệ
            fprintf(stderr, "Realloc that bai, giu nguyen arr\n");
            free(arr);
            return 1;
        }
        arr = tmp;
    } else {
        fprintf(stderr, "Yeu cau kich thuoc qua lon\n");
        free(arr);
        return 1;
    }

    // Dùng arr...
    free(arr);  // giải phóng
    arr = NULL; // tránh dangling
    printf("run successfully.");
    return 0;
}
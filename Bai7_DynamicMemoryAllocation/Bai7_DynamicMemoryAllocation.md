Tuyệt — mình sẽ giải thích từ cơ bản đến chi tiết kèm ví dụ, lưu ý an toàn và các lỗi thường gặp khi làm việc với **cấp phát bộ nhớ động (dynamic memory allocation)** trong C.

# 1) Ý tưởng chung — Heap vs Stack

* Trong C có hai vùng nhớ chính: **stack** (biến cục bộ, tự động, kích thước nhỏ, tuổi thọ ngắn) và **heap** (bộ nhớ động do chương trình yêu cầu lúc chạy).
* Khi bạn cần một vùng nhớ có kích thước động (ví dụ số phần tử nhập vào lúc chạy) hoặc cần vùng nhớ tồn tại sau khi hàm trả về, dùng **heap** bằng các hàm cấp phát động.
* Về mức thấp: runtime/allocator (thư viện C) quản lý heap; khi cần nhiều hơn, allocator gọi hệ thống (ví dụ `sbrk`/`mmap`) để lấy thêm bộ nhớ từ OS. Allocator giữ metadata cho từng khối, có chiến lược phân chia/ghép khối (free lists, bins...) — chi tiết này tùy implement nhưng bạn không cần thay đổi trong code.

# 2) Các kiểu dữ liệu và chữ ký hàm chính

```c
#include <stdlib.h>

/* Các hàm chính */
void *malloc(size_t size);            // cấp phát size byte, không khởi tạo
void *calloc(size_t nmemb, size_t size); // cấp phát nmemb*size byte, được khởi tạo 0
void *realloc(void *ptr, size_t size);   // thay đổi kích thước khối ptr thành size byte
void free(void *ptr);                 // giải phóng khối đã cấp phát
```

* Tất cả trả về `void *`. Bạn gán về con trỏ kiểu phù hợp.
* Nếu `malloc`/`calloc`/`realloc` thất bại thì trả về `NULL`. Luôn kiểm tra.

# 3) `malloc()` — cấp phát thô, không khởi tạo

* `void *p = malloc(nbytes);`
* Trả về pointer tới `nbytes` byte liên tiếp, căn chỉnh đúng cho mọi kiểu cơ bản.
* Dữ liệu bên trong **không được khởi tạo** — có thể chứa “rác”.
* Nếu không đủ bộ nhớ -> trả `NULL`.

Ví dụ:

```c
int *a = malloc(n * sizeof *a); // dùng sizeof *a để tránh lỗi khi đổi kiểu
if (a == NULL) { /* xử lý lỗi */ }
```

Lưu ý an toàn: khi tính `n * sizeof *a` dùng `size_t` và kiểm tra tràn số nguyên:

```c
if (n > SIZE_MAX / sizeof *a) { /* overflow, từ chối */ }
```

# 4) `calloc()` — cấp phát + zero-initialize

* `void *q = calloc(nmemb, size);` tương đương về ý nghĩa là cấp `nmemb*size` byte **và** khởi tất cả byte = 0.
* Thường dùng khi muốn mảng bắt đầu bằng 0.
* `calloc` đôi khi nhanh hơn nếu allocator có cách tối ưu zeroing, nhưng không phải luôn.

Ví dụ:

```c
int *b = calloc(n, sizeof *b); // tất cả phần tử = 0
if (b == NULL) { /* xử lý lỗi */ }
```

# 5) `realloc()` — thay đổi kích thước khối đã cấp phát

* `void *r = realloc(ptr, new_size);`
* Trường hợp:

  * Nếu `ptr == NULL` → tương đương `malloc(new_size)`.
  * Nếu `new_size == 0` → hành vi có phần **implementation-defined**: có thể trả `NULL` và giải phóng ptr, hoặc trả con trỏ (mà vẫn phải gọi free). Vì vậy tốt nhất xử lý `new_size == 0` riêng.
  * Nếu không đủ chỗ tại chỗ, realloc có thể cấp khối mới, copy dữ liệu tối thiểu (min(old,new)), giải phóng khối cũ và trả pointer mới.
* **Quan trọng**: nếu `realloc` trả `NULL` do lỗi, khối `ptr` cũ **vẫn nguyên vẹn** — đừng gán trực tiếp `ptr = realloc(ptr, ...)` nếu bạn không muốn mất con trỏ cũ và gây rò rỉ; dùng biến tạm.

An toàn khi dùng realloc:

```c
int *tmp = realloc(arr, new_n * sizeof *arr);
if (tmp == NULL) {
    // xử lý lỗi: arr vẫn giữ dữ liệu cũ
} else {
    arr = tmp;
}
```

# 6) `free()` — giải phóng bộ nhớ

* `free(ptr);` — giải phóng khối được cấp phát bởi `malloc/calloc/realloc`.
* `free(NULL);` an toàn (không làm gì).
* Sau `free(ptr)`, con trỏ `ptr` trở thành **dangling pointer** — **không** dùng nữa. Thói quen tốt: `ptr = NULL;` sau khi free để tránh dùng nhầm.
* Không được `free`:

  * pointer không phải do `malloc/calloc/realloc` trả về (ví dụ pointer trỏ vào stack),
  * pointer đã được `free` trước đó (double free) — gây undefined behavior.

# 7) Mã minh họa đầy đủ, an toàn cơ bản

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n = 10;
    int *arr = malloc(n * sizeof *arr);
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
    return 0;
}
```

# 8) Các lỗi thường gặp & cách phòng tránh

* **Quên kiểm tra `NULL`** sau `malloc`/`calloc`/`realloc` → crash hoặc UB.
* **Tràn khi tính kích thước** (ví dụ `n * sizeof(type)` overflow) → cấp ít byte hơn mong đợi → buffer overflow. Kiểm tra trước bằng `if (n > SIZE_MAX / sizeof *p)`.
* **Sử dụng sau khi `free`** (use-after-free) → UB, dễ khai thác.
* **Double free** → UB, có thể gây crash hoặc lỗ hổng bảo mật.
* **Rò rỉ bộ nhớ (memory leak)**: cấp rồi không `free` → ứng dụng tiêu tốn bộ nhớ theo thời gian. Dùng công cụ kiểm tra (Valgrind, AddressSanitizer) để phát hiện.
* **Gán trực tiếp `ptr = realloc(ptr, ...)`**: khi realloc thất bại, bạn mất con trỏ gốc và gây rò rỉ. Dùng biến tạm.

# 9) Các mẹo, qui ước tốt

* Dùng `sizeof *p` thay vì `sizeof(type)` để khi thay đổi kiểu biến, bạn không quên sửa `sizeof`.

  ```c
  int *p = malloc(n * sizeof *p);
  ```
* Sau `free(p); p = NULL;` để an toàn nếu có vô tình gọi `free` hai lần.
* Ưu tiên `fgets()` + `strtol/strtod/sscanf` khi đọc input thay vì scanf trực tiếp, để tránh issues với buffer.
* Dùng công cụ debug: `valgrind --leak-check=full ./app` (Linux) hoặc Biến thể: AddressSanitizer (`-fsanitize=address`) khi xây dựng.
* Nếu cần cấp phát vùng nhớ có yêu cầu căn chỉnh đặc biệt, dùng `aligned_alloc` (C11) hoặc platform-specific APIs.

# 10) Cấp phát mảng 2 chiều (ví dụ hai cách)

* Cách 1: mảng con trỏ (mỗi hàng một `malloc`):

  ```c
  int **mat = malloc(rows * sizeof *mat);
  for (i = 0; i < rows; ++i)
      mat[i] = malloc(cols * sizeof *mat[i]);
  // giải phóng: free mỗi mat[i] rồi free(mat)
  ```
* Cách 2 (khuyến nghị khi cần hiệu năng và locality): một khối liên tiếp:

  ```c
  int *data = malloc(rows * cols * sizeof *data);
  int (*mat)[cols] = (int (*)[cols]) data; // nếu muốn truy cập mat[i][j]
  // hoặc truy cập data[i*cols + j]
  ```

# Tóm tắt ngắn gọn

* `malloc` để cấp phát, không khởi tạo; `calloc` cấp phát và zero-initialize; `realloc` điều chỉnh kích thước; `free` giải phóng.
* Luôn kiểm tra `NULL`, phòng overflow khi tính kích thước, tránh use-after-free/double-free, và giải phóng tài nguyên khi không dùng nữa.
* Dùng `sizeof *p` là thói quen an toàn; dùng biến tạm khi `realloc` để tránh mất con trỏ gốc.

---

Muốn mình viết mấy ví dụ cụ thể hơn (ví dụ quản lý array thay đổi kích thước với `realloc` theo kiểu "doubling", hoặc script kiểm tra rò rỉ đơn giản), mình sẽ viết luôn đoạn code tối ưu kèm giải thích. Bạn muốn ví dụ nào tiếp theo?

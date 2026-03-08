# Xử lý file trong C — giải thích từng bước, chi tiết và ví dụ

Dưới đây mình sẽ mô tả **từng bước** khi làm việc với file trong ngôn ngữ C (std I/O), từ mở file → đọc/ghi → định vị (seek) → đóng, kèm các hàm, lưu ý lỗi, ví dụ thực tế và những lỗi thường gặp.

---

## 1) Chuẩn bị: include header

```c
#include <stdio.h>
#include <stdlib.h>   // exit, malloc, free
#include <string.h>   // strncpy, memset
#include <errno.h>    // errno
```

---

## 2) Mở file — `fopen`

* Hàm: `FILE *fopen(const char *pathname, const char *mode);`
* Các mode thường dùng:

  * `"r"`  — mở để đọc (file phải tồn tại).
  * `"w"`  — mở để ghi (nếu tồn tại -> truncate; nếu không -> tạo mới).
  * `"a"`  — mở để append (ghi vào cuối file; tạo nếu không tồn tại).
  * `"r+"` — mở để đọc/ghi (file phải tồn tại).
  * `"w+"` — mở đọc/ghi, truncate hoặc tạo mới.
  * `"a+"` — mở đọc/ghi, ghi luôn append.
  * Thêm `"b"` cho binary: `"rb"`, `"wb"`, ... (trên Windows phải dùng `"b"` để tránh chuyển newline).
* Luôn **kiểm tra** kết quả:

```c
FILE *f = fopen("data.txt", "r");
if (f == NULL) {
    perror("fopen failed");
    exit(EXIT_FAILURE);
}
```

* Lưu ý: `fopen` trả `NULL` khi thất bại (không tồn tại file, không có quyền, v.v.). Dùng `perror` hoặc `strerror(errno)` để biết nguyên nhân.

---

## 3) Đọc dữ liệu

Các hàm đọc phổ biến:

* `int fgetc(FILE *stream);` — đọc 1 ký tự (trả `EOF` khi hết).
* `char *fgets(char *s, int size, FILE *stream);` — đọc 1 dòng (đến `\n` hoặc EOF), an toàn với giới hạn `size`.
* `size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);` — đọc `nmemb` phần tử mỗi phần tử `size` byte (dùng cho binary).
* `int fscanf(FILE *stream, const char *format, ...);` — tương tự `scanf` nhưng đọc từ file.

Ví dụ đọc dòng:

```c
char buf[256];
if (fgets(buf, sizeof buf, f) != NULL) {
    // buf chứa newline nếu có; thường strip newline nếu muốn
    buf[strcspn(buf, "\n")] = '\0';
}
```

Ví dụ đọc binary:

```c
struct Item { int id; double value; };
struct Item items[100];
size_t got = fread(items, sizeof items[0], 100, f);
if (got == 0 && ferror(f)) { /* xử lý lỗi */ }
```

---

## 4) Ghi dữ liệu

Các hàm ghi phổ biến:

* `int fputc(int c, FILE *stream);`
* `char *fputs(const char *s, FILE *stream);`
* `int fprintf(FILE *stream, const char *format, ...);`
* `size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);`

Ví dụ ghi text:

```c
fprintf(f, "Name: %s\nAge: %d\n", name, age);
```

Ví dụ ghi binary:

```c
struct Item it = { 1, 3.14 };
fwrite(&it, sizeof it, 1, f);
```

Luôn **kiểm tra** trả về `fwrite`/`fread` (số phần tử thực sự đọc/ghi).

---

## 5) Flush bộ đệm — `fflush`

* `int fflush(FILE *stream);` đảm bảo dữ liệu buffer được ghi xuống file (disk). `fflush(NULL)` flush tất cả output streams.
* Gọi `fflush` khi cần đảm bảo dữ liệu ổn (ví dụ trước `fork()`/trước crash-critical sections). `fclose` tự động flush.

---

## 6) Định vị trong file (random access)

* `int fseek(FILE *stream, long offset, int whence);`

  * `whence` có thể là `SEEK_SET` (từ đầu), `SEEK_CUR` (từ vị trí hiện tại), `SEEK_END` (từ cuối).
* `long ftell(FILE *stream);` trả vị trí hiện tại (offset từ đầu, kiểu long).
* `void rewind(FILE *stream);` về đầu file (tương đương `fseek(stream, 0, SEEK_SET)` và clear lỗi).
* `fseek`/`ftell` hữu dụng để đọc/ghi file theo offset, update record cụ thể.

Ví dụ: đọc thứ N-th record:

```c
fseek(f, n * sizeof(struct Item), SEEK_SET);
fread(&it, sizeof it, 1, f);
```

Lưu ý: với file lớn hơn 2GB, dùng `fseeko`/`ftello` (off_t) hoặc API platform-specific.

---

## 7) Kiểm tra EOF và lỗi

* `int feof(FILE *stream);` — kiểm tra EOF.
* `int ferror(FILE *stream);` — kiểm tra lỗi I/O.
* `void clearerr(FILE *stream);` — xóa cờ lỗi/EOF.
  Luôn kiểm tra kết quả `fread/fgets/fscanf` để quyết định có lỗi hay EOF.

---

## 8) Đóng file — `fclose`

* Gọi `fclose(f);` khi xong để giải phóng tài nguyên và flush buffer.
* `fclose` trả `0` khi thành công, EOF (-1) khi lỗi.
* Không dùng `FILE *` sau khi đã `fclose`.

---

## 9) File text vs file binary

* Text: có chuyển đổi newline (`\n` ↔ `\r\n` trên Windows nếu mở `"t"` được hỗ trợ), thường không dùng cho lưu dữ liệu nhị phân.
* Binary: dùng `"rb"`/`"wb"` để tránh chuyển đổi newline và lưu nguyên bytes.

---

## 10) Đọc/Ghi struct — portability issues

* Ghi struct bằng `fwrite(&s, sizeof s, 1, f)` và đọc lại tương tự nhanh nhưng:

  * Không portable giữa hệ có endianness khác nhau.
  * Không portable nếu struct có padding hoặc kích thước trường không cố định.
* Để portable, serialize từng trường theo định dạng chuẩn (ví dụ dùng `uint32_t` với `htonl`/`ntohl` cho network).

---

## 11) Tạo file tạm và bảo mật

* `tmpfile()` (tiêu chuẩn) tạo file tạm bị xóa tự động khi đóng.
* Tránh `tmpnam()` vì có thể có race condition; trên POSIX dùng `mkstemp()` (không phải chuẩn C) để tạo file tạm an toàn.

---

## 12) Các lỗi thường gặp & cách phòng tránh

* **Quên kiểm tra kết quả fopen / fread / fwrite / fgets** → crash hoặc dữ liệu sai.
* **Buffer overflow** khi dùng `fscanf("%s", buf)` không có width. Dùng `%Ns` hoặc `fgets`.
* **Dùng `fread`/`fwrite` mà không kiểm tra số phần tử trả về** → mất dữ liệu không phát hiện.
* **Trộn chế độ text và binary** (quên `"b"` trên Windows) → newline bị đổi.
* **Không đóng file** dẫn tới leak descriptor (hệ thống giới hạn số file mở).
* **Gọi `fseek` với offset không hợp lệ** (kiểm tra return).
* **Ghi struct trực tiếp cho mục đích cross-platform** — không portable.

---

## 13) Ví dụ thực tế — copy file (binary-safe)

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *in = fopen("input.bin", "rb");
    if (!in) { perror("fopen input"); return 1; }
    FILE *out = fopen("output.bin", "wb");
    if (!out) { perror("fopen output"); fclose(in); return 1; }

    unsigned char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, in)) > 0) {
        if (fwrite(buf, 1, n, out) != n) {
            perror("write error");
            fclose(in); fclose(out);
            return 1;
        }
    }
    if (ferror(in)) { perror("read error"); }

    fclose(in);
    fclose(out);
    return 0;
}
```

---

## 14) Ví dụ: lưu/đọc struct (như demo, có chú ý)

```c
// write_struct.c
#include <stdio.h>
#include <stdlib.h>

struct Person { char name[32]; int age; double salary; };

int main(void) {
    struct Person p = { "Alice", 30, 5000.0 };
    FILE *f = fopen("people.bin", "wb");
    if (!f) { perror("fopen"); return 1; }
    if (fwrite(&p, sizeof p, 1, f) != 1) { perror("fwrite"); }
    fclose(f);
    return 0;
}

// read_struct.c
#include <stdio.h>
#include <stdlib.h>

struct Person { char name[32]; int age; double salary; };

int main(void) {
    struct Person p;
    FILE *f = fopen("people.bin", "rb");
    if (!f) { perror("fopen"); return 1; }
    if (fread(&p, sizeof p, 1, f) == 1) {
        printf("%s %d %.2f\n", p.name, p.age, p.salary);
    } else {
        perror("fread");
    }
    fclose(f);
    return 0;
}
```

> **Lưu ý**: cách này nhanh nhưng KHÔNG đảm bảo portable (endianness, padding).

---

## 15) Tối ưu hiệu năng / buffer control

* Thư viện stdio đã buffer I/O; để xử lý performance:

  * Đọc/ghi theo khối lớn (`fread`/`fwrite` với buffer 4KB/8KB).
  * `setvbuf(FILE *stream, char *buf, int mode, size_t size);` để đặt buffer thủ công.
* File system cache và disk I/O rất phức tạp — cho đa phần ứng dụng, dùng buffer lớn và `fclose/fflush` đúng chỗ là đủ.

---

## 16) File descriptors (POSIX) vs `FILE*`

* `FILE *` là wrapper cao cấp (buffered) của stdio.
* POSIX `open()` trả file descriptor `int fd`; bạn có thể chuyển giữa hai bằng `fdopen(fd, "r+")` hoặc lấy `fileno(FILE*)` để lấy fd.
* Dùng `open/read/write/lseek` khi cần control thấp-level (permissions, flags, flock, O_SYNC, v.v.).

---

## 17) Đồng bộ hóa / locking (ngắn)

* C chuẩn không cung cấp file locking portable.
* Trên POSIX dùng `flock()` hoặc `fcntl()`; trên Windows dùng `LockFile`/`LockFileEx`. Đây là platform-specific.

---

## 18) Kết luận — checklist khi dùng file

1. `fopen` với mode phù hợp.
2. Kiểm tra `NULL`.
3. Đọc/ghi bằng `fgets/fputs/fread/fwrite/fprintf/...` tùy tình huống.
4. Kiểm tra giá trị trả về (số phần tử đọc/ghi).
5. Dùng `fflush` nếu cần đảm bảo ghi ngay.
6. `fclose` khi xong.
7. Tránh `scanf("%s",...)` không có width; dùng `fgets`.
8. Với struct/binary: chú ý portability (endianness, padding).

---

Nếu bạn muốn, mình có thể:

* Viết sẵn một **thư viện nhỏ helper** (hàm mở an toàn, đọc dòng an toàn, write/read struct với serialize) theo phong cách bạn cần;
* Hoặc sửa đoạn code cụ thể của bạn để xử lý file đúng và an toàn. Bạn muốn ví dụ nào tiếp theo?

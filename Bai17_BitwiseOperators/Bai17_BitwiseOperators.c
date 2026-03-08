#include <stdio.h>

#define READ  1  // 0001
#define WRITE 2  // 0010
#define EXEC  4  // 0100

int main() {
  int permissions = READ | WRITE;  // user can read and write

  if (permissions & READ) {
    printf("Read allowed\n");
  }
  if (permissions & WRITE) {
    printf("Write allowed\n");
  }
  if (permissions & EXEC) {
    printf("Execute allowed\n");
  }
  return 0;
}
#include <stdio.h>

int add(int a, int b) {
  return a + b;
}

void greetMorning() { printf("Good morning!\n"); }
void greetEvening() { printf("Good evening!\n"); }

void greet(void (*func)()) {
  func();
}

int main() {
  int (*ptr)(int, int) = add;
  int result = ptr(5, 3);
  printf("Result: %d\n", result);
  
  greet(greetMorning);
  greet(greetEvening);

  return 0;
}
#include <stdio.h>

// getting memory address of var num (*)
void calculate(int* num, int a, int b) {
  *num += a + b;
}

int main() {
  int num = 10;
  int a = 2;
  int b = 2;

  // passing memory address of var num (&)
  calculate(&num, a, b);

  printf("%d", num);

  return 0;
}

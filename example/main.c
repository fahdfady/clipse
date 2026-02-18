#include <stdio.h>
int sum(int *a, int n);

int array[2] = {1, 2};

int main() {
  int val = sum(array, 2);

  printf("Your value is: %d\n", val);
  return val;
}

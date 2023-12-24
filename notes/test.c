#include <stdio.h>

int main(int arc, char* argv[]) {
  int *p = (int *) 0x12345678;
  unsigned char *cp = (unsigned char *) &p;

  int i;
  for (i = 0; i < sizeof(p); i++)
    printf("%d: %.2x\n", i, cp[i]);

  return 0;
}


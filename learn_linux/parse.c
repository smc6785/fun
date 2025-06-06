#include <stdio.h>

/* Build a sepeerate kernel module.
https://imil.net/blog/posts/2022/build-a-single-in-tree-linux-kernel-module-debian--clones/
typedef struct cheshe_struct
*/
{
  char data;
  char data_2;
  char data_3;
  char data_4;
} cheshe_struct;

int main(int argc, char *argv[])
{
  FILE *f = fopen(argv[1], "rb");
  cheshe_struct header;
  fread(&header, 1, sizeof(cheshe_struct), f);

  printf("size of cheshe sturct: %d\n", \
    sizeof(cheshe_struct));
  printf("data: %x\n", header.data);
  printf("data: %x\n", header.data_2);
  printf("data: %x\n", header.data_3);
  printf("data: %x\n", header.data_4);
  printf("argc : %d\n", argc);

  /* In C, Argv[0] represents the program's name.*/
  printf("argc 0 : %c\n", argv[0][0]);
  printf("argc 0 : %c\n", argv[0][1]);
  printf("argc 0 : %c\n", argv[0][2]);
  printf("argc 0 : %c\n", argv[0][3]);
  return 0;
}

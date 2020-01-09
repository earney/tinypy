#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int putchar(int c) __naked
{
    __asm

    ld   hl, #2
    add  hl, sp
    ld   l, (hl)
    ld   a, #1
    rst  0x08
    ret
  __endasm;
}

struct s1 {
  int i;
  int j;
  int k;
};


struct s2 {
  int z;
  struct s1 * s;
  int y;
  int x;
};


struct s3 {
   int i;
   struct s2 * t;
   int j;
   int k;
};

int main(int argc, char * argv[]) {
   struct s3 *a;
   a=calloc(1, sizeof(struct s3));
   a->i=1;

   a->t=calloc(1, sizeof(struct s1));

   printf("%d\n", a->i);
   assert(a->i == 1);

   return 0;
}

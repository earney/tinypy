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

void prints(char *s)
{
  while (*s)
    putchar(*s++);
}

void main(void)
{
  prints("Start.\n");
  for (int j= 0; j<41; j++)
    {
      putchar('a');
    }

  prints("Done.\n");
}

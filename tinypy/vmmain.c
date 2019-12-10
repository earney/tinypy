#define TP_COMPILER 0
#include "tp.h"
#include "vm.h"
#include "bc.h"

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


int main(int argc, char *argv[]) {
    //if (argc != 2) {
    //   printf("Error.. You must enter a tpc file\n");
    //   return 0;
    //}
    DBGPRINT1(9, "begin:vmmain\n");
    char* arg[] = {""};
    //tp_vm *tp = tp_init(argc,argv);
    tp_vm *tp = tp_init(0, arg);
    //tp_import(tp,argv[1],"__main__",0,0);
    printf("\nimport main module\n");
    tp_import(tp,"main1","main",tp_main1,0);
    tp_ez_call(tp, "main1", "main1", tp_None_ptr);
    tp_deinit(tp);
    DBGPRINT1(9,"\nend:vmmain\n");
    printf("\nWe have reached the end...\n");
    return 0;
}

#include "tp.c"
/* INCLUDE */

int main(int argc, char *argv[]) {
    if (argc != 2) {
       printf("Error must provide a script to execute\n");
       return 0;
    }

    tp_vm *tp = tp_init(argc,argv);
    /* INIT */
    tp_ez_call(tp,"py2bc","tinypy",tp_None);
    tp_deinit(tp);
    return 0;
}

/**/

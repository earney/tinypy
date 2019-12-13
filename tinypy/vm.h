/* File: VM
 * Functionality pertaining to the virtual machine.
 */

#ifndef TP_VM
#define TP_VM

void _tp_init(void);
void tp_deinit();
void tp_frame(tp_obj* globals,tp_obj* code,tp_obj *ret_dest);
void _tp_raise(tp_obj* e);
void tp_print_stack();
void tp_handle();
tp_obj* tp_call(tp_obj* self, tp_obj* params);
void tp_return(tp_obj* v);

enum {
    TP_IEOF,TP_IADD,TP_ISUB,TP_IMUL,TP_IDIV,TP_IPOW,TP_IBITAND,TP_IBITOR,TP_ICMP,TP_IGET,TP_ISET,
    TP_INUMBER,TP_ISTRING,TP_IGGET,TP_IGSET,TP_IMOVE,TP_IDEF,TP_IPASS,TP_IJUMP,TP_ICALL,
    TP_IRETURN,TP_IIF,TP_IDEBUG,TP_IEQ,TP_ILE,TP_ILT,TP_IDICT,TP_ILIST,TP_INONE,TP_ILEN,
    TP_ILINE,TP_IPARAMS,TP_IIGET,TP_IFILE,TP_INAME,TP_INE,TP_IHAS,TP_IRAISE,TP_ISETJMP,
    TP_IMOD,TP_ILSH,TP_IRSH,TP_IITER,TP_IDEL,TP_IREGS,TP_IBITXOR, TP_IIFN, 
    TP_INOT, TP_IBITNOT,
    TP_ITOTAL
};

#define VA ((int)e.regs.a)
#define VB ((int)e.regs.b)
#define VC ((int)e.regs.c)
#define RA regs[e.regs.a]
#define RB regs[e.regs.b]
#define RC regs[e.regs.c]
#define UVBC (unsigned short)(((VB<<8)+VC))
#define SVBC (short)(((VB<<8)+VC))
#define GA tp_grey(&RA)
#define SR(v) f->cur = cur; return(v);

int tp_step();
void _tp_run(int cur);
void tp_run(int cur);

tp_obj* tp_ez_call(const char *mod, const char *fnc, tp_obj* params);
tp_obj* _tp_import(tp_obj* fname, tp_obj* name, tp_obj* code);
tp_obj* tp_import(const char * fname, const char * name, void *codes, int len);
tp_obj* tp_exec_();
tp_obj* tp_import_();
void tp_builtins();
void tp_args(int argc, char *argv[]);
tp_obj* tp_main(char *fname, void *code, int len);
tp_obj* tp_compile(tp_obj* text, tp_obj* fname);
tp_obj* tp_exec(tp_obj* code, tp_obj* globals);
tp_obj* tp_eval(const char *text, tp_obj* globals);
void tp_init(int argc, char *argv[]);

#endif

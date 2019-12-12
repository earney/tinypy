#ifndef TP_COMPILER
#define TP_COMPILER 1
#endif

#include <stdio.h>

#include "tp.h"
#include "vm.h"
#include "builtins.h"

#ifdef TP_SANDBOX
#include "sandbox.c"
#endif

extern void exit(int);

/*
#if TP_COMPILER
#include "bc.c"
void tp_compiler(TP) {
    tp_import(tp,0,"tokenize",tp_tokenize,sizeof(tp_tokenize));
    tp_import(tp,0,"parse",tp_parse,sizeof(tp_parse));
    tp_import(tp,0,"encode",tp_encode,sizeof(tp_encode));
    tp_import(tp,0,"py2bc",tp_py2bc,sizeof(tp_py2bc));
    tp_ez_call(tp,"py2bc","_init",tp_None_ptr);
}
#else
#endif
*/

void tp_compiler(TP) {
   //tp_import(tp,0,"main1",tp_main,sizeof(tp_main));
}

tp_obj* tp_string(char const *v) {
    //DBGPRINT2(9,"tp_string:string:'%s'\n", v);
    //DBGPRINT2(9,"tp_string:len:'%d'\n", strlen(v));
    return tp_string_n(v,strlen(v));
}

tp_inline_static void tp_cstr(TP,tp_obj* v, char *s, int l) {
    if (v->type != TP_STRING) {
        tp_raise(,tp_string("(tp_cstr) TypeError: value not a string"));
    }

    tp_string_* s1 = TP_TO_STRING(v->obj);

    if (s1->len >= l) {
        tp_raise(,tp_string("(tp_cstr) TypeError: value too long"));
    }
    memset(s,0,l);
    memcpy(s,s1->val,s1->len);
}

tp_obj* tp_type(TP,int t,tp_obj* v) {
    if (v->type != t)
       tp_raise(tp_None_ptr,tp_string("(tp_type) TypeError: unexpected type"));
    return v;
}


tp_inline_static int _tp_min(int a, int b) { return (a<b?a:b); }
tp_inline_static int _tp_max(int a, int b) { return (a>b?a:b); }
tp_inline_static int _tp_sign(tp_num v) { return (v<0?-1:(v>0?1:0)); }


/* Function: tp_number
 * Creates a new numeric object.
 */

tp_obj* tp_number(tp_num v) {
    tp_obj *val=calloc(1, sizeof(tp_obj));
    val->type = TP_NUMBER;
    val->obj = (tp_number_ *) calloc(1, sizeof(tp_number_));
    TP_TO_NUMBER(val->obj)->val = v;
    return val;
}

tp_inline_static void tp_echo(TP,tp_obj* e) {
    //DBGASSERT(9, e->type == TP_STRING);
    //DBGPRINT1(9,"begin:tp_echo:\n");
    //DBGPRINT2(9, "%s\n", e->string.val);
    e = tp_str(tp,e);
    DBGPRINT2(9, "%s", TP_TO_STRING(e->obj)->val);
    //DBGPRINT1(9,"end:tp_echo\n");
}

/* Function: tp_string_n
 * Creates a new string object from a partial C string.
 * 
 * Like <tp_string>, but you specify how many bytes of the given C string to
 * use for the string object. The *note* also applies for this function, as the
 * string reference and length are kept, but no actual substring is stored.
 */

tp_obj* tp_string_n(char const *v,int n) {
    //DBGPRINT1(9, "begin:tp_string_n\n");
    //DBGPRINT2(9, "string:'%s'\n", v);
    //DBGPRINT2(9, "len:'%d'\n", n);

    tp_obj * o = calloc(1, sizeof(tp_obj));
    if (!o) {
        printf("tp_string_n:Error cannot allocate memory\n");
        printf("'%s', size='%d'\n", v, sizeof(tp_obj));
        exit(0);
    }
    //static tp_string_ s = {TP_STRING, 0,v,n};
    //static tp_string_ s = {TP_STRING, v,n};
   
    //tp_string_ * s = calloc(1, sizeof(tp_string_));
    //s->val = (char const *)calloc(n+1, sizeof(char));
  
    //o->string=calloc(1, sizeof(tp_string_));
    //printf("before calloc:o->string.val=%d\n", o->string.val);

    o->obj=(tp_string_ *)calloc(1, sizeof(tp_string_));

    tp_string_* s1 = TP_TO_STRING(o->obj);
    s1->val=calloc(n+1, sizeof(char));
    s1->len=n;
    o->type=TP_STRING;

    //printf("after calloc:o->string.val=%d\n", o->string.val);
    memcpy(s1->val, v, sizeof(char)*(n+1)); //strncpy(t, v, n);
    //printf("after memcpy:o->string.val=%d\n", o->string.val);

    return o;
}

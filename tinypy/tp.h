/* File: General
 * Things defined in tp.h.
 */
#ifndef TP_H
#define TP_H

#include <setjmp.h>
#ifndef __USE_ISOC99
#define __USE_ISOC99
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>

#ifdef __GNUC__
#define tp_inline __inline__
#endif

#ifdef _MSC_VER
#ifdef NDEBUG
#define tp_inline __inline
#else
/* don't inline in debug builds (for easier debugging) */
#define tp_inline
#endif
#endif


#define DBGASSERT(level, x) do {\
  if (DEBUG_LEVEL >= level) assert(x);\
} while (0)


#define DBGPRINT2(level, fmt, x) do {\
   if (DEBUG_LEVEL >= level) printf(fmt, x);\
} while (0)

#define DBGPRINT1(level, x) do {\
   if (DEBUG_LEVEL >= level) \
       printf(x);\
} while (0)

#if 1
#define SDCC 1
#define tp_inline __inline
#define tp_inline_static
#define clock_t int
#define double float
#else
#define tp_inline_static tp_inline static
#endif


//#ifndef tp_inline
//#error "Unsupported compiler"
//#endif


typedef enum {
    TP_NONE,TP_NUMBER,TP_STRING,TP_DICT,
    TP_LIST,TP_FNC,TP_DATA,
} tp_obj_type;


typedef double tp_num;

typedef struct tp_number_ {
    tp_num val;
} tp_number_;

typedef struct tp_string_ {
    char *val;
    unsigned char len;
} tp_string_;

typedef struct tp_list_ {
    struct _tp_list *val;
} tp_list_;

typedef struct tp_dict_ {
    struct _tp_dict *val;
    unsigned char dtype;
} tp_dict_;

typedef struct tp_fnc_ {
    struct _tp_fnc *info;
    unsigned char ftype;
    void *cfnc;
} tp_fnc_;

typedef struct tp_data_ {
    struct _tp_data *info;
    void *val;
    int magic;
} tp_data_;

/* Type: tp_obj*
 * Tinypy's object representation.
 * 
 * Every object in tinypy is of this type in the C API.
 *
 * Fields:
 * type - This determines what kind of objects it is. It is either TP_NONE, in
 *        which case this is the none type and no other fields can be accessed.
 *        Or it has one of the values listed below, and the corresponding
 *        fields can be accessed.
 * number - TP_NUMBER
 * number.val - A double value with the numeric value.
 * string - TP_STRING
 * string.val - A pointer to the string data.
 * string.len - Length in bytes of the string data.
 * dict - TP_DICT
 * list - TP_LIST
 * fnc - TP_FNC
 * data - TP_DATA
 * data.val - The user-provided data pointer.
 * data.magic - The user-provided magic number for identifying the data type.
 */

/*
typedef union tp_type_ {
    tp_number_ *number;
    struct { int type; int *data; } gci;
    tp_string_ *string;
    tp_dict_ *dict;
    tp_list_ *list;
    tp_fnc_ *fnc;
    tp_data_ *data;
} tp_type_;
*/

typedef struct tp_gci_ {
     unsigned char type;
     int *data;
} gci;


typedef struct tp_obj {
    tp_obj_type type;
    void * obj;
    struct { unsigned char type; int *data; } gci;
} tp_obj;


/*
typedef struct _tp_string {
    int gci;
    int len;
    char s[1];
} _tp_string;
*/

typedef struct _tp_list {
    int gci;
    tp_obj *items;
    unsigned char len;
    int alloc;
} _tp_list;

typedef struct tp_item {
    unsigned char used;
    int hash;
    tp_obj *key;
    tp_obj *val;
} tp_item;

typedef struct _tp_dict {
    int gci;
    tp_item *items;
    int len;
    int alloc;
    int cur;
    int mask;
    int used;
    tp_obj *meta;
} _tp_dict;

typedef struct _tp_fnc {
    unsigned char gci;
    tp_obj self;
    tp_obj globals;
    tp_obj code;
} _tp_fnc;


typedef union tp_code {
    unsigned char i;
    struct { unsigned char i,a,b,c; } regs;
    struct { char val[4]; } string;
    struct { float val; } number;
} tp_code;


typedef struct tp_frame_ {
/*    tp_code *codes; */
    tp_obj code;
    tp_code *cur;
    tp_code *jmp;
    tp_obj *regs;
    tp_obj *ret_dest;
    tp_obj *fname;
    tp_obj *name;
    tp_obj *line;
    tp_obj *globals;
    int lineno;
    int cregs;
} tp_frame_;

//const short SIZEOF_TP_OBJ = sizeof(tp_obj);
//const short SIZEOF_TP_ITEM = sizeof(tp_item);

#define TP_GCMAX 4096
#define TP_FRAMES 4
#define TP_REGS_EXTRA 2
#define TP_REGS_PER_FRAME 256
//#define TP_REGS 16384
#define TP_REGS 4

/* Type: tp_vm
 * Representation of a tinypy virtual machine instance.
 * 
 * A new tp_vm struct is created with <tp_init>, and will be passed to most
 * tinypy functions as first parameter. It contains all the data associated
 * with an instance of a tinypy virtual machine - so it is easy to have
 * multiple instances running at the same time. When you want to free up all
 * memory used by an instance, call <tp_deinit>.
 * 
 * Fields:
 * These fields are currently documented: 
 * 
 * builtins - A dictionary containing all builtin objects.
 * modules - A dictionary with all loaded modules.
 * params - A list of parameters for the current function call.
 * frames - A list of all call frames.
 * cur - The index of the currently executing call frame.
 * frames[n].globals - A dictionary of global sybmols in callframe n.
 */
typedef struct tp_vm {
    tp_obj *builtins;
    tp_obj *modules;
    tp_frame_ frames[TP_FRAMES];
    tp_obj *_params;
    tp_obj *params;
    tp_obj *_regs;
    tp_obj *regs;
    tp_obj *root;
    jmp_buf buf;
#ifdef CPYTHON_MOD
    jmp_buf nextexpr;
#endif
    int jmp;
    tp_obj *ex;
    //char chars[256][2];
    int cur;
    /* gc */
    tp_list_ *white;
    tp_list_ *grey;
    tp_list_ *black;
    int steps;
    /* sandbox */
    //clock_t clocks;
    //double time_elapsed;
    //double time_limit;
#ifdef TP_SANDBOX
    unsigned int mem_limit;
    unsigned int mem_used;
    int mem_exceeded;
#endif
} tp_vm;

#define TP tp_vm *tp
typedef struct _tp_data {
    int gci;
    void (*free)(TP,tp_obj*);
} _tp_data;

tp_inline_static tp_obj* tp_number(tp_num);
tp_inline_static tp_obj* tp_string(char const *);
tp_inline_static tp_obj* tp_type(TP,int,tp_obj*);
tp_inline_static void tp_echo(TP,tp_obj*);
tp_inline_static int _tp_max(int a, int b);
tp_inline_static int _tp_sign(tp_num);
tp_inline_static int _tp_min(int, int);
tp_obj* tp_string_n(char const *,int);
void tp_compiler(TP);

#define tp_True tp_number(1)
#define tp_False tp_number(0)

static tp_obj tp_None = {TP_NONE};
static tp_obj* tp_None_ptr = &(tp_None);

//void * tp_realloc(void*, int, int);

#ifdef TP_SANDBOX
void *tp_malloc(TP, unsigned long);
//void *tp_realloc(TP, void *, unsigned long);
void tp_free(TP, void *);
#else
//#define tp_malloc(TP,x) calloc((x),1)
//#define tp_realloc(TP,x,y) realloc(x,y)
//#define tp_free(TP,x) free(x)
#endif

//void tp_sandbox(TP, double, unsigned long);
//void tp_time_update(TP);
//void tp_mem_update(TP);

void tp_run(TP,int cur);
//void tp_set(TP,tp_obj*,tp_obj*,tp_obj*);
tp_obj* tp_get(TP,tp_obj*,tp_obj*);
tp_obj* tp_has(TP,tp_obj* self, tp_obj* k);
tp_obj* tp_len(TP,tp_obj*);
void tp_del(TP,tp_obj*,tp_obj*);
tp_obj* tp_str(TP,tp_obj*);
int tp_bool(TP,tp_obj*);
int tp_cmp(TP,tp_obj*,tp_obj*);
//void _tp_raise(TP,tp_obj*);
tp_obj* tp_printf(TP,char const *fmt,...);
tp_obj* tp_track(TP,tp_obj*);
void tp_grey(TP,tp_obj*);
tp_obj* tp_call(TP, tp_obj* fnc, tp_obj* params);
tp_obj* tp_add(TP,tp_obj* a, tp_obj* b) ;

/* __func__ __VA_ARGS__ __FILE__ __LINE__ */

/* Function: tp_raise
 * Macro to raise an exception.
 * 
 * This macro will return from the current function returning "r". The
 * remaining parameters are used to format the exception message.
 */
/*
#define tp_raise(r,fmt,...) { \
    _tp_raise(tp,tp_printf(tp,fmt,__VA_ARGS__)); \
    return r; \
}
*/

#define TP_TO_NUMBER(d) ((tp_number_*)(d))
#define TP_TO_STRING(d) ((tp_string_*)(d))
#define TP_TO_LIST(d) ((tp_list_*)(d))
#define TP_TO_FNC(d) ((tp_fnc_*)(d))
#define TP_TO_DICT(d) ((tp_dict_*)(d))
#define TP_TO_DATA(d) ((tp_data_*)(d))

#define TP_TO_GCI(d) ((tp_gci_*)(d))

#define tp_raise(r,v) {_tp_raise(tp,v); return r;}
#define TP_CSTR_LEN 256

#define TP_OBJ() (tp_get(tp,tp->params,tp_None_ptr))
#define TP_NO_LIMIT 0
#define TP_TYPE(t) tp_type(tp,t,TP_OBJ())
#define TP_NUM() (TP_TO_NUMBER(TP_TYPE(TP_NUMBER)->obj)->val)
/* #define TP_STR() (TP_CSTR(TP_TYPE(TP_STRING))) */
#define TP_STR() (TP_TYPE(TP_STRING))
#define TP_DEFAULT(d) (TP_TO_LIST(tp->params->obj)->val->len?tp_get(tp,tp->params,tp_None_ptr):(d))

#endif

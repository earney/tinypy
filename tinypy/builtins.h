/* File: Builtins
 * Builtin tinypy functions.
 */

#ifndef TP_BUILTINS_H
#define TP_BUILTINS_H

#include "tp.h"

tp_num tp_fabs(tp_num);

tp_obj* tp_print();
tp_obj* tp_bind();
tp_obj* tp_min();
tp_obj* tp_max();
tp_obj* tp_copy();
tp_obj* tp_len_();
tp_obj* tp_assert();
tp_obj* tp_range();
//tp_obj tp_system(TP);
tp_obj* tp_istype();
tp_obj* tp_float();
tp_obj* tp_abs();
tp_obj* tp_int();
tp_num _roundf(tp_num v);
tp_obj* tp_round();
int _tp_lookup_(tp_obj* self, tp_obj* k, tp_obj *meta, int depth);
int _tp_lookup(tp_obj* self, tp_obj* k, tp_obj *meta);


/*
#define TP_META_BEGIN(self,name) \
    if (self->dict.dtype == 2) { \
        tp_obj meta; if (_tp_lookup(tp,self,tp_string(name),&meta)) {

#define TP_META_END \
        } \
    }
*/

tp_obj* tp_setmeta();
tp_obj* tp_getmeta();
tp_obj* tp_object();
tp_obj* tp_object_new();
tp_obj* tp_object_call();
tp_obj* tp_getraw();
tp_obj* tp_class();
tp_obj* tp_builtins_bool();

#endif

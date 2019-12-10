/* File: Builtins
 * Builtin tinypy functions.
 */

#ifndef TP_BUILTINS_H
#define TP_BUILTINS_H

#include "tp.h"

tp_num tp_fabs(tp_num);

tp_obj* tp_print(TP);
tp_obj* tp_bind(TP);
tp_obj* tp_min(TP);
tp_obj* tp_max(TP);
tp_obj* tp_copy(TP);
tp_obj* tp_len_(TP);
tp_obj* tp_assert(TP);
tp_obj* tp_range(TP);
//tp_obj tp_system(TP);
tp_obj* tp_istype(TP);
tp_obj* tp_float(TP);
tp_obj* tp_save(TP);
tp_obj* tp_load(TP);
tp_obj* tp_fpack(TP);
tp_obj* tp_abs(TP);
tp_obj* tp_int(TP);
tp_num _roundf(tp_num v);
tp_obj* tp_round(TP);
tp_obj* tp_exists(TP);
tp_obj* tp_mtime(TP);
int _tp_lookup_(TP,tp_obj* self, tp_obj* k, tp_obj *meta, int depth);
int _tp_lookup(TP,tp_obj* self, tp_obj* k, tp_obj *meta);


#define TP_META_BEGIN(self,name) \
    if (self->dict.dtype == 2) { \
        tp_obj meta; if (_tp_lookup(tp,self,tp_string(name),&meta)) {

#define TP_META_END \
        } \
    }

tp_obj* tp_setmeta(TP);
tp_obj* tp_getmeta(TP);
tp_obj* tp_object(TP);
tp_obj* tp_object_new(TP);
tp_obj* tp_object_call(TP);
tp_obj* tp_getraw(TP);
tp_obj* tp_class(TP);
tp_obj* tp_builtins_bool(TP);

#endif

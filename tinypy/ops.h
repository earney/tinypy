/* File: Operations
 * Various tinypy operations.
 */

#ifndef OPS_H
#define OPS_H

#include <math.h>
#include "tp.h"

tp_obj* tp_str(tp_obj* self);
int tp_bool(tp_obj* v);
tp_obj* tp_has(tp_obj* self, tp_obj* k);
void tp_del(tp_obj* self, tp_obj* k);
tp_obj* tp_iter(tp_obj* self, tp_obj* k);
tp_obj* tp_get(tp_obj* self, tp_obj* k);
int tp_iget(tp_obj *r, tp_obj* self, tp_obj* k);
void tp_set(tp_obj* self, tp_obj* k, tp_obj* v);
tp_obj* tp_add(tp_obj* a, tp_obj* b);
tp_obj* tp_sub(tp_obj* a, tp_obj* b);
tp_obj* tp_mul(tp_obj* a, tp_obj* b);
tp_obj* tp_div(tp_obj* a, tp_obj* b);
tp_obj* tp_pow(tp_obj* a, tp_obj* b);
tp_obj* tp_len(tp_obj* self);
int tp_cmp(tp_obj* a, tp_obj* b);


tp_obj* tp_bitwise_and(tp_obj*, tp_obj*);
tp_obj* tp_bitwise_or(tp_obj*, tp_obj*);
tp_obj* tp_bitwise_xor(tp_obj*, tp_obj*);
tp_obj* tp_mod(tp_obj*,tp_obj*);
tp_obj* tp_lshift(tp_obj*,tp_obj*);
tp_obj* tp_rshift(tp_obj*,tp_obj*);

tp_obj* tp_bitwise_not(tp_obj*);

#endif

/* File: Operations
 * Various tinypy operations.
 */

/* Function: tp_str
 * String representation of an object.
 *
 * Returns a string object representating self.
 */

#ifndef OPS_H
#define OPS_H

#include <math.h>
#include "tp.h"

tp_obj* tp_str(TP,tp_obj* self);
int tp_bool(TP,tp_obj* v);
tp_obj* tp_has(TP,tp_obj* self, tp_obj* k);
void tp_del(TP,tp_obj* self, tp_obj* k);
tp_obj* tp_iter(TP,tp_obj* self, tp_obj* k);
tp_obj* tp_get(TP,tp_obj* self, tp_obj* k);
int tp_iget(TP,tp_obj *r, tp_obj* self, tp_obj* k);
void tp_set(TP,tp_obj* self, tp_obj* k, tp_obj* v);
tp_obj* tp_add(TP,tp_obj* a, tp_obj* b);
tp_obj* tp_sub(TP,tp_obj* a, tp_obj* b);
tp_obj* tp_mul(TP,tp_obj* a, tp_obj* b);
tp_obj* tp_div(TP,tp_obj* a, tp_obj* b);
tp_obj* tp_pow(TP,tp_obj* a, tp_obj* b);
tp_obj* tp_len(TP,tp_obj* self);
int tp_cmp(TP,tp_obj* a, tp_obj* b);


tp_obj* tp_bitwise_and(TP, tp_obj*, tp_obj*);
tp_obj* tp_bitwise_or(TP, tp_obj*, tp_obj*);
tp_obj* tp_bitwise_xor(TP, tp_obj*, tp_obj*);
tp_obj* tp_mod(TP, tp_obj*,tp_obj*);
tp_obj* tp_lshift(TP, tp_obj*,tp_obj*);
tp_obj* tp_rshift(TP, tp_obj*,tp_obj*);

tp_obj* tp_bitwise_not(TP, tp_obj*);

#endif

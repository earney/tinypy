/* File: Dict
 * Functions for dealing with dictionaries.
 */

#ifndef TP_DICT_H
#define TP_DICT_H

#include "tp.h"

extern void exit(int);

int tp_lua_hash(void const *,int l);
void _tp_dict_free(_tp_dict *);
int tp_hash(tp_obj*);
void _tp_dict_hash_set(_tp_dict *self, int hash, tp_obj* k, tp_obj* v);
void _tp_dict_tp_realloc(_tp_dict *self,int len);
int _tp_dict_hash_find(_tp_dict *self, int hash, tp_obj* k);
int _tp_dict_find(_tp_dict *self,tp_obj* k);
void _tp_dict_setx(_tp_dict *self,tp_obj* k, tp_obj* v);
void _tp_dict_set(_tp_dict *self,tp_obj* k, tp_obj* v);
tp_obj* _tp_dict_get(_tp_dict *self,tp_obj* k, const char *error);
void _tp_dict_del(_tp_dict *,tp_obj*, const char *);

_tp_dict *_tp_dict_new();
tp_obj* _tp_dict_copy(tp_obj* rr);
int _tp_dict_next(_tp_dict *self);
tp_obj* tp_merge();
tp_obj* tp_dict();
tp_obj* tp_dict_n(int n, tp_obj* argv);

#endif


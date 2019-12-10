/* File: Dict
 * Functions for dealing with dictionaries.
 */

#ifndef TP_DICT_H
#define TP_DICT_H

#include "tp.h"

extern void exit(int);

int tp_lua_hash(void const *,int l);
void _tp_dict_free(TP, _tp_dict *);
int tp_hash(TP,tp_obj*);
void _tp_dict_hash_set(TP,_tp_dict *self, int hash, tp_obj* k, tp_obj* v);
void _tp_dict_tp_realloc(TP,_tp_dict *self,int len);
int _tp_dict_hash_find(TP,_tp_dict *self, int hash, tp_obj* k);
int _tp_dict_find(TP,_tp_dict *self,tp_obj* k);
void _tp_dict_setx(TP,_tp_dict *self,tp_obj* k, tp_obj* v);
void _tp_dict_set(TP,_tp_dict *self,tp_obj* k, tp_obj* v);
tp_obj* _tp_dict_get(TP,_tp_dict *self,tp_obj* k, const char *error);
void _tp_dict_del(TP,_tp_dict *,tp_obj*, const char *);

_tp_dict *_tp_dict_new(TP);
tp_obj* _tp_dict_copy(TP,tp_obj* rr);
int _tp_dict_next(TP,_tp_dict *self);
tp_obj* tp_merge(TP);
tp_obj* tp_dict(TP);
tp_obj* tp_dict_n(TP,int n, tp_obj* argv);

#endif


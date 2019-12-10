#ifndef LIST_H
#define LIST_H

#include "tp.h"
#include "builtins.h"

void _tp_list_realloc(TP, tp_list_*,int);
void _tp_list_set(TP,tp_list_ *,int, tp_obj*, const char *);
void _tp_list_free(TP, tp_list_ *);
tp_obj* _tp_list_get(TP,tp_list_ *,int ,const char *);
void _tp_list_insertx(TP,tp_list_ *, int, tp_obj*);
void _tp_list_appendx(TP,tp_list_ *, tp_obj*);
void _tp_list_insert(TP,tp_list_ *self, int n, tp_obj* v);
void _tp_list_append(TP,tp_list_ *self, tp_obj* v);
tp_obj* _tp_list_pop(TP,tp_list_ *self, int n, const char *error);
int _tp_list_find(TP,tp_list_ *self, tp_obj* v);
tp_obj* tp_index(TP);
tp_list_ *_tp_list_new(TP);
tp_obj* _tp_list_copy(TP, tp_obj* rr);
tp_obj* tp_append(TP);
tp_obj* tp_pop(TP);
tp_obj* tp_insert(TP);
tp_obj* tp_extend(TP);
tp_obj* tp_list_nt(TP);
tp_obj* tp_list(TP);
tp_obj* tp_list_n(TP,int n,tp_obj *argv);
int _tp_sort_cmp(tp_obj *a,tp_obj *b);
tp_obj* tp_sort(TP);

#endif

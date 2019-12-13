#ifndef LIST_H
#define LIST_H

#include "tp.h"
#include "builtins.h"

void _tp_list_realloc(tp_list_*,int);
void _tp_list_set(tp_list_ *,int, tp_obj*, const char *);
void _tp_list_free(tp_list_ *);
tp_obj* _tp_list_get(tp_list_ *,int ,const char *);
void _tp_list_insertx(tp_list_ *, int, tp_obj*);
void _tp_list_appendx(tp_list_ *, tp_obj*);
void _tp_list_insert(tp_list_ *self, int n, tp_obj* v);
void _tp_list_append(tp_list_ *self, tp_obj* v);
tp_obj* _tp_list_pop(tp_list_ *self, int n, const char *error);
int _tp_list_find(tp_list_ *self, tp_obj* v);
tp_obj* tp_index();
tp_list_ *_tp_list_new();
tp_obj* _tp_list_copy(tp_obj* rr);
tp_obj* tp_append();
tp_obj* tp_pop();
tp_obj* tp_insert();
tp_obj* tp_extend();
tp_obj* tp_list_nt();
tp_obj* tp_list();
tp_obj* tp_list_n(int n,tp_obj *argv);
int _tp_sort_cmp(tp_obj *a,tp_obj *b);
tp_obj* tp_sort();

#endif

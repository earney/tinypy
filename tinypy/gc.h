
#ifndef GC_H
#define GC_H

#include "tp_list.h"
#include "dict.h"

void tp_grey(TP,tp_obj* v);
void tp_follow(TP,tp_obj* v);
void tp_reset(TP);
void tp_gc_init(TP);
void tp_gc_deinit(TP);
void tp_delete(TP,tp_obj* v);
void tp_collect(TP);
void _tp_gcinc(TP);
void tp_full(TP);
void tp_gcinc(TP);
tp_obj* tp_track(TP,tp_obj* v);

#endif // GC_H

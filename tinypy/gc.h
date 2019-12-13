
#ifndef GC_H
#define GC_H

#include "tp_list.h"
#include "dict.h"

void tp_grey(tp_obj* v);
void tp_follow(tp_obj* v);
void tp_reset();
void tp_gc_init();
void tp_gc_deinit();
void tp_delete(tp_obj* v);
void tp_collect();
void _tp_gcinc();
void tp_full();
void tp_gcinc();
tp_obj* tp_track(tp_obj* v);

#endif // GC_H

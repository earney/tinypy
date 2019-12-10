#include "dict.h"
#include "gc.h"
#include "vm.h"
#include "tp.h"
#include "tp_string.h"

#define DLEVEL 9

void tp_grey(TP,tp_obj* v) {
    DBGPRINT2(DLEVEL, "begin:tp_grey,'%d'\n", v->type);
    DBGASSERT(DLEVEL, v->type <= TP_DATA);
    DBGASSERT(DLEVEL, v->type >= 0);
    switch(v->type) {
       case TP_NONE:
       case TP_NUMBER:
         return;
       case TP_STRING:
       case TP_DATA:
         // fix me  *(v->gci->data) = 1;
         _tp_list_appendx(tp,tp->black,v);
         DBGPRINT2(DLEVEL, "end:tp_grey,'%d'\n", v->type);
         return;
    }
    // fix me  *(v->gci->data) = 1;
    _tp_list_appendx(tp,tp->grey,v);
    DBGPRINT2(DLEVEL, "end:tp_grey,'%d'\n", v->type);
}

void tp_follow(TP,tp_obj* v) {
    DBGPRINT2(DLEVEL, "begin:tp_follow,'%d'\n", v->type);
    //if (v->type == TP_STRING) printf("%s\n", TP_TO_STRING(v->obj)->val);
    switch(v->type) {
      case TP_LIST:
        ;
        tp_list_* l = TP_TO_LIST(v->obj);
        //printf("tp_follow:list length:'%d'\n", l->val->len);
        for (int n=0; n < l->val->len; n++) {
            tp_grey(tp,&(l->val->items[n]));
        }
        break;
      case TP_DICT:
        ;
        tp_dict_* d = TP_TO_DICT(v->obj);
        //printf("dict length:'%d'\n", d->val->len);
        for (int i=0; i < d->val->len; i++) {
            int n = _tp_dict_next(tp,d->val);
            tp_grey(tp,d->val->items[n].key);
            tp_grey(tp,d->val->items[n].val);
        }
        //printf("tp_grey:dict_meta\n");
        tp_grey(tp,d->val->meta);
        break;
      case TP_FNC:
        ;
        tp_fnc_* f = TP_TO_FNC(v->obj);
        //tp_grey(tp,(tp_obj*)(f->info->self));
        tp_grey(tp,&(f->info->self));
        tp_grey(tp,&(f->info->globals));
        tp_grey(tp,&(f->info->code));
        break;
    }
    DBGPRINT2(DLEVEL, "end:tp_follow,'%d'\n", v->type);
}

void tp_reset(TP) {
    DBGPRINT1(DLEVEL, "begin:_tp_reset\n");
    for (int n=0; n<tp->black->val->len; n++) {
        tp->black->val->items[n].gci.data = 0;
    }

    tp_list_ *tmp= tp->white;
    tp->white = tp->black;
    tp->black = tmp;
    DBGPRINT1(DLEVEL, "end:_tp_reset\n");
}

void tp_gc_init(TP) {
    DBGPRINT1(9, "begin:_tp_gc_init\n");
    tp->white = _tp_list_new(tp);
    tp->grey = _tp_list_new(tp);
    tp->black = _tp_list_new(tp);
    //printf("tp->white:'%d'\n", tp->white);
    //printf("tp->grey:'%d'\n", tp->grey);
    //printf("tp->black:'%d'\n", tp->black);

    //printf("tp->white->val->items:'%d'\n", tp->white->val->items);

    DBGASSERT(9, tp->white->val->items != tp->grey->val->items);
    DBGASSERT(9, tp->white->val->items != tp->black->val->items);
    DBGASSERT(9, tp->black->val->items != tp->grey->val->items);
    tp->steps = 0;
    DBGPRINT1(9, "end:_tp_gc_init\n");
}

void tp_gc_deinit(TP) {
    DBGPRINT1(9, "begin:_tp_gc_deinit\n");
    _tp_list_free(tp, tp->white);
    _tp_list_free(tp, tp->grey);
    _tp_list_free(tp, tp->black);
    DBGPRINT1(9, "end:_tp_gc_deinit\n");
}

void tp_delete(TP,tp_obj* v) {
    DBGPRINT1(9, "begin:_tp_delete\n");
    switch(v->type) {
      case TP_LIST:
        _tp_list_free(tp, TP_TO_LIST(v->obj));
        break;
      case TP_DICT:
        _tp_dict_free(tp, TP_TO_DICT(v->obj)->val);
        break;
      case TP_STRING:
        _tp_string_free(tp, TP_TO_STRING(v->obj)->val);
        break;
      case TP_DATA:
        ;
        tp_data_* d = TP_TO_DATA(v->obj);
        if (d->info->free) {
            d->info->free(tp,v);
        }
        free(d->info);
        break;
        //tp_raise(,tp_string("(tp_delete) TP_DATA error?"));
      case TP_FNC:
        free(TP_TO_FNC(v->obj)->info);
        break;
    }

    free(v->obj);
    v->obj=NULL;
    free(v);
    v=NULL;
    DBGPRINT1(9, "end:_tp_delete\n");
    tp_raise(,tp_string("(tp_delete) TypeError: ?"));
}

void tp_collect(TP) {
    DBGPRINT1(9, "begin:_tp_collect\n");
    for (int n=0; n < tp->white->val->len; n++) {
        tp_obj *r = &(tp->white->val->items[n]);
        if (r->gci.data) continue;
        tp_delete(tp,r);
    }
    tp->white->val->len = 0;
    tp_reset(tp);
    DBGPRINT1(9, "end:_tp_collect\n");
}

void _tp_gcinc(TP) {
    DBGPRINT2(DLEVEL, "begin:_tp_gcinc:grey length='%d'\n", tp->grey->val->len);
    if (!tp->grey->val->len) return;

    //printf("tp->grey:'%d'\n", tp->grey);
    //printf("tp->grey->items:'%d'\n", tp->grey->val->items);
    tp_obj* v= _tp_list_pop(tp,tp->grey,tp->grey->val->len-1,"_tp_gcinc");
    tp_follow(tp,v);
    DBGPRINT2(DLEVEL, "end:_tp_gcinc:grey length='%d'\n", tp->grey->val->len);
    //printf("tp->black:'%d'\n", tp->black);
    //printf("tp->black->items:'%d'\n", tp->black->val->items);
    if (tp->black->val->items == tp->grey->val->items) {
       printf("black items == grey items\n");
       exit(0);
    }
    _tp_list_appendx(tp,tp->black,v);
    DBGPRINT2(DLEVEL, "end:_tp_gcinc:grey length='%d'\n", tp->grey->val->len);
    DBGPRINT1(DLEVEL, "end:_tp_gcinc\n");
}

void tp_full(TP) {
    DBGPRINT1(DLEVEL, "begin:tp_full\n");
    while (tp->grey->val->len) _tp_gcinc(tp);

    tp_collect(tp);
    tp_follow(tp,tp->root);
    DBGPRINT1(DLEVEL, "end:tp_full\n");
}

void tp_gcinc(TP) {
    DBGPRINT1(8, "begin:tp_gcinc\n");
    tp->steps += 1;
    DBGPRINT2(8, "steps:%d\n", tp->steps);
    DBGPRINT2(8, "grey:%d\n", tp->grey->val->len);
    if (tp->steps < TP_GCMAX || tp->grey->val->len > 0) {
        _tp_gcinc(tp);
        _tp_gcinc(tp);
    }

    if (tp->steps < TP_GCMAX || tp->grey->val->len > 0) return;
    tp->steps = 0;
    tp_full(tp);
    DBGPRINT1(DLEVEL, "end:tp_gcinc\n");
    return;
}

tp_obj* tp_track(TP,tp_obj* v) {
    DBGPRINT1(DLEVEL,"begin:tp_track\n");
    tp_gcinc(tp);
    tp_grey(tp,v);
    DBGPRINT1(DLEVEL,"end:tp_track\n");

    return v;
}

/**/

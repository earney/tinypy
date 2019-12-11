#include "tp.h"
#include "builtins.h"
#include "tp_list.h"
#include "vm.h"

extern void exit(int);

#define DLEVEL 9

void _tp_list_realloc(TP, tp_list_ *self,int len) {
    DBGPRINT1(DLEVEL, "\nbegin:_tp_list_realloc\n");
    DBGPRINT2(DLEVEL, "len=%d\n", len);
    DBGPRINT2(DLEVEL, "alloc=%d\n", self->val->alloc);
    DBGPRINT2(DLEVEL, "self->val->len=%d\n", self->val->len);
    if (!len) len=1;
    DBGPRINT2(DLEVEL, "items ptr=%d\n", self->val->items);
    if (self->val->len == 0) {
       self->val->items = calloc(2, SIZEOF_TP_OBJ);
       self->val->alloc = 2;
    } else {
       self->val->items = realloc(self->val->items, len*SIZEOF_TP_OBJ);
       if (self->val->items == NULL) {
          printf("_tp_list_realloc:Cannot allocate memory..\n");
          printf("Cannot allocate %d bytes of memory\n", len*SIZEOF_TP_OBJ);
          exit(0);
       }
       self->val->alloc = len;
    }

    DBGPRINT2(DLEVEL, "items ptr=%d\n", self->val->items);
    DBGPRINT2(DLEVEL, "len=%d\n", self->val->len);
    DBGPRINT2(DLEVEL, "alloc=%d\n", self->val->alloc);
    DBGPRINT1(DLEVEL,"\nend:_tp_list_realloc\n");
}

void _tp_list_set(TP,tp_list_ *self,int k, tp_obj* v, const char *error) {
    DBGPRINT1(9,"begin:_tp_list_set\n");
    tp; // so sdcc doesnt' complain about warning 85
    DBGPRINT2(9, "k=%d\n", k);
    DBGPRINT2(9, "self->len=%d\n", self->val->len);
    DBGASSERT(9, self->val->len >= 0);
    if (k >= self->val->len) {
        DBGPRINT2(9, "k=%d", k);
        DBGPRINT2(9, "self->len=%d", self->val->len);
        tp_raise(,tp_string("(_tp_list_set) KeyError"));
    }
    self->val->items[k] = *v;
    tp_grey(tp,v);
    DBGPRINT1(9,"end:_tp_list_set\n");
}

void _tp_list_free(TP, tp_list_ *self) {
    free(self->val->items);
    self->val->items=NULL;
    free(self->val);
    self->val=NULL;
    free(self);
    self=NULL;
}

tp_obj* _tp_list_get(TP, tp_list_ *self,int k,const char *error) {
    tp; // so sdcc doesnt' complain about warning 85
    if (k >= self->val->len) {
        tp_raise(tp_None_ptr,tp_string("(_tp_list_get) KeyError"));
    }
    return &(self->val->items[k]);
}
void _tp_list_insertx(TP, tp_list_ *self, int n, tp_obj* v) {
    DBGPRINT1(9, "\nbegin:_tp_list_insertx\n");
    DBGPRINT2(9, "\nlist item n #%d\n", n);
    DBGPRINT2(9, "\nlist len %d\n", self->val->len);
    DBGPRINT2(9, "\nlist alloc %d\n", self->val->alloc);
    DBGASSERT(9, n >= 0);
    //printf("items:'%d'\n", self->val->items);
    if (self->val->items == 0) exit(0);
    if (self->val->len >= self->val->alloc) {
        _tp_list_realloc(tp, self,(self->val->len)*2);
        DBGPRINT2(9, "\nlist after alloc %d\n", self->val->alloc);
    }
    DBGPRINT2(9, "\nlist len %d\n", self->val->len);
    if (n < self->val->len) {
       memmove(&(self->val->items[n+1]),&(self->val->items[n]),
               SIZEOF_TP_OBJ*(self->val->len-n));
       DBGPRINT2(9, "\nlist after memmove alloc %d\n", self->val->alloc);
    }
    self->val->items[n] = *v;
    self->val->len += 1;

    DBGPRINT2(9, "\nlist len %d\n", self->val->len);
    DBGPRINT2(9, "\nlist alloc %d\n", self->val->alloc);
    DBGPRINT1(9, "\nend:_tp_list_insertx\n");
}

void _tp_list_appendx(TP, tp_list_ *self, tp_obj* v) {
    _tp_list_insertx(tp,self,self->val->len,v);
}

void _tp_list_insert(TP, tp_list_ *self, int n, tp_obj* v) {
    DBGPRINT1(9,"begin:_tp_list_insert\n");
    DBGASSERT(9,self->val->len >=0);
    _tp_list_insertx(tp,self,n,v);
    tp_grey(tp,v);
    DBGPRINT1(9,"end:_tp_list_insert\n");

}
void _tp_list_append(TP, tp_list_ *self, tp_obj* v) {
    DBGPRINT1(9,"begin:_tp_list_append\n");
    DBGASSERT(9,self->val->len >=0);
    DBGASSERT(9,self->val->alloc >=0);
    _tp_list_insert(tp,self,self->val->len,v);
    DBGPRINT2(9,"alloc = '%d' \n", self->val->alloc);
    DBGASSERT(9,self->val->alloc >=0);
    DBGPRINT1(9,"end:_tp_list_append\n");
}

tp_obj* _tp_list_pop(TP, tp_list_ *self, int n, const char *error) {
    tp_obj* r = _tp_list_get(tp,self,n,error);
    if (n != self->val->len-1) {
       memmove(&(self->val->items[n]),&(self->val->items[n+1]),
                 SIZEOF_TP_OBJ*(self->val->len-(n+1)));
    }
    self->val->len -= 1;
    DBGPRINT2(9, "%d\n", self->val->len);
    return r;
}

int _tp_list_find(TP, tp_list_ *self, tp_obj* v) {
    for (int n=0; n < self->val->len; n++) {
        if (tp_cmp(tp,v,&(self->val->items[n])) == 0) return n;
    }
    return -1;
}

tp_obj* tp_index(TP) {
    tp_obj* self = TP_OBJ();
    tp_obj* v = TP_OBJ();
    int i = _tp_list_find(tp,TP_TO_LIST(self->obj),v);
    if (i < 0) {
        tp_raise(tp_None_ptr,tp_string("(tp_index) ValueError: list.index(x): x not in list"));
    }
    return tp_number(i);
}

tp_list_ *_tp_list_new(TP) {
    tp_list_ * l = calloc(1, sizeof(tp_list_));
    l->val = calloc(1, sizeof(_tp_list));
    l->val->items = calloc(1, SIZEOF_TP_OBJ);
    l->val->alloc=1;

    return l;
}

tp_obj* _tp_list_copy(TP, tp_obj* rr) {
    tp_obj *val = calloc(1, SIZEOF_TP_OBJ);
    val->type=TP_LIST;
    tp_list_ *o = TP_TO_LIST(rr->obj);
    tp_list_ *r = _tp_list_new(tp);

    tp; // so sdcc doesnt' complain about warning 85
    r = o;
    r->val->gci = 0;
    r->val->items = calloc(o->val->len, SIZEOF_TP_OBJ);
    memcpy(r->val->items,o->val->items, SIZEOF_TP_OBJ*(o->val->len));

    val->obj=(tp_list_*) calloc(1, sizeof(tp_list_));
    val->obj = r;
    return tp_track(tp,val);
}

tp_obj* tp_append(TP) {
    tp_obj* self = TP_OBJ();
    tp_obj* v = TP_OBJ();
    _tp_list_append(tp,TP_TO_LIST(self->obj),v);
    return tp_None_ptr;
}

tp_obj* tp_pop(TP) {
    tp_obj* self = TP_OBJ();
    return _tp_list_pop(tp,TP_TO_LIST(self->obj),TP_TO_LIST(self->obj)->val->len-1,"pop");
}

tp_obj* tp_insert(TP) {
    tp_obj* self = TP_OBJ();
    int n = TP_NUM();
    tp_obj* v = TP_OBJ();
    _tp_list_insert(tp,TP_TO_LIST(self->obj),n,v);
    return tp_None_ptr;
}

tp_obj* tp_extend(TP) {
    tp_obj* self = TP_OBJ();
    tp_obj* v = TP_OBJ();

    tp_list_* l = TP_TO_LIST(v->obj);
    for (int i=0; i < l->val->len; i++) {
        _tp_list_append(tp,l,&(l->val->items[i]));
    }
    return tp_None_ptr;
}

tp_obj* tp_list_nt(TP) {
    DBGPRINT1(9,"begin:tp_list_nt\n");
    tp_obj *r=calloc(1, SIZEOF_TP_OBJ);
    DBGPRINT2(8, "calloc:'%d'\n", r);
    r->obj= (tp_list_*) calloc(1, sizeof(tp_list_));
    DBGPRINT2(8, "calloc:'%u'\n", r->obj);
    if (!r->obj) {
       printf("tp_list_nt:out of memory\n");
    }
    r->obj = _tp_list_new(tp);
    tp_list_* l = TP_TO_LIST(r->obj);
    l->val->len=0;
    l->val->alloc=0;
    r->type=TP_LIST;
    //DBGPRINT2(9, "ptr:'%u'\n", r->obj->list);
    //r->list = calloc(1, sizeof(tp_list_));
    //assert(r->list->len == 0);
    DBGPRINT2(8, "type:'%d'\n", r->type);
    DBGASSERT(9,r->type == TP_LIST);
    DBGPRINT1(9,"end:tp_list_nt\n");
    return r;
}

tp_obj* tp_list(TP) {
    DBGPRINT1(9,"begin:tp_list\n");
    //tp_obj* r =(tp_obj*)tp_malloc(tp, sizeof(tp_obj));
    DBGPRINT1(9,"end:tp_list\n");
    //return r;
    return tp_track(tp,tp_list_nt(tp));
}

tp_obj* tp_list_n(TP,int n,tp_obj *argv) {
    tp_obj* r = tp_list(tp);
    //r->obj= (tp_list_*) calloc(1, sizeof(tp_list_));
    _tp_list_realloc(tp, TP_TO_LIST(r->obj),n);
    for (int i=0; i<n; i++) {
        _tp_list_append(tp,TP_TO_LIST(r->obj),&(argv[i]));
    }
    return r;
}

int _tp_sort_cmp(tp_obj *a,tp_obj *b) {
    return tp_cmp(0,a,b);
}

tp_obj* tp_sort(TP) {
    tp_obj* self = TP_OBJ();
    qsort(TP_TO_LIST(self->obj)->val->items, TP_TO_LIST(self->obj)->val->len, SIZEOF_TP_OBJ,
          (int(*)(const void*,const void*))_tp_sort_cmp);
    return tp_None_ptr;
}

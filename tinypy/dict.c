/* File: Dict
 * Functions for dealing with dictionaries.
 */

//#include "string.h"
#include "dict.h"
#include "ops.h"
#include "vm.h"
#include "gc.h"

#define DLEVEL 9

int tp_lua_hash(void const *v,int l) {
    int step = (l>>5)+1;
    int h = l + (l >= 4?*(int*)v:0);
    for (int i=l; i>=step; i-=step) {
        h = h^((h<<5)+(h>>2)+((unsigned char *)v)[i-1]);
    }
    return h;
}

void _tp_dict_free(TP, _tp_dict *self) {
    for (int i=0; i < self->len; i++) {
        tp_delete(tp, self->items[i].key);
        tp_delete(tp, self->items[i].val);
    }
    free(self->items);
    self->items = NULL;
    free(self);
    self = NULL;
}

void _tp_dict_reset(_tp_dict *self) {
       memset(self->items,0,(self->alloc)*sizeof(tp_item));
       self->len = 0;
       self->used = 0;
       self->cur = 0;
}

int tp_hash(TP,tp_obj* v) {
    DBGPRINT1(DLEVEL, "begin:tp_hash\n");
    DBGPRINT2(DLEVEL, "'%d'\n", v->type);
    //if (v->type == TP_STRING) DBGPRINT2(9, "key='%s'\n", v->obj->string->val);
    switch (v->type) {
        case TP_NONE: return 0;
        case TP_NUMBER: return tp_lua_hash(&(TP_TO_NUMBER(v->obj)->val),sizeof(tp_num));
        case TP_STRING: return tp_lua_hash(TP_TO_STRING(v->obj)->val,TP_TO_STRING(v->obj)->len);
        case TP_DICT: return tp_lua_hash(TP_TO_DICT(v->obj)->val,sizeof(void*));
        case TP_LIST: ;
            tp_list_* lst = TP_TO_LIST(v->obj);
            int r = lst->val->len;
            for(int n=0; n < lst->val->len; n++) {
                 tp_obj* vv = &(lst->val->items[n]);
                 if (vv->type != TP_LIST) {
                    r+=tp_hash(tp,&(lst->val->items[n]));
                 } else {
                    r+=tp_lua_hash(lst,sizeof(void*));
                 }
            }
            return r;
        case TP_FNC: return tp_lua_hash(TP_TO_FNC(v->obj)->info,sizeof(void*));
        case TP_DATA: return tp_lua_hash(TP_TO_DATA(v->obj)->val,sizeof(void*));
    }
    DBGPRINT1(DLEVEL, "end:tp_hash\n");
    tp_raise(0,tp_string("(tp_hash) TypeError: value unhashable"));
}

void _tp_dict_hash_set(TP,_tp_dict *self, int hash, tp_obj* k, tp_obj* v) {
    DBGPRINT1(9, "begin:_tp_dict_hash_set\n");

    int idx = hash&self->mask;
    for (int i=idx; i < idx+self->alloc; i++) {
        int n = i&self->mask;
        if (self->items[n].used > 0) continue;
        if (self->items[n].used == 0) self->used += 1;
        tp_item * item = calloc(1, sizeof(tp_item));
        if (!item) {
           printf("_tp_dict_hash_set:out of memory..\n");
           exit(0);
        }
        item->used = 1;
        item->hash = hash;
        item->key = k;
        item->val = v;
        self->items[n] = *item;
        self->len += 1;
        DBGPRINT1(9, "end:_tp_dict_hash_set\n");
        return;
    }

    //DBGPRINT2(9, " <-- key\n", _debugprint_obj(k));
    //DBGPRINT2(9, " <-- value\n", _debugprint_obj(v));
    //DBGPRINT2(9, "key_type:%s\n", k->type);
    //DBGPRINT2(9, "key:%s\n", k->string.val);
    //DBGPRINT2(9, "value:%d\n", v->string.val);
    DBGPRINT1(9, "end:_tp_dict_hash_set\n");
    tp_raise(,tp_string("(_tp_dict_hash_set) RuntimeError: ?"));
}

void _tp_dict_tp_realloc(TP,_tp_dict *self,int len) {
    DBGPRINT1(9, "begin:_tp_dict_tp_realloc\n");
    DBGPRINT2(9, "len:%d\n", len);
    tp_item *items = self->items;
    int alloc = self->alloc;
    len = _tp_max(2,len);

    DBGPRINT1(9, "dict:before calloc\n");

    self->items = calloc(len, sizeof(tp_item));
    DBGPRINT1(9, "dict:after calloc\n");
    if (self->items == NULL) {
       printf("tp_dict_tp_realloc..  out of memory\n");
       printf("Cannot allocate %d bytes of memory\n", len*sizeof(tp_item));
       exit(0);
    }
    self->alloc = len;
    self->mask = len-1;
    self->len = 0;
    self->used = 0;

    for (int i=0; i<alloc; i++) {
        if (items[i].used != 1) continue;

        //DBGPRINT2(9, "key:%s\n", _debugprint_obj(items[i].key));
        //DBGPRINT2(9, "value:%s\n", _debugprint_obj(items[i].val));
        //DBGPRINT2(9, "key value:%s\n", items[i].key->obj->string->val);
        _tp_dict_hash_set(tp,self,items[i].hash,items[i].key,items[i].val);
    }
    free(items);
    DBGPRINT1(9, "end:_tp_dict_tp_realloc\n");
}

int _tp_dict_hash_find(TP,_tp_dict *self, int hash, tp_obj* k) {
    DBGPRINT1(9,"begin:_tp_dict_hash_find\n");
    int idx = hash&self->mask;

    for (int i=idx; i<idx+self->alloc; i++) {
        int n = i&self->mask;
        if (self->items[n].used == 0) break;
        if (self->items[n].used < 0) continue;
        if (self->items[n].hash != hash) continue;
        if (tp_cmp(tp,self->items[n].key,k) != 0) continue;
        return n;
    }
    DBGPRINT1(9,"end:_tp_dict_hash_find\n");
    return -1;
}

int _tp_dict_find(TP,_tp_dict *self,tp_obj* k) {
    DBGPRINT1(9,"_tp_dict_find\n");
    return _tp_dict_hash_find(tp,self,tp_hash(tp,k),k);
}

void _tp_dict_setx(TP,_tp_dict *self,tp_obj* k, tp_obj* v) {
    DBGPRINT1(9, "begin:_tp_dict_setx\n");
    //DBGPRINT2(9, "self.type='%d'\n", self->type);
    printf("\n");
    //DBGPRINT1(9, _debugprint_obj(k));
    printf("\n");
    //DBGPRINT1(9, _debugprint_obj(v));
    printf("\n");
    int hash = tp_hash(tp,k);
    DBGPRINT2(9, "hash='%d'\n", hash);
    DBGPRINT2(9, "len='%d'\n", self->len);
    DBGPRINT2(9, "alloc='%d'\n", self->alloc);
    int n = _tp_dict_hash_find(tp,self,hash,k);
    DBGPRINT2(9, "hash_find='%d'\n", n);
    if (n == -1) {
        if (self->len >= (self->alloc/2)) {
            DBGPRINT1(9, "self->len >= self->alloc*1.5\n");
            _tp_dict_tp_realloc(tp,self,(self->alloc*1.5));
        } else if (self->used >= (self->alloc)*3/4) {
            DBGPRINT1(9, "self->used >= self->alloc*3/4\n");
            _tp_dict_tp_realloc(tp,self,self->alloc);
        }
        _tp_dict_hash_set(tp,self,hash,k,v);
    } else {
        self->items[n].val = v;
    }
    DBGPRINT1(9, "end:_tp_dict_setx\n");
}

void _tp_dict_set(TP,_tp_dict *self,tp_obj* k, tp_obj* v) {
    DBGPRINT1(9, "begin:_tp_dict_set\n");
    //_debugprint_obj(k);
    //_debugprint_obj(v);
    _tp_dict_setx(tp,self,k,v);
    tp_grey(tp,k);
    tp_grey(tp,v);
    DBGPRINT1(9, "end:_tp_dict_set\n");
}

tp_obj* _tp_dict_get(TP,_tp_dict *self,tp_obj* k, const char *error) {
    int n = _tp_dict_find(tp,self,k);
    if (n < 0) {
        error="_tp_dict_get:fixme";
        tp_raise(tp_None_ptr,tp_add(tp,tp_string("(_tp_dict_get) KeyError: "),tp_str(tp,k)));
    }
    return self->items[n].val;
}

void _tp_dict_del(TP,_tp_dict *self,tp_obj* k, const char *error) {
    int n = _tp_dict_find(tp,self,k);
    if (n < 0) {
        error="_tp_dict_del:fixme";
        tp_raise(,tp_add(tp,tp_string("(_tp_dict_del) KeyError: "),tp_str(tp,k)));
    }
    self->items[n].used = -1;
    //should we remove the key and value object????
    tp_delete(tp, self->items[n].key);
    tp_delete(tp, self->items[n].val);
    self->len -= 1;
}

_tp_dict *_tp_dict_new(TP) {
    return (_tp_dict*) calloc(1, sizeof(_tp_dict));
}

tp_obj* _tp_dict_copy(TP,tp_obj* rr) {
    DBGPRINT1(9, "begin:_tp_dict_copy\n");
    DBGASSERT(9, rr->type == TP_DICT);
    tp_obj *to = calloc(1, SIZEOF_TP_OBJ);
    _tp_dict *o = TP_TO_DICT(rr->obj)->val;
    _tp_dict *r = _tp_dict_new(tp);
    r = o;
    r->gci = 0;
    r->items = calloc(o->alloc, sizeof(tp_item));
    memcpy(r->items,o->items,sizeof(tp_item)*o->alloc);

    r->meta=calloc(1, SIZEOF_TP_OBJ);
    memset(r->meta, 0, sizeof(tp_obj));

    to->obj = (tp_dict_ *) calloc(1, sizeof(tp_dict_));
    tp_dict_* d = TP_TO_DICT(to->obj);
    d->val = r;
    d->dtype = 1;
    to->type = TP_DICT;
    DBGPRINT1(9, "end:_tp_dict_copy\n");
    return tp_track(tp,to);
}

int _tp_dict_next(TP,_tp_dict *self) {
    if (!self->len) {
        tp_raise(0,tp_string("(_tp_dict_next) RuntimeError"));
    }
    while (1) {
        self->cur = ((self->cur + 1) & self->mask);
        if (self->items[self->cur].used > 0) {
            return self->cur;
        }
    }
}

tp_obj* tp_merge(TP) {
    tp_obj* self = TP_OBJ();
    tp_obj* v = TP_OBJ();

    tp_dict_* d = TP_TO_DICT(v->obj);
    tp_dict_* s = TP_TO_DICT(self->obj);

    for (int i=0; i < d->val->len; i++) {
        int n = _tp_dict_next(tp,d->val);
        _tp_dict_set(tp,
                     s->val,
                     s->val->items[n].key,
                     s->val->items[n].val);
    }
    return tp_None_ptr;
}

/* Function: tp_dict
 *
 * Creates a new dictionary object.
 *
 * *Note* If you use <tp_setmeta> on the dictionary, you have to use <tp_getraw> to
 * access the "raw" dictionary again.
 *
 * Returns:
 * The newly created dictionary.
 */
tp_obj* tp_dict(TP) {
    DBGPRINT1(DLEVEL, "begin:tp_dict\n");
    tp_obj *r = calloc(1, SIZEOF_TP_OBJ);
    DBGPRINT1(DLEVEL, "tp_dict:after allocation\n");

    r->obj = (tp_dict_*) calloc(1, sizeof(tp_dict_));
    tp_dict_* d= TP_TO_DICT(r->obj);
    d->val = _tp_dict_new(tp);
    d->dtype = 1;

    d->val->meta=calloc(1, SIZEOF_TP_OBJ);

    r->type = TP_DICT;
    DBGPRINT1(DLEVEL, "end:tp_dict\n");
    return tp ? tp_track(tp,r) : r;
}

tp_obj* tp_dict_n(TP,int n, tp_obj* argv) {
    tp_obj* r = tp_dict(tp);
    for (int i=0; i<n; i++) tp_set(tp,r,&(argv[i*2]),&(argv[i*2+1]));
    return r;
}

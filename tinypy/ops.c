/* File: Operations
 * Various tinypy operations.
 */

#include <math.h>

#include "tp.h"
#include "builtins.h"
#include "dict.h"
#include "misc.h"
#include "ops.h"
#include "tp_list.h"
#include "tp_string.h"
#include "vm.h"

/* Function: tp_str
 * String representation of an object.
 *
 * Returns a string object representating self.
 */


tp_obj* tp_str(tp_obj* self) {
    //DBGPRINT1(9,"begin:tp_str\n");
    // DBGPRINT2("tp_str:self->type:'%d'\n", self->type);
    switch(self->type) {
      case TP_STRING :return self;
      case TP_NUMBER:
        ;
        //tp_num v = self->number.val;
        float v = TP_TO_NUMBER(self->obj)->val;
        float f =tp_fabs(v)-tp_fabs((long)(v));
        if (f < 0.000001) {
        //if ((fabs(*v)-fabs((long)*v)) < 0.000001) {
           return tp_printf("%ld",tp_number(v));
        }
        return tp_printf("%f",v);
      case TP_DICT:
        return tp_printf("<dict 0x%x>",TP_TO_DICT(self->obj)->val);
      case TP_LIST:
        return tp_printf("<list 0x%x>",TP_TO_LIST(self->obj)->val);
      case TP_NONE:
        return tp_string("None");
#ifdef TP_DATA
      case TP_DATA:
        return tp_printf("<data 0x%x>",TP_TO_DATA(self->obj)->val);
#endif
#ifdef TP_FNC
      case TP_FNC:
        return tp_printf("<fnc 0x%x>",TP_TO_FNC(self->obj)->info);
#endif
    }

    DBGPRINT2(0, "tp_str:self->type:'%d'\n", self->type);
    return tp_printf("<type:'%d'>", self->type);
}

/* Function: tp_bool
 * Check the truth value of an object
 *
 * Returns false if v is a numeric object with a value of exactly 0, v is of
 * type None or v is a string list or dictionary with a length of 0. Else true
 * is returned.
 */
int tp_bool(tp_obj* v) {
    switch(v->type) {
        case TP_NUMBER: return TP_TO_NUMBER(v->obj)->val != 0;
        case TP_NONE: return 0;
        case TP_STRING: return TP_TO_STRING(v->obj)->len != 0;
        case TP_LIST: return TP_TO_LIST(v->obj)->val->len != 0;
        case TP_DICT: return TP_TO_DICT(v->obj)->val->len != 0;
    }
    return 1;
}


/* Function: tp_has
 * Checks if an object contains a key.
 *
 * Returns tp_True if self[k] exists, tp_False otherwise.
 */
tp_obj* tp_has(tp_obj* self, tp_obj* k) {
    switch(self->type) {
      case TP_DICT:
        return _tp_dict_find(TP_TO_DICT(self->obj)->val,k) != -1?tp_True:tp_False;
      case TP_STRING:
        if (k->type == TP_STRING)
           return tp_number(_tp_str_index(self,k)!=-1?1:0);
        break;
      case TP_LIST:
        return tp_number(_tp_list_find(TP_TO_LIST(self->obj),k)!=-1?1:0);
    }
    tp_raise(tp_None_ptr,tp_string("(tp_has) TypeError: iterable argument required"));
}

/* Function: tp_del
 * Remove a dictionary entry.
 *
 * Removes the key k from self. Also works on classes and objects.
 *
 * Note that unlike with Python, you cannot use this to remove list items.
 */
void tp_del(tp_obj* self, tp_obj* k) {
    if (self->type == TP_DICT) {
        _tp_dict_del(TP_TO_DICT(self->obj)->val,k,"tp_del");
        return;
    }
    tp_raise(,tp_string("(tp_del) TypeError: object does not support item deletion"));
}


/* Function: tp_iter
 * Iterate through a list or dict.
 *
 * If self is a list/string/dictionary, this will iterate over the
 * elements/characters/keys respectively, if k is an increasing index
 * starting with 0 up to the length of the object-1.
 *
 * In the case of a list of string, the returned items will correspond to the
 * item at index k. For a dictionary, no guarantees are made about the order.
 * You also cannot call the function with a specific k to get a specific
 * item -- it is only meant for iterating through all items, calling this
 * function len(self) times. Use <tp_get> to retrieve a specific item, and
 * <tp_len> to get the length.
 *
 * Parameters:
 * self - The object over which to iterate.
 * k - You must pass 0 on the first call, then increase it by 1 after each call,
 *     and don't call the function with k >= len(self).
 *
 * Returns:
 * The first (k = 0) or next (k = 1 .. len(self)-1) item in the iteration.
 */
tp_obj* tp_iter(tp_obj* self, tp_obj* k) {
    switch(self->type) {
      case TP_LIST:
      case TP_STRING:
         return tp_get(self,k);
      case TP_DICT:
         if (k->type == TP_NUMBER) {
            tp_dict_* d = TP_TO_DICT(self->obj);
            int n = _tp_dict_next(d->val);
            return d->val->items[n].key;
         }
    }
    tp_raise(tp_None_ptr,tp_string("(tp_iter) TypeError: iteration over non-sequence"));
}


/* Function: tp_get
 * Attribute lookup.
 * 
 * This returns the result of using self[k] in actual code. It works for
 * dictionaries (including classes and instantiated objects), lists and strings.
 *
 * As a special case, if self is a list, self[None] will return the first
 * element in the list and subsequently remove it from the list.
 */
tp_obj* tp_get(tp_obj* self, tp_obj* k) {
    DBGPRINT2(0, "tp_get:self->type='%d'\n", self->type);
    switch(self->type) {
      case TP_DICT:
        ;
        tp_dict_ * d = TP_TO_DICT(self->obj);
        if (d->dtype == 2) { \
           tp_obj *meta = calloc(1, sizeof(tp_obj));
           if (_tp_lookup(self,tp_string("__get__"),meta)) {
              return tp_call(meta,tp_params_v(1,k));
           }
        }
        tp_obj *r=calloc(1, sizeof(tp_obj));
        if (d->dtype && _tp_lookup(self,k,r)) return r;
        // delete r?
        return _tp_dict_get(d->val,k,"tp_get");
      case TP_LIST:
        switch(k->type) {
          case TP_NUMBER:
            ;
            int l = TP_TO_NUMBER(tp_len(self)->obj)->val;
            int n = TP_TO_NUMBER(k->obj)->val;
            n = (n<0?l+n:n);
            return _tp_list_get(TP_TO_LIST(self->obj),n,"tp_get");
          case TP_STRING:
            if (tp_cmp(tp_string("append"),k) == 0)
               return tp_method(self,tp_append);
            if (tp_cmp(tp_string("pop"),k) == 0)  return tp_method(self,tp_pop);
            if (tp_cmp(tp_string("index"),k) == 0) return tp_method(self,tp_index);
            if (tp_cmp(tp_string("sort"),k) == 0) return tp_method(self,tp_sort);
            //fix me
            //if (tp_cmp(tp_string("extend"),k) == 0) return tp_method(self,tp_extend);
            if (tp_cmp(tp_string("*"),k) == 0) {
                tp_params_v(1,self);
                tp_obj *r=calloc(1, sizeof(tp_obj));
                r = tp_copy();
                TP_TO_LIST(self->obj)->val->len=0;
                return r;
            } // if
            break;
          case TP_NONE:
            return _tp_list_pop(TP_TO_LIST(self->obj),0,"tp_get");
        }// switch
      case TP_STRING:
        switch(k->type) {
          case TP_NUMBER:
            ;
            int l = TP_TO_STRING(self->obj)->len;
            int n = TP_TO_NUMBER(k->obj)->val;
            n = (n<0?l+n:n);
            if (n >= 0 && n < l) {
               //fix me
               tp_raise(tp_None_ptr,tp_string("(tp_get) not implemented ops.c:204"));

               //return tp_string_n(tp->chars[(unsigned char)self->string->val[n]],1);
            }
            break;
          case TP_STRING:
            if (tp_cmp(tp_string("join"),k) == 0) return tp_method(self,tp_join);
            if (tp_cmp(tp_string("split"),k) == 0) return tp_method(self,tp_split);
            if (tp_cmp(tp_string("index"),k) == 0) return tp_method(self,tp_str_index);
            if (tp_cmp(tp_string("strip"),k) == 0) return tp_method(self,tp_strip);
            if (tp_cmp(tp_string("replace"),k) == 0) return tp_method(self,tp_replace);
            break;
        } // switch
    } //switch

    if (k->type == TP_LIST) {
        int a,b,l = TP_TO_NUMBER(tp_len(self)->obj)->val;

        tp_obj *tmp = tp_get(k,tp_number(0));

        switch(tmp->type) {
          case TP_NUMBER:
            a = TP_TO_NUMBER(tmp->obj)->val;
            break;
          case TP_NONE:
            a = 0;
            break;
          default:
            tp_raise(tp_None_ptr,tp_string("(tp_get) TypeError: indices must be numbers")); 
        }//switch

        tmp = tp_get(k,tp_number(1));
        switch(tmp->type) {
          case TP_NUMBER:
            b = TP_TO_NUMBER(tmp->obj)->val;
            break;
          case TP_NONE:
            b = l;
            break;
          default:
            tp_raise(tp_None_ptr,tp_string("(tp_get) TypeError: indices must be numbers")); 
        }//switch

        a = _tp_max(0,(a<0?l+a:a));
        b = _tp_min(l,(b<0?l+b:b));
        switch(self->type) {
          case TP_LIST: return tp_list_n(b-a,&(TP_TO_LIST(self->obj)->val->items[a]));
          case TP_STRING: return tp_string_sub(self,a,b);
        }
    }

    printf("Error! tp_get: type='%d'\n", self->type);
    DBGPRINT2(0, "tp_get:self->type='%d'\n", self->type);
    DBGPRINT2(0, "tp_get:k->type='%d'\n", k->type);
    tp_raise(tp_None_ptr,tp_string("(tp_get) TypeError: ?"));
}

/* Function: tp_iget
 * Failsafe attribute lookup.
 *
 * This is like <tp_get>, except it will return false if the attribute lookup
 * failed. Otherwise, it will return true, and the object will be returned
 * over the reference parameter r.
 */
int tp_iget(tp_obj *r, tp_obj* self, tp_obj* k) {
    switch(self->type) {
      case TP_DICT:
        ;
        tp_dict_* d = TP_TO_DICT(self->obj);
        int n = _tp_dict_find(d->val,k);
        if (n == -1) return 0;
        r = d->val->items[n].val;
        tp_grey(r);
        return 1;
      case TP_LIST:
        if  (!TP_TO_LIST(self->obj)->val->len) return 0;
    }

    r = tp_get(self,k);
    tp_grey(r);
    return 1;
}

/* Function: tp_set
 * Attribute modification.
 * 
 * This is the counterpart of tp_get, it does the same as self[k] = v would do
 * in actual tinypy code.
 */
void tp_set(tp_obj* self, tp_obj* k, tp_obj* v) {
    DBGPRINT1(9,"begin:tp_set\n");
    DBGPRINT2(9,"type:%d\n", self->type);
    //printf("\n");
    //_debugprint_obj(k);
    //printf("\n");
    //_debugprint_obj(v);
    //printf("\n");
    switch(self->type) {
      case TP_DICT:
        DBGPRINT1(9,"is a TP_DICT\n");
        tp_dict_* d = TP_TO_DICT(self->obj);
        if (d->dtype == 2) {
           tp_obj * meta = calloc(1, sizeof(tp_obj));
           if (_tp_lookup(self,tp_string("__set__"),meta)) {
              tp_call(meta,tp_params_v(2,k,v));
              return;
           }
        }
        DBGPRINT2(8,"k.type='%d'\n", k->type);
        _tp_dict_set(d->val,k,v);
        return;
      case TP_LIST:
        switch(k->type) {
          case TP_NUMBER:
              _tp_list_set(TP_TO_LIST(self->obj),TP_TO_NUMBER(k->obj)->val,v,"tp_set");
              return;
          case TP_NONE:
              _tp_list_append(TP_TO_LIST(self->obj),v);
              return;
          case TP_STRING:
              if (tp_cmp(tp_string("*"),k) == 0) {
                  tp_params_v(2,self,v);
                  tp_extend();
                  return;
              }
        } // switch
    }// switch
    DBGPRINT2(0, "self type:'%d'\n", self->type);
    //if (self->type == 1) printf("%f\n", self->obj->number->val);
    DBGPRINT2(9, "k type:'%d'\n", k->type);
    DBGPRINT2(9, "v type:'%d'\n", v->type);
    DBGPRINT1(9,"end:tp_set\n");
    tp_raise(,tp_string("(tp_set) TypeError: object does not support item assignment"));
}

tp_obj* tp_add(tp_obj* a, tp_obj* b) {
    switch(a->type) {
      case TP_NUMBER:
        if (b->type == TP_NUMBER)
           return tp_number(TP_TO_NUMBER(a->obj)->val + TP_TO_NUMBER(b->obj)->val);
      case TP_STRING:
        if (b->type == TP_STRING) {
           tp_raise(tp_None_ptr,tp_string("(tp_add) TypeError: ?"));

           tp_string_* s1 = TP_TO_STRING(a->obj);
           tp_string_* s2 = TP_TO_STRING(b->obj);
           int al = s1->len, bl = s2->len;
           tp_obj* r = tp_string_t(al+bl);
           char *s = TP_TO_STRING(r->obj)->val; //.info->s;
           memcpy(s,s1->val,al);
           memcpy(s+al,s2->val,bl);
           return tp_track(r);
        }
        break;
      case TP_LIST:
        if (b->type == TP_LIST) {
           tp_obj* r;
           tp_params_v(1,a);
           r = tp_copy();
           tp_params_v(2,r,b);
           tp_extend();
           return r;
        }
        break;
    }
    DBGPRINT2(9, "tp_add: type='%d'\n", a->type);
    tp_raise(tp_None_ptr,tp_string("(tp_add) TypeError: ?"));
}

tp_obj* tp_mul(tp_obj* a, tp_obj* b) {
    if (a->type == TP_NUMBER && b->type == TP_NUMBER)
       return tp_number(TP_TO_NUMBER(a->obj)->val* TP_TO_NUMBER(b->obj)->val);

    if ((a->type == TP_STRING && b->type == TP_NUMBER) ||
        (a->type == TP_NUMBER && b->type == TP_STRING)) {
        //fixme
        //tp_raise(tp_None_ptr,tp_string("(tp_mul) TypeError: string"));

        if(a->type == TP_NUMBER) {
            tp_obj* c = a; a = b; b = c;
        }

        tp_string_* s1 = TP_TO_STRING(a->obj);
        tp_number_* s2 = TP_TO_NUMBER(b->obj);

        int al = s1->len;
        int n = s2->val;
        if(n <= 0) {
            tp_obj* r = tp_string_t(0);
            return tp_track(r);
        }

        tp_obj* r = tp_string_t(al*n);
        char *s = TP_TO_STRING(r->obj)->val;

        for (int i=0; i<n; i++) memcpy(s+al*i,s1->val,al);
        return tp_track(r);
    }

    tp_raise(tp_None_ptr,tp_string("(tp_mul) TypeError: ?"));
}

/* Function: tp_len
 * Returns the length of an object.
 *
 * Returns the number of items in a list or dict, or the length of a string.
 */
tp_obj* tp_len(tp_obj* self) {
    switch(self->type) {
       case TP_STRING: return tp_number(TP_TO_STRING(self->obj)->len);
       case TP_DICT: return tp_number(TP_TO_DICT(self->obj)->val->len);
       case TP_LIST: return tp_number(TP_TO_LIST(self->obj)->val->len);
    }

    tp_raise(tp_None_ptr,tp_string("(tp_len) TypeError: len() of unsized object"));
}

int tp_cmp(tp_obj* a, tp_obj* b) {
    if (a->type != b->type) return a->type - b->type;
    switch(a->type) {
        case TP_NONE: return 0;
        case TP_NUMBER: return _tp_sign(TP_TO_NUMBER(a->obj)->val - TP_TO_NUMBER(b->obj)->val);
        case TP_STRING:
            ;
            tp_string_* s1 = TP_TO_STRING(a->obj);
            tp_string_* s2 = TP_TO_STRING(b->obj);
            int l = _tp_min(s1->len,s2->len);
            int _v = memcmp(s1->val,s2->val,l);
            if (_v == 0) _v = s1->len - s2->len;
            return _v;
        case TP_LIST:
            ;
            int v;
            tp_list_ *_a=TP_TO_LIST(a->obj);
            tp_list_ *_b=TP_TO_LIST(b->obj);
            int _l = _tp_min(_a->val->len, _b->val->len);
            //tp_obj aa, bb;
            for(int n=0; n < _l; n++) {
                //aa = _a->val->items[n];
                //bb = _b->val->items[n];
                if (_a->val->items[n].type == TP_LIST && _b->val->items[n].type == TP_LIST) {
                   v = TP_TO_LIST(_a->val->items[n].obj)->val - TP_TO_LIST(_b->val->items[n].obj)->val;
                } else {
                   v = tp_cmp(&(_a->val->items[n]),&(_b->val->items[n]));
                }
                if (v) return v;
            }
            return _a->val->len - _b->val->len;
        case TP_DICT: return TP_TO_DICT(a->obj)->val - TP_TO_DICT(b->obj)->val;
        case TP_FNC: return TP_TO_FNC(a->obj)->info - TP_TO_FNC(b->obj)->info;
#ifdef TP_DATA
        case TP_DATA: return TP_TO_DATA(a->obj)->val - TP_TO_DATA(b->obj)->val;
#endif
    }//switch
    tp_raise(0,tp_string("(tp_cmp) TypeError: ?"));
}

tp_obj* tp_bitwise_and(tp_obj* a,tp_obj* b) {
    if (a->type == TP_NUMBER && b->type == TP_NUMBER) {
        return tp_number((long)TP_TO_NUMBER(a->obj)->val & (long)TP_TO_NUMBER(b->obj)->val);
    }
    tp_raise(tp_None_ptr,tp_string("(tp_bitwise_and) TypeError: unsupported operand type(s)"));
}

tp_obj* tp_bitwise_or(tp_obj* a,tp_obj* b) {
    if (a->type == TP_NUMBER && b->type == TP_NUMBER) {
        return tp_number((long) TP_TO_NUMBER(a->obj)->val | (long) TP_TO_NUMBER(b->obj)->val);
    }
    tp_raise(tp_None_ptr,tp_string("(tp_bitwise_or) TypeError: unsupported operand type(s)"));
}

tp_obj* tp_bitwise_xor(tp_obj* a,tp_obj* b) {
    if (a->type == TP_NUMBER && b->type == TP_NUMBER) {
        return tp_number((long)TP_TO_NUMBER(a->obj)->val ^ (long)TP_TO_NUMBER(b->obj)->val);
    }
    tp_raise(tp_None_ptr,tp_string("(tp_bitwise_xor) TypeError: unsupported operand type(s)"));
}

tp_obj* tp_mod(tp_obj* a,tp_obj* b) {
    if (a->type == TP_NUMBER && b->type == TP_NUMBER) {
        return tp_number((long)TP_TO_NUMBER(a->obj)->val % (long)TP_TO_NUMBER(b->obj)->val);
    }
    tp_raise(tp_None_ptr,tp_string("(tp_mod) TypeError: unsupported operand type(s)"));
}

tp_obj* tp_lshift(tp_obj* a,tp_obj* b) {
    if (a->type == TP_NUMBER && b->type == TP_NUMBER) {
        return tp_number((long)TP_TO_NUMBER(a->obj)->val << (int)TP_TO_NUMBER(b->obj)->val);
    }
    tp_raise(tp_None_ptr,tp_string("(tp_lshift) TypeError: unsupported operand type(s)"));
}

tp_obj* tp_rshift(tp_obj* a,tp_obj* b) {
    if (a->type == TP_NUMBER && b->type == TP_NUMBER) {
        return tp_number((int)TP_TO_NUMBER(a->obj)->val >> (int) TP_TO_NUMBER(b->obj)->val);
    }
    tp_raise(tp_None_ptr,tp_string("(tp_rshift) TypeError: unsupported operand type(s)"));
}

tp_obj* tp_sub(tp_obj* a,tp_obj* b) {
    if (a->type == TP_NUMBER && b->type == TP_NUMBER) {
        return tp_number((long)TP_TO_NUMBER(a->obj)->val - (long)TP_TO_NUMBER(b->obj)->val);
    }
    tp_raise(tp_None_ptr,tp_string("(tp_sub) TypeError: unsupported operand type(s)"));
}

tp_obj* tp_div(tp_obj* a,tp_obj* b) {
    if (a->type == TP_NUMBER && b->type == TP_NUMBER) {
        return tp_number((long)TP_TO_NUMBER(a->obj)->val / (long)TP_TO_NUMBER(b->obj)->val);
    }
    tp_raise(tp_None_ptr,tp_string("(tp_sub) TypeError: unsupported operand type(s)"));
}

tp_obj* tp_pow(tp_obj* a,tp_obj* b) {
    if (a->type == TP_NUMBER && b->type == TP_NUMBER) {
        return tp_number(powf(TP_TO_NUMBER(a->obj)->val,TP_TO_NUMBER(b->obj)->val));
    }
    tp_raise(tp_None_ptr,tp_string("(tp_sub) TypeError: unsupported operand type(s)"));
}

tp_obj* tp_bitwise_not(tp_obj* a) {
    if (a->type == TP_NUMBER) return tp_number(~(long)TP_TO_NUMBER(a->obj)->val);
    tp_raise(tp_None_ptr,tp_string("(tp_bitwise_not) TypeError: unsupported operand type"));
}

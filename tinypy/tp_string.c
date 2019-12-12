/* File: String
 * String handling functions.
 */
 
/*
 * Create a new empty string of a certain size.
 * Does not put it in for GC tracking, since contents should be
 * filled after returning.
 */ 

#include "tp.h"
#include "tp_list.h"
#include "tp_string.h"
#include "vm.h"

tp_obj* tp_string_t(TP, int n) {
    tp_obj *r = tp_string_n(0,n);
    tp_string_* s1 = TP_TO_STRING(r->obj);
    memcpy(s1->val, 0, n); //, r->string.info->s;
    s1->len=n;
    return r;
}

/*
 * Create a new string which is a copy of some memory.
 * This is put into GC tracking for you.
 */
tp_obj* tp_string_copy(TP, const char *s, int n) {
    tp_obj* r = tp_string_t(tp,n);
    //memcpy(r->string.info->s,s,n);
    memcpy(TP_TO_STRING(r->obj)->val,s,n);
    return tp_track(tp,r);
}

/*
 * Create a new string which is a substring slice of another STRING.
 * Does not need to be put into GC tracking, as its parent is
 * already being tracked (supposedly).
 */
tp_obj* tp_string_sub(TP, tp_obj* s, int a, int b) {
    int l = TP_TO_STRING(s->obj)->len;

    a = _tp_max(0,(a<0?l+a:a));
    b = _tp_min(l,(b<0?l+b:b));
    tp_obj *r = calloc(1, sizeof(tp_obj));
    r = s;
    r->obj=(tp_string_*) calloc(1, sizeof(tp_string_));
    tp_string_* s1 = TP_TO_STRING(r->obj);
    s1->val += a;
    s1->len = b-a;
    return r;
}

void _tp_string_free(TP, char * s) {
    free(s);
    s=NULL;
}

tp_obj* tp_printf(TP, char const *fmt,...) {
    int l;
    tp_obj* r;
    char *s;
    va_list arg;
    va_start(arg, fmt);
    //SDCC doesnot have vsnprintf..
    //l = vsnprintf(NULL, 0, fmt,arg);
    #if defined(HAVE_VSNPRINTF)
       l = vsnprintf(NULL, 0, fmt, arg);
    #else
       vsprintf(NULL, fmt, arg);
       l = strlen(NULL) + 1;
    #endif

    r = tp_string_t(tp,l);
    //s = r->string.info->s;
    s=TP_TO_STRING(r->obj)->val;
    va_end(arg);
    va_start(arg, fmt);
    vsprintf(s,fmt,arg);
    va_end(arg);
    return tp_track(tp,r);
}

int _tp_str_index(tp_obj* s, tp_obj* k) {
    int i=0;
    tp_string_* s1 = TP_TO_STRING(s->obj);
    tp_string_* s2 = TP_TO_STRING(k->obj);
    while ((s1->len - i) >= s2->len) {
        if (memcmp(s1->val+i,s2->val,s2->len) == 0) return i;
        i++;
    }
    return -1;
}

tp_obj* tp_join(TP) {
    tp_obj* delim = TP_OBJ();
    tp_obj* val = TP_OBJ();
    int l=0,i;
    tp_obj* r;
    char *s;

    tp_list_* v = TP_TO_LIST(val->obj);
    tp_string_* d1 = TP_TO_STRING(delim->obj);

    for (i=0; i < v->val->len; i++) {
        if (i!=0) l += d1->len;
        l += TP_TO_STRING(tp_str(tp,&(v->val->items[i]))->obj)->len;
    }
    r = tp_string_t(tp,l);
    //s = r->string.info->s;
    s = TP_TO_STRING(r->obj)->val;
    l = 0;
    for (i=0; i < v->val->len; i++) {
        tp_obj* e;
        if (i!=0) {
            memcpy(s+l,d1->val,d1->len);
            l += d1->len;
        }
        e = tp_str(tp,&(TP_TO_LIST(val->obj)->val->items[i]));
        tp_string_* e_str= TP_TO_STRING(e->obj);
        memcpy(s+l,e_str->val,e_str->len);
        l += e_str->len;
    }
    return tp_track(tp,r);
}

tp_obj* tp_split(TP) {
    tp_obj* v = TP_OBJ();
    tp_obj* d = TP_OBJ();
    tp_obj* r = tp_list(tp);

    tp_string_* s1 = TP_TO_STRING(v->obj);
    tp_string_* s2 = TP_TO_STRING(d->obj);
    tp_list_* l = TP_TO_LIST(r->obj);

    int i;
    while ((i=_tp_str_index(v,d))!=-1) {
        _tp_list_append(tp,l,tp_string_sub(tp,v,0,i));
        s1->val += i + s2->len;
        s1->len -= i + s2->len;
    }
    _tp_list_append(tp,l,tp_string_sub(tp,v,0,s1->len));
    return r;
}


tp_obj* tp_find(TP) {
    tp_obj* s = TP_OBJ();
    tp_obj* v = TP_OBJ();
    return tp_number(_tp_str_index(s,v));
}

tp_obj* tp_str_index(TP) {
    tp_obj* s = TP_OBJ();
    tp_obj* v = TP_OBJ();
    int n = _tp_str_index(s,v);
    if (n >= 0) return tp_number(n);
    tp_raise(tp_None_ptr,tp_string("(tp_str_index) ValueError: substring not found"));
}

tp_obj* tp_str2(TP) {
    tp_obj* v = TP_OBJ();
    return tp_str(tp,v);
}

tp_obj* tp_chr(TP) {
    int v = TP_NUM();
    tp_raise(tp_None_ptr,tp_string("(tp_chr) not implemented"));
    return tp_string_n((char*) v, 1);
   // return tp_string_n(tp->chars[(unsigned char)v],1);
}

tp_obj* tp_ord(TP) {
    tp_obj* s = TP_STR();
    tp_string_* s1 = TP_TO_STRING(s->obj);
    if (s1->len != 1) {
        tp_raise(tp_None_ptr,tp_string("(tp_ord) TypeError: ord() expected a character"));
    }
    return tp_number((unsigned char)s1->val[0]);
}

tp_obj* tp_strip(TP) {
    tp_obj* o = TP_TYPE(TP_STRING);
    tp_string_* s1 = TP_TO_STRING(o->obj);
    char const *v = s1->val;
    int l = s1->len;
    int a = l, b = 0;
    char *s;
    for (int i=0; i<l; i++) {
        switch(*(v+i)) {
          case ' ':
          case '\n':
          case '\t':
          case '\r':
           break;
          default:
            a = _tp_min(a,i);
            b = _tp_max(b,i+1);
        }
    }
    if ((b-a) < 0) return tp_string("");

    tp_obj * r = calloc(1, sizeof(tp_obj));
    r = tp_string_t(tp,b-a);
    //s = r.string.info->s;
    s = TP_TO_STRING(r->obj)->val;
    memcpy(s,v+a,b-a);
    return tp_track(tp,r);
}

tp_obj* tp_replace(TP) {
    tp_obj* s = TP_OBJ();
    tp_obj* k = TP_OBJ();
    tp_obj* v = TP_OBJ();
    tp_obj* p = s;
    int i,n = 0;
    int c, l;
    tp_obj* rr;
    char *r;
    char *d;
    tp_obj* z;

    tp_string_* s1 = TP_TO_STRING(p->obj);
    tp_string_* s2 = TP_TO_STRING(k->obj);

    tp_string_* s3 = TP_TO_STRING(s->obj);
    tp_string_* v1 = TP_TO_STRING(v->obj);
    tp_string_* z1 = TP_TO_STRING(z->obj);

    while ((i = _tp_str_index(p,k)) != -1) {
        n += 1;
        s1->val += i + s2->len;
        s1->len -= i + s2->len;
    }
/*     fprintf(stderr,"ns: %d\n",n); */
    l = TP_TO_STRING(s->obj)->len + n * (TP_TO_STRING(v->obj)->len - s2->len);
    rr = tp_string_t(tp,l);
    //r = rr->string.info->s;
    r = TP_TO_STRING(rr->obj)->val;
    d = r;
    z = p = s;
    while ((i = _tp_str_index(p,k)) != -1) {
        s1->val += i;
        s1->len -= i;
        memcpy(d,z1->val,c=(s1->val-z1->val));
        d += c;
        s1->val += s2->len;
        s1->len -= s2->len;
        memcpy(d,v1->val,v1->len);
        d += v1->len;
        z = p;
    }
    memcpy(d,z1->val, s3->val + s3->len - z1->val);

    return tp_track(tp,rr);
}

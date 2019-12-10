/* File: Builtins
 * Builtin tinypy functions.
 */

#include "tp.h"
#include "builtins.h"
#include "dict.h"
#include "misc.h"
#include "tp_list.h"
#include "tp_string.h"
#include "vm.h"

tp_obj* tp_print(TP) {
    unsigned char n = 0;
    tp_obj* e;

    tp_list_* lst=TP_TO_LIST(tp->params->obj);
    int l = lst->val->len;
    for (unsigned char i=0; i<l; i++) {
        e = _tp_list_get(tp,lst,i,"TP_LOOP");
        if (n) printf(" ");
        tp_echo(tp,e);
        n += 1;
    }
    printf("\n");
    return tp_None_ptr;
}

tp_obj* tp_bind(TP) {
    tp_obj* r = TP_TYPE(TP_FNC);
    tp_obj* self = TP_OBJ();

    tp_fnc_ * f= TP_TO_FNC(r->obj);
    return tp_fnc_new(tp,
                      f->ftype|2,
                      f->cfnc,
                      &(f->info->code),
                      self,
                      &(f->info->globals));
}

tp_obj* tp_min(TP) {
    tp_obj* r = TP_OBJ();
    tp_obj* e;

    tp_list_* lst = TP_TO_LIST(tp->params->obj);
    int l = lst->val->len;
    for (int i=0; i<l; i++) {
      e = _tp_list_get(tp,lst,i,"TP_LOOP");
      if (tp_cmp(tp,r,e) > 0) r = e;
    }
    return r;
}

tp_obj* tp_max(TP) {
    tp_obj* r = TP_OBJ();
    tp_obj* e;

    int l = TP_TO_LIST(tp->params->obj)->val->len;
    for (int i=0; i<l; i++) {
      e = _tp_list_get(tp,TP_TO_LIST(tp->params->obj),i,"TP_LOOP");
      if (tp_cmp(tp,r,e) < 0) r = e;
    }
    return r;
}

tp_obj* tp_copy(TP) {
    tp_obj* r = TP_OBJ();
    switch(r->type) {
      case TP_LIST:
        return _tp_list_copy(tp,r);
      case TP_DICT:
        return _tp_dict_copy(tp,r);
    }
    tp_raise(tp_None_ptr,tp_string("(tp_copy) TypeError: ?"));
}


tp_obj* tp_len_(TP) {
    tp_obj* e = TP_OBJ();
    return tp_len(tp,e);
}

tp_obj* tp_assert(TP) {
    int a = TP_NUM();
    if (a) return tp_None_ptr;
    tp_raise(tp_None_ptr,tp_string("(tp_assert) AssertionError"));
}

tp_obj* tp_range(TP) {
    int a,b,c;
    tp_obj* r = tp_list(tp);
    switch (TP_TO_LIST(tp->params->obj)->val->len) {
        case 1:
           a = 0;
           b = TP_NUM();
           c = 1;
           break;
        case 2:
        case 3:
           a = TP_NUM();
           b = TP_NUM();
           c = TP_TO_NUMBER(TP_DEFAULT(tp_number(1))->obj)->val;
           break;
        default:
           return r;
    }
    if (c != 0) {
        for (int i=a; (c>0) ? i<b : i>b; i+=c) {
            _tp_list_append(tp,(tp_list_*) r->obj,tp_number(i));
        }
    }
    return r;
}

/* Function: tp_system
 *
 * The system builtin. A grave security flaw. If your version of tinypy
 * enables this, you better remove it before deploying your app :P
 */
tp_obj* tp_system(TP) {
/*
    char s[TP_CSTR_LEN]; tp_cstr(tp,TP_STR(),s,TP_CSTR_LEN);
    int r = system(s);
    return tp_number(r);
*/

    tp_raise(tp_None_ptr,tp_string("(system) is not supported: ?"));
}

tp_obj* tp_istype(TP) {
    tp_obj* v = TP_OBJ();
    tp_obj* t = TP_STR();
    if (tp_cmp(tp,t,tp_string("string")) == 0) return tp_number(v->type == TP_STRING);
    if (tp_cmp(tp,t,tp_string("list")) == 0) return tp_number(v->type == TP_LIST);
    if (tp_cmp(tp,t,tp_string("dict")) == 0) return tp_number(v->type == TP_DICT);
    if (tp_cmp(tp,t,tp_string("number")) == 0) return tp_number(v->type == TP_NUMBER);
   
    tp_fnc_ *vo=(tp_fnc_*)(v->obj);
    if (tp_cmp(tp,t,tp_string("fnc")) == 0) return tp_number(v->type == TP_FNC && (vo->ftype&2) == 0);
    if (tp_cmp(tp,t,tp_string("method")) == 0) return tp_number(v->type == TP_FNC && (vo->ftype&2) != 0);
    tp_raise(tp_None_ptr,tp_string("(is_type) TypeError: ?"));
}


tp_obj* tp_float(TP) {
    tp_obj* v = TP_OBJ();

    switch(v->type) {
      case TP_NUMBER: return v;
      case TP_STRING:
        ;
        tp_string_ *str=(tp_string_*)(v->obj);
        if (str->len < 32) {
           char s[32];
           memset(s,0,str->len+1);
           memcpy(s,str->val,str->len);
           if (strchr(s,'.')) return tp_number(atof(s));
           int ord = 0; //TP_DEFAULT( (tp_number_*)
                        //          (tp_number(0)->obj) )->val;
           return(tp_number(strtol(s,0,ord)));
        }
    }//switch
    tp_raise(tp_None_ptr,tp_string("(tp_float) TypeError: ?"));
}


tp_obj* tp_save(TP) {
    tp;
    tp_raise(tp_None_ptr,tp_string("(tp_save) IOError: ?"));
    /*
    char fname[256]; 
    tp_cstr(tp,TP_STR(),fname,256);

    tp_obj* v = TP_OBJ();
    FILE *f;
    f = fopen(fname,"wb");
    if (!f) { tp_raise(tp_None,tp_string("(tp_save) IOError: ?")); }
    fwrite(v.string.val,v.string.len,1,f);
    fclose(f);
    */
    return tp_None_ptr;
}

tp_obj* tp_load(TP) {
    tp;
    tp_raise(tp_None_ptr,tp_string("(tp_load) IOError: ?"));

    /*
    FILE *f;
    long l;
    tp_obj* r;
    char *s;
    char fname[256];
    tp_cstr(tp,TP_STR(),fname,256);
    struct stat stbuf;
    stat(fname, &stbuf);
    l = stbuf.st_size;
    f = fopen(fname,"rb");
    if (!f) {
        tp_raise(tp_None,tp_string("(tp_load) IOError: ?"));
    }
    r = tp_string_t(tp,l);
    s = r.string.info->s;
    fread(s,1,l,f);
    fclose(f);
    return tp_track(tp,r);
    */
    return tp_None_ptr;
}

tp_obj* tp_fpack(TP) {
/*
    tp_num v = TP_NUM();
    tp_obj* r = tp_string_t(tp,sizeof(tp_num));
    //fixme
    r->string.val = v;
    return tp_track(tp,r);
*/
    tp_raise(tp_None_ptr,tp_string("(fpack) is not supported"));
}

tp_num tp_fabs(tp_num v) {return v > 0?v:-v;}
tp_obj* tp_abs(TP) {return tp_number(tp_fabs(((tp_number_*)(tp_float(tp)->obj))->val));}
tp_obj* tp_int(TP) {return tp_number((long)((tp_number_*)(tp_float(tp)->obj))->val);}
tp_obj* tp_round(TP) {return tp_number(_roundf(((tp_number_*)(tp_float(tp)->obj))->val));}

tp_num _roundf(tp_num v) {
    tp_num av = tp_fabs(v);
    tp_num iv = (long)av;
    av = (av-iv < 0.5?iv:iv+1);
    return (v<0?-av:av);
}

tp_obj* tp_exists(TP) {
/*
    char fname[TP_CSTR_LEN];
    tp_cstr(tp,TP_STR(),fname,TP_CSTR_LEN);
    struct stat stbuf;
    return tp_number(!stat(fname,&stbuf));
*/
    tp_raise(tp_None_ptr,tp_string("(tp_exists) IOError: ?"));
}

tp_obj* tp_mtime(TP) {
/*
    char fname[TP_CSTR_LEN]; tp_cstr(tp,TP_STR(),fname,TP_CSTR_LEN);
    struct stat stbuf;
    if (!stat(fname,&stbuf)) { return tp_number(stbuf.st_mtime); }
*/
    tp_raise(tp_None_ptr,tp_string("(tp_mtime) IOError: ?"));
}

int _tp_lookup_(TP,tp_obj* self, tp_obj* k, tp_obj *meta, int depth) {
    tp_dict_* d = (tp_dict_*)(self->obj);
    int n = _tp_dict_find(tp,d->val,k);
    if (n != -1) {
        meta = d->val->items[n].val;
        return 1;
    }
    depth--;
    if (!depth) tp_raise(0,tp_string("(tp_lookup) RuntimeError: maximum lookup depth exceeded"));
    if (d->dtype && d->val->meta->type == TP_DICT &&
        _tp_lookup_(tp,d->val->meta,k,meta,depth)) {
        if (d->dtype == 2 && meta->type == TP_FNC) {
            tp_fnc_ *f=(tp_fnc_*)(meta->obj);
            meta = tp_fnc_new(tp,
                              f->ftype|2,
                              &(f->cfnc),
                              &(f->info->code),
                              self,
                              &(f->info->globals));
        }
        return 1;
    }
    return 0;
}

int _tp_lookup(TP,tp_obj* self, tp_obj* k, tp_obj *meta) {
    return _tp_lookup_(tp,self,k,meta,8);
}


/* Function: tp_setmeta
 * Set a "dict's meta".
 *
 * This is a builtin function, so you need to use <tp_params> to provide the
 * parameters.
 *
 * In tinypy, each dictionary can have a so-called "meta" dictionary attached
 * to it. When dictionary attributes are accessed, but not present in the
 * dictionary, they instead are looked up in the meta dictionary. To get the
 * raw dictionary, you can use <tp_getraw>.
 *
 * This function is particulary useful for objects and classes, which are just
 * special dictionaries created with <tp_object> and <tp_class>. There you can
 * use tp_setmeta to change the class of the object or parent class of a class.
 *
 * Parameters:
 * self - The dictionary for which to set a meta.
 * meta - The meta dictionary.
 *
 * Returns:
 * None
 */
tp_obj* tp_setmeta(TP) {
    tp_obj* self = TP_TYPE(TP_DICT);
    tp_obj* meta = TP_TYPE(TP_DICT);
    ((tp_dict_*)(self->obj))->val->meta = meta;
    return tp_None_ptr;
}

tp_obj* tp_getmeta(TP) {
    tp_obj* self = TP_TYPE(TP_DICT);
    return ((tp_dict_*)(self->obj))->val->meta;
}

/* Function: tp_object
 * Creates a new object.
 *
 * Returns:
 * The newly created object. The object initially has no parent class, use
 * <tp_setmeta> to set a class. Also see <tp_object_new>.
 */
tp_obj* tp_object(TP) {
    DBGPRINT1(9, "begin:tp_object\n");
    tp_obj* self = tp_dict(tp);
    TP_TO_DICT(self->obj)->dtype = 2;
    DBGPRINT1(9, "end:tp_object\n");
    return self;
}

tp_obj* tp_object_new(TP) {
    tp_obj* klass = TP_TYPE(TP_DICT);
    tp_obj* self = tp_object(tp);

    tp_dict_* d=TP_TO_DICT(self->obj);

    d->val->meta = klass;
    if (d->dtype == 2) { \
        tp_obj* meta=calloc(1, SIZEOF_TP_OBJ);
        if (_tp_lookup(tp,self,tp_string("__init__"),meta)) {
           tp_call(tp,meta,tp->params);
        }
    }
    return self;
}

tp_obj* tp_object_call(TP) {
    tp_obj* self;

    if (TP_TO_LIST(tp->params->obj)->val->len) {
        self = TP_TYPE(TP_DICT);
        TP_TO_DICT(self->obj)->dtype = 2;
    } else {
        self = tp_object(tp);
    }
    return self;
}

/* Function: tp_getraw
 * Retrieve the raw dict of a dict.
 *
 * This builtin retrieves one dict parameter from tinypy, and returns its raw
 * dict. This is very useful when implementing your own __get__ and __set__
 * functions, as it allows you to directly access the attributes stored in the
 * dict.
 */
tp_obj* tp_getraw(TP) {
    tp_obj* self = TP_TYPE(TP_DICT);
    TP_TO_DICT(self->obj)->dtype = 0;
    return self;
}

/* Function: tp_class
 * Creates a new base class.
 *
 * Parameters:
 * none
 *
 * Returns:
 * A new, empty class (derived from tinypy's builtin "object" class).
 */
tp_obj* tp_class(TP) {
    tp_obj* klass = tp_dict(tp);
    TP_TO_DICT(klass->obj)->val->meta = tp_get(tp,tp->builtins,tp_string("object"));
    return klass;
}

/* Function: tp_builtins_bool
 * Coerces any value to a boolean.
 */
tp_obj* tp_builtins_bool(TP) {
    tp_obj* v = TP_OBJ();
    return tp_number(tp_bool(tp, v));
}

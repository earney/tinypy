/* File: Miscellaneous
 * Various functions to help interface tinypy.
 */

#include "tp.h"
#include "tp_list.h"
#include "misc.h"

tp_obj* _tp_dcall(TP,tp_obj* (*fn)(TP)) {return (*fn)(tp);}

//fixme
tp_obj* _tp_tcall(TP,tp_obj* fnc) {
    if (TP_TO_FNC(fnc->obj)->ftype&2) {
        _tp_list_insert(tp,TP_TO_LIST(tp->params),0,&(TP_TO_FNC(fnc->obj)->info->self));
    }
   return _tp_dcall(tp, TP_TO_FNC(fnc->obj)->cfnc);
}

tp_obj* tp_fnc_new(TP,int t, void *v, tp_obj* c, tp_obj* s, tp_obj* g) {
    tp_obj * r = calloc(1, sizeof(tp_obj));
    r->type = TP_FNC;
    _tp_fnc *info = calloc(1, sizeof(_tp_fnc));
    info->code = *c;
    info->self = *s;
    info->globals = *g;

    r->obj = (tp_fnc_*) calloc(1, sizeof(tp_fnc_));

    tp_fnc_* f = TP_TO_FNC(r->obj);
    f->ftype = t;
    f->info = info;
    f->cfnc = v;
    return tp_track(tp,r);
}

tp_obj* tp_def(TP,tp_obj* code, tp_obj* g) {
    return tp_fnc_new(tp,1,0,code,tp_None_ptr,g);
}

/* Function: tp_fnc
 * Creates a new tinypy function object.
 * 
 * This is how you can create a tinypy function object which, when called in
 * the script, calls the provided C function.
 */
tp_obj* tp_fnc(TP,tp_obj* v(TP)) {
    return tp_fnc_new(tp,0,v,tp_None_ptr,tp_None_ptr,tp_None_ptr);
}

tp_obj* tp_method(TP,tp_obj* self, tp_obj* v(TP)) {
    return tp_fnc_new(tp,2,v,tp_None_ptr,self,tp_None_ptr);
}

/* Function: tp_data
 * Creates a new data object.
 * 
 * Parameters:
 * magic - An integer number associated with the data type. This can be used
 *         to check the type of data objects.
 * v     - A pointer to user data. Only the pointer is stored in the object,
 *         you keep all responsibility for the data it points to.
 *
 * 
 * Returns:
 * The new data object.
 * 
 * Public fields:
 * The following fields can be access in a data object:
 * 
 * magic      - An integer number stored in the object.
 * val        - The data pointer of the object.
 * info->free - If not NULL, a callback function called when the object gets
 *              destroyed.
 * 
 * Example:
 * > void *__free__(TP, tp_obj self)
 * > {
 * >     free(self.data.val);
 * > }
 * >
 * > tp_obj my_obj = tp_data(TP, 0, my_ptr);
 * > my_obj.data.info->free = __free__;
 */
tp_obj* tp_data(TP,int magic,void *v) {
    tp_obj *r = calloc(1, sizeof(tp_obj));
    r->type = TP_DATA;

    r->obj = (tp_data_*) calloc(1, sizeof(tp_data_));
    tp_data_* f = TP_TO_DATA(r->obj);

    f->info = calloc(1, sizeof(_tp_data));
    f->val = v;
    f->magic = magic;
    return tp_track(tp,r);
}

/* Function: tp_params
 * Initialize the tinypy parameters.
 *
 * When you are calling a tinypy function, you can use this to initialize the
 * list of parameters getting passed to it. Usually, you may want to use
 * <tp_params_n> or <tp_params_v>.
 */
tp_obj* tp_params(TP) {
    tp_obj *r = calloc(1, sizeof(tp_obj));

    tp_list_* l = TP_TO_LIST(tp->_params->obj);

    tp->params = &(l->val->items[tp->cur]);
    r = &(l->val->items[tp->cur]);
    TP_TO_LIST(r->obj)->val->len = 0;
    return r;
}

/* Function: tp_params_n
 * Specify a list of objects as function call parameters.
 *
 * See also: <tp_params>, <tp_params_v>
 *
 * Parameters:
 * n - The number of parameters.
 * argv - A list of n tinypy objects, which will be passed as parameters.
 *
 * Returns:
 * The parameters list. You may modify it before performing the function call.
 */
tp_obj* tp_params_n(TP,int n, tp_obj* argv[]) {
    tp_obj* r = tp_params(tp);
    tp_list_* l = TP_TO_LIST(r->obj);
    for (int i=0; i<n; i++) _tp_list_append(tp,l,argv[i]);
    return r;
}

/* Function: tp_params_v
 * Pass parameters for a tinypy function call.
 * 
 * When you want to call a tinypy method, then you use this to pass parameters
 * to it.
 * 
 * Parameters:
 * n   - The number of variable arguments following.
 * ... - Pass n tinypy objects, which a subsequently called tinypy method will
 *       receive as parameters.
 * 
 * Returns:
 * A tinypy list object representing the current call parameters. You can modify
 * the list before doing the function call.
 */
tp_obj* tp_params_v(TP,int n,...) {
    tp_obj* r = tp_params(tp);
    va_list* a;
    va_start(a,n);
    tp_list_* l = TP_TO_LIST(r->obj);

    for (int i=0; i<n; i++) _tp_list_append(tp,l,&(va_arg(a,tp_obj)));
    va_end(a);
    return r;
}

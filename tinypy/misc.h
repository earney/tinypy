/* File: Miscellaneous
 * Various functions to help interface tinypy.
 */

#ifndef TP_MISC
#define TP_MISC

tp_obj* _tp_dcall(tp_obj* (*fnc)());
tp_obj* _tp_tcall(tp_obj* fnc);
tp_obj* tp_fnc_new(int t, void *v, tp_obj* c,tp_obj* s, tp_obj* g);
tp_obj* tp_def(tp_obj* code, tp_obj* g);
tp_obj* tp_fnc(tp_obj* v());
tp_obj* tp_method(tp_obj* self, tp_obj* (*v)());
tp_obj* tp_data(int magic,void *v);
tp_obj* tp_params();
tp_obj* tp_params_n(int, tp_obj*[]);
tp_obj* tp_params_v(int,...);

#endif

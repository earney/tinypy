#ifndef TP_STRING_H
#define TP_STRING_H

tp_obj* tp_string_t(int n);
tp_obj* tp_string_copy(const char *s, int n);
tp_obj* tp_string_sub(tp_obj* s, int a, int b);

void _tp_string_free(char*);
tp_obj* tp_printf(char const *fmt,...);
int _tp_str_index(tp_obj* s, tp_obj* k);
tp_obj* tp_join();
tp_obj* tp_split();
tp_obj* tp_find();
tp_obj* tp_str_index();
tp_obj* tp_str2();
tp_obj* tp_chr();
tp_obj* tp_ord();
tp_obj* tp_strip();
tp_obj* tp_replace();

#endif //STRING_H

#ifndef __VM_H__
#define __VM_H__

#define Qnil (VALUE) 0
#define RB_INT(x) ((int) (x >> 1))
#define RB_CSTR(x) ((struct RString *)x)->content

typedef unsigned long VALUE;

typedef struct VM {
  VALUE symtbl;
} VM;

VM* rb_vm_new();
VALUE rb_vm_store(VM* vm, VALUE key, VALUE value);
VALUE rb_vm_lookup(VM* vm, VALUE key);
VALUE rb_gc_add(VM* vm, VALUE value);
void rb_vm_destroy(VM* vm);
void rb_print(VALUE value);
void rb_free(VALUE value);

#endif

#ifndef __VM_H__
#define __VM_H__

typedef unsigned long VALUE;

typedef struct VM {
  VALUE symtbl;
} VM;

VM* rb_vm_new();
void rb_vm_store(VM* vm, VALUE key, VALUE value);
void rb_vm_destroy(VM* vm);

#endif

#include <stdlib.h>
#include "vm.h"
#include "hash.h"

VM* rb_vm_new() {
  VM* vm = (VM*)malloc(sizeof(VM));
  vm->symtbl = rb_hash_allocate();
  return vm;
}

void rb_vm_destroy(VM* vm) {
  rb_hash_dealloc(vm->symtbl);
  free(vm);
}

void rb_vm_store(VM* vm, VALUE key, VALUE value) {
  rb_hash_store(vm->symtbl, key, value);
}

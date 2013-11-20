#include <stdlib.h>
#include <stdio.h>
#include "vm.h"
#include "hash.h"
#include "string.h"

VM* rb_vm_new() {
  VM* vm = (VM*)malloc(sizeof(VM));
  vm->symtbl = rb_hash_allocate();
  return vm;
}

void rb_vm_destroy(VM* vm) {
  rb_hash_dealloc(vm->symtbl);
  free(vm);
}

void rb_print(VALUE value) {
  if(value & 0x1) {
    printf("%d\n", RB_INT(value));
  } else {
    printf("%s\n", RB_CSTR(value));
  }
}

VALUE rb_vm_store(VM* vm, VALUE key, VALUE value) {
  rb_hash_store(vm->symtbl, key, value);
  return value;
}

VALUE rb_vm_lookup(VM* vm, VALUE key) {
  return rb_hash_lookup(vm->symtbl, key);
}

void rb_free(VALUE value) {
  if(value & 0x1) {
  } else {
    rb_str_dealloc(value);
  }
}

VALUE rb_gc_add(VM* vm, VALUE value) {
  return value;
}

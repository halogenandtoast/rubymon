#include <stdlib.h>
#include "vm.h"

VM* rb_vm_new() {
  VM* vm = (VM*)malloc(sizeof(VM));
  return vm;
}

void rb_vm_destroy(VM* vm) {
  free(vm);
}

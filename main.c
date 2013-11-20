#include <stdio.h>
#include "vm.h"
#include "y.tab.h"
#include "hash.h"
#include "string.h"

extern FILE* yyin;

int main(int argc, char* argv[]) {
  VM* vm = rb_vm_new();
  if(argc > 1) {
    yyin = fopen(argv[1], "r");
  }
  yyparse(vm);
  rb_vm_destroy(vm);
  return 0;
}

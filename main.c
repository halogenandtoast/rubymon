#include <stdio.h>
#include "vm.h"
#include "y.tab.h"
#include "hash.h"
#include "string.h"

extern FILE* yyin;

int main(int argc, char* argv[]) {

  VALUE key = rb_str_new("name");
  VALUE value = rb_str_new("Goose Mongeau");

  VALUE hash = rb_hash_allocate();
  rb_hash_store(hash, key, value);

  key = rb_str_new("spouse");
  value = rb_str_new("Brandy Mongeau");

  rb_hash_store(hash, key, value);

  rb_hash_dump(hash);
  rb_hash_dealloc(hash);

  VM* vm = rb_vm_new();
  if(argc > 1) {
    yyin = fopen(argv[1], "r");
  }
  yyparse(vm);
  rb_vm_destroy(vm);
  return 0;
}

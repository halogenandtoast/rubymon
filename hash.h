#ifndef HASH_H
#define HASH_H

#include "khash.h"
#include "vm.h"

KHASH_MAP_INIT_INT64(VALUE, VALUE);

typedef struct rb_hash {
  kh_VALUE_t* kh;
} rb_hash;

VALUE rb_hash_allocate();
void rb_hash_dealloc(VALUE hash);
void rb_hash_store(VALUE hash, VALUE key, VALUE value);
void rb_hash_dump(VALUE hash);

#endif

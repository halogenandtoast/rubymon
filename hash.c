#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "string.h"
#include "ruby.h"

VALUE rb_hash_allocate() {
  struct rb_hash* hash = (rb_hash*)malloc(sizeof(rb_hash));
  hash->kh = kh_init(VALUE);
  return (VALUE) hash;
}

void rb_hash_dealloc(VALUE hash) {
  khiter_t k;
  kh_VALUE_t* khash = ((struct rb_hash*) hash)->kh;
  for (k = kh_begin(khash); k != kh_end(khash); ++k) {
    if(kh_exist(khash, k)) {
      rb_str_dealloc((VALUE)kh_key(khash, k));
      rb_str_dealloc((VALUE)kh_value(khash, k));
    }
  }
  kh_destroy(VALUE, khash);
  free((struct rb_hash *)hash);
}

void rb_hash_store(VALUE hash, VALUE key, VALUE value) {
  int ret;
  kh_VALUE_t* khash = ((struct rb_hash*) hash)->kh;
  unsigned k = kh_put(VALUE, khash, key, &ret);
  if (!ret) {
    kh_del(VALUE, khash, k);
  }
  kh_value(khash, k) = value;
}

void rb_hash_dump(VALUE hash) {
  char* lookup;
  char* key;
  kh_VALUE_t* khash = ((struct rb_hash*) hash)->kh;
  printf("{");
  khiter_t k;
  int count = 0;
  int size = kh_size(khash);
  for (k = kh_begin(khash); k != kh_end(khash); ++k) {
    if (kh_exist(khash, k)) {
      if(count++ != 0) {
        printf(",");
      }
      key = RB_CSTR(kh_key(khash, k));
      lookup = RB_CSTR(kh_value(khash, k));
      printf(" %s => %s", key, lookup);
      if(count == size) {
        printf(" ");
      }
    }
  }
  printf("}\n");
}

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

VALUE rb_hash_lookup(VALUE hash, VALUE key) {
  int absent;
  kh_VALUE_t* khash = ((struct rb_hash*) hash)->kh;
  khint_t k = kh_put(VALUE, khash, RB_CSTR(key), &absent);
  if(absent) {
    return Qnil;
  } else {
    return kh_value(khash, k);
  }
}

void rb_hash_dealloc(VALUE hash) {
  khiter_t k;
  kh_VALUE_t* khash = ((struct rb_hash*) hash)->kh;
  for (k = kh_begin(khash); k != kh_end(khash); ++k) {
    if(kh_exist(khash, k)) {
      /* rb_str_dealloc((VALUE)kh_key(khash, k)); */
      /* rb_str_dealloc((VALUE)kh_value(khash, k)); */
    }
  }
  kh_destroy(VALUE, khash);
  free((struct rb_hash *)hash);
}

void rb_hash_store(VALUE hash, VALUE key, VALUE value) {
  int ret;
  kh_VALUE_t* khash = ((struct rb_hash*) hash)->kh;
  khint_t k = kh_put(VALUE, khash, RB_CSTR(key), &ret);
  if (!ret) {
    kh_del(VALUE, khash, k);
  }
  kh_value(khash, k) = value;
}

void rb_hash_dump(VALUE hash) {
  VALUE lookup;
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
      key = (char*) kh_key(khash, k);
      lookup = kh_value(khash, k);
      if(lookup & 0x1) {
        printf(" %s => %d", key, RB_INT(lookup));
      } else {
        printf(" %s => %s", key, RB_CSTR(lookup));
      }
      if(count == size) {
        printf(" ");
      }
    }
  }
  printf("}\n");
}

#ifndef RB_STRING_H
#define RB_STRING_H

#include "object.h"
#include "vm.h"

struct RString {
  struct rb_object_header;
  char* content;
};

VALUE rb_str_new(char* text);
void rb_str_dealloc(VALUE string);

#endif

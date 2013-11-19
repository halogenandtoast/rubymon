#include "string.h"
#include <string.h>
#include <stdlib.h>

VALUE rb_str_new(char* text) {
  struct RString* str = (struct RString *)malloc(sizeof(struct RString));
  str->content = strdup(text);
  return (VALUE) str;
}

void rb_str_dealloc(struct RString* string) {
  free(string);
}

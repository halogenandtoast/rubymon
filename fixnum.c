#include "vm.h"
#include <stdio.h>

VALUE rb_fixnum_new(int num) {
  return (VALUE) ((num << 1) + 1);
}

VALUE rb_fixnum_add(VALUE left, VALUE right) {
  return rb_fixnum_new(RB_INT(left) + RB_INT(right));
}

VALUE rb_fixnum_sub(VALUE left, VALUE right) {
  return rb_fixnum_new(RB_INT(left) - RB_INT(right));
}

VALUE rb_fixnum_mult(VALUE left, VALUE right) {
  return rb_fixnum_new(RB_INT(left) * RB_INT(right));
}

VALUE rb_fixnum_div(VALUE left, VALUE right) {
  return rb_fixnum_new(RB_INT(left) / RB_INT(right));
}

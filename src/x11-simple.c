// mruby libraries
#include "mruby.h"
#include "mruby/array.h"
#include "mruby/data.h"
#include "mruby/string.h"

#include <X11/Xlib.h>

mrb_value x11_simple_test(mrb_state* mrb, mrb_value self)
{
  Display *dpy = XOpenDisplay(NULL);
  Window win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 256, 256, 0, 0, 0);
  XMapWindow(dpy, win);
  XFlush(dpy);
  while(1);
  return mrb_nil_value();
}

// initializer
void mrb_mruby_x11_simple_gem_init(mrb_state* mrb)
{
  struct RClass* rclass = mrb_define_module(mrb, "X11");
  mrb_define_class_method(mrb, rclass, "test", x11_simple_test, ARGS_NONE());
  return;
}

// finalizer
void mrb_mruby_x11_simple_gem_final(mrb_state* mrb)
{
  return;
}


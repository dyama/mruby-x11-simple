#include <stdio.h>
#include <stdlib.h>

// mruby libraries
#include "mruby.h"
#include "mruby/array.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "mruby/class.h"

#include <X11/Xlib.h>

struct x11_attr
{
  Display* disp;
  Window* win;
};

void x11_window_final(mrb_state* mrb, void* p)
{
  struct x11_attr* pw = (struct x11_attr*)p;
  mrb_free(mrb, pw->win);
  free(pw->disp);
  mrb_free(mrb, pw);
}

static struct mrb_data_type x11_window_type = { "X11Window", x11_window_final };

mrb_value x11_window_init(mrb_state* mrb, mrb_value self)
{
  struct x11_attr* attr = (struct x11_attr*)mrb_malloc(mrb, sizeof(struct x11_attr));
  attr->disp = XOpenDisplay(NULL);
  attr->win = mrb_malloc(mrb, sizeof(Window));
  *(attr->win) = XCreateSimpleWindow(attr->disp, DefaultRootWindow(attr->disp), 0, 0, 480, 360, 0, 0, 0);
  XMapWindow(attr->disp, *(attr->win));
  XFlush(attr->disp);

  DATA_PTR(self) = attr;
  DATA_TYPE(self) = &x11_window_type;
  return self;
}

struct x11_attr* x11_window_get(mrb_state* mrb, mrb_value obj)
{
  return (struct x11_attr*)mrb_get_datatype(mrb, obj, &x11_window_type);
}

mrb_value x11_window_handle(mrb_state* mrb, mrb_value self)
{
  struct x11_attr* attr = x11_window_get(mrb, self);
  int handle = (int)(attr->win);
  return mrb_fixnum_value(handle);
}

// initializer
void mrb_mruby_x11_simple_gem_init(mrb_state* mrb)
{
  struct RClass* rclass = mrb_define_class(mrb, "X11Window", mrb->object_class);
  MRB_SET_INSTANCE_TT(rclass, MRB_TT_DATA);
  mrb_define_class_method(mrb, rclass, "initialize", x11_window_init,   MRB_ARGS_NONE());
  mrb_define_class_method(mrb, rclass, "handle",     x11_window_handle, MRB_ARGS_NONE());
  return;
}

// finalizer
void mrb_mruby_x11_simple_gem_final(mrb_state* mrb)
{
  return;
}


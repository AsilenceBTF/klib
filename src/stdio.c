#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

// format string and put on the stdout
int printf(const char *fmt, ...) {
  panic("Not implemented");
}

// ap is a pointer to the fmt...  format string and store in the buff 
int vsprintf(char *out, const char *fmt, va_list ap) {
  char *c = out;

}

// format string and store in the buff
int sprintf(char *out, const char *fmt, ...) {
  panic("Not implemented");
}

// similar to sprintf, but limit the buff in byte n 
int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

// similar to vsprintf, but limit the buff in byte n 
int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif

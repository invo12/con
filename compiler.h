#ifndef conq_compiler_h
#define conq_compiler_h

#include "vm.h"
#include "object.h"

ObjFunction *compile(const char *source);

#endif

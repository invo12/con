//
// Created by invo on 2/17/2022.
//

#ifndef conq_object_h
#define conq_object_h

#include "common.h"
#include "value.h"
#include "chunk.h"

#define OBJ_TYPE(value)        (AS_OBJ(value)->type)

#define IS_CLOSURE(value)      isObjType(value, OBJ_CLOSURE)
#define AS_CLOSURE(value)      ((ObjClosure*)AS_OBJ(value))

#define IS_FUNCTION(value)     isObjType(value, OBJ_FUNCTION)
#define AS_FUNCTION(value)     ((ObjFunction*)AS_OBJ(value))

#define IS_NATIVE(value)       isObjType(value, OBJ_NATIVE)
#define AS_NATIVE(value) \
    (((ObjNative*)AS_OBJ(value))->function)

#define IS_STRING(value)       isObjType(value, OBJ_STRING)
#define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)

typedef enum {
    OBJ_CLOSURE,
    OBJ_FUNCTION,
    OBJ_NATIVE,
    OBJ_STRING,
    OBJ_UPVALUE
} ObjType;

struct Obj {
    ObjType type;
    struct Obj *next;
};

struct ObjString {
    Obj obj;
    int length;
    char *chars;
    uint32_t hash;
};


typedef struct {
    Obj obj;
    int arity;
    int upvalueCount;
    Chunk chunk;
    ObjString *name;
} ObjFunction;

typedef struct ObjUpvalue {
    Obj obj;
    Value *location;
    Value closed;
    struct ObjUpvalue* next;
} ObjUpvalue;

typedef struct {
    Obj obj;
    ObjFunction *function;
    ObjUpvalue** upvalues;
    int upvalueCount;
} ObjClosure;

typedef Value (*NativeFn)(int argCount, Value *args);

typedef struct {
    Obj obj;
    NativeFn function;
} ObjNative;

ObjString *copyString(const char *chars, int length);

ObjUpvalue *newUpvalue(Value *slot);

ObjClosure *newClosure(ObjFunction *function);

ObjFunction *newFunction();

ObjNative *newNative(NativeFn function);

ObjString *takeString(char *chars, int length);

void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif

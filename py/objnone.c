#include <stdlib.h>

#include "nlr.h"
#include "misc.h"
#include "mpconfig.h"
#include "qstr.h"
#include "obj.h"
#include "runtime0.h"

typedef struct _mp_obj_none_t {
    mp_obj_base_t base;
} mp_obj_none_t;

STATIC void none_print(void (*print)(void *env, const char *fmt, ...), void *env, mp_obj_t self_in, mp_print_kind_t kind) {
    print(env, "None");
}

STATIC mp_obj_t none_unary_op(int op, mp_obj_t o_in) {
    switch (op) {
        case MP_UNARY_OP_BOOL: return mp_const_false;
        default: return MP_OBJ_NOT_SUPPORTED;
    }
}

const mp_obj_type_t mp_type_NoneType = {
    { &mp_type_type },
    .name = MP_QSTR_NoneType,
    .print = none_print,
    .unary_op = none_unary_op,
};

const mp_obj_none_t mp_const_none_obj = {{&mp_type_NoneType}};

#include <stdint.h>

// options to control how Micro Python is built

#define MICROPY_ALLOC_PATH_MAX      (128)
#define MICROPY_EMIT_THUMB          (1)
#define MICROPY_EMIT_INLINE_THUMB   (1)
#define MICROPY_ENABLE_GC           (1)
#define MICROPY_ENABLE_FINALISER    (1)
#define MICROPY_HELPER_REPL         (1)
#define MICROPY_ENABLE_SOURCE_LINE  (1)
#define MICROPY_LONGINT_IMPL        (MICROPY_LONGINT_IMPL_MPZ)
#define MICROPY_FLOAT_IMPL          (MICROPY_FLOAT_IMPL_FLOAT)
#define MICROPY_OPT_COMPUTED_GOTO   (1)

#define MICROPY_PY_IO               (0)
#define MICROPY_PY_FROZENSET        (1)
#define MICROPY_PY_SYS_EXIT         (1)
#define MICROPY_PY_SYS_STDFILES     (1)
#define MICROPY_PY_CMATH            (1)

#define MICROPY_TIMER_REG           (0)
#define MICROPY_REG                 (MICROPY_TIMER_REG)

#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF   (1)
#define MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE  (0)

// extra built in names to add to the global namespace
extern const struct _mp_obj_fun_builtin_t mp_builtin_help_obj;
extern const struct _mp_obj_fun_builtin_t mp_builtin_input_obj;
extern const struct _mp_obj_fun_builtin_t mp_builtin_open_obj;
#define MICROPY_PORT_BUILTINS \
    { MP_OBJ_NEW_QSTR(MP_QSTR_help), (mp_obj_t)&mp_builtin_help_obj }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_input), (mp_obj_t)&mp_builtin_input_obj }, \

// extra built in modules to add to the list of known ones
extern const struct _mp_obj_module_t os_module;
extern const struct _mp_obj_module_t pyb_module;
extern const struct _mp_obj_module_t time_module;
#define MICROPY_PORT_BUILTIN_MODULES \
    { MP_OBJ_NEW_QSTR(MP_QSTR_pyb), (mp_obj_t)&pyb_module }, \

// extra constants
#define MICROPY_PORT_CONSTANTS \
    { MP_OBJ_NEW_QSTR(MP_QSTR_pyb), (mp_obj_t)&pyb_module }, \

// type definitions for the specific machine

#define BYTES_PER_WORD (4)

#define MICROPY_MAKE_POINTER_CALLABLE(p) ((void*)((mp_uint_t)(p) | 1))

#define UINT_FMT "%u"
#define INT_FMT "%d"

typedef int32_t mp_int_t; // must be pointer size
typedef unsigned int mp_uint_t; // must be pointer size
typedef void *machine_ptr_t; // must be of pointer size
typedef const void *machine_const_ptr_t; // must be of pointer size

// We have inlined IRQ functions for efficiency (they are generally
// 1 machine instruction).
//
// Note on IRQ state: you should not need to know the specific
// value of the state variable, but rather just pass the return
// value from disable_irq back to enable_irq.  If you really need
// to know the machine-specific values, see irq.h.

#ifndef __disable_irq
#define __disable_irq() __asm__ volatile("CPSID i");
#endif

__attribute__(( always_inline )) static inline uint32_t __get_PRIMASK(void) {
    uint32_t result;
    __asm volatile ("MRS %0, primask" : "=r" (result));
    return(result);
}

__attribute__(( always_inline )) static inline void __set_PRIMASK(uint32_t priMask) {
    __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}

__attribute__(( always_inline )) static inline void enable_irq(mp_uint_t state) {
    __set_PRIMASK(state);
}

__attribute__(( always_inline )) static inline mp_uint_t disable_irq(void) {
    mp_uint_t state = __get_PRIMASK();
    __disable_irq();
    return state;
}

#define MICROPY_BEGIN_ATOMIC_SECTION()     disable_irq()
#define MICROPY_END_ATOMIC_SECTION(state)  enable_irq(state)

// There is no classical C heap in bare-metal ports, only Python
// garbage-collected heap. For completeness, emulate C heap via
// GC heap. Note that MicroPython core never uses malloc() and friends,
// so these defines are mostly to help extension module writers.
#define malloc gc_alloc
#define free gc_free
#define realloc gc_realloc

// We need to provide a declaration/definition of alloca()
#include <alloca.h>

// The following would be from a board specific file, if one existed

#define MICROPY_HW_BOARD_NAME       "CC3200-LAUNCHXL"
#define MICROPY_HW_MCU_NAME         "CC3200"

/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <stdint.h>

#include "cc3200_hal.h"

#include "mpconfig.h"
#include "nlr.h"
#include "misc.h"
#include "qstr.h"
#include "obj.h"
#include "runtime.h"
#include "bufhelper.h"
#include "uart.h"
//#include "pybioctl.h"

/// \moduleref pyb
/// \class UART - duplex serial communication bus
///
/// UART implements the standard UART/USART duplex serial communications protocol.  At
/// the physical level it consists of 2 lines: RX and TX.
///
/// See usage model of I2C.  UART is very similar.  Main difference is
/// parameters to init the UART bus:
///
///     from pyb import UART
///
///     uart = UART(1, 9600)                         # init with given baudrate
///     uart.init(9600, bits=8, stop=1, parity=None) # init with given parameters
///
/// Bits can be 8 or 9, stop can be 1 or 2, parity can be None, 0 (even), 1 (odd).
///
/// Extra method:
///
///     uart.any()               # returns True if any characters waiting

struct _pyb_uart_obj_t {
    mp_obj_base_t base;
    pyb_uart_t uart_id;
    bool is_enabled;
    /* UART_HandleTypeDef */ void* uart;
};

// assumes Init parameters have been set up correctly
bool uart_init2(pyb_uart_obj_t *uart_obj) {

    return true;
}

bool uart_init(pyb_uart_obj_t *uart_obj, uint32_t baudrate) {

    return uart_init2(uart_obj);
}

void uart_deinit(pyb_uart_obj_t *uart_obj) {

}

bool uart_rx_any(pyb_uart_obj_t *uart_obj) {
    return true;
}

int uart_rx_char(pyb_uart_obj_t *uart_obj) {
    return '0';
}

void uart_tx_char(pyb_uart_obj_t *uart_obj, int c) {
}

void uart_tx_strn(pyb_uart_obj_t *uart_obj, const char *str, uint len) {
}

void uart_tx_strn_cooked(pyb_uart_obj_t *uart_obj, const char *str, uint len) {
}

/******************************************************************************/
/* Micro Python bindings                                                      */

STATIC void pyb_uart_print(void (*print)(void *env, const char *fmt, ...), void *env, mp_obj_t self_in, mp_print_kind_t kind) {

}

/// \method init(baudrate, *, bits=8, stop=1, parity=None)
///
/// Initialise the SPI bus with the given parameters:
///
///   - `baudrate` is the clock rate.
///   - `bits` is the number of bits per byte, 8 or 9.
///   - `stop` is the number of stop bits, 1 or 2.
///   - `parity` is the parity, `None`, 0 (even) or 1 (odd).
STATIC const mp_arg_t pyb_uart_init_args[] = {
    { MP_QSTR_baudrate, MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 9600} },
    { MP_QSTR_bits,     MP_ARG_KW_ONLY | MP_ARG_INT,  {.u_int = 8} },
    { MP_QSTR_stop,     MP_ARG_KW_ONLY | MP_ARG_INT,  {.u_int = 1} },
    { MP_QSTR_parity,   MP_ARG_KW_ONLY | MP_ARG_OBJ,  {.u_obj = mp_const_none} },
};
#define PYB_UART_INIT_NUM_ARGS MP_ARRAY_SIZE(pyb_uart_init_args)

STATIC mp_obj_t pyb_uart_init_helper(pyb_uart_obj_t *self, mp_uint_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    return mp_const_none;
}

/// \classmethod \constructor(bus, ...)
///
/// Construct a UART object on the given bus.  `bus` can be 1-6, or 'XA', 'XB', 'YA', or 'YB'.
/// With no additional parameters, the UART object is created but not
/// initialised (it has the settings from the last initialisation of
/// the bus, if any).  If extra arguments are given, the bus is initialised.
/// See `init` for parameters of initialisation.
///
/// The physical pins of the UART busses are:
///
///   - `UART(4)` is on `XA`: `(TX, RX) = (X1, X2) = (PA0, PA1)`
///   - `UART(1)` is on `XB`: `(TX, RX) = (X9, X10) = (PB6, PB7)`
///   - `UART(6)` is on `YA`: `(TX, RX) = (Y1, Y2) = (PC6, PC7)`
///   - `UART(3)` is on `YB`: `(TX, RX) = (Y9, Y10) = (PB10, PB11)`
///   - `UART(2)` is on: `(TX, RX) = (X3, X4) = (PA2, PA3)`
STATIC mp_obj_t pyb_uart_make_new(mp_obj_t type_in, mp_uint_t n_args, mp_uint_t n_kw, const mp_obj_t *args) {
    return mp_const_none;
}

STATIC mp_obj_t pyb_uart_init(mp_uint_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    return pyb_uart_init_helper(args[0], n_args - 1, args + 1, kw_args);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(pyb_uart_init_obj, 1, pyb_uart_init);

/// \method deinit()
/// Turn off the UART bus.
STATIC mp_obj_t pyb_uart_deinit(mp_obj_t self_in) {
    pyb_uart_obj_t *self = self_in;
    uart_deinit(self);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(pyb_uart_deinit_obj, pyb_uart_deinit);

/// \method any()
/// Return `True` if any characters waiting, else `False`.
STATIC mp_obj_t pyb_uart_any(mp_obj_t self_in) {
    pyb_uart_obj_t *self = self_in;
    if (uart_rx_any(self)) {
        return mp_const_true;
    } else {
        return mp_const_false;
    }
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(pyb_uart_any_obj, pyb_uart_any);

/// \method send(send, *, timeout=5000)
/// Send data on the bus:
///
///   - `send` is the data to send (an integer to send, or a buffer object).
///   - `timeout` is the timeout in milliseconds to wait for the send.
///
/// Return value: `None`.
STATIC const mp_arg_t pyb_uart_send_args[] = {
    { MP_QSTR_send,    MP_ARG_REQUIRED | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
    { MP_QSTR_timeout, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 5000} },
};
#define PYB_UART_SEND_NUM_ARGS MP_ARRAY_SIZE(pyb_uart_send_args)

STATIC mp_obj_t pyb_uart_send(mp_uint_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(pyb_uart_send_obj, 1, pyb_uart_send);

/// \method recv(recv, *, timeout=5000)
///
/// Receive data on the bus:
///
///   - `recv` can be an integer, which is the number of bytes to receive,
///     or a mutable buffer, which will be filled with received bytes.
///   - `timeout` is the timeout in milliseconds to wait for the receive.
///
/// Return value: if `recv` is an integer then a new buffer of the bytes received,
/// otherwise the same buffer that was passed in to `recv`.
STATIC const mp_arg_t pyb_uart_recv_args[] = {
    { MP_QSTR_recv,    MP_ARG_REQUIRED | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
    { MP_QSTR_timeout, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 5000} },
};
#define PYB_UART_RECV_NUM_ARGS MP_ARRAY_SIZE(pyb_uart_recv_args)

STATIC mp_obj_t pyb_uart_recv(mp_uint_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(pyb_uart_recv_obj, 1, pyb_uart_recv);

STATIC const mp_map_elem_t pyb_uart_locals_dict_table[] = {
    // instance methods
    { MP_OBJ_NEW_QSTR(MP_QSTR_init), (mp_obj_t)&pyb_uart_init_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_deinit), (mp_obj_t)&pyb_uart_deinit_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_any), (mp_obj_t)&pyb_uart_any_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_send), (mp_obj_t)&pyb_uart_send_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_recv), (mp_obj_t)&pyb_uart_recv_obj },
};

STATIC MP_DEFINE_CONST_DICT(pyb_uart_locals_dict, pyb_uart_locals_dict_table);

mp_uint_t uart_ioctl(mp_obj_t self_in, mp_uint_t request, int *errcode, ...) {
    mp_uint_t ret = 0;
    return ret;
}

STATIC const mp_stream_p_t uart_stream_p = {
    //.read = uart_read, // TODO
    //.write = uart_write, // TODO
    .ioctl = uart_ioctl,
    .is_text = false,
};

const mp_obj_type_t pyb_uart_type = {
    { &mp_type_type },
    .name = MP_QSTR_UART,
    .print = pyb_uart_print,
    .make_new = pyb_uart_make_new,
    .stream_p = &uart_stream_p,
    .locals_dict = (mp_obj_t)&pyb_uart_locals_dict,
};

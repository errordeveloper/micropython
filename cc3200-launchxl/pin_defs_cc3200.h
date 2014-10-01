/*
 * This file is part of the CC3200-LAUNCHXL port of the Micro Python project
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Daniel Campora
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
#ifndef CC3200_LAUNCHXL_PIN_DEFS_CC3200_H_
#define CC3200_LAUNCHXL_PIN_DEFS_CC3200_H_


enum {
  PORT_A,
  PORT_B,
  PORT_C,
  PORT_D,
  PORT_E,
  PORT_Z,
};

enum {
    AF_FN_FTM,
    AF_FN_I2C,
    AF_FN_UART,
    AF_FN_SPI
};

enum {
    AF_PIN_TYPE_FTM_CH0 = 0,
    AF_PIN_TYPE_FTM_CH1,
    AF_PIN_TYPE_FTM_CH2,
    AF_PIN_TYPE_FTM_CH3,
    AF_PIN_TYPE_FTM_CH4,
    AF_PIN_TYPE_FTM_CH5,
    AF_PIN_TYPE_FTM_CH6,
    AF_PIN_TYPE_FTM_CH7,
    AF_PIN_TYPE_FTM_QD_PHA,
    AF_PIN_TYPE_FTM_QD_PHB,

    AF_PIN_TYPE_I2C_SDA = 0,
    AF_PIN_TYPE_I2C_SCL,

    AF_PIN_TYPE_SPI_MOSI = 0,
    AF_PIN_TYPE_SPI_MISO,
    AF_PIN_TYPE_SPI_SCK,
    AF_PIN_TYPE_SPI_NSS,

    AF_PIN_TYPE_UART_TX = 0,
    AF_PIN_TYPE_UART_RX,
    AF_PIN_TYPE_UART_CTS,
    AF_PIN_TYPE_UART_RTS,
};

#define PIN_DEFS_PORT_AF_UNION \
    I2C_TypeDef   *I2C; \
    UART_TypeDef  *UART; \
    SPI_TypeDef   *SPI;

typedef GPIO_TypeDef pin_gpio_t;



#endif /* CC3200_LAUNCHXL_PIN_DEFS_CC3200_H_ */

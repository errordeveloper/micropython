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
#ifndef CC3200_LAUNCHXL_HAL_CC3200_HAL_H_
#define CC3200_LAUNCHXL_HAL_CC3200_HAL_H_


/*----------------------------------------------------------------------------
** Declare exported functions
*/

extern uint32_t HAL_GetTick(void);

extern void HAL_Delay(uint32_t Delay);

typedef struct {
    uint32_t dummy;
} I2C_TypeDef;

typedef struct {
    uint32_t dummy;
} UART_TypeDef;

typedef struct {
    uint32_t dummy;
} SPI_TypeDef;

typedef struct {
    volatile    uint32_t    PDOR;   // Output register
    volatile    uint32_t    PSOR;   // Set output register
    volatile    uint32_t    PCOR;   // Clear output register
    volatile    uint32_t    PTOR;   // Toggle output register
    volatile    uint32_t    PDIR;   // Data Input register
    volatile    uint32_t    PDDR;   // Data Direction register
    volatile    uint32_t    MODER;  // TODO: Fix this
} GPIO_TypeDef;

#define GPIO_OUTPUT_TYPE    ((uint32_t)0x00000010)  // Indicates OD

#define GPIO_MODE_INPUT     ((uint32_t)0x00000000)
#define GPIO_MODE_OUTPUT_PP ((uint32_t)0x00000001)
#define GPIO_MODE_OUTPUT_OD ((uint32_t)0x00000011)
#define GPIO_MODE_AF_PP     ((uint32_t)0x00000002)
#define GPIO_MODE_AF_OD     ((uint32_t)0x00000012)
#define GPIO_MODE_ANALOG    ((uint32_t)0x00000003)

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_MODE_INPUT)              ||\
                            ((MODE) == GPIO_MODE_OUTPUT_PP)          ||\
                            ((MODE) == GPIO_MODE_OUTPUT_OD)          ||\
                            ((MODE) == GPIO_MODE_AF_PP)              ||\
                            ((MODE) == GPIO_MODE_AF_OD)              ||\
                            ((MODE) == GPIO_MODE_ANALOG))

#define GPIO_NOPULL         ((uint32_t)0)
#define GPIO_PULLUP         ((uint32_t)1)
#define GPIO_PULLDOWN       ((uint32_t)2)

#define IS_GPIO_PULL(PULL) (((PULL) == GPIO_NOPULL) || ((PULL) == GPIO_PULLUP) || \
                            ((PULL) == GPIO_PULLDOWN))

#define  GPIO_SPEED_LOW         ((uint32_t)0)
#define  GPIO_SPEED_MEDIUM      ((uint32_t)1)
#define  GPIO_SPEED_FAST        ((uint32_t)2)
#define  GPIO_SPEED_HIGH        ((uint32_t)3)

#define IS_GPIO_AF(af)      ((af) >= 0 && (af) <= 7)

typedef struct {
    uint32_t    Pin;
    uint32_t    Mode;
    uint32_t    Pull;
    uint32_t    Speed;
    uint32_t    Alternate;
} GPIO_InitTypeDef;

#define GPIO_PORT_TO_PORT_NUM(GPIOx) \
    ((&GPIOx->PDOR - &GPIOA_PDOR) / (&GPIOB_PDOR - &GPIOA_PDOR))

#define GPIO_PIN_TO_PORT_PCR(GPIOx, pin) \
    (&PORTA_PCR0 + (GPIO_PORT_TO_PORT_NUM(GPIOx) * 0x400) + (pin))

#define GPIO_AF2_I2C0   2
#define GPIO_AF2_I2C1   2
#define GPIO_AF2_SPI0   2
#define GPIO_AF3_FTM0   3
#define GPIO_AF3_FTM1   3
#define GPIO_AF3_FTM2   3
#define GPIO_AF3_UART0  3
#define GPIO_AF3_UART1  3
#define GPIO_AF3_UART2  3
#define GPIO_AF4_FTM0   4
#define GPIO_AF6_FTM1   6
#define GPIO_AF6_FTM2   6
#define GPIO_AF6_I2C1   6
#define GPIO_AF7_FTM1   7

__attribute__(( always_inline )) static inline void __WFI(void) {
  __asm volatile ("wfi");
}

extern void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *init);

#define GPIO_read_pin(gpio, pin)        (((gpio)->PDIR >> (pin)) & 1)
#define GPIO_set_pin(gpio, pin_mask)    (((gpio)->PSOR) = (pin_mask))
#define GPIO_clear_pin(gpio, pin_mask)  (((gpio)->PCOR) = (pin_mask))
#define GPIO_read_output_pin(gpio, pin) (((gpio)->PDOR >> (pin)) & 1)

#endif /* CC3200_LAUNCHXL_HAL_CC3200_HAL_H_ */

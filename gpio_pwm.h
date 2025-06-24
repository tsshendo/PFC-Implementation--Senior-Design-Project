#ifndef GPIO_PWM_H
#define GPIO_PWM_H

#include "svpwm.h"  // for SVPWMOutput

/**
 * @brief Initialize GPIO pins for gate control (optional)
 */
void gpio_pwm_init(void);

/**
 * @brief Set target PWM duty cycles (normalized 0.0 to 1.0)
 */
void gpio_pwm_set_duty(SVPWMOutput pwm_output);

/**
 * @brief Call this function on every timer tick (e.g. 10 µs at 100 kHz)
 */
void gpio_pwm_update(void);

#endif // GPIO_PWM_H

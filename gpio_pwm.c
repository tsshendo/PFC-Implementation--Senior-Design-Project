#include "gpio_pwm.h"
#include "gpio.h"  // Assuming this has GPIO_setPxxState()

#define PWM_FREQ_HZ     100000
#define CPU_FREQ_HZ     60000000
#define PWM_PERIOD_TICKS (CPU_FREQ_HZ / PWM_FREQ_HZ)

static uint16_t pwm_counter = 0;

// Duty cycle storage
static float duty_a_high = 0.0f;
static float duty_a_low  = 0.0f;
static float duty_b_high = 0.0f;
static float duty_b_low  = 0.0f;
static float duty_c_high = 0.0f;
static float duty_c_low  = 0.0f;

void gpio_pwm_set_duty(SVPWMOutput pwm_output) {
    duty_a_high = pwm_output.duty_a_high;
    duty_a_low  = pwm_output.duty_a_low;
    duty_b_high = pwm_output.duty_b_high;
    duty_b_low  = pwm_output.duty_b_low;
    duty_c_high = pwm_output.duty_c_high;
    duty_c_low  = pwm_output.duty_c_low;
}

void gpio_pwm_update(void) {
    pwm_counter++;
    if (pwm_counter >= PWM_PERIOD_TICKS)
        pwm_counter = 0;

    float t = (float)pwm_counter / PWM_PERIOD_TICKS;

    // PHASE A ? P08 (High), P09 (Low)
    GPIO_setP08State(t < duty_a_high ? GPIO_STATE_HIGH : GPIO_STATE_LOW); // High Side
    GPIO_setP09State(t < duty_a_low  ? GPIO_STATE_HIGH : GPIO_STATE_LOW); // Low Side

    // PHASE B ? P06 (High), P07 (Low)
    GPIO_setP06State(t < duty_b_high ? GPIO_STATE_HIGH : GPIO_STATE_LOW); // High Side
    GPIO_setP07State(t < duty_b_low  ? GPIO_STATE_HIGH : GPIO_STATE_LOW); // Low Side

    // PHASE C ? P04 (High), P05 (Low)
    GPIO_setP04State(t < duty_c_high ? GPIO_STATE_HIGH : GPIO_STATE_LOW); // High Side
    GPIO_setP05State(t < duty_c_low  ? GPIO_STATE_HIGH : GPIO_STATE_LOW); // Low Side
}

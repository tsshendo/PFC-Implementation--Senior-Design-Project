#ifndef SVPWM_H
#define SVPWM_H

typedef struct {
    float duty_a_high;
    float duty_a_low;
    float duty_b_high;
    float duty_b_low;
    float duty_c_high;
    float duty_c_low;
} SVPWMOutput;

/**
 * @brief Generate 3-phase PWM duty cycles for high-side and low-side FETs
 * @param alpha Alpha-axis voltage
 * @param beta  Beta-axis voltage
 * @return High and low side duty cycles for phases A, B, C
 */
SVPWMOutput svpwm_generate(float alpha, float beta);

#endif // SVPWM_H

#include "svpwm.h"
#include <math.h>

#define SQRT3 1.7320508f

SVPWMOutput svpwm_generate(float alpha, float beta) {
    SVPWMOutput out;

    // Project aﬂ into three-phase signals
    float tA = alpha;
    float tB = -0.5f * alpha + (SQRT3 / 2.0f) * beta;
    float tC = -0.5f * alpha - (SQRT3 / 2.0f) * beta;

    // Center the signals (space vector balancing)
    float t_min = fminf(fminf(tA, tB), tC);
    float t_max = fmaxf(fmaxf(tA, tB), tC);
    float t_mid = 0.5f * (t_max + t_min);

    float dA = tA - t_mid + 0.5f;
    float dB = tB - t_mid + 0.5f;
    float dC = tC - t_mid + 0.5f;

    // Clamp and assign high/low side
    dA = fminf(fmaxf(dA, 0.0f), 1.0f);
    dB = fminf(fmaxf(dB, 0.0f), 1.0f);
    dC = fminf(fmaxf(dC, 0.0f), 1.0f);

    out.duty_a_high = dA;
    out.duty_a_low  = 1.0f - dA;

    out.duty_b_high = dB;
    out.duty_b_low  = 1.0f - dB;

    out.duty_c_high = dC;
    out.duty_c_low  = 1.0f - dC;

    return out;
}

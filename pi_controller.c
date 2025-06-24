/*******************************************************************************
 * @file    pi_controller.c
 * @brief   Generic PI controller implementation with anti-windup and clamping
 *******************************************************************************/

#include "pi_controller.h"

/*******************************************************************************
 * @brief   Run a single PI controller instance
 * @param   pi        Pointer to PIController struct with gains/state
 * @param   ref       Reference input (e.g. I_d_ref)
 * @param   feedback  Measured value (e.g. I_d from Park transform)
 * @param   dt        Time step (seconds)
 * @return  Output of the PI controller (e.g. V_d)
 *******************************************************************************/
float pi_update(PIController* pi, float ref, float feedback, float dt) {
    float error = ref - feedback;

    // Integrate error
    pi->integral += pi->ki * error * dt;

    // Anti-windup (integral clamp)
    if (pi->integral > pi->out_max) pi->integral = pi->out_max;
    else if (pi->integral < pi->out_min) pi->integral = pi->out_min;

    // PI output
    float output = pi->kp * error + pi->integral;

    // Clamp output
    if (output > pi->out_max) output = pi->out_max;
    else if (output < pi->out_min) output = pi->out_min;

    return output;
}

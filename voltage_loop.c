/*******************************************************************************
 * @file    voltage_loop.c
 * @brief   Outer voltage loop to generate I_d_ref from output voltage error
 *******************************************************************************/

#include "voltage_loop.h"

/*******************************************************************************
**                              External Variable                             **
*******************************************************************************/
extern volatile float V_OUT;  // Measured DC output voltage from sensors
extern volatile float V_D;

/*******************************************************************************
**                             Configuration Constants                        **
*******************************************************************************/
//#define V_REF            // Desired output DC voltage (Volts)
#define VLOOP_DT    0.0001f   // Voltage loop update interval (100 µs)

#define V_KP        5.0f     // Proportional gain
#define V_KI        20.0f     // Integral gain

#define ID_MIN      0.0f      // Clamp I_d_ref to prevent negative values
#define ID_MAX      5.0f     // Upper current reference limit

/*******************************************************************************
**                          Internal State Variables                          **
*******************************************************************************/
static float vloop_integral = 0.0f;
float v_ref;
/*******************************************************************************
 * @brief   Update voltage loop and compute I_d_ref
 * @return  I_d_ref value to feed into D-axis PI controller
 *******************************************************************************/
float voltage_loop_update(void) {
		v_ref = 1.8;
    float error = v_ref - V_OUT;

    // Integrate error
    vloop_integral += V_KI * error * VLOOP_DT;

    // Anti-windup: clamp integral
    if (vloop_integral > ID_MAX) vloop_integral = ID_MAX;
    else if (vloop_integral < ID_MIN) vloop_integral = ID_MIN;

    // Compute output
    float id_ref = V_KP * error + vloop_integral;

    // Clamp I_d_ref output
    if (id_ref > ID_MAX) id_ref = ID_MAX;
    else if (id_ref < ID_MIN) id_ref = ID_MIN;

    return id_ref;
}

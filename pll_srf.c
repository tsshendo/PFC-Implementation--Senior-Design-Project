/*******************************************************************************
 * @file    pll.c
 * @brief   3-phase Synchronous Reference Frame PLL (angle + frequency estimator)
 *******************************************************************************/

#include "pll_srf.h"
#include <math.h>

#define M_PI 3.14159265358979323846f
/*******************************************************************************
**                         PLL State Variables (static)                       **
*******************************************************************************/
// Constants
#define TS            0.0001f             // 100 µs sample time
#define TWO_PI        (2.0f * M_PI)
#define FN            60.0f               // Nominal grid frequency
#define PLL_KP        300.0f        // From TI code
#define PLL_KI        60000.0f  // Adjusted from MATLAB
#define PLL_VMAX      200.0f              // Clamp filter output

// Control step time
#define PLL_DT     0.0001f  // 100 µs

// State variables
static float theta = 0.0f;
static float omega = 2 * M_PI * FN;
static float ylf = 0.0f;
static float v_q_prev = 0.0f;

extern volatile float I_A;
extern volatile float I_B;
extern volatile float I_C;

extern volatile float V_A;
extern volatile float V_B;
extern volatile float V_C;

extern volatile float I_ALPHA;
extern volatile float I_BETA;
extern volatile float V_ALPHA;
extern volatile float V_BETA;

float V_Q;
float V_D;
/*******************************************************************************
 * @brief   Update PLL state using V_alpha and V_beta from Clarke transform
 * @param   alpha Clarke alpha voltage component
 * @param   beta  Clarke beta voltage component
 * @return  PLLResult containing updated phase angle and frequency
 *******************************************************************************/
 
PLLResult pll_update(void) {
		PLLResult result;
    // Compute Park Q-axis voltage (error signal)
		// Park Transform (Q-axis only used)
		float v_d =  V_ALPHA * cosf(theta) + V_BETA * sinf(theta);
		float v_q = -V_ALPHA * sinf(theta) + V_BETA * cosf(theta);
	
		V_Q = v_q;
		V_D = v_d;

    // Loop Filter (IIR PI)
    ylf += PLL_KP * (v_q - v_q_prev) + PLL_KI * v_q;
    if (ylf > PLL_VMAX) ylf = PLL_VMAX;
    if (ylf < -PLL_VMAX) ylf = -PLL_VMAX;

    v_q_prev = v_q;

    // Frequency estimate (rad/s)
    omega = TWO_PI * FN + ylf;

    // Integrate to get theta
    theta += omega * TS;
    if (theta >= TWO_PI) theta -= TWO_PI;
    if (theta < 0.0f)    theta += TWO_PI;

    // Output
    result.theta = theta;
    result.omega = omega;
		
    return result;
}

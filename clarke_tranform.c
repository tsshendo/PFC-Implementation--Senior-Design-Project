/*******************************************************************************
 * @file    clarke_transform.c
 * @brief   Clarke Transformation (abc ? alpha-beta-zero) implementation
 *          Converts 3-phase currents (I_A, I_B, I_C) into a/ﬂ/0 components
 *******************************************************************************/

#include "clarke_transform.h"
#include "math.h"

/*******************************************************************************
**                            External Variables                              **
*******************************************************************************/
extern volatile float I_A;
extern volatile float I_B;
extern volatile float I_C;

extern volatile float V_A;
extern volatile float V_B;
extern volatile float V_C;


float I_ALPHA;
float I_BETA;
float V_ALPHA;
float V_BETA;
/*******************************************************************************
 * @brief   Perform Clarke transform using global current values
 * @return  ClarkeOutput structure with alpha, beta, and zero-sequence current
 *******************************************************************************/
ClarkeOutput clarke_transform_currents(void) {
    ClarkeOutput out;

    // Clarke Transform equations (stationary aﬂ0 frame)
    I_ALPHA = out.alpha = (1.0f / 3.0f) * ((2.0f * I_A) - I_B - I_C);
    I_BETA =  out.beta  = (1.0f / sqrt(3)) * (I_B - I_C); 
    //out.zero  = (1.0f / 3.0f) * (I_A + I_B + I_C);           // optional for diagnostics

    return out;
}

ClarkeOutput clarke_transform_voltages(void) {
    ClarkeOutput out;

    V_ALPHA = out.alpha = (1.0f / 3.0f) * ((2.0f * V_A) - V_B - V_C);
    V_BETA = out.beta  = (1.0f / sqrt(3)) * (V_B - V_C); 
    //out.zero  = (1.0f / 3.0f) * (V_A + V_B + V_C);

    return out;
}

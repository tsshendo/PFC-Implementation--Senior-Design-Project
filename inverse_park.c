/*******************************************************************************
 * @file    inverse_park.c
 * @brief   Inverse Park Transform (dq ? aﬂ) for voltage vector rotation
 *******************************************************************************/

#include "inverse_park.h"
#include <math.h>

/*******************************************************************************
 * @brief   Perform inverse Park transform
 * @param   d     D-axis voltage (aligned with angle)
 * @param   q     Q-axis voltage (orthogonal)
 * @param   theta Angle in radians (from PLL)
 * @return  AlphaBeta structure with a and ﬂ voltages
 *******************************************************************************/
AlphaBeta inverse_park_transform(float d, float q, float theta) {
    AlphaBeta out;

    float sin_theta = sinf(theta);
    float cos_theta = cosf(theta);

    out.alpha = d * cos_theta - q * sin_theta;
    out.beta  = d * sin_theta + q * cos_theta;

    return out;
}

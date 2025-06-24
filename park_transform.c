/*******************************************************************************
 * @file    park_transform.c
 * @brief   Park and Inverse Park Transforms (aﬂ ? dq)
 *******************************************************************************/

#include "park_transform.h"
#include <math.h>

/*******************************************************************************
 * @brief   Forward Park Transform (aﬂ ? dq)
 * @param   alpha Alpha-axis input (stationary frame)
 * @param   beta  Beta-axis input (stationary frame)
 * @param   theta Angle in radians from PLL (electrical angle)
 * @return  ParkDQ structure containing D- and Q-axis values
 *******************************************************************************/
ParkDQ park_transform(float alpha, float beta, float theta) {
    ParkDQ out;
    float sin_theta = sinf(theta);
    float cos_theta = cosf(theta);

    out.d =  alpha * cos_theta + beta * sin_theta;
    out.q = -alpha * sin_theta + beta * cos_theta;

    return out;
}

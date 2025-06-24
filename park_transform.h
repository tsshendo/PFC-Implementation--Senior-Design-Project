#ifndef PARK_TRANSFORM_H
#define PARK_TRANSFORM_H

// Output structure for Park transform
typedef struct {
    float d;
    float q;
} ParkDQ;

/**
 * @brief Forward Park Transform (aﬂ ? dq)
 * @param alpha Alpha-axis input
 * @param beta  Beta-axis input
 * @param theta Angle in radians (from PLL)
 * @return Struct containing D and Q outputs
 */
ParkDQ park_transform(float alpha, float beta, float theta);

#endif // PARK_TRANSFORM_H

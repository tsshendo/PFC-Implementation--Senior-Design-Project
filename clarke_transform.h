#ifndef CLARKE_TRANSFORM_H
#define CLARKE_TRANSFORM_H

// Output of Clarke transform
typedef struct {
    float alpha;  // Alpha-axis (stationary horizontal axis)
    float beta;   // Beta-axis (stationary vertical axis)
    //float zero;   // Zero-sequence (optional, used in diagnostics)
} ClarkeOutput;

/**
 * @brief Perform Clarke transformation on I_A, I_B, I_C
 * @return ClarkeOutput structure
 */
ClarkeOutput clarke_transform_currents(void);

/**
 * @brief Clarke transform for 3-phase voltages (V_A/B/C)
 */
ClarkeOutput clarke_transform_voltages(void);

#endif // CLARKE_TRANSFORM_H

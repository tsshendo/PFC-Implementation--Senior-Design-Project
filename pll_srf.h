#ifndef PLL_H
#define PLL_H

typedef struct {
    float theta;  // Phase angle (radians)
    float omega;  // Angular frequency (rad/s)
} PLLResult;

/**
 * @brief Update the 3-phase PLL based on alpha/beta inputs
 * @param alpha Clarke alpha voltage
 * @param beta  Clarke beta voltage
 * @return Updated theta and omega
 */
PLLResult pll_update(void);

#endif // PLL_H

#ifndef INVERSE_PARK_H
#define INVERSE_PARK_H

typedef struct {
    float alpha;
    float beta;
} AlphaBeta;

/**
 * @brief Perform inverse Park transform (dq ? aﬂ)
 * @param d     D-axis input
 * @param q     Q-axis input
 * @param theta Phase angle (radians)
 * @return AlphaBeta structure
 */
AlphaBeta inverse_park_transform(float d, float q, float theta);

#endif // INVERSE_PARK_H

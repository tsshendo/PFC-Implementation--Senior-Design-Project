#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H

// PI controller state and config
typedef struct {
    float kp;
    float ki;
    float integral;
    float out_min;
    float out_max;
} PIController;

/**
 * @brief Update a PI controller
 * @param pi        Pointer to PIController object
 * @param ref       Setpoint/reference value
 * @param feedback  Measured value
 * @param dt        Time step
 * @return Output of the PI controller
 */
float pi_update(PIController* pi, float ref, float feedback, float dt);

#endif // PI_CONTROLLER_H

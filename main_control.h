#ifndef MAIN_CONTROL_H
#define MAIN_CONTROL_H

/**
 * @brief Run one control cycle.
 *        Should be called at the PWM switching frequency (e.g., 100 kHz).
 */
void control_loop_step(void);

#endif // MAIN_CONTROL_H

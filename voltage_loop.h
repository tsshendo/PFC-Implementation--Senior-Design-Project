#ifndef VOLTAGE_LOOP_H
#define VOLTAGE_LOOP_H

/**
 * @brief Run the outer voltage loop PI controller
 * @return I_d_ref value (current ref for D-axis current controller)
 */
float voltage_loop_update(void);

#endif // VOLTAGE_LOOP_H

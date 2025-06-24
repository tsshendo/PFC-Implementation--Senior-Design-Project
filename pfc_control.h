/*******************************************************************************
**                         PFC Control Header File                            **
*******************************************************************************/

#ifndef PFC_CONTROL_H
#define PFC_CONTROL_H

#include <stdint.h>

typedef struct {
    float Va, Vb, Vc; // 3-phase voltages
    float Ia, Ib, Ic; // 3-phase currents
    float Vout_sense;
    float Iout_sense;
} PFC_Input;

typedef struct {
    float duty_a, duty_b, duty_c; // Duty cycles for SVPWM
} PFC_Output;

void pfc_control_init(void);
void pfc_control_step(PFC_Input *in, PFC_Output *out);

#endif // PFC_CONTROL_H

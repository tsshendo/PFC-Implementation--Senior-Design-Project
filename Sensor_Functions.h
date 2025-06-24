#ifndef SENSOR_FUNCTIONS_H
#define SENSOR_FUNCTIONS_H

#include "types.h"  // for uint16, etc.

/*******************************************************************************
 * Global sensor readings (read-only for control logic)
 *******************************************************************************/
extern float I_A;
extern float I_B;
extern float I_C;
extern float I_OUT; // Not yet implemented
extern float V_A;
extern float V_B;
extern float V_C;
extern float V_OUT;

/*******************************************************************************
 * ADC polling and per-channel read functions
 *******************************************************************************/
 void Sensor_Init(void);
void PollADC1(void);

void V_Sense_A(void);
void V_Sense_B(void);
void V_Sense_C(void);

void I_Sense_A(void);
void I_Sense_B(void);
void I_Sense_C(void);

#endif // SENSOR_FUNCTIONS_H

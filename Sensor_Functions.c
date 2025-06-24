/*******************************************************************************
This file contains the functions that read the Voltage and Current Sensor Readings 
and Store them as a global variable which can be used for further calculation
*******************************************************************************/

/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "tle_device.h"
#include "types.h"
#include "adc1.h"
#include "gpio.h"
#include "stdlib.h"
#include "math.h"


/*******************************************************************************
**                                 Variables                                  **
*******************************************************************************/


// GLOBAL VARIABLES
float I_A;
float I_B;
float I_C;
float V_A;
float V_B;
float V_C;

// Local Variables
// ADC1 Variables
uint16 v_sense_a;
uint16 v_sense_b;
uint16 v_sense_c;
uint16 v_sense_out;
uint16 i_sense_a;
uint16 i_sense_b;
uint16 i_sense_c;
uint16 i_sense_out;	// Currently not hoooked up properly.
// Buffers for SMA averaging of values
float v_a_buffer[3] = {0.0f,0.0f,0.0f};
float v_b_buffer[3] = {0.0f,0.0f,0.0f};
float v_c_buffer[3] = {0.0f,0.0f,0.0f};
float v_out_buffer[3] = {0.0f,0.0f,0.0f};
float i_a_buffer[3] = {0.0f,0.0f,0.0f};
float i_b_buffer[3] = {0.0f,0.0f,0.0f};
float i_c_buffer[3] = {0.0f,0.0f,0.0f};
// Indexing for buffers
uint8 v_a_index = 0;
uint8 v_b_index = 0;
uint8 v_c_index = 0;
uint8 v_out_index = 0;
uint8 i_a_index = 0;
uint8 i_b_index = 0;
uint8 i_c_index = 0;


/*******************************************************************************
**                           Function Declarations                            **
*******************************************************************************/
void Sensor_Init(void) {
	// Initialize sensor values to 0
	I_A = 0;
	I_B = 0;
	I_C = 0;
	V_A = 0;
	V_B = 0;
	V_C = 0;
}

void PollADC1(void) {
	// Start Sequences 0-3, called in Main
	ADC1_startSequence(ADC1_SEQ0);
	ADC1_startSequence(ADC1_SEQ1);
	ADC1_startSequence(ADC1_SEQ2);
}

void V_Sense_A(void){
	// Read ADC1 Channel 0
	ADC1_getChResult_mV(&v_sense_a,ADC1_DCH0);
	float value = ((v_sense_a * 0.001) - 2.5) * 36 / sqrt(3); // See Sensor Schematic
	V_A = value;
}

void V_Sense_B (void){
	// Read ADC1 Channel 1
	ADC1_getChResult_mV(&v_sense_b,ADC1_DCH1);
	float value = ((v_sense_b * 0.001) - 2.5) * 36 / sqrt(3); // See Sensor Schematic
	V_B = value;
}

void V_Sense_C(void){
	// Read ADC1 Channel 2
	ADC1_getChResult_mV(&v_sense_c,ADC1_DCH2);
	float value = ((v_sense_c * 0.001) - 2.5) * 36 / sqrt(3); // See Sensor Schematic
	V_C = value;
}

void I_Sense_A(void){
	// Read ADC1 Channel 4
	ADC1_getChResult_mV(&i_sense_a,ADC1_DCH4);
	float value = ((i_sense_a *0.001) - 2.5) * 2.5; 		// Op Amp Conversion : Refer to Altium Model.
	I_A = value;
}
void I_Sense_B(void){
	// Read ADC1 Channel 5
	ADC1_getChResult_mV(&i_sense_b,ADC1_DCH5);
	float value = ((i_sense_b * 0.001) - 2.5) * 2.5; 		// Op Amp Conversion : Refer to Altium Model.
	I_B = value;//(i_b_buffer[0] + i_b_buffer[1] + i_b_buffer[2]) / 3;
}
void I_Sense_C(void){
	// Read ADC1 Channel 6
	ADC1_getChResult_mV(&i_sense_c,ADC1_DCH6);
	float value = ((i_sense_c * 0.001) - 2.5) * 2.5; 		// Op Amp Conversion : Refer to Altium Model.
	I_C = value; //(i_c_buffer[0] + i_c_buffer[1] + i_c_buffer[2]) / 3;
}
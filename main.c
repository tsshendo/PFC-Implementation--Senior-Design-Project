/*******************************************************************************
 * @file    main.c
 * @brief   Main entry point for PFC control on TLE9893 using GPIO-based SVPWM
 *******************************************************************************/

#include "Sensor_Functions.h"
#include "gpio_pwm.h"
#include "main_control.h"  // contains control_loop_step()
#include "tle_device.h"
#include "gpio.h"
#include "adc1.h"
#include "isr.h"
#include "scu.h"
#include "int.h"
#include "timer2x.h"
#include "math.h"
#include "types.h"
#include <stdint.h>
//#include "Can_Api.h"
//#include "Com_Api.h"
//#include "com_cfg.h"

#define Poll_Output_Voltage (0x00) // output voltage adc
#define Poll_Output_Current (0x08) // output current adc
#define BUFFER_SIZE 10

float I_OUT = 0;
float I_A_CAN = 0;
float I_B_CAN = 0;
float I_C_CAN = 0;
float I_OUT_CAN = 0;

float V_OUT = 0;
float V_A_CAN = 0;
float V_B_CAN = 0;
float V_C_CAN = 0;
float V_OUT_CAN = 0;


uint64 u64_receiveValue = 0u; // SPI data received
/* Buffer to hold the received values */
uint64 receiveBuffer[BUFFER_SIZE] = {0};  // Array to store up to 10 received values
uint8 bufferIndex = 0;
uint8_t txBuffer[8];  // 8-byte can buffer that stores the data in packet 

//SPI data receive vals
uint64 receiveValue1 = 0u;
uint64 receiveValue2 = 0u;
volatile uint64 SPI_result = 0;
uint16 adc_code1 = 0;
uint16 adc_code2 = 0;
float V_REF = 5;  // Ref voltage for SPI ADC

/*******************************************************************************
 * @brief   Initialize application peripherals (ADC, GPIO, Timer, etc.)
 *******************************************************************************/
void system_init(void) {
    // System Core Init (clock, power)
		//CCU7_startT16();
    SCU_init();      // Clock + PLL setup
    INT_init();      // Interrupt controller

    // ADC1 Init for current and voltage sensing
    ADC1_init();

    // GPIO Init for gate driver output
    GPIO_init();     // Your GPIO config
		Sensor_Init();
}

/*******************************************************************************
 * @brief   Timer interrupt handler (100 kHz loop)
 *          Called from TIMER2 ISR
 *******************************************************************************/
void T16_isr(void) {
    // Not used, running too fast.
}

/*******************************************************************************
 * @brief   Entry point
 *******************************************************************************/
int main(void) {
    system_init();
	
		receiveValue1 = 0u;
	  receiveValue2 = 0u;
		sint8 s8_returnCode;
		s8_returnCode = ERR_LOG_SUCCESS;
	
//		Can_Init();
//		Com_Init();
   
		/* Request Full communication */
//		Com_EnableReceptionDM(0);
//		Com_EnableTransmission(STD_ON);
	
		/* Initialization of hardware modules based on Config Wizard configuration */
		s8_returnCode = TLE_init();

    while (1) {
			
								/* SPI ADC: Output Voltage
				  (void)SSC0_getRXvalue();  										 // Clear buffer before next poll
					SSC0_setTXvalue((uint8) Poll_Output_Voltage);  // Send poll command
					while (SSC0_getBusySts() != 0) {}              // Wait for command to send
					receiveValue1 = (uint8)SSC0_getRXvalue();      // Read fresh data
					adc_code1 = (uint16)(receiveValue1 & 0xFFF);
					V_OUT_CAN = ((float)adc_code1 / 4095.0) * V_REF;	
					SCU_delay_us(10000); 
				*/
					SSC0_setTXvalue((uint16) 0x0000);  // 16-bit: 0x00 padded
					while (SSC0_getBusySts() != 0) {}
					SSC0_setTXvalue((uint16) 0x0000);  // 16-bit dummy
					while (SSC0_getBusySts() != 0) {}
					SCU_delay_us(10);
					receiveValue1 = SSC0_getRXvalue();
					adc_code1 = (uint16)(receiveValue1 & 0xFFF);
					V_OUT_CAN = (((float)adc_code1 / 4095.0) * V_REF) * 10;
					V_OUT = V_OUT_CAN;
					//V_OUT_CAN = V_OUT;
					//V_OUT_CAN = V_OUT_CAN / 10;
			
					SSC0_setTXvalue((uint16) 0x0800);  // 16-bit: 0x08 in upper byte
					while (SSC0_getBusySts() != 0) {}
					SSC0_setTXvalue((uint16) 0x0000);  // 16-bit dummy
					while (SSC0_getBusySts() != 0) {}
					SCU_delay_us(10);
					receiveValue2 = SSC0_getRXvalue();
					adc_code2 = (uint16)(receiveValue2 & 0xFFF);
					I_OUT_CAN = (((float)adc_code2 / 4095.0) * V_REF) * 0.17;
					I_OUT = I_OUT_CAN * 100;
					//I_OUT_CAN = I_OUT;
					//I_OUT_CAN = I_OUT_CAN / 10;
			
			control_loop_step();     // Core control loop (ADC to SVPWM)
			gpio_pwm_update();       // Bit-banged PWM output
        // Main loop can sleep or handle low-priority tasks
        //__WFI(); // Wait for interrupt (low power sleep)
    }
}

void Check_value(void) {
    // Read the received value from SSC0
		SPI_result = 0;
    uint64 receivedValue = SSC0_getRXvalue();
		
    // Store the received value in the buffer
    receiveBuffer[bufferIndex] = receivedValue;
		SPI_result = receivedValue;


    // Update the index for the next value
    bufferIndex++;

    // If the buffer is full, wrap around to the beginning (circular buffer)
    if (bufferIndex >= BUFFER_SIZE) {
        bufferIndex = 0;
    }
	}
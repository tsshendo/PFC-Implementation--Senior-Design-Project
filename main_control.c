/*******************************************************************************
 * @file    main_control.c
 * @brief   Main control loop tying together sensor input, PLL, PI control, and SVPWM
 *******************************************************************************/

#include "Sensor_Functions.h"
#include "clarke_transform.h"
#include "pll_srf.h"
#include "park_transform.h"
#include "inverse_park.h"
#include "voltage_loop.h"
#include "pi_controller.h"
#include "svpwm.h"
#include "gpio_pwm.h"

// Timing step for current loop (match with your interrupt frequency)
#define CONTROL_DT 0.00001f  // 100 kHz = 10 µs

//Variables
extern volatile float I_ALPHA;
extern volatile float I_BETA;
extern volatile float V_APLHA;
extern volatile float V_BETA;

// D- and Q-axis current PI controllers
static PIController id_pi = {.kp = 2.0f, .ki = 500.0f, .integral = 0.0f, .out_min = -100.0f, .out_max = 100.0f};
static PIController iq_pi = {.kp = 2.0f, .ki = 500.0f, .integral = 0.0f, .out_min = -100.0f, .out_max = 100.0f};

/*******************************************************************************
 * @brief   Call this function in your 100 kHz timer interrupt or fast loop
 *******************************************************************************/
void control_loop_step(void) {
    // 1. Poll ADCs (3-phase voltage + current + output voltage)
    PollADC1();
    V_Sense_A(); V_Sense_B(); V_Sense_C();
    I_Sense_A(); I_Sense_B(); I_Sense_C();
		
		if(I_A >0.25 || I_B > 0.25 || I_C > 0.25){
			// 2. Clarke Transform for input current (I_A/B/C)
			clarke_transform_currents();

			// 3. Clarke Transform for input voltage (V_A/B/C)
			clarke_transform_voltages();

			// 4. PLL ? get phase angle (theta) and frequency
			PLLResult pll = pll_update();

			// 5. Voltage loop ? get I_d_ref from V_OUT vs. 85V
			float i_d_ref = voltage_loop_update();

			// 6. Park Transform on current to get I_d, I_q
			ParkDQ i_dq = park_transform(I_ALPHA, I_BETA, pll.theta);

			// 7. Current PI Controllers
			float v_d = pi_update(&id_pi, i_d_ref, i_dq.d, CONTROL_DT);
			float v_q = pi_update(&iq_pi, 0.0f,   i_dq.q, CONTROL_DT);  // Q-axis = 0 ref

			// 8. Inverse Park ? V_a, V_ß
			AlphaBeta v_ab = inverse_park_transform(v_d, v_q, pll.theta);

			// 9. SVPWM ? Get duty cycles
			SVPWMOutput pwm_out = svpwm_generate(v_ab.alpha, v_ab.beta);

			// 10. Push PWM duty cycles to GPIO
			gpio_pwm_set_duty(pwm_out);
		}
}

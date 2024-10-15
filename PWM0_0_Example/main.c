/*
 * @file main.c
 *
 * @brief Main source code for the PWM0_0_Example program.
 *
 * @author Aaron Nanas
 */

#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "PWM_Clock.h"
#include "PWM0_0.h"
#include "PMOD_BTN_Interrupt.h"

// Declare the user-defined function prototype for PMOD_BTN_Interrupt
void PMOD_BTN_Handler(uint8_t pmod_btn_status);

int main(void)
{
	// Initialize the SysTick timer used to provide blocking delay functions
	SysTick_Delay_Init();
	
	// Initialize the PWM clock to use the PWM clock divisor as the source
	// and update the PWM clock frequency to 50 MHz / 16 = 3.125 MHz
	PWM_Clock_Init();
	
	// Initialize the Module 0 PWM Generator 0 Block (PWM0_0) to generate a PWM signal
	// using the PB6 pin that has a frequency of 50 Hz with 3% duty cycle
	// Period constant = ((50 MHz / 16) / 50 Hz) = 62500
	// Duty cycle = (62500 * 0.03) = 1875
	PWM0_0_Init(62500, 1875);
	
	// Initialize the push buttons on the PMOD BTN module (Port A)
	PMOD_BTN_Interrupt_Init(&PMOD_BTN_Handler);
	
	while(1)
	{						

	}
}

/**
 * @brief Updates the duty cycle for the HS-485HB servo using the PMOD BTN module.
 *
 * @param uint8_t pmod_btn_status Indicates the status of the buttons on the PMOD BTN module.
 *
 * @return None
 */
void PMOD_BTN_Handler(uint8_t pmod_btn_status)
{
	switch(pmod_btn_status)
	{
		// BTN0 (PA2)
		case 0x04:
		{
			// 3% -> 600 us
			PWM0_0_Update_Duty_Cycle(1875);
			break;
		}
		
		// BTN1 (PA3)
		case 0x08:
		{
			// 5% -> 1000 us
			PWM0_0_Update_Duty_Cycle(3125);
			break;
		}
		
		// BTN2 (PA4)
		case 0x10:
		{
			// 8% -> 1600 us
			PWM0_0_Update_Duty_Cycle(5000);
			break;
		}
		
		// BTN3 (PA5)
		case 0x20:
		{
			// 11.5% -> 2.300 ms
			PWM0_0_Update_Duty_Cycle(7187);
			break;
		}
		
		default:
		{
			break;
		}
	}
}

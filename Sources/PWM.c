/*
 * TimerA.c
 *
 *  Created on: Feb 5, 2015
 *      Author: Luis Ivan Escamilla Estrada
 */

#include "PWM.h"

void vfnInitPWM(void)
{
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(eMCGFLLCLK);//set clock source to be from MCGFLLCLK clock or MCGPLLCLK/2
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;	//This bit controls the clock gate to the TPMx module.
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;	//This bit controls the clock gate to the TPMx module.
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	/*
	 * clk in -> 48Mhz
	 * */
	/*WAIST PWM SIGNAL*/
	PORTC_PCR1 |= PORT_PCR_MUX(4);	//TPM0_CH0
	GPIOC_PDDR |= (1<<1);
	
	/*SHOULDER PWM SIGNAL*/
	PORTC_PCR2|= PORT_PCR_MUX(4);	//TPM0_CH1
	GPIOC_PDDR |= (1<<2);
	
	/*ELBOW PWM SIGNAL*/
	PORTE_PCR29|= PORT_PCR_MUX(3);	//TPM0_CH2
	GPIOE_PDDR |= (1<<29);
	
	/*WRIST PWM SIGNAL*/
	PORTE_PCR30|= PORT_PCR_MUX(3);	//TPM0_CH3
	GPIOE_PDDR |= (1<<30);
		
	/*GRIPPER PWM SIGNAL*/
	PORTE_PCR20|= PORT_PCR_MUX(3);	//TPM1_CH0
	GPIOE_PDDR |= (1<<20);
	
	TPM1_CONF = TPM_CONF_DBGMODE(3); //Enable Debug Counting, 11 LPTPM counter continues in debug mode.
	TPM1_SC = TPM_SC_CMOD(eLPTPM_INC) | TPM_SC_PS(eDiv_16);
	TPM1_MOD  = (CLOCK48M/16)/50;
	
	TPM0_CONF = TPM_CONF_DBGMODE(3); //Enable Debug Counting, 11 LPTPM counter continues in debug mode.
	TPM0_SC = TPM_SC_CMOD(eLPTPM_INC) | TPM_SC_PS(eDiv_16);
	TPM0_MOD  = (CLOCK48M/16)/50;
	/*
	 * PS -> 8
	 * 48Mhz/16 = 3Mhz 50Hz = 20ms = 1/50 .:. 1/50/1/3Mhz = 3Mhz/50 = 60,000
	 *   _   _   _
	 * _| |_| |_| |_  -> clk para CNT 
	 * 
	 * para que 1T de 50Hz se requerien 60000 ciclos del clock de CNT
	 * 
	 * 
	 * */
	TPM0_C0SC = (TPM_CnSC_MSB_MASK & ~TPM_CnSC_MSA_MASK) | (TPM_CnSC_ELSB_MASK);
	TPM0_C1SC = (TPM_CnSC_MSB_MASK & ~TPM_CnSC_MSA_MASK) | (TPM_CnSC_ELSB_MASK);
	TPM0_C2SC = (TPM_CnSC_MSB_MASK & ~TPM_CnSC_MSA_MASK) | (TPM_CnSC_ELSB_MASK);
	TPM0_C3SC = (TPM_CnSC_MSB_MASK & ~TPM_CnSC_MSA_MASK) | (TPM_CnSC_ELSB_MASK);
	TPM1_C0SC = (TPM_CnSC_MSB_MASK & ~TPM_CnSC_MSA_MASK) | (TPM_CnSC_ELSB_MASK);
	
	/*Set to 1.5ms for 0°*/
	TPM0_C0V = TPM_CnV_VAL(4250);
	TPM0_C1V = TPM_CnV_VAL(4250);
	TPM0_C2V = TPM_CnV_VAL(4250);
	TPM0_C3V = TPM_CnV_VAL(4250);
	TPM1_C0V = TPM_CnV_VAL(4250);
	TPM0_CNT = 0;//resetea el contador de tmp
	TPM1_CNT = 0;//resetea el contador de tmp

}

void vfnSetPosition(U08 servo, U16 angle)
{

	switch(servo)
	{
		case WAIST:		WAISTVAL(angle);
		break;
		case SHOULDER:	SHOULDERVAL(angle);
		break;
		case ELBOW:		ELBOWVAL(angle);
		break;
		case WRIST:		WRISTVAL(angle);
		break;
		case GRIPPER:	GRIPPERVAL(angle);
		break;
	}
	
}

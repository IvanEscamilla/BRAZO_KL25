/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "UART0.h"
#include "PWM.h"
#include "GPIO.h"

#define HIGH	1
#define LOW 	0

typedef struct 
{
	U08 leftPower;
	U08 leftAtenuation;
	U08 rightPower;
	U08 rightAtenuation;
}_sMotorsPower;

typedef struct 
{
	U08 SOF;
	U08 leftPower;
	U08 leftDir;	
	U08 rightPower;
	U08 rightDir;
	U08 chksm;
}_sMessage;

_sMotorsPower spMotors;
_sMessage newMessage;
_sMessage ansMessage;
U08 ans[4];
U08 tmpData;

void vfnSetClk48MHZ(void);
void vfnUpdateMotorPower(void);
U16 wfnMaps(U16 wX, U16 wInMin, U16 wInMax, U16 wOutMin, U16 wOutMax);
void vfnGpiosConfiguration(void);
void turnOff(void);
void vfnSetDirMotor(U08 bMotor, U08 bDir);

int i;

int main(void)
{
	vfnSetClk48MHZ();
	vfnGpiosConfiguration();
	vfnInitUart0(115200);
	vfnInitPWM();
	/*hombro*/
	

	vfnSetDirMotor(LEFTMOTOR, BACKWARD);
	vfnSetDirMotor(RIGHTMOTOR, FORWARD);
	vfnUpdateMotorPower();
	turnOff();
	
	for(;;) 
	{	   
				
		if(msgRcvFlag == 1)
		{
			/*actualiza angulos correspondientes*/
			newMessage.leftPower   	= buffer[1];
			newMessage.leftDir     	= buffer[2];
			newMessage.rightPower   = buffer[3];
			newMessage.rightDir   	= buffer[4];
			
			vfnSetDirMotor(LEFTMOTOR, newMessage.leftDir);
			vfnSetDirMotor(RIGHTMOTOR, newMessage.rightDir);
			spMotors.leftPower = newMessage.leftPower;
			spMotors.rightPower = newMessage.rightPower;
			vfnUpdateMotorPower();
			/*10ms*/
			//for(i=0;i<40000;i++);

			msgRcvFlag = 0;
			//turnOff();
			//UART0_vfnSendMessage((U08 *)ans, 4);
		}

	}
	
	return 0;
}

void vfnUpdateMotorPower(void)
{//8520
	vfnSetMotorPower(LEFTMOTOR,wfnMaps(spMotors.leftPower,0,100,6000,60000));
	vfnSetMotorPower(RIGHTMOTOR,wfnMaps(spMotors.rightPower,0,100,6000,60000));
}

U16 wfnMaps(U16 wX, U16 wInMin, U16 wInMax, U16 wOutMin, U16 wOutMax)
{
  return (wX - wInMin) * ((wOutMax - wOutMin) / (wInMax - wInMin)) + wOutMin;
}

void vfnSetClk48MHZ(void)
{
   U08 temp_reg;
	
   SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV4(1); //Clock 1 output divider value
   
   MCG_C1 |= MCG_C1_IREFS_MASK;         // Select internal reference
		
   temp_reg = MCG_C4;
   
   temp_reg &= ~MCG_C4_DRST_DRS_MASK;    // Clear the DRS field 
   temp_reg |= MCG_C4_DRST_DRS(1);       // Mid range 
   temp_reg |= MCG_C4_DMX32_MASK;        // make sure DMX32 is set 
   
   MCG_C4 = temp_reg;
   
   /* Wait until FLL output is stable */
   while(MCG_S & MCG_S_CLKST_MASK);
   
}

void vfnGpiosConfiguration(void)
{
	GPIO_ENABLE_MODULE_CLOCK(PORTB);
	/*LEFT MOTOR DIRECTION
		EN3 EN4
		0 	0 = stop
		0 	1 = F
		1 	0 = B
	*/
	GPIO_CONFIG_PIN_FUNCTION(B,0,GPIO);
	GPIO_CONFIG_PIN_FUNCTION(B,1,GPIO);
	/*RIGHT MOTOR DIRECTION*/
	GPIO_CONFIG_PIN_FUNCTION(B,2,GPIO);
	GPIO_CONFIG_PIN_FUNCTION(B,3,GPIO);
	
	GPIO_CONFIG_PIN_AS_OUTPUT(B,0);
	GPIO_CONFIG_PIN_AS_OUTPUT(B,1);
	GPIO_CONFIG_PIN_AS_OUTPUT(B,2);
	GPIO_CONFIG_PIN_AS_OUTPUT(B,3);
	
	GPIO_WRITE_PIN(B,0,LOW);
	GPIO_WRITE_PIN(B,1,LOW);
	GPIO_WRITE_PIN(B,2,LOW);
	GPIO_WRITE_PIN(B,3,LOW);
}

void turnOff(void)
{
	vfnSetMotorPower(LEFTMOTOR, 0);
	vfnSetMotorPower(RIGHTMOTOR, 0);
	GPIO_WRITE_PIN(B,0,LOW);
	GPIO_WRITE_PIN(B,1,LOW);
	GPIO_WRITE_PIN(B,2,LOW);
	GPIO_WRITE_PIN(B,3,LOW);
}

void vfnSetDirMotor(U08 bMotor, U08 bDir)
{
	if(bMotor == LEFTMOTOR)
	{
		if(bDir == FORWARD)
		{
			GPIO_WRITE_PIN(B,0,LOW);
			GPIO_WRITE_PIN(B,1,HIGH);			
		}
		else
		{
			GPIO_WRITE_PIN(B,0,HIGH);
			GPIO_WRITE_PIN(B,1,LOW);
		}
	}
	else
	{
		if(bDir == FORWARD)
		{
			GPIO_WRITE_PIN(B,2,HIGH);
			GPIO_WRITE_PIN(B,3,LOW);
		}
		else
		{
			GPIO_WRITE_PIN(B,2,LOW);
			GPIO_WRITE_PIN(B,3,HIGH);
		}

	}
}


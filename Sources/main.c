/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "UART0.h"
#include "PWM.h"

typedef struct 
{
	U08 waistAngle;
	U08 shoulderAngle;
	U08 elbowAngle;
	U08 wristAngle;
	U08 gripperAngle;
}_sArmsAngle;

typedef struct 
{
	U08 SOF;
	U08 servo;
	U08 dir;
	U08 angle;
	U08 chksm;
}_sMessage;

_sArmsAngle spArm;
_sMessage newMessage;
_sMessage ansMessage;
U08 ans[4];
U08 tmpData;

void vfnSetClk48MHZ(void);
void vfnUpdateArmsPosition(void);
U16 wfnMaps(U16 wX, U16 wInMin, U16 wInMax, U16 wOutMin, U16 wOutMax);

int main(void)
{
	vfnSetClk48MHZ();
	vfnInitUart0(115200);
	vfnInitPWM();
	/*cintura*/
	spArm.waistAngle = 0;
	/*hombro*/
	spArm.shoulderAngle = 90;

	vfnUpdateArmsPosition();
	
	for(;;) 
	{	   
				
		if(msgRcvFlag == 1)
		{
			/*actualiza angulos correspondientes*/
			newMessage.dir   = buffer[1];
			newMessage.servo = buffer[2];
			newMessage.angle  = buffer[3];
			newMessage.chksm = buffer[4];
			
			switch (newMessage.servo)
			{
				case WAIST:{					

						if(newMessage.dir == FORWARD)
						{
							if((spArm.waistAngle + newMessage.angle) > 180)
							{
								/*do nothing*/
							}
							else
							{
								/*add angle*/
								spArm.waistAngle += newMessage.angle;
							}
						}
						else
						{	
							if(((spArm.waistAngle - newMessage.angle) < 5) || ((spArm.waistAngle - newMessage.angle) > 180))
							{
								/*do nothing*/
							}
							else
							{
								/*substract angle*/
								spArm.waistAngle -= newMessage.angle;
							}
						}
				}break;
				
				case ELBOW:{
					if(newMessage.dir == FORWARD)
					{
						if((spArm.elbowAngle + newMessage.angle) > 180)
						{
							/*do nothing*/
						}
						else
						{
							/*add angle*/
							spArm.elbowAngle += newMessage.angle;
						}
					}
					else
					{	
						if(((spArm.elbowAngle - newMessage.angle) < 5) || ((spArm.elbowAngle - newMessage.angle) > 180))
						{
							/*do nothing*/
						}
						else
						{
							/*substract angle*/
							spArm.elbowAngle -= newMessage.angle;
						}
					}	
				}break;
				
				case SHOULDER:{
					if(newMessage.dir == FORWARD)
					{
						if((spArm.shoulderAngle + newMessage.angle) > 180)
						{
							/*do nothing*/
						}
						else
						{
							/*add angle*/
							spArm.shoulderAngle += newMessage.angle;
						}
					}
					else
					{	
						if(((spArm.shoulderAngle - newMessage.angle) < 5) || ((spArm.shoulderAngle - newMessage.angle) > 180))
						{
							/*do nothing*/
						}
						else
						{
							/*substract angle*/
							spArm.shoulderAngle -= newMessage.angle;
						}
					}
									
				}break;
				
				case WRIST:{
					if(newMessage.dir == FORWARD)
					{
						if((spArm.wristAngle + newMessage.angle) > 180)
						{
							/*do nothing*/
						}
						else
						{
							/*add angle*/
							spArm.wristAngle += newMessage.angle;
						}
					}
					else
					{	
						if(((spArm.wristAngle - newMessage.angle) < 5) || ((spArm.wristAngle - newMessage.angle) > 180))
						{
							/*do nothing*/
						}
						else
						{
							/*substract angle*/
							spArm.wristAngle -= newMessage.angle;
						}
					}
									
				}break;
				case GRIPPER:{
					if(newMessage.dir == FORWARD)
					{
						if((spArm.gripperAngle + newMessage.angle) > 180)
						{
							/*do nothing*/
						}
						else
						{
							/*add angle*/
							spArm.gripperAngle += newMessage.angle;
						}
					}
					else
					{	
						if(((spArm.gripperAngle - newMessage.angle) < 5) || ((spArm.gripperAngle - newMessage.angle) > 180))
						{
							/*do nothing*/
						}
						else
						{
							/*substract angle*/
							spArm.gripperAngle -= newMessage.angle;
						}
					}
									
				}break;
			}
			/*Responder al servidor*/
			msgRcvFlag = 0;
			vfnUpdateArmsPosition();
			//UART0_vfnSendMessage((U08 *)ans, 4);
		}

	}
	
	return 0;
}

void vfnUpdateArmsPosition(void)
{//8520 4700 12000
	vfnSetPosition(WAIST,wfnMaps(spArm.waistAngle,0,180,2200,7000));
	vfnSetPosition(SHOULDER,wfnMaps(spArm.shoulderAngle,0,180,1000,4200));
	vfnSetPosition(ELBOW,wfnMaps(spArm.elbowAngle,0,180,1850,7200));
	vfnSetPosition(WRIST,wfnMaps(spArm.wristAngle,0,180,1850,6200));
	vfnSetPosition(GRIPPER,wfnMaps(spArm.gripperAngle,0,180,1850,7200));
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


/*
 * PWM.h
 */

#ifndef PWM_H_
#define PWM_H_

#include "derivative.h"
#include "myTypes.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define LEFTMOTOR 		0
#define RIGHTMOTOR		1
#define FORWARD	 		0
#define BACKWARD		1

#define SETPOWERLEFTMOTOR(x) 		TPM0_C0V = TPM_CnV_VAL(x);
#define SETPOWERRIGHTMOTOR(x)		TPM0_C1V = TPM_CnV_VAL(x);

typedef enum
{
	eLPTPM_DIS = 0,
	eLPTPM_INC,
	eLPTPM_RISE,
	eLPTPM_RESERVED
}_eCMODConf;

typedef enum
{
	eDiv_1 = 0,
	eDiv_2,
	eDiv_4,
	eDiv_8,
	eDiv_16,
	eDiv_32,
	eDiv_64,
	eDiv_128
}_ePS;

typedef enum
{
	eCLOCK_DIS = 0,
	eMCGFLLCLK,
	eOSCERCLK,
	eMCGIRCLK
}_eTMPSRC;

/*************************************************************************************************/
/*********************					Global Variables					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/

void vfnInitPWM(void);
void vfnSetMotorPower(U08 bMotor, U16 wPower);
#endif /* PWM_H_ */

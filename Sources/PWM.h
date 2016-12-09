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
#define WAIST 		0
#define SHOULDER	1
#define ELBOW 		2
#define WRIST 		3
#define GRIPPER 	4
/*custom positions*/
#define INITIALPOS	4
#define ALLUP 		5
#define ANGLED 		6
#define FORWARD	 	0
#define BACKWARD	1

#define WAISTVAL(x) 		TPM0_C0V = TPM_CnV_VAL(x);//C1
#define SHOULDERVAL(x)		TPM0_C1V = TPM_CnV_VAL(x);//C2
#define ELBOWVAL(x) 		TPM0_C2V = TPM_CnV_VAL(x);//E29
#define WRISTVAL(x) 		TPM0_C3V = TPM_CnV_VAL(x);//E30
#define GRIPPERVAL(x)		TPM1_C0V = TPM_CnV_VAL(x);//E20


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
void vfnSetPosition(U08 servo, U16 angle);
#endif /* PWM_H_ */

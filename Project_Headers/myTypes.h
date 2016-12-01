/*
 * myTypes.h
 */

#ifndef MYTYPES_H_
#define MYTYPES_H_

/*************************************************************************************************/
/*********************                      Includes                        **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                      Defines                         **********************/
/*************************************************************************************************/
#ifndef TRUE
    #define TRUE                        (1)
#endif

#ifndef FALSE
    #define FALSE                       (0)
#endif

#ifndef NULL
  #define NULL          (void*)0
#endif

#define CLOCK48M		48000000

typedef enum
{
	eNVIC_DMA0 = 0,
	eNVIC_DMA1,
	eNVIC_DMA2,
	eNVIC_DMA3,
	eNVIC_RESERVED1,
	eNVIC_FTFA, //5
	eNVIC_PMC,
	eNVIC_LLWU,
	eNVIC_I2C0,
	eNVIC_I2C1,
	eNVIC_SPI0, //10
	eNVIC_SPI1,
	eNVIC_UART0,
	eNVIC_UART1,
	eNVIC_UART2,
	eNVIC_ADC0, //15
	eNVIC_CMP0,
	eNVIC_TPM0,
	eNVIC_TPM1,
	eNVIC_TPM2,
	eNVIC_RTC_ALARM, //20
	eNVIC_RTC_SEC,
	eNVIC_PIT,
	eNVIC_RESERVED2,
	eNVIC_USB_OTG,
	eNVIC_DAC0,  //25
	eNVIC_TSI0,
	eNVIC_MCG,
	eNVIC_LPTMR0,
	eNVIC_RESERVED3,
	eNVIC_PORTA, //30
	eNVIC_PORTD
}_eNVIC_INT;
/*************************************************************************************************/
/*********************                      Typedefs                        **********************/
/*************************************************************************************************/

typedef unsigned char               U08;  
typedef unsigned char               BOOLEAN;  
typedef unsigned short              U16;
typedef unsigned long               U32;
typedef signed char                 S08;
typedef signed short                S16;     
typedef signed long                 S32;


typedef struct
{
    U08 bActualState;
    U08 bPrevState;
    U08 bNextState;
    U08 bNextNextState;
    U08 bErrorState;
}_sStateMachine;

#endif /* MYTYPES_H_ */

/*
 * GPIO.h
 */

#ifndef GPIO_H_
#define GPIO_H_


/*************************************************************************************************/
/*********************                  Own Includes                        **********************/
/*************************************************************************************************/

#include "derivative.h"

/*************************************************************************************************/
/*********************                  Defines                             **********************/
/*************************************************************************************************/

#define GPIO_ENABLE_MODULE_CLOCK(Port)\
    if(Port == PORTA) \
        SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; \
    else if(Port == PORTB) \
        SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; \
     else if(Port == PORTC) \
      SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; \
    else if(Port == PORTD) \
        SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; \
    else if(Port == PORTE) \
        SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK; \

#define GPIO_DISABLE_MODULE_CLOCK(Port)\
	if(Port == PORTA) \
        SIM_SCGC5 &= ~SIM_SCGC5_PORTA_MASK; \
    else if(Port == PORTB) \
        SIM_SCGC5 &= ~SIM_SCGC5_PORTB_MASK; \
     else if(Port == PORTC) \
      SIM_SCGC5 &= ~SIM_SCGC5_PORTC_MASK; \
    else if(Port == PORTD) \
        SIM_SCGC5 &= ~SIM_SCGC5_PORTD_MASK; \
    else if(Port == PORTE) \
        SIM_SCGC5 &= ~SIM_SCGC5_PORTE_MASK; \
           
#define GPIO_CONFIG_PIN_FUNCTION(port,pin,alternate)            PORT##port##_PCR(pin) = PORT_PCR_MUX(alternate)

//Drive Strength (PTB0, PTB1, PTD6, PTD7)
#define GPIO_CONFIG_DRIVE_STRENGTH(port,pin,strength)\
    if(strength == 1) \
        PORT##port##_PCR(pin) |= PORT_PCR_DSE_MASK; \
    else \
        PORT##port##_PCR(pin) &= ~PORT_PCR_DSE_MASK;

#define GPIO_CONFIG_PIN_AS_INPUT(port,pin)                      GPIO##port##_PDDR &= ~(1 << pin)

#define GPIO_CONFIG_PIN_AS_OUTPUT(port,pin)                     GPIO##port##_PDDR |= (1 << pin)

#define GPIO_WRITE_PIN(port,pin,set) \
    if(set == 1) \
        GPIO##port##_PDOR |= (1 << pin); \
    else \
        GPIO##port##_PDOR &= ~(1 << pin);

#define FGPIO_WRITE_PIN(port,pin,set) \
    if(set == 1) \
    	FGPIO##port##_PSOR |= (1 << pin);\
    else \
    	FGPIO##port##_PCOR |= (1 << pin);

#define GPIO_TOGGLE_PIN(port,pin)                               GPIO##port##_PTOR |= (1 << pin)

#define FGPIO_TOGGLE_PIN(port,pin)                              FGPIO##port##_PTOR |= (1 << pin)

#define GPIO_READ_PIN(port,pin)                                 (GPIO##port##_PDIR & (1 << pin)) 

#define FGPIO_READ_PIN(port,pin)								(FGPIO##port##_PDIR & (1 << pin))

#define GPIO_READ_PORT(port)                                    GPIO##port##_PDIR

#define GPIO_WRITE_PORT(port)                                   GPIO##port##_PDOR


/*************************************************************************************************/
typedef enum
{    
   PORTA = 0,
   PORTB,
   PORTC,
   PORTD,
   PORTE  
}_GPIO_PortClock_;

typedef enum
{
   Analog = 0,
   GPIO,
   ALT2,
   ALT3,
   ALT4,
   ALT5,
   ALT6,
   ALT7
}_GPIO_MuxAlt;

#endif /* GPIO_H_ */

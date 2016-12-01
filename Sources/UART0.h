/*
 * UART0.h
 */

#ifndef UART0_H_
#define UART0_H_

#include "derivative.h"
#include "myTypes.h"


#define UART0_POLLING_RX		(UART0_S1 & UART_S1_RDRF_MASK) == UART_S1_RDRF_MASK

extern U16 Index;
extern U08 buffer[6];
extern U08 brcv;
extern U08 msgRcvFlag;

void vfnInitUart0(U32 dwBaudRate);
void UART0_vfnChangeBaudRate(U32 BaudRate);
void UART0_vfnSendData(U08 *str);
void UART0_vfnSendMessage(U08 *str,U32 Size);

#endif /* UART0_H_ */

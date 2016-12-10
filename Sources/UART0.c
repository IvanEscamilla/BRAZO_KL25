/*
 * UART0_BT.c
 */


#include "UART0.h"

U16 Index = 0;
U08 buffer[4];
U08 msgRcvFlag;
U08 chksm;

void vfnInitUart0(U32 dwBaudRate)
{
	 SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;    
	 SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK ;
	 /*TX PORTE_PCR20: ISF=0,MUX=4 */
	 PORTE_PCR20 = PORT_PCR_MUX(0x4);
	 /*RX PORTE_PCR21: ISF=0,MUX=4 */
	 PORTE_PCR21 = PORT_PCR_MUX(0x4);
	 /* Disable TX & RX while we configure settings */
	 UART0_C2 &= ~(UART0_C2_TE_MASK); //disable transmitter
	 UART0_C2 &= ~(UART0_C2_RE_MASK); //disable receiver
	 
	 /* UART0_C1: LOOPS=0,DOZEEN=0,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0 */
	 UART0_C1 = 0x00; /* Set the C1 register */
	 /* UART0_C3: R8T9=0,R9T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
	 UART0_C3 = 0x00; /* Set the C3 register */
	 /* UART0_S2: LBKDIF=0,RXEDGIF=0,MSBF=0,RXINV=0,RWUID=0,BRK13=0,LBKDE=0,RAF=0 */
	 UART0_S2 = 0x00; /* Set the S2 register */
	 
	 SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); //set clock source to be from MCGFLLCLK clock or MCGPLLCLK/2
	 SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b010);
 
	 U08 OSR = 3; //set the oversampling ratio to option #3 = 4x
	 
	 U16 SBR = (48000000/(OSR+1))/dwBaudRate;
	 UART0_BDH = 0;
	 UART0_BDH |= (~UART0_BDH_SBR_MASK) | SBR >> 8;
	 UART0_BDL = 0;
	 UART0_BDL |= (~UART0_BDL_SBR_MASK) | SBR;	 
	 
	 UART0_C4 &= (~UART0_C4_OSR_MASK) | OSR;
		 
	 /*
	 * Target Baud rate = 115200, 56600, 34800, 19200
	 * ~21MHz
	 *
	 * SBR = baud clock / ((OSR+1) * BaudRate)
	 * Baud rate = baud clock / ((OSR+1) * SBR)
	 * baud clock = FLL/PLL = ~21MHz
	 * OSR = 3
	 * 
	 * Resulting Baud rate = Variable.
	 */
	
	 UART0_C5 |= UART0_C5_BOTHEDGE_MASK; //enable sampling on both edges of the clock
	 // Enable the transmitter, receiver, and receive interrupts
	 UART0_C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UART_C2_RIE_MASK; 
	 
	 NVIC_ISER |= (1<<12);
	 NVIC_ICPR |= (1<<12); //Clear Pending Register for UART0s
}

void UART0_vfnChangeBaudRate(U32 BaudRate)
{
	/* Disable TX & RX while we configure settings */
	 UART0_C2 &= ~(UART0_C2_TE_MASK); //disable transmitter
	 UART0_C2 &= ~(UART0_C2_RE_MASK); //disable receiver
	 
	 UART0_S1 = 0x00; 
	 /* UART0_C1: LOOPS=0,DOZEEN=0,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0 */
	 UART0_C1 = 0x00; /* Set the C1 register */
	 /* UART0_C3: R8T9=0,R9T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
	 UART0_C3 = 0x00; /* Set the C3 register */
	 /* UART0_S2: LBKDIF=0,RXEDGIF=0,MSBF=0,RXINV=0,RWUID=0,BRK13=0,LBKDE=0,RAF=0 */
	 UART0_S2 = 0x00; /* Set the S2 register */
	 U08 OSR = 3; //set the oversampling ratio to option #3 = 4x
		 
	 U16 SBR = (48000000/(OSR+1))/BaudRate;
	 UART0_BDH = 0;
	 UART0_BDH |= (~UART0_BDH_SBR_MASK) | SBR >> 8;
	 UART0_BDL = 0;
	 UART0_BDL |= (~UART0_BDL_SBR_MASK) | SBR;		 
	 
	 UART0_C4 &= (~UART0_C4_OSR_MASK) | OSR;
	 
	 /*
	 * Target Baud rate = 115200, 56600, 34800, 19200
	 * ~21MHz
	 *
	 * SBR = baud clock / ((OSR+1) * BaudRate)
	 * Baud rate = baud clock / ((OSR+1) * SBR)
	 * baud clock = FLL/PLL = ~21MHz
	 * OSR = 3
	 * 
	 * Resulting Baud rate = Variable.
	 */
	
	 UART0_C5 |= UART0_C5_BOTHEDGE_MASK; //enable sampling on both edges of the clock
	 // Enable the transmitter, receiver, and receive interrupts
	 UART0_C2 = UART0_C2_RE_MASK | UART0_C2_TE_MASK; 
}

void UART0_vfnSendData(U08 *str) 
{
  while(*str!='\0') { //send every character except the null or '\0' character that terminates the string
    UART0_D = *str++; //put the next character in the transmit register & increment which character is next
    while((UART0_S1 & UART0_S1_TDRE_MASK) == 0); //wait for the trasmit register to be empty (meaning the whole character has been sent)
  }
}

void UART0_vfnSendChar(U08 *str) 
{
  
    UART0_D = *str; //put the next character in the transmit register & increment which character is next
    while((UART0_S1 & UART0_S1_TDRE_MASK) == 0);
}

void UART0_vfnSendShort(U16 str) 
{
  
    UART0_D = (str >> 8); //put the next character in the transmit register & increment which character is next
    while((UART0_S1 & UART0_S1_TDRE_MASK) == 0);
    UART0_D = (str & 0x00FF); //put the next character in the transmit register & increment which character is next
    while((UART0_S1 & UART0_S1_TDRE_MASK) == 0);
}

void UART0_vfnSendMessage(U08 *str,U32 Size)
{
	while(Size-- > 0)
	{
		UART0_D = *str++; //put the next character in the transmit register & increment which character is next
		while((UART0_S1 & UART0_S1_TDRE_MASK) == 0); //wait for the trasmit register to be empty (meaning the whole character has been sent)
	}
}


void UART0_ISR()
{
    while (!(UART0_S1 & UART_S1_RDRF_MASK));
    
	buffer[Index++] = UART0_D;
	
	if(Index == 5)
	{
		Index = 0;
		
		if(chksm == buffer[4])
		{
			msgRcvFlag = 1;
			chksm = 0;
		}
		else
		{
			chksm = 0;
			msgRcvFlag = 0;
		}
		
	}
	else
	{
		chksm += buffer[Index-1];
	}
	
	NVIC_ICPR |= (1<<12);
	UART0_S2 |= UART_S2_RXEDGIF_MASK;
}

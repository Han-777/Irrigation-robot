
#ifndef __BLUEBOOTH_H
#define __BLUEBOOTH_H
// #include "stdio.h"	
// #include "stm32f4xx_conf.h"
#include "sys.h" 

#define USART_REC_LEN  			200  	//????????? 200
#define EN_USART1_RX 			1		//??(1)/??(0)??1??
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //????,??USART_REC_LEN???.??????? 
extern u16 USART_RX_STA;         		//??????	
//?????????,??????????

#endif
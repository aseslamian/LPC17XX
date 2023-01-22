#include "lpc17xx_gpio.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_timer.h"
#include "debug_frmwrk.h"
#include "lpc17xx_uart.h"
#include "gpio.h"
#include "delay.h"
#include "lpc17xx_exti.h"
// #include "LiquidCrystal.h  // for lcd



volatile uint16_t X1[45],X2[45],X3[45],Y[30],z1,z2,z3,z4,z5;
uint16_t i=0,j=0,k=0,p=0,r=0,TR=1;
volatile uint32_t Z[500];
uint16_t Vth;

void EINT1_IRQHandler(){
	EXTI_ClearEXTIFlag(EXTI_EINT1);
 // GPIO_ClearValue(1,(1<<16));
	TIM_Cmd(LPC_TIM0,ENABLE);
}

TIM_TIMERCFG_Type timcfg;
TIM_MATCHCFG_Type mtcfg;
void TIMER0_IRQHandler(void);
void EINT1_IRQHandler(void);

void TIMER0_IRQHandler(void){
						if(TIM_GetIntStatus(LPC_TIM0,TIM_MR0_INT)==SET){ // TIMER Routine 
							
						      ADC_StartCmd(LPC_ADC,ADC_START_NOW);  // adc start conversion
									while(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_0,ADC_DATA_DONE)==0); // wait until done!		
									switch(k){
        							case 0: {  
													 X1[i]=ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);
													 Y[j]=(X1[i]-(2*X3[i])+X2[i]);if(Y[j]>35000){Y[j]=~Y[j];}
													 i++; j++;if(j>26){j=0;} Z[r]=0; for(p=0;p<26;p++){Z[r]=Z[r]+Y[p];} (Z[r]=Z[r]/26);
													 switch(TR){case 1:z1=Z[r];TR++;break; case 2:z2=Z[r];TR++;break; case 3:z3=Z[r];TR++;break; case 4:z4=Z[r];TR++;break; case 5:z5=Z[r];TR=1;break;}
													 r++; if(r>499){r=0;}
													 if(i>40){i=0;k=1; TIM_Cmd(LPC_TIM0,DISABLE);}
															 } break;	
										  case 1:{
													 X2[i]=ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);	
													 Y[j]=(X2[i]-(2*X1[i])+X3[i]);if(Y[j]>35000){Y[j]=~Y[j];}											 
													 i++; j++; if(j>26) {j=0;} Z[r]=0; for(p=0;p<26;p++){Z[r]=Z[r]+Y[p];} (Z[r]=Z[r]/26);
													 switch(TR){case 1:z1=Z[r];TR++;break; case 2:z2=Z[r];TR++;break; case 3:z3=Z[r];TR++;break; case 4:z4=Z[r];TR++;break; case 5:z5=Z[r];TR=1;break;}
													 r++;if(r>499){r=0;}
													 if(i>40){i=0;k=2; TIM_Cmd(LPC_TIM0,DISABLE);}
        											 } break;	
										 	case 2 : {
													 X3[i]=ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);
													 Y[j]=(X3[i]-(2*X2[i])+X1[i]);if(Y[j]>35000){Y[j]=~Y[j];}
													 i++; j++; if(j>26)
													 {j=0;} Z[r]=0; for(p=0;p<26;p++){Z[r]=Z[r]+Y[p];} (Z[r]=Z[r]/26); 
													 switch(TR){case 1:z1=Z[r];TR++;break; case 2:z2=Z[r];TR++;break; case 3:z3=Z[r];TR++;break; case 4:z4=Z[r];TR++;break; case 5:z5=Z[r];TR=1;break;}
													 r++;if(r>499){r=0;}
											     if(i>40){i=0;k=0; TIM_Cmd(LPC_TIM0,DISABLE);} 
													
											             } break;
																 } //end switch		
					       	}   // End Timer Routine
				  	TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT); // Clear timer flag
}
void NVIC_setting(){
   PINSEL_CFG_Type extCFG;
	 EXTI_InitTypeDef exticonfig;
   extCFG.Funcnum=PINSEL_FUNC_1;
	 extCFG.OpenDrain=PINSEL_PINMODE_NORMAL;
	 extCFG.Pinmode=PINSEL_PINMODE_PULLDOWN;
	 extCFG.Pinnum=11;
	 extCFG.Portnum=2;
	 PINSEL_ConfigPin(&extCFG);
	 GPIO_SetDir(2,(1<<11),0);
	 exticonfig.EXTI_Line=EXTI_EINT1;
   exticonfig.EXTI_Mode=EXTI_MODE_EDGE_SENSITIVE;
   exticonfig.EXTI_polarity=EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE;
	 EXTI_Config(&exticonfig);	
	 NVIC_EnableIRQ(EINT1_IRQn);
	
	 NVIC_SetPriority(EINT1_IRQn,NVIC_EncodePriority(0x07,0,1));
	 NVIC_SetPriorityGrouping(0x07);
}

void ADC_setting(){
	
	PINSEL_CFG_Type adcpinsel;
	adcpinsel.Funcnum=PINSEL_FUNC_1;
	adcpinsel.OpenDrain=PINSEL_PINMODE_NORMAL;
	adcpinsel.Pinmode=PINSEL_PINMODE_TRISTATE;
	adcpinsel.Pinnum=23;
	adcpinsel.Portnum=0;
	PINSEL_ConfigPin(&adcpinsel);
	
	ADC_Init(LPC_ADC,200000);
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_0,ENABLE);
	for(uint32_t count=0;count<UINT16_MAX+40000;count++);  //6.4mS	delay
}
int  TIMER_setting (void){
	
		timcfg.PrescaleOption=TIM_PRESCALE_USVAL;
		timcfg.PrescaleValue=1; // 1Pulse = 1 us
		mtcfg.MatchChannel=0;
    mtcfg.IntOnMatch=TRUE;
	  mtcfg.ResetOnMatch=TRUE;
	  mtcfg.StopOnMatch=FALSE;
	  mtcfg.ExtMatchOutputType=TIM_EXTMATCH_NOTHING; 
	  mtcfg.MatchValue=12;  // 10000 us on match
	  TIM_Init(LPC_TIM0,TIM_TIMER_MODE,&timcfg);
	  TIM_ConfigMatch(LPC_TIM0,&mtcfg);
	  NVIC_SetPriority(TIMER0_IRQn,((0x01<<3)|(0x01)));
	  NVIC_EnableIRQ(TIMER0_IRQn);
	 // TIM_Cmd(LPC_TIM0,ENABLE);
 	return 1;	
}
void UART_setting(){
	
	PINSEL_CFG_Type uartpinsel;
	UART_CFG_Type uartConfig;
  uartpinsel.Funcnum=PINSEL_FUNC_1;
	uartpinsel.OpenDrain=PINSEL_PINMODE_NORMAL;
	uartpinsel.Pinmode=PINSEL_PINMODE_TRISTATE;
	uartpinsel.Pinnum=2;
	uartpinsel.Portnum=0;
	
	PINSEL_ConfigPin(&uartpinsel);
	uartpinsel.Pinnum=3;
	PINSEL_ConfigPin(&uartpinsel);
	
  uartConfig.Baud_rate=115200;
  uartConfig.Databits=UART_DATABIT_8;
	uartConfig.Parity=UART_PARITY_NONE;
	uartConfig.Stopbits=UART_STOPBIT_1;
	
	UART_Init(LPC_UART0,&uartConfig);
	UART_TxCmd(LPC_UART0,ENABLE);
}

void LCD_setting(){
init3( P1_20/*rs*/, P1_21/*rw*/, P1_22/*enable*/, P1_23/*d4*/, P1_24/*d5*/, P1_25/*d6*/, P1_26/*d7*/ );
begin(16, 2, 0x00);
}
void DAC_setting(){
PINSEL_CFG_Type dacPinsel;
	
	dacPinsel.Funcnum=PINSEL_FUNC_2;
	dacPinsel.OpenDrain=PINSEL_PINMODE_NORMAL;
	dacPinsel.Pinmode=PINSEL_PINMODE_TRISTATE;
	dacPinsel.Pinnum=26;
	dacPinsel.Portnum=0;
	
	PINSEL_ConfigPin(&dacPinsel);
	
	DAC_Init(LPC_DAC);
	for(uint32_t count=0;count<UINT16_MAX+40000;count++);  //6.4mS	delay
}
int main (void){
	
//GPIO_SetDir(1,(3<<30),1);
//GPIO_ClearValue(1,(3<<30));

//GPIO_SetDir(0,(7<<24),1);
//GPIO_ClearValue(0,(7<<24));
	
//UART//  GPIO_SetDir(0,(3<<2),1);
//UART//  GPIO_ClearValue(0,(3<<2));
	
TIMER_setting();
ADC_setting();
UART_setting();
LCD_setting();
DAC_setting();

NVIC_setting();	
NVIC_SetPriorityGrouping(0x07);
	
k=0;
	

	
    while(1){
			      
			 Vth=((z1+z2+z4+z5)/4);
			 DAC_UpdateValue(LPC_DAC,Vth);
			 
						//	clear();
						//	setCursor(3,0);
						//	print("KING ES 22");
		        //  write();
						//	delayMs_Timer0(3000);
			    		
		        }

}

void show (void)  {
								 j--;
								UART_SendByte(LPC_UART0,(Y[j]>>8));
								while(UART_CheckBusy(LPC_UART0));		
								UART_SendByte(LPC_UART0,Y[j]);
								while(UART_CheckBusy(LPC_UART0));	
								 j++;
								 }

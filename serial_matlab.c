/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
unsigned char valor_ADC=0;
unsigned char  i=0;
unsigned char cont=0;

//unsigned int valor_mvolts;//int por que es un valor mayor a 255

void clk_init (void)
{
// FIRC = 4 MHz. BusClk = 4 MHz
// UART0: FIRC. UART1: BusClk. UART2: BusClk. TPM: FIRC. IIC: BusClk. PIT:
MCG_C1|=(1<<6) + (1<<1); //MCGOUTCLK : IRCLK. CG: Clock gate, MCGIRCLK enable pag 116
MCG_C2|=1; //Mux IRCLK : FIRC (4 MHz) pag 116
MCG_SC=0; //Preescaler FIRC 1:1 pag 116
SIM_CLKDIV1=0; //OUTDIV4=OUTDIV1= 1:1 pag 116. Busclk 4 MHz
SIM_SOPT2|=15<<24; //Seleccion MCGIRCLK tanto para UART0 como para TPM
}
void ADC0_IRQHandler()
{
	
	valor_ADC=ADC0_RA;
	ADC0_SC1A=(1<<6)+8; //Inicia nueva conversion;			
	
	NVIC_ISER=(1<<12); //Hab intr UART en NVIC

}
void UART0_IRQHandler()
{
		UART0_D=valor_ADC;
		NVIC_ICER=(1<<12);
}

int main(void)
{

//UART	
clk_init(); //UART clk a 4MHz
SIM_SCGC5=(1<<9); //PORTA
PORTA_PCR1=(2<<8); //UART0
PORTA_PCR2=(2<<8); //UART0
SIM_SCGC4=(1<<10); //Reloj interfaz UART0
UART0_BDL=26; //9600bps, UART clk 4 Mz
UART0_C2=(1<<3)+(1<<7); //Transmit Enable	

//ADC	
SIM_SCGC6=(1<<27); //Clk interfaz ADC0
NVIC_ISER=(1<<15); //Hab intr ADC en NVIC
ADC0_SC1A=(1<<6)+8;	//canal[contador]; //Inicia Conv ADC, CH8 (PTB0)











while(1)
return 0;
}

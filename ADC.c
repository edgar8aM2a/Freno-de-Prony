/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

//port 8 y port 9
//canal 0 1


#include "derivative.h" /* include peripheral declarations */

unsigned char valor_ADC;
unsigned int valor_mvolts;
int main(void)
{
//configurar PTB11  No necesario, por default es entrada analogica

	
SIM_SCGC6=(1<<27); //Clk interfaz ADC0
while (1)
{
ADC0_SC1A=8;			//canal[contador]; //Inicia Conv ADC, CH8 (PTB11)

//do {} while (ADC0_SC1A==8);
valor_ADC=ADC0_RA;
valor_mvolts=(valor_ADC*3300)/255;
}

return 0;
}

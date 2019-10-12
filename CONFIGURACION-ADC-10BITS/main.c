//CANAL JORGE MIRANDA REDES NEURONALES
//INCLUIR ARCHIVOS DE CABECERA 
#include <xc.h>
#include "reloj.h"
#include <libpic30.h>
//declarar variable del tipo flotante
int valor_adc;
void main(void) 
{   TRISBbits.TRISB6=0;
    //INICIALIZAR EL ADC
    //MODO 10 BITS
    AD1CON1bits.AD12B=0;
    //VOLTAJE DE REFENCIAS
    AD1CON2bits.VCFG=0b000;//AVDD AVSS
    //TAD
    AD1CON3bits.ADCS=0x0F;//TAD=TCY(ADCS+1)
    //configuracion de pines analogicos
    AD1PCFGLbits.PCFG0=0; 
   
    //multiplexores para ubicar las entradas a los S/H
    //AN0 CON CH0
    AD1CHS0bits.CH0NA=1;//VREFL 
    AD1CHS0bits.CH0SA=0;//AN0 CH0
    //AN3 CON CH1
    AD1CHS123bits.CH123NA=0;//VREFL PARA CH1,CH2,CH3
    AD1CHS123bits.CH123SA=1;//CH1 AN3,CH2AN4,CH3,AN5
    //ELEGIR EL NUMERO DE CANALES A UTILIAR
    AD1CON2bits.CHPS=0b00;//2 CANALES A UTILIZAR CH0,CH1
    //SELECCIONAR EL MUESTREO SIMULTANEO O SECUENCIAL 
    AD1CON1bits.SIMSAM=0;//SECUENCIAL
    //elegir el modo de muestreo  manual
    AD1CON1bits.ASAM=0;
    //elegir el SOC
    AD1CON1bits.SSRC=0b000;//MANUAL
    //COMFIGURE DMA 
    
    //ENCENDER ADC1
    AD1CON1bits.ADON=1;
    while(1)
    {
        //inicia  muestreo
        AD1CON1bits.SAMP=1;
        __delay_ms(10);
        AD1CON1bits.SAMP=0;
        //iniciar conversion
        while(!AD1CON1bits.DONE);
        //LEER EL VALOR ALMACENADO
        valor_adc=ADC1BUF0;
        if(valor_adc>=500)
        {
            //ENCENDER DIODO LED 
            LATBbits.LATB6=1;
        }
        else
        {
            //APAGAR DIODO LED
            LATBbits.LATB6=0;
        }
              
    }
    return;
}

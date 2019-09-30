
#include <xc.h>
#include "reloj.h"
#include <libpic30.h>
#include "lcd_dspic.h"
#include <stdio.h>
#include <math.h>
int RPM=0;//RPM
char velocidad[3]={0};
void Init_INT0(void);
int cont=0;
void main(void) 
{ 
    AD1PCFGL=0xFFFF; 
  TRISBbits.TRISB14=0;
  TRISBbits.TRISB13=0;
  TRISBbits.TRISB12=0;
  Init_INT0();
  Lcd_Init();
  Lcd_Cmd(LCD_CURSOR_OFF);
  Lcd_string(1,0,"dsPIC33FJ32GP202");
  LATBbits.LATB14=1;//EN=1
  LATBbits.LATB13=1;//IN1=1
  while(1)
  {
      cont=0;
      __delay_ms(1000);//1
      RPM=60*cont/100;//RPM
      sprintf(velocidad,"%d",RPM);
      if(RPM<100)
      {
         Lcd_string(2,3," "); 
      }
      Lcd_string(2,1,velocidad);
      Lcd_string(2,5,"RPM");  
  }
    return;
}
void Init_INT0(void)
{
    INTCON2bits.INT0EP=0;
    IPC0bits.INT0IP=2;
    IEC0bits.INT0IE=1;
    IFS0bits.INT0IF=0;
 
}
void __attribute__(( __interrupt__,no_auto_psv))_INT0Interrupt(void)
{
    IFS0bits.INT0IF=0;
    cont++;
     
} 
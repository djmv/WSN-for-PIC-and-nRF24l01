/* 
 * File:   main.c
 * Author: Jorge Luis Silva C
 *
 * Created on 17 de marzo de 2017, 11:17 PM
 */

#include <16F886.h>
#FUSES NOWDT, XT, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#device ADC=10
#use delay(crystal=16MHz)
#include "lib_rf2gh4_10.h"
#byte porta=0x05
#byte portb=0x06
#use rs232(uart1, baud=9600)//usart1 -->ajuste de XMIT y RCV para la USART 1 
#int_ext
#define LED PIN_B2

void IntRB0()
{
   int8 ret1;
   
   ret1 = RF_RECEIVE();
   if ( (ret1 == 0) || (ret1 == 1) )
   {
      do
      {  
         ret1 = RF_RECEIVE(); 
      }  while ( (ret1 == 0) || (ret1 == 1) );
   }  
}

void main()
{  
    //*
  //  setup_adc_ports(AN1);//Selecciona el puerto a realizar la conversion
  //  setup_adc(adc_clock_internal);//Selecciona el reloj de conversion
 //   set_adc_channel(0);//Selecciona el canal de conversion
    int8 ret2;
    output_low(LED);
      delay_ms(1000);
      output_high(LED);
      delay_ms(1000);
      output_low(LED);
      delay_ms(1000);
      output_high(LED);
      delay_ms(1000);
   RF_INT_EN();              // Habilitar interrupción RB0/INT.
   RF_CONFIG_SPI();          // Configurar módulo SPI del PIC.
   RF_CONFIG(0x40,0x01);     // Configurar módulo RF canal y dirección.
   RF_ON();                  // Activar el módulo RF.
   printf("configurado! \n");
   set_tris_a(0b111111);     // Todo el puerto A como entradas.
        while(true)
        {  
           RF_DATA[0]=0x61;
      //     RF_DATA[3]=read_adc();
           RF_DATA[1]=0x62;
           RF_DATA[2]=0x50;
           RF_DIR=0x08;           // Dirección del receptor.
           ret2=RF_SEND();        // Enviar datos.
           delay_ms(1000);
           printf("Enviado! \n");
           printf("%d",ret2);

        }
}

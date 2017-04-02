#include <16F886.h> 
#FUSES NOWDT, XT, NOPUT, NOPROTECT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG 
#use delay(crystal=16MHz)
#include "lib_rf2gh4_10.h"
#use rs232(uart1, baud=9600)//usart1 -->ajuste de XMIT y RCV para la USART 1 
#define LED PIN_B1
#byte porta=0x05           // Dirección del puerto A.
#int_ext                   // Interrupción del módulo RF.

void IntRB0()
{
   int8 ret1;
   ret1 = RF_RECEIVE();
   if ( (ret1 == 0) || (ret1 == 1) )         // Tanto si hay recepción simple o múltiple, leer datos.
   {
      do
      {    
         porta=RF_DATA[0];                   // El puerto A contendrá el valor que le llegue del emisor, a través de RF_DATA[0].
         printf("\n %c",RF_DATA[2]);
         printf("\n %u",RF_DATA[3]);
         ret1 = RF_RECEIVE();                // "ret1" nos dirá si hay recepción simple, múltiple o no hay datos para leer.
      }while ( (ret1 == 0) || (ret1 == 1) ); // Mientras haya datos para leer, seguir leyendo.
   }  
}

void main() { 
    output_low(LED);
    delay_ms(1000);
    output_high(LED);
    delay_ms(1000);
    output_low(LED);
    delay_ms(1000);
    output_high(LED);
    delay_ms(1000); 
    output_low(LED);
    delay_ms(1000);   
    set_tris_a(0b000000);     // Todo el puerto A como salida.
    porta=0;                  // Inicialmente lo ponemos a cero.
    RF_INT_EN();              // Habilitar interrupción RB0/INT.
    RF_CONFIG_SPI();          // Configurar módulos SPI del PIC.
    RF_CONFIG(0x40,0x08);     // Configurar módulo RF (canal y dirección).
    RF_ON();                  // Activar el módulo RF.
    printf("configurado! \n");
   // Bucle infinito. 
 while(TRUE) 
 { 
    //putc('h');//Envía el caracter vía serie por la USART del PIC 
    // delay_ms(1000);

 } 
 
}

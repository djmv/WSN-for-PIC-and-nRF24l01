#include <16F877A.h> 
#FUSES NOWDT, XT, NOPUT, NOPROTECT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG 
#use delay(crystal=16MHz)
#include "lib_rf2gh4_10.h"
#use rs232(uart1, baud=9600)//usart1 -->ajuste de XMIT y RCV para la USART 1 
#define LED PIN_B1
#byte porta=0x05           // Direcci�n del puerto A.
#int_ext                   // Interrupci�n del m�dulo RF.
void int_RB0()
{
   int8 ret1;
   printf("\n 1er");
   ret1 = RF_RECEIVE();
   printf("\n %d",ret1);
   if ( (ret1 == 0) || (ret1 == 1) )         // Tanto si hay recepci�n simple o m�ltiple, leer datos.
   {
      do
      {    
         porta=RF_DATA[0];                   // El puerto A contendr� el valor que le llegue del emisor, a trav�s de RF_DATA[0].
         printf("\n %c",porta);                  // El puerto A contendr� el valor que le llegue del emisor, a trav�s de RF_DATA[0].
         printf("\n %c",RF_DATA[1]);
         printf("\n %c",RF_DATA[2]);
         printf("\n %d",RF_DATA[3]);
         printf("\n %u",RF_DATA[3]);
         printf("\n 2do");
         ret1 = RF_RECEIVE();                // "ret1" nos dir� si hay recepci�n simple, m�ltiple o no hay datos para leer.
         printf("\n %d",ret1);
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
      set_tris_a(0b000000);     // Todo el puerto A como salida.
      porta=0;                  // Inicialmente lo ponemos a cero.
    RF_INT_EN();              // Habilitar interrupci�n RB0/INT.
    RF_CONFIG_SPI();          // Configurar m�dulos SPI del PIC.
   RF_CONFIG(0x40,0x08);     // Configurar m�dulo RF (canal y direcci�n).
   RF_ON();                  // Activar el m�dulo RF.
   printf("configurado! \n");
   // Bucle infinito. 

 while(TRUE) 
 { 
 //putc('h');//Env�a el caracter v�a serie por la USART del PIC 
// delay_ms(1000);
// printf("Hello world! \n"); 
 
 } 
 
}

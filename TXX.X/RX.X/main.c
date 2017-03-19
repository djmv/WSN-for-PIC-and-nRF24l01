#include <16F877A.h> 
#FUSES NOWDT, XT, NOPUT, NOPROTECT, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG 
#use delay(crystal=16MHz)
#use rs232(uart1, baud=9600)//usart1 -->ajuste de XMIT y RCV para la USART 1 
#define LED PIN_B0
void main() { 
    
      output_low(LED);
      delay_ms(1000);
      output_high(LED);
      delay_ms(1000);
      output_low(LED);
      delay_ms(1000);
      output_high(LED);
      delay_ms(1000);
 while(TRUE) 
 { 
 putc('h');//Envía el caracter vía serie por la USART del PIC 
 delay_ms(1000);
 printf("Hello world! \n"); 
 
 } 
 
}

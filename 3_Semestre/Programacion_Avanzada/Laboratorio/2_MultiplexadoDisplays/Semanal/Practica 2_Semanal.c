#include <18f4550.h>   // Libreria del Microcontrolador
#fuses INTRC, NOWDT, NOPROTECT, NOLVP, CPUDIV1, PLL1, NOMCLR // Fusibles (Configuraciones del microcontrolador)
#use delay(clock = 8M) 

// DEFINIMOS LAS VARIABLES

#define Display1 pin_a3
#define Display2 pin_a4
#define Inicio pin_a0
#define Pausa pin_a1
#define Reinicio pin_a2

void displays(int d, int u);

// Vector para impresion de numeros en display tipo catodo
int vec_c[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,0x7D,0x07,0x7F,0x67};

void main()
{
   int i=0,j=0, time = 0, B = 0;
   
   while(true)
   {
      if(input(Inicio)) // Si se presiona el pin de inicio
      {
         while(input(Inicio)); // Se detiene el codigo para evitar errores
         
         // Etiqueta para hacer el reinicio
         loop:
         B = 0; // Bandera para saber si se ha pausado
         
         // CICLO DE IMPRESION DE NUMEROS. j = Decenas  i = Unidades
         for(j=0;j<10;j++)
            for(i=0;i<10;i++)
            {
               for(time = 0; (time < 50) || B; time++ ) // Se imprime 50 veces en el display (1 seg). Si esta pausado se queda ahi
               {
                  displays(j,i);
               
                  if(input(Pausa) && !B) // Permite pausar con el boton "PAUSA" si no se ha pausado antes
                  {
                     while(input(Pausa))
                        displays(j,i);
                     
                     B = 1;
                  }
                  else if(input(Inicio) && B) // Permite reanudar con el boton "INICIO" si se ha pausado antes
                  {
                     while(input(Inicio))
                        displays(j,i);
                     
                     B = 0;
                  }
               
                  if(input(Reinicio)) // Si se presiona el boton "INICIO"
                  {
                     while(input(Reinicio))
                        displays(j,i);
                        
                     goto loop; // Vuelve a la etiqueta que redefine las variables
                  }
               }
            }
      }
   }
}

void displays(int d, int u) // Realiza el multiplexado de los displays en 20 ms
{
   output_high(Display2); // Apagamos D2
   output_low(Display1); // Prendemos D1
   output_d(vec_c[d]); // Mandamos decenas a D1
   delay_ms(10);
   output_high(Display1); // Apagamos D1
   output_low(Display2); // Prendemos D2
   output_d(vec_c[u]); // Mandamos unidades a D2
   delay_ms(10);
   
}

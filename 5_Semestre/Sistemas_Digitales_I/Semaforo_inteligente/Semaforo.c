#include <18f4550.h>
#fuses INTRC, NOLVP, NOPROTECT, NOWDT, CPUDIV1, PLL1
#use delay(internal = 8M)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
#define sensor input(PIN_B4)//suma carros en el carril superior e inferior
#define sensor2 input(PIN_B5)//Resta carros en el carril superior e inferior
#define sensor3 input(PIN_B6)//suma carros en el carril derecho e izquierdo
#define sensor4 input(PIN_B7)//Resta carros en el carril derecho e izquierdo
/////////////////////////////////////////////////////////////////////////////////
int8 LUZSUIN[]={0b00010010,0b00011010,0b00010100,0b00100001,0b10100001,0b01000001,0b10000100,0b00100001,0b01000100,0b00010001};
int8 Peaton[5]={0b00000110,0b00000101,0b00000110,0b00010010,0b00010001};
int16 carrosup = 0, carrosLD = 0;
int8 salida, flag = 2, state = 0;
int16 timer = 0; // Temporizador para intervalos
int32 w=20000, x=30000,y=10000;
int1 conf;
/////////////////////////////////////////////////////////////////////////////////
// Interrupción para botón peatonal
#int_ext
void intRB0()
{
   output_D(LUZSUIN[8]);  // Luces de advertencia para semáforo peatonal
   delay_ms(5000);        // Tiempo para cambiar
   output_D(LUZSUIN[9]);  // Luces de paso para peatón
   output_A(Peaton[4]);   // Activar señal peatonal
   delay_ms(30000);        // Tiempo de paso para peatones
   
}

// Función para verificar sensores y ajustar luces si es necesario (contar carros)
#int_RB
void Sensores()
{
   if(sensor==0 )//contar sin importar la luz
   {
     carrosup++;
     printf("\rCarros Ve: %lu",carrosup);
     printf("\rCarros Ho: %lu",carrosLD);
   }
   if((salida==LUZSUIN[1] && sensor2==0) || (salida==LUZSUIN[0] && sensor2==0)|| (salida==LUZSUIN[2] && sensor2==0))
   {
      carrosup--;
      printf("\rCarros Ve: %lu",carrosup);
      printf("\rCarros Ho: %lu",carrosLD);
   }
   if(salida==LUZSUIN[1] && sensor4==0)
   {
      carrosup--;
      printf("\rCarros Ve: %lu",carrosup);
      printf("\rCarros Ho: %lu",carrosLD);
   }
////////////////////////////////////////////////////////////////////   
      if(sensor3==0 )
   {
     carrosLD++;
     printf("\rCarros Ho: %lu",carrosLD);
     printf("\rCarros Ve: %lu",carrosup);
   }
   if((salida==LUZSUIN[4] && sensor4==0)||(salida==LUZSUIN[3] && sensor4==0)||(salida==LUZSUIN[5] && sensor4==0))
   {
      carrosLD--;
      printf("\rCarros Ho: %lu",carrosLD);
      printf("\rCarros Ve: %lu",carrosup);
   }
   if(salida==LUZSUIN[4] && sensor2==0)
   {
      carrosLD--;
      printf("\rCarros Ho: %lu",carrosLD);
      printf("\rCarros Ve: %lu",carrosup);
   }  
////////////////////////////////////////////////////////////////////
   if(carrosup==0 && carrosLD==0){flag=2;}//ningun carro
   if(carrosup==1 && carrosLD==0){flag=0;state=0;}//carros en eje vertical y no en el horizontal
   if(carrosup==0 && carrosLD==1){flag=1;state=0;}//carros en eje Horizontal y no en el vertical
   if((carrosup>carrosLD)&&(carrosup!=1)){flag=3;state=0;}//más carros en eje vertical y no en el horizontal
   if((carrosLD>carrosup)&&(carrosLD!=1)){flag=4;state=0;}// mas carros en eje Horizontal y no en el vertical
   if(carrosup==carrosLD){flag=flag;}
/////////////////////////////////////////////////////////////////////

}
// Función para manejar el semáforo en intervalos
void actualizar_semaforo() {
   switch (flag) {
      case 0:{ // Eje vertical activo
         if (state == 0 && timer == 0) {//Verde y giro SU e IN
            output_d(LUZSUIN[1]);
            salida = LUZSUIN[1];
            output_A(Peaton[0]);
            timer = w; state = 1;
         } else if (state == 1 && timer == 0) {//Verde SU e IN
            output_d(LUZSUIN[0]);
            salida = LUZSUIN[0];
            output_A(Peaton[1]);
            timer = x; state = 2;
         } else if (state == 2 && timer == 0) {//Amarillo SU e IN
            output_d(LUZSUIN[2]);
            salida = LUZSUIN[2];
            output_A(Peaton[1]);
            timer = y; state = 3;
         } else if (state == 3 && timer == 0) {//Verde  y giro LD e LI
            output_d(LUZSUIN[4]);
            salida=LUZSUIN[4];
            output_A(Peaton[2]);
            timer = w; state = 4;
         }else if (state == 4 && timer == 0) {//Verde LD y LI
            output_d(LUZSUIN[3]);
            salida=LUZSUIN[3];
            output_A(Peaton[3]);
            timer = x; state = 5;
         }else if (state == 5 && timer == 0) {//Amarillo LD y LI
            output_d(LUZSUIN[5]);
            salida=LUZSUIN[5];
            output_A(Peaton[3]);
            timer = y; state = 0;
         }
         break;
   }
      case 1:{ // Eje horizontal activo
         if (state == 0&& timer == 0) {//Verde  y giro LD e LI
            output_d(LUZSUIN[4]);
            salida = LUZSUIN[4];
            output_A(Peaton[2]);
            timer = w; state = 1;
         } else if (state == 1 && timer == 0) {//Verde LD y LI
            output_d(LUZSUIN[3]);
            salida = LUZSUIN[3];
            output_A(Peaton[3]);
            timer = x; state = 2;
         } else if (state == 2 && timer == 0) {//Amarillo LD y LI
            output_d(LUZSUIN[5]);
            salida = LUZSUIN[5];
            output_A(Peaton[3]);
            timer = y; state = 3;
         } else if (state == 3 && timer == 0) {//Verde y giro SU e IN
            output_d(LUZSUIN[1]);
            salida = LUZSUIN[1];
            output_A(Peaton[0]);
            timer = w; state = 4;
         } else if (state == 4 && timer == 0) {//Verde SU e IN
            output_d(LUZSUIN[0]);
            salida = LUZSUIN[0];
            output_A(Peaton[1]);
            timer = x; state = 5;
         } else if (state == 5 && timer == 0) {//Amarillo SU e IN
            output_d(LUZSUIN[2]);
            salida = LUZSUIN[2];
            output_A(Peaton[1]);
            timer = y; state = 0;
         }
            break;
   }

      case 2: // Modo peatonal
      {
         output_d(LUZSUIN[9]);
         output_A(Peaton[4]);
         state = 0; // Reiniciar estado para volver a modo normal
         break;
      }
      case 3:// Mas en el vertical
      {
        if (state == 0 && timer == 0) {//Amarillo LD y LI
            output_d(LUZSUIN[5]);
            salida = LUZSUIN[5];
            output_A(Peaton[3]);
            timer = y; state = 1;
            }else if (state == 1 && timer == 0) {//Verde y giro SU e IN
            output_d(LUZSUIN[1]);
            salida = LUZSUIN[1];
            output_A(Peaton[0]);
            timer = w; state = 2;
         } else if (state == 2 && timer == 0) {//Verde SU e IN
            output_d(LUZSUIN[0]);
            salida = LUZSUIN[0];
            output_A(Peaton[1]);
            timer = x; state = 3;
         } else if (state == 3 && timer == 0) {//Amarillo SU e IN
            output_d(LUZSUIN[2]);
            salida = LUZSUIN[2];
            output_A(Peaton[1]);
            timer = y; state = 4;
         }if (state == 4&& timer == 0) {//Verde  y giro LD e LI
            output_d(LUZSUIN[4]);
            salida = LUZSUIN[4];
            output_A(Peaton[2]);
            timer = w; state = 5;
         } else if (state == 5 && timer == 0) {//Verde LD y LI
            output_d(LUZSUIN[3]);
            salida = LUZSUIN[3];
            output_A(Peaton[3]);
            timer = x; state = 0;
         }
         break;
      }//case 3
      case 4://mas en el horizontal
      {
         if (state == 0 && timer == 0) {//Amarillo SU e IN
            output_d(LUZSUIN[2]);
            salida = LUZSUIN[2];
            output_A(Peaton[1]);
            timer = y; state = 1;
         }else if (state == 1 && timer == 0) {//Verde  y giro LD e LI
            output_d(LUZSUIN[4]);
            salida = LUZSUIN[4];
            output_A(Peaton[2]);
            timer = w; state = 2;
         }else if (state == 2 && timer == 0) {//Verde LD y LI
            output_d(LUZSUIN[3]);
            salida = LUZSUIN[3];
            output_A(Peaton[3]);
            timer = x; state = 3;
         }else if (state == 3 && timer == 0) {//Amarillo LD y LI
            output_d(LUZSUIN[5]);
            salida = LUZSUIN[5];
            output_A(Peaton[3]);
            timer = y; state = 4;
         }else if (state == 4 && timer == 0) {//Verde y giro SU e IN
            output_d(LUZSUIN[1]);
            salida = LUZSUIN[1];
            output_A(Peaton[0]);
            timer = w; state = 5;
         }else if (state == 5 && timer == 0) {//Verde SU e IN
            output_d(LUZSUIN[0]);
            salida = LUZSUIN[0];
            output_A(Peaton[1]);
            timer = x; state = 0;
         } 
            break;
      }//case 4
   }
}//función

void main() {

   set_tris_b(0xFF);
   enable_interrupts(int_ext);
   enable_interrupts(int_RB);
   enable_interrupts(GLOBAL);
   
   while (true) {
      actualizar_semaforo();
      printf("Presiona 0 para tiempo base o presiona 1 para configurar los tiempos");
      conf=getc();
      switch(conf)
      {
         case 0:
         {
            break;
         }
         case 1:
         {
           printf("tiempo para el giro a la izquierda(poner el tiempo en segundos ejemplo 20):");
           w=(getc())*1000;
           printf("tiempo para luz verde (poner el tiempo en milisegundos ejemplo 20seg se anota 20000):");
           x=(getc())*1000;
           printf("tiempo para la luz Amarilla (poner el tiempo en milisegundos ejemplo 20seg se anota 20000):");
           y=(getc())*1000;
           break;
         }
      }
      //if (timer > 0) timer -= 100; // Descuenta 100 ms en cada ciclo para que se coordine con el delay de abajo
      if (timer >= 1000) //Para intervalos de 10 a 60 seg
      {
         timer -= 1000;  // Decrementa en intervalos de 1 segundo siempre que sea posible
      }
      delay_ms(600); // Espera pequeña para dar tiempo al cambio de flag
   }
}






// --------------- Preprocesadores de microcontrolador -------------- //
   #include    <18F4550.h> 
   #device     ADC=8
   #include    <stdlib.h>
   #include    <stdio.h>
   #include    <math.h>
   #fuses      HS,NOWDT,NOPROTECT, CPUDIV1,PLL5,NOLVP
   #use        delay(CLOCK=20M)
   #use        RS232(BAUD = 115200, XMIT = PIN_C6, RCV = PIN_C7, BITS = 8, PARITY = N)
   #use        I2C(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW)

// --------------------- Direccion de registros --------------------- //
// GPIO
   #byte porta = 0xf80
   #byte portb = 0xf81
   #byte portc = 0xf82
   #byte portd = 0xf83
   #byte porte = 0xf84
   
   #bit  PD4   = 0xf83.4

// TIMER
   #byte TMR0H = 0xfd7 //TMR0H
   #byte TMR0L = 0xfd6 //TMR0L
   #byte T0CON = 0xfd5 //T0CON
   #byte INTCON= 0xff2 //INTCON

// --------------------------- Constantes --------------------------- //
   #define pi_     3.141593   // Valor de PI
   #define pi_s2   1.570796

// Parametros para sistema de control
   // Ganancias
   #define k1 0.19//0.1403//0.19
   #define k2 1.94//1.1961//1.94
   #define k3 0.90//0.8757//0.90
   #define k4 2.57//1.2474//2.57

   #define kp 0.08//0.16//0.08
   #define kv 0.008//0.016//0.008

   #define vd     0.075                // Velocidad traslacional deseada en m/s
   #define Ts     0.01                 // Periodo de muestreo
   
// Parametros fisicos del robot
   #define ppr    12.0                 // Pulsos por revolucion de encoder
   #define Ra     3.0                  
   #define NR     44.0                 // Relacion de transmision
   #define R      0.034                // Radio de la rueda
   #define km     0.0008
   #define b      0.0965               // Distancia entre ruedas

   #define calpha 0.145

   #define tauM   0.3                  // Par maximo de rueda [Nm]
   #define alphaM 1.4                  // 1.57
   #define omegaM 16.0                 // Omega maximo // 70 rev en 30 s, 140 rev/min, 14.7 rad/s 
   #define uM     10.55                // Voltaje maximo   
   #define uNM    10.00                // Voltaje nominal maximo

// Factores de conversion
   #define deg_2_rad          0.0174533 
   #define rad_2_deg          57.29578
   #define accel_div_factor   16384.0
   #define gyro_div_factor    131.0
   #define accel_factor       0.0000610352
   #define gyro_factor        0.0076336

   #define c1 0.995//0.993

// ---------------- Direcciones de registros del IMU ---------------- //
   #define W_DATA         0xD0
   #define R_DATA         0xD1
   #define PWR_MGMT_1     0x6B
   #define PWR_MGMT_2     0x6C
   #define SMPRT_DIV      0x19
   #define CONFIG_R       0x1A
   #define GYRO_CONFIG    0x1B
   #define ACCEL_CONFIG   0x1C
   #define ACCEL_XOUT_H   0x3B
   #define ACCEL_XOUT_L   0x3C
   #define ACCEL_YOUT_H   0x3D
   #define ACCEL_YOUT_L   0x3E
   #define ACCEL_ZOUT_H   0x3F
   #define ACCEL_ZOUT_L   0x40
   #define TEMP_OUT_H     0x41
   #define TEMP_OUT_L     0x42
   #define GYRO_XOUT_H    0x43
   #define GYRO_XOUT_L    0x44
   #define GYRO_YOUT_H    0x45
   #define GYRO_YOUT_L    0x46
   #define GYRO_ZOUT_H    0x47
   #define GYRO_ZOUT_L    0x48

// ----------------------- Variables globales ----------------------- //
   signed int16 Ax,Gy;
   int8 uWr,uWl;
   signed int8 incr,incl;
   float Sr,Sl;
   int8 posr,posl;               //Posiciones o cuentas del encoder.
   int8 puerto,AB,AB_1,CD,CD_1,auxAB,auxCD; // Variables auxiliares lectura de encoders.
   int8 vdg,vg,thetag,alphag,omegalg,omegarg,ulg,urg;

// Muestreo de datos del MPU 
   signed int8 A_data_x[2];      // Lectura Ax del MPU (Parte baja y parte alta)
   signed int8 A_data_y[2];      // Lectura Ay del MPU (Parte baja y parte alta)
   signed int8 A_data_z[2];      // Lectura Az del MPU (Parte baja y parte alta)
   signed int8 G_data_y[2];      // Lectura Gy del MPU (Parte baja y parte alta)

// Filtro complementario y angulos
   float Xa=0.0,Yg=0.0,alpha=0.0;
   float accelx=0.15,angulox=0.15,angulox_1=0.0,c2=1.0-c1;

// Variables auxiliares
   float t=0.0,iTs=1.0/Ts,esc=pi_/(2.0*ppr*NR),escs=255.0/uM;

//Velocidades
   float omegar=0,omegal=0;

//Voltajes a motores
   float ur=0.0,ul=0.0;
   float v=0.0,alpha_1=0.0,theta=0.0,thetad=0.0,thetatil=0.0,taua=0.0,u=0.0;
   float alphap=0.0,vtil=0.0,thetap=0.0,taur=0.0,taul=0.0; 
   float Rasnkm=Ra/(NR*km),nkm=NR*km,intvtil=0.0,v2tauM=2.0*tauM;

// Pendientes para graficas
   float mv=255.0/(2.0*omegaM*R),mtheta=255.0/(2.0*0.3),malpha=255.0/(2.0*alphaM),momega=255.0/(2.0*omegaM),mu=255.0/(2.0*uM);

// ---------------------------- Funciones --------------------------- //
void MPU6050_write(int add, int data)     // Funcion para escribir al MPU6050
{
   i2c_start();
   i2c_write(W_DATA);
   i2c_write(add);
   i2c_write(data);
   i2c_stop();
}

int16 MPU6050_read(int add)               // Funcion para leer datos del MPU6050
{
   int retval;
   i2c_start();
   i2c_write(W_DATA);
   i2c_write(add);
   i2c_start();
   i2c_write(R_DATA);
   retval = i2c_read(0);
   i2c_stop();
   return retval;
}

void MPU6050_init()                       // Funcion para iniciar el MPU6050
{
   MPU6050_write(PWR_MGMT_1, 0x80);
   delay_ms(100);
   MPU6050_write(PWR_MGMT_1, 0x00);
   delay_ms(100);
   MPU6050_write(CONFIG_R, 0x01);
   delay_ms(10);
   MPU6050_write(GYRO_CONFIG, 0x00);
}

void MPU6050_get_Ax()                     // Funcion para leer el valor Ax del MPU
{
   A_data_x[0] = MPU6050_read(ACCEL_XOUT_H);
   A_data_x[1] = MPU6050_read(ACCEL_XOUT_L);
}

void MPU6050_get_Ay()                     // Funcion para leer el valor Ay del MPU
{
   A_data_y[0] = MPU6050_read(ACCEL_YOUT_H);
   A_data_y[1] = MPU6050_read(ACCEL_YOUT_L);
}

void MPU6050_get_Az()                     // Funcion para leer el valor Az del MPU
{
   A_data_z[0] = MPU6050_read(ACCEL_ZOUT_H);
   A_data_z[1] = MPU6050_read(ACCEL_ZOUT_L);
}

void MPU6050_get_Gy()                     // Funcion para leer el valor Gy del MPU
{
   G_data_y[0] = MPU6050_read(GYRO_YOUT_H);
   G_data_y[1] = MPU6050_read(GYRO_YOUT_L);
}

// -------------------------- Interrupciones ------------------------ //   
#int_rb                                   // Interrupcion de cambio en el puerto B, para leer encoders en pines B4-B7
void rb_isr()
{
   puerto = PORTB;              // Almacenamos valor de pines del puerto B
   AB =((puerto)&(0x30)) >> 4;
   auxAB=AB^AB_1;

   if(auxAB!=0)
      if(auxAB!=3)
      {
          if(((AB_1<<1)^AB)&(0x02))
             posr--;
          else
             posr++;
      }
   
   AB_1=AB;
    
   CD =((puerto)&(0xC0)) >> 6;
   auxCD=CD^CD_1;
   if(auxCD!=0)
      if(auxCD!=3)
      {
         if(((CD_1<<1)^CD)&(0x02))
            posl--;
         else
            posl++;
      }

   CD_1 = CD;
}

// ------------------------ Codigo Principal ------------------------ //
int main()
{  
   //Configuracion de pines como entradas o salidas.
   set_tris_a(0b11111111);
   set_tris_b(0b11110011);
   set_tris_c(0b01000000);
   set_tris_d(0b11100000);
   set_tris_e(0b11111111);

   MPU6050_init();   //Inicializamos MPU6050
   
   // Configuracion de TIMER0
   T0CON = 0xC7;       //Prescaler asignado a timer0 con relacion 1:256
   TMR0L = 0;
   PD4 = 0;
   
   // Inicializacion de variables para cuentas de encoder a 0   
   AB = AB_1 = 0;
   // Inicializacion de cuentas encoder derecho a mitad del rango para que no desborde
   posr = 127;
   // Inicializacion variables para cuentas de encoder a 0
   CD = CD_1 = 0;
   // Inicio de cuentas encoder izquierdo a mitad del rango para que no desborde
   posl = 127;
   
   //Configurar timer 2 como PWM de x frecuencia
   setup_timer_2(T2_DIV_BY_16,254,1);
   
   //Configurar pines 16 y 17 del 4550 como PWM
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   
   // Configurar puertos ADC
   setup_adc(ADC_CLOCK_INTERNAL);         // Utilizando oscilador interno
   setup_adc_ports(AN0_TO_AN1);
   
   // Habilitamos interrupciones
   enable_interrupts(int_rb);
   enable_interrupts(global);
   
   while(true)
   {
      PD4 = 1;   //Se prende bit de tiempo de ejecuci�n
      
      // Obtenemos datos del sensor de linea izquierdo
      set_adc_channel(0);
      delay_us(15);
      Sl = read_adc();

      // Obtenemos datos del sensor de linea derecho
      set_adc_channel(1);
      delay_us(15);
      Sr = read_adc();
      
      //Se Leen los datos del MPU
      MPU6050_get_Ax();
      MPU6050_get_Gy();
      
      Ax = 0;
      Ax = A_data_x[0];
      Ax = Ax<<8;
      Ax = Ax+A_data_x[1];    //Lectura cargada en variable Ax
      
      Gy = 0;
      Gy = G_data_y[0];
      Gy = Gy<<8;
      Gy = Gy+G_data_y[1];    // Lectura cargada en variable Gy
      
      theta = Sr-Sl;

      if(theta > 160.0)
         theta = 160.0;
      if(theta < -160.0)
         theta =- 160.0;

      theta =- 0.3*theta/160.0;   //Error de seguimiento en radianes  
      
      //Calculo de velocidad derecha en radianes
      incr=127-posr;
      posr=127;
      omegar=incr*esc*iTs;

      //Calculo de velocidad izquierda en radianes
      incl=127-posl;
      posl=127;
      omegal=incl*esc*iTs;
      
      //Los valores del MPU los paso a valores flotantes con sus respectivas escalas
      Xa=-Ax*accel_factor; //Xa en rango de -1 a 1
      Yg=Gy*gyro_factor;   //Yg en grados sobre segundo
      Yg=deg_2_rad*Yg;     //Yg en rad sobre segundo 
      
      //Calculo del filtro complementario
      accelx=Xa*pi_s2;  //Inclinaci�n en rango de -pi/2 a pi/2 rad
      angulox=c1*(angulox_1+Yg*Ts)+c2*accelx;//Ecuaci�n del filtro complementario
      angulox_1=angulox;//Respaldando valor pasado
      alpha=-angulox;
      alpha=alpha-calpha;//Compensaci�n de alineaci�n del MPU
      
      if(alpha>=alphaM)
         alpha=alphaM;
      if(alpha<=(-alphaM))
         alpha=-alphaM;

      // Calculo de velocidad traslacional
      v = (omegar+omegal) * R / 2.0;   
      // Calculo de theta punto
      thetap = (omegar-omegal) * R / (2.0*b);
               
      thetatil = theta-thetad;     //Se calcula theta tilde
      alphap = (alpha-alpha_1)*iTs;//Se calcula alpha punto
      alpha_1 = alpha;
      vtil = v-vd;                 //Se calcula v tilde
      
      if((intvtil<v2tauM)&&(intvtil>(-v2tauM))) //Integral de v tilde
         intvtil=intvtil+Ts*vtil;
      else
      {
         if(intvtil>=v2tauM)
            intvtil=0.95*v2tauM;
         if(intvtil<=(-v2tauM))
            intvtil=-0.95*v2tauM; 
      }

      //Esfuerzos de control   
      taua = (-kv*thetap-kp*thetatil)*2.0*b/R;
      u = k1*alphap+k2*alpha+k3*vtil+k4*intvtil;
      if(u>=v2tauM)
         u = v2tauM;
      if(u<=(-v2tauM))
         u =- v2tauM; 
                           
      //Pares por rueda      
      taur = (taua+u)/2.0;    // par derecho
      taul = (-taua+u)/2.0;   // par izquierdo
                           
      //Voltaje rueda izquierda
      ul = taul*Rasnkm+nkm*omegal;   
      //ul=uNM*sin(0.314*t);
      //ul=0.0;
      //ul=5.0;
      //ul=uNM;
      if(ul>=uNM)
         ul=uNM;
      if(ul<=(-uNM))
         ul=-uNM;
      uWl=escs*fabs(ul);
      if(ul<0)
      {
         output_high(pin_d0);
         output_low(pin_d1);
      }
      else
      {
         output_low(pin_d0);
         output_high(pin_d1);
      }

      
      //Voltaje rueda derecha    
      ur = taur*Rasnkm+nkm*omegar;
      //ur=uNM*cos(0.314*t);
      //ur=0.0;
      //ur=5.0;
      //ur=uNM;
      if(ur>=uNM)
         ur = uNM;
      if(ur<=(-uNM))
         ur =- uNM;
      uWr = escs*fabs(ur);
      if(ur<0)
      {
         output_high(pin_d2);
         output_low(pin_d3);
      }
      else
      {
         output_low(pin_d2);
         output_high(pin_d3);
      }
      
      set_pwm1_duty(uWl); //Actualizando el valor del pwm rueda izquierda
      set_pwm2_duty(uWr); //Actualizando el valor del pwm rueda derecha
      
      // Envio de datos muestreados por UART
      putc(0xAA); //ID a la PC
      vdg=(int8)(mv*vd+127);
      putc(vdg);          
      vg=(int8)(mv*v+127);
      putc(vg);          
      thetag=(int8)(mtheta*theta+127);
      putc(thetag);   
      alphag=(int8)(malpha*alpha+127);
      putc(alphag);   
      omegalg=(int8)(momega*omegal+127);
      putc(omegalg);   
      omegarg=(int8)(momega*omegar+127);
      putc(omegarg);   
      ulg=(int8)(mu*ul+127);
      putc(ulg);          
      urg=(int8)(mu*ur+127);
      putc(urg);
      
      PD4=0;            //Se apaga bit de tiempo de ejecuci�n
      while(TMR0L<196); //Cada cuenta vale (4/FXtal)*256 seg
      t=t+Ts;
      TMR0L = 0;        //Reseteo contador del timer0
   }

   return 0;
}


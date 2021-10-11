
/*
 * Nombre del Proyecto:
    Radiometro
 * Copyright:
     Dr. Victor Pasilla Campos
     creado : 2 de agosto de 2019
 * Descripción:
      Radiometro.c    programa principal
      def_pines.h contiene la deficiones de pines de I/O usados
      funciones.h contiene las funcipones especiales para este proeyecto
      PCF85176.h  contiene las funciones para e
      funciones_atmega168.h   Contiene las funciones de inicializacion de perifericos del Atmega168a

      Historial de modificaciones

      02/ 08 / 2019  Version inicial
      5 /08 /2019 se agregaron funciones para el driver PCF85176T
      7/08/2019   se agrego funcion de letrero de bAT bAJA y la lectura del sensor optico
      8/08/2019   se eliminaron ceros a la izquierda
      21/08/2019  se cambio al Modo de  integracion de 100 del sensor OPT
      16/08/2019  se agrego promediacion de muestras para despliegue
      29/09/2019  se agrego letrero "OL" para escala maximo
      ultima modificacion:   29/09 /2019


  */
  
  #define Bateria_muy_baja    0
  #define Bateria_baja        1
  #define Bateria_Aceptable   2
  
  #define MODO_A               0
  #define MODO_B               1


 #include "Funciones_atmega168a.h"
 #include "Def_pines.h"
 #include "Funciones.h"
 #include "PCF85176T.h"
 
 #define OPT_ADDR_W   0x88
 #define OPT_ADDR_R   0x89



/* **************************************************************************
    variables utilizadas
 ************************************************************************** */

bit bandera_blink;
volatile unsigned char contadorTicks=0;
volatile unsigned char contador_segundos=0;
volatile unsigned  char  contador_minutos=0;
unsigned char Estado_bateria;
int contador;
unsigned int Lectura_potencia;
unsigned int Lecturas [5];
unsigned char Modo;
bit Bandera_10_min;
bit Bandera_20_min;
unsigned char Contador_reset;
int Contador_muestras ;
long int suma_datos;


/* **************************************************************************
  //  timer 1 genera  el conteo de tiempo
  // se activa cada 250 ms

 ************************************************************************** */

void Timer1Overflow_ISR() org IVT_ADDR_TIMER1_OVF {
     Set_timer1(19000);
     contadorTicks++ ;
     if ( contadorTicks > 3 ){ // 4 ticks Ha pasado un segundo
          contador_segundos++;
          if (contador_segundos >59){
             contador_minutos++;
             if ( contador_minutos == 5){ // 5 minutos para prueba
                Bandera_10_min=CIERTO;
             }
             if ( contador_minutos > 9){    // 10 min para prueba
                Bandera_20_min=CIERTO;
             }
             contador_segundos=0;
          }   // termina if de conteo de segundos
          Contador_reset ++;
          if (Contador_reset>=5){  // 5 segundos que el sistema se congelo por alguna razon
              Boton_OFF_dir=SALIDA;   // cambiar el boton de encendide de entrada a salida
              Boton_OFF_port=0;      // enviar un 0 a la salida de off para apagado por software
          }
          contadorTicks=0;
     } //  termina if de conteo de ticks
}


  /* **************************************************************************
     Interrupcion Externa por cambio del pin
    se usa para leer el boton de cambio de Modo, hace que el sistema pase del Modo A al Modo B
     Modo A = lectura de potencia (uW/cm2) / 20
     Modo B = lectura de potencia (uW/cm2)


 ************************************************************************** */
  void Interrupcion_ext2() iv IVT_ADDR_PCINT2 ics ICS_AUTO {
      if ( Boton1 ) {
         if  (Modo==MODO_A){    // cambia al Modo  B y resetea contadores y banderas
             Modo=MODO_B;
             Bandera_10_min=FALSO;
             contadorTicks=0;
             contador_segundos=0;
             contador_minutos=0;
         }
         else{       // cambia al Modo  A y resetea contadores y banderas
             Modo=MODO_A;
             Bandera_10_min=FALSO;
             contadorTicks=0;
             contador_segundos=0;
             contador_minutos=0;
         }
      }
  }

/* ******************************************************************************
*    Declaracion de prototipo de funciones
*
*/

  int  Medir_bateria(void );
  void Marquesina_BAT_BAJA( void );
  void Configura_OPT3002( void );
  int Lectura_OPT3002( void ) ;


/********************************************************************************
*    Programa Main principal
*    configura timers, interrupciones y pines de I/O
*    Lectura de botones y conteo de tiempo se realiza en interrupciones
*     el programa principal actualiza display y hace lectura del sensor optico
*/
void main() {

     Inicializa_pines();
     bandera_blink=FALSO;

     configuraTIMER1(Preescaler_64);    // timer para conteo de tiempo
    // configuracion del ADC para la lectura del nivel de la bateria
     Configura_ADC (Preescaler_ADC_128);      // configuraciones para el ADC
     Configura_ADC (CANAL_0);
     Configura_ADC (VREF_AVCC);
     Configura_ADC (INICIA_ADC);
     Configura_ADC (INICIA_CONVERSION_ADC);     // primera conversion del ADC
     // variables para digitos individuales
     UNIDADES=0;
     DECENAS=0;
     CENTENAS=0;
     MILLAR=0;
     contador_segundos=0;
     Contador_muestras=0;
     contador=0;
     Contador_reset=0;
     Estado_bateria=0;
     Modo= MODO_A;
     Bandera_10_min=FALSO;
     Bandera_20_min=FALSO;
     TWI_Init(100000);
    /* do {      // leer el boton de encendido un minimo de tiempo  antes de encender todo el sistema

        if ( Boton_OFF_pin ==0){   // se esta presionando el boton de on/off
           contador++;
        }
        else {
           contador--;
           if (contador==0){   // no se presiono el boton el suficiente tiempo
             Boton_OFF_dir=SALIDA;   // cambiar el boton de encendido de entrada a salida
             Boton_OFF_port=0;      // enviar un 0 a la salida de off para apagado por software
             delay_ms(1000);
           
           }
        }
        delay_ms(100);
     }while ( contador <20);
      */
     init_PCF85176(); 
     Led1=ENCENDIDO;         // inicializar driver del LCD
     Estado_bateria=Medir_bateria();            // medir nivel de bateria ahi se decide si continua o se apaga el sistema

     /// si pasa significa que el nivel de bateria es aceptable , continua configuracion perifericos
     SETBIT(PCICR,PCIE2); // activar interrupcion externa pines PCINT[23:16]
     SETBIT (PCMSK2,PCINT22);  // seleccionar pin PD6 (PCINT22) para interrupcion externa
     init_PCF85176();
     delay_ms(1000);

     delay_ms(500);
     Configura_OPT3002();        //  configurar el sensor optico para lectura
     Inicia_timer1();    // arrancar timer de conteo de tiempo
     SREG_I_bit=1;                    // habilitar interrupciones
     Lectura_potencia=Lectura_OPT3002();     // leer potencia y se regresa en uW/ cm2

// inicia el programa pincipal, aqui mide y despliegua dependiendo del Modo activo
// este Modo se cambia en interrupcion por boton
     while (1){
          Lecturas[Contador_muestras]=Lectura_OPT3002();     // leer potencia y se regresa en uW/ cm2

         Contador_muestras++;
          if (Contador_muestras>3){
             suma_datos= (Lecturas[0]+Lecturas[1]+Lecturas[2]+Lecturas[3])/4;
             Lectura_potencia=(unsigned int) suma_datos;
             Contador_muestras=0;
          }

          if ( Modo == MODO_A ){
              LED1=ENCENDIDO;         // led indica Modo A
              LED2=APAGADO;
              if (Lectura_potencia<10000){
                 DEC_A_DIG ( Lectura_potencia/2);        //  si es Modo A se despliega potencia /20
                 Actualiza_display(MILLAR,CENTENAS,DECENAS+10, UNIDADES, bandera_blink);  // DECENAS +10 despliega el digito junto con el punto decimal
              }
              else {
                 Actualiza_display(ESPACIO,ESPACIO,LETRA_O, LETRA_L, bandera_blink);
              }
          }
          else {   // esta en Modo B
              LED1=APAGADO;
              LED2=ENCENDIDO;            // Led que indica Modo B
              if (Lectura_potencia<10000){
                 DEC_A_DIG ( Lectura_potencia);
                 Actualiza_display(MILLAR,CENTENAS,DECENAS, UNIDADES, bandera_blink);
              }
              else {
                 Actualiza_display(ESPACIO,ESPACIO,LETRA_O, LETRA_L, bandera_blink);
              }
              
          }
          if (Bandera_20_min){      // si se llega a 20 minutos de inactividad se apaga
             Bandera_20_min=FALSO;
             Boton_OFF_dir=SALIDA;   // cambiar el boton de encendide de entrada a salida
             Boton_OFF_port=0;      // enviar un 0 a la salida de off para apagado por software
             delay_ms(1000);
          }
          if (Bandera_10_min){       // cada 10 minutos mide la bateria
             Medir_bateria();
             Bandera_10_min=FALSO;
          }
          Contador_reset=0;    // reiniciar en cada ciclo el contador de reset y apagado automatico
          delay_ms(200);
     }
}

/*
*   Funcion para medir el nivel de la bateria
*   mide el voltaje con un divisor de voltaje Vbat/2
*   regresa un valor que indica el estado de la bateria
*/

int  Medir_bateria(){
  int Voltaje;
  int estado;
  
  Voltaje = Lee_canal_AD(CANAL_0);
  if (Voltaje >819){  // voltaje aceptable  V > 8V
      estado= Bateria_Aceptable;
  }
  else {  // es menor del aceptable
       if (Voltaje >768){  // voltaje bajo  7.5v > V < 8V
          estado= Bateria_baja;
         Marquesina_BAT_BAJA();

       }
       else {   // voltaje muy bajo       V < 7.5V
          estado= Bateria_muy_baja;
          Boton_OFF_dir=SALIDA;   // cambiar el boton de encendide de entrada a salida
          Boton_OFF_port=0;      // enviar un 0 a la salida de off para apagado por software
          delay_ms(1000);
       }
  }
  return estado;
}
 /*
 *    Funcion para desplegar el letrero de "BAt BAJA"
 *
 *
 */

 void Marquesina_BAT_BAJA(){

         Actualiza_display(LETRA_B , LETRA_A, LETRA_T,ESPACIO,bandera_blink);
         delay_ms(2500);
         Actualiza_display(LETRA_B, LETRA_A,LETRA_J,LETRA_A ,bandera_blink);
         delay_ms(2500);
 }
   /*
 *    Funcion para configurar el sensor OPT3002
 *
 *
 */
void Configura_OPT3002( void ) {

       TWI_Start();
       TWI_Write(OPT_ADDR_W);
       TWI_Write(0x01);              // registro de configuracion   , y dos bytes de configuracion
   //    twi_write(0xCE);             //  Automatic Full-Scale , 800 ms,  Continuous conversions,
       twi_write(0xC6);             //  Automatic Full-Scale , 100 ms,  Continuous conversions,
       TWI_Write(0x10);             //
       TWI_Stop();

}

 /*
 *    Funcion para leer de el sensor OPT3002
 *    el valor leido son dos bytes
 *   Bit Field         Type    Reset    Description
 *    15-12 E[3:0]      R        0h      Exponent. These bits are the exponent bits. Table 8 provides further details.
       11-0 R[11:0]     R       000h     Fractional result.T hese bits are the result in straight binary coding (zero to full-scale).
  *  la funcion realiza la conversion aptencia optia y regresa un valor entero en uW/cm2
  *  para la lectura del sensor primero se escribe al sensor la direccion del resultado de la medicion y
  *  despues se Lee del registro
  * el resultado es Pot_optica = Fractional result (mantisa) * 2^Exponente *1.2     nW /cm2
  * se divide entre 1000 para tener resultado en uW/cm2
  */
int Lectura_OPT3002( void ) {
unsigned char Res_H,Res_L;
int exponente,mantisa;
float pot_optica=0;
int   pot_optica_uw;

       TWI_Start();
       TWI_Write(OPT_ADDR_W);
       TWI_Write(0x00);              // registro de resultado
       TWI_Stop();
       delay_us(100);
       TWI_Start();
       TWI_Write(OPT_ADDR_R);
       Res_H= TWI_READ(1);              // registro de resultado
       Res_L= TWI_READ(0);              // registro de resultado
       TWI_Stop();
       exponente =(Res_H & 0xF0)>>4;
       mantisa=(Res_H & 0x0F)*256 +  Res_L;
       pot_optica = mantisa* pow (2,exponente)*1.2/1000;
       pot_optica_uw= (int )pot_optica ;
       return   (pot_optica_uw);
}
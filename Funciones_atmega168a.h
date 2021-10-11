

#define SETBIT(ADD,BIT) ADD |= (1 << BIT)
#define CLRBIT(ADD,BIT) ADD &= ~(1 << BIT)
#define CHKBIT(ADD,BIT) ADD & (1 << BIT)
#define GLOBAL                        SREG |= (1 << 7)
#define NOGLOBAL                SREG &= ~(1 << 7)
#define SALIDA    1
#define ENTRADA   0
#define CIERTO    1
#define FALSO     0
#define APAGADO    0
#define ENCENDIDO 1


//#define        TOGGLE(ADD,BIT);        {if((ADD & (1 << BIT))) ADD &= (1 << BIT); else ADD |= (1 << BIT);}


/*
*      Definiciones para el timer 0 y 1
*
*/


#define Preescaler_1           1      // valores de configuracion de los timers
#define Preescaler_8           2     // Nota : no todos los timers aceptan todos los parametros
#define Preescaler_32          3
#define Preescaler_64          4
#define Preescaler_128         5
#define Preescaler_256         6
#define Preescaler_1024        7


/*
*      Definiciones para el ADC
*
*/
#define Preescaler_ADC_2         1      // valores de configuracion del ADC
#define Preescaler_ADC_4         2
#define Preescaler_ADC_8         3
#define Preescaler_ADC_16        4
#define Preescaler_ADC_32        5
#define Preescaler_ADC_64        6
#define Preescaler_ADC_128       7
#define INICIA_ADC               8
#define INICIA_CONVERSION_ADC    9
#define DETEN_ADC                10
#define FREE_RUN_ADC             11
#define ACTIVA_INTERRUPCION_ADC  12
#define  CANAL_0                 13
#define  CANAL_1                 14
#define  CANAL_2                 15
#define  CANAL_3                 16
#define  CANAL_4                 17
#define  CANAL_5                 18
#define  CANAL_6                 19
#define  VREF_AVCC               20
#define  VREF_11                 21
#define  NO_AVCC                 22
#define         ADC_IZQUIERDA    23
#define  ADC_DERECHA             24



 /**************************************************
 *
 *      Función para arrancar el timer 0 de 8 bits
 *      Parametros permitidos:
 *
 *
 */
void Inicia_timer0(){

        SETBIT(TIMSK0,0);
}

 /**************************************************
 *
 *      Función para detener el timer 0 de 8 bits
 *      Parametros permitidos:
 *
 *
 */
  void Detiene_timer0(){

         CLRBIT(TIMSK0,0);

 }


 /**************************************************
 *
 *      Función para configurar el timer 0 de 8 bits
 *      Parametros permitidos:
 *      Preescaler1, Preescales8, Preescaler64, Preescaler256,Preescaler1024
 *
 */


void configuraTIMER0(int parametros){


        switch(parametros){
                case Preescaler_1:

                        SETBIT(TCCR0B,0);                  // reloj con preescalamiento de 1
                        CLRBIT(TCCR0B,1);
                        CLRBIT(TCCR0B,2);
                        //CS02=1;//
                break;
                case Preescaler_8:
                        CLRBIT(TCCR0B,0);                  // reloj con preescalamiento de 8
                        SETBIT(TCCR0B,1);
                        CLRBIT(TCCR0B,2);

                break;
                case Preescaler_64:
                        SETBIT(TCCR0B,0);                  // reloj con preescalamiento de 64
                        SETBIT(TCCR0B,1);
                        CLRBIT(TCCR0B,2);

                break;
                case Preescaler_256:
                        CLRBIT(TCCR0B,0);                  // reloj con preescalamiento de 256
                        CLRBIT(TCCR0B,1);
                        SETBIT(TCCR0B,2);
                break;
                case Preescaler_1024:
                        SETBIT(TCCR0B,0);                  // reloj con preescalamiento de 1024
                        CLRBIT(TCCR0B,1);
                        SETBIT(TCCR0B,2);
                break;
        }

}

   /**************************************************
 *
 *      Función para arrancar el timer 0 de 8 bits en un valor
 *      Parametros permitidos:
 *      valor de inicio
 *
 */

void Set_timer1(unsigned int valor ){

      TCNT1H= valor >> 8;
      TCNT1L= valor & 0xFF;

}

 /**************************************************
 *
 *      Función para arrancar el timer 0 de 8 bits
 *      Parametros permitidos:
 *
 *
 */
void Inicia_timer1(){

        SETBIT(TIMSK1,0);
}

 /**************************************************
 *
 *      Función para detener el timer 0 de 8 bits
 *      Parametros permitidos:
 *
 *
 */
  void Detiene_timer1(){

         CLRBIT(TIMSK1,0);

 }


 /**************************************************
 *
 *      Función para configurar el timer 0 de 8 bits
 *      Parametros permitidos:
 *      Preescaler1, Preescales8, Preescaler64, Preescaler256,Preescaler1024
 *
 */


void configuraTIMER1(int parametros){


        switch(parametros){
                case Preescaler_1:

                        SETBIT(TCCR1B,0);                  // reloj con preescalamiento de 1
                        CLRBIT(TCCR1B,1);
                        CLRBIT(TCCR1B,2);
                        //CS02=1;//
                break;
                case Preescaler_8:
                        CLRBIT(TCCR1B,0);                  // reloj con preescalamiento de 8
                        SETBIT(TCCR1B,1);
                        CLRBIT(TCCR1B,2);

                break;
                case Preescaler_64:
                        SETBIT(TCCR1B,0);                  // reloj con preescalamiento de 64
                        SETBIT(TCCR1B,1);
                        CLRBIT(TCCR1B,2);

                break;
                case Preescaler_256:
                        CLRBIT(TCCR1B,0);                  // reloj con preescalamiento de 256
                        CLRBIT(TCCR1B,1);
                        SETBIT(TCCR1B,2);
                break;
                case Preescaler_1024:
                        SETBIT(TCCR1B,0);                  // reloj con preescalamiento de 1024
                        CLRBIT(TCCR1B,1);
                        SETBIT(TCCR1B,2);
                break;
        }

}

   /**************************************************
 *
 *      Función para arrancar el timer 0 de 8 bits en un valor
 *      Parametros permitidos:
 *      valor de inicio
 *
 */

void Set_timer0(unsigned char valor ){

      TCNT0= valor;

}


/**************************************************
 *
 *      Función para arrancar el timer 0 de 8 bits
 *      Parametros permitidos:
 *
 *
 */
void Inicia_timer2(){

        SETBIT(TIMSK2,0);
}

 /**************************************************
 *
 *      Función para detener el timer 0 de 8 bits
 *      Parametros permitidos:
 *
 *
 */
  void Detiene_timer2(){

         CLRBIT(TIMSK2,0);

 }


 /**************************************************
 *
 *      Función para configurar el timer 0 de 8 bits
 *      Parametros permitidos:
 *      Preescaler1, Preescales8, Preescaler64, Preescaler256,Preescaler1024
 *
 */


void configuraTIMER2(int parametros){


        switch(parametros){
                case Preescaler_1:

                        SETBIT(TCCR2B,0);                  // reloj con preescalamiento de 1
                        CLRBIT(TCCR2B,1);
                        CLRBIT(TCCR2B,2);
                        //CS02=1;//
                break;
                case Preescaler_8:
                        CLRBIT(TCCR2B,0);                  // reloj con preescalamiento de 8
                        SETBIT(TCCR2B,1);
                        CLRBIT(TCCR2B,2);

                break;
                case Preescaler_32:
                        SETBIT(TCCR2B,0);                  // reloj con preescalamiento de 64
                        SETBIT(TCCR2B,1);
                        CLRBIT(TCCR2B,2);

                break;
                case Preescaler_128:
                        SETBIT(TCCR2B,0);                  // reloj con preescalamiento de 256
                        CLRBIT(TCCR2B,1);
                        SETBIT(TCCR2B,2);
                break;
                case Preescaler_256:
                        CLRBIT(TCCR2B,0);                  // reloj con preescalamiento de 256
                        CLRBIT(TCCR2B,1);
                        SETBIT(TCCR2B,2);
                break;
                case Preescaler_1024:
                        SETBIT(TCCR2B,0);                  // reloj con preescalamiento de 1024
                        CLRBIT(TCCR2B,1);
                        SETBIT(TCCR2B,2);
                break;
        }

}

   /**************************************************
 *
 *      Función para arrancar el timer 0 de 8 bits en un valor
 *      Parametros permitidos:
 *      valor de inicio
 *
 */

void Set_timer2(unsigned int valor ){

      TCNT2= valor;
    //  TCNT2L= valor & 0xFF;

}



/*
*
 *      Función para configurar el puerto serial
 *      configura el puerto 1 debido a que el puerto 0 esta siendo usado por
 *      el puerto de programacion
 *      Parametros permitidos:
 *
 *
 */

void USART_init(){

        UBRR0H = 0;
        UBRR0L = 77;      // este valor es para 9600 con 12 Mhz
        UCSR0B = (1<<RXEN0)|(1<<TXEN0);
        SETBIT(UCSR0C,UCSZ00);    // configuracion de 8 bits
        SETBIT(UCSR0C,UCSZ01);

}


void USART_send( char dato){

        while(!(UCSR0A & (1<<UDRE0)));
        UDR0 = dato;

}


  /*  función para asignar un manejador para las funciones de impresión al puerto serial
*    lo uso para debug en el puerto serial, es parte de las funciones de
*     MikroC  pero la cambie por una función propia
*/

 void PrintHandler(char c){

  USART_send(c);

}

/************************************************************************/
/*  Funcion de inicializacion del modulo PWM                            */
/*  Parametros de entrada : Ninguno                                                                                */
/*  Valores de Retorno : Ninguno                                                                                */
/*  Timer/Counter1 Control Register A – TCCR1A
* Bit         7       6       5          4         3         2         1         0
*           COM1A1  COM1A0   COM1B1   COM1B0    COM1C1     COM1C0    WGM11     WGM10
*
* COM1A1 =0 y COM1A0 = 0 , normal port operation
* COM1B1 =1 y COM1B0 = 0 , clear OC1B on Compare Match set at top
* WGM11 =0 y  WGM10= 0   ,  PWM  CORREGIDO EN FASE  para eliminar glitch
*   TCCR1A=  0010 0001b = 0x21
*
*  Timer/Counter Control Register B – TCCR1B
* Bit         7       6        5        4       3        2         1      0
*           ICNC1    ICES1     –      WGM13    WGM12    CS12     CS11    CS10
*
* WGM13    =0 y WGM12  = 1 ,
* CS11    =1 y CS10= 0 ,  clk /8
*   TCCR1B = 0000 0010b = 0x02
*
************************************************************************/
void pwm_init()
{

        TCCR1A= 0xA1;
        TCCR1B= 0x02;

}



   /**************************************************
 *
 *      Función para configurar el ADC
 *      Parametros permitidos:
 *       int Parametros :
 *                        Preescaler_ADC_2                :   preescalar por 2
 *                        Preescaler_ADC_4                :   preescalar por 4
 *                        Preescaler_ADC_8                :   preescalar por 8
 *                        Preescaler_ADC_16                :  preescalar por 16
 *                        Preescaler_ADC_32                :  preescalar por 32
 *                        Preescaler_ADC_64                :  preescalar por 64
 *                        Preescaler_ADC_128                 : preescalar por 128
 *                        INICIA_CONVERSION_ADC        :inicia una conversion AD
 *                        INICIA_ADC                                : inicia el modulo AD
 *                        DETEN_ADC                                : detiene el modulo AD
 *                        FREE_RUN_ADC                          : Ad en modo Freerun
 *                        ACTIVA_INTERRUPCION_ADC : inicia la interrupcion del AD
 *                        CANAL_0                                        : selecciona el canal 0 del AD
 *                        CANAL_1                                        : selecciona el canal 1 del AD
 *                        CANAL_2                                        : selecciona el canal 2 del AD
 *                        CANAL_3                                        : selecciona el canal 3 del AD
 *                        CANAL_4                                        : selecciona el canal 4 del AD
                        CANAL_5                                        : selecciona el canal 4 del AD
                        CANAL_6                                        : selecciona el canal 4 del AD
 *                        VREF_11                                        : selecciona referencia interna de 1.1 V
 *                        VREF_AVCC                                : selecciona referencia de Avcc
 *                        NO_AVCC                                        : selecciona sin referencia interna
 *                        ADC_IZQUIERDA                        : selecciona justificacion izquierda
 *                        ADC_DERECHA                                : Selecciona justificacion Derecha
 */


void Configura_adc(int parametros){

        switch (parametros){

                case Preescaler_ADC_2:
                        SETBIT(ADCSRA,ADPS0);
                        CLRBIT(ADCSRA,ADPS1);
                        CLRBIT(ADCSRA,ADPS2);
                break;

                case Preescaler_ADC_4:
                        CLRBIT(ADCSRA,ADPS0);
                        SETBIT(ADCSRA,ADPS1);
                        CLRBIT(ADCSRA,ADPS2);
                break;
                case Preescaler_ADC_8:
                        SETBIT(ADCSRA,ADPS0);
                        SETBIT(ADCSRA,ADPS1);
                        CLRBIT(ADCSRA,ADPS2);
                break;
                case Preescaler_ADC_16:
                        CLRBIT(ADCSRA,ADPS0);
                        CLRBIT(ADCSRA,ADPS1);
                        SETBIT(ADCSRA,ADPS2);
                break;
                case Preescaler_ADC_32:
                        SETBIT(ADCSRA,ADPS0);
                        CLRBIT(ADCSRA,ADPS1);
                        SETBIT(ADCSRA,ADPS2);
                break;
                case Preescaler_ADC_64:
                        CLRBIT(ADCSRA,ADPS0);
                        SETBIT(ADCSRA,ADPS1);
                        SETBIT(ADCSRA,ADPS2);
                break;
                case Preescaler_ADC_128:
                        SETBIT(ADCSRA,ADPS0);
                        SETBIT(ADCSRA,ADPS1);
                        SETBIT(ADCSRA,ADPS2);
                break;

                case INICIA_CONVERSION_ADC:
                        SETBIT(ADCSRA,ADSC);
                break;
                case INICIA_ADC:
                        SETBIT(ADCSRA,ADEN);
                break;
                case DETEN_ADC:
                        SETBIT(ADCSRA,ADEN);
                break;
                case FREE_RUN_ADC:
                        SETBIT(ADCSRA,ADATE);
                break;
                case ACTIVA_INTERRUPCION_ADC:
                        SETBIT(ADCSRA,ADIE);
                break;
                // seleccion de canales AD
                case CANAL_0:
                        CLRBIT(ADMUX,MUX0);
                        CLRBIT(ADMUX,MUX1);
                        CLRBIT(ADMUX,MUX2);
                        CLRBIT(ADMUX,MUX3);
                break;

                case CANAL_1:
                        SETBIT(ADMUX,MUX0);
                        CLRBIT(ADMUX,MUX1);
                        CLRBIT(ADMUX,MUX2);
                        CLRBIT(ADMUX,MUX3);
                break;
                case CANAL_2:
                        CLRBIT(ADMUX,MUX0);
                        SETBIT(ADMUX,MUX1);
                        CLRBIT(ADMUX,MUX2);
                        CLRBIT(ADMUX,MUX3);
                break;
                case CANAL_3:
                        SETBIT(ADMUX,MUX0);
                        SETBIT(ADMUX,MUX1);
                        CLRBIT(ADMUX,MUX2);
                        CLRBIT(ADMUX,MUX3);
                break;
                case CANAL_4:
                        CLRBIT(ADMUX,MUX0);
                        CLRBIT(ADMUX,MUX1);
                        SETBIT(ADMUX,MUX2);
                        CLRBIT(ADMUX,MUX3);
                        //SETBIT(DIDR0,ADC4D);    // deshabilita el buffer de entrada digital
                break;
                case CANAL_5:
                        SETBIT(ADMUX,MUX0);
                        CLRBIT(ADMUX,MUX1);
                        SETBIT(ADMUX,MUX2);
                        CLRBIT(ADMUX,MUX3);
                        //SETBIT(DIDR0,ADC4D);    // deshabilita el buffer de entrada digital
                break;
                case CANAL_6:
                        CLRBIT(ADMUX,MUX0);
                        SETBIT(ADMUX,MUX1);
                        SETBIT(ADMUX,MUX2);
                        CLRBIT(ADMUX,MUX3);
                        //SETBIT(DIDR0,ADC4D);    // deshabilita el buffer de entrada digital
                break;
                case VREF_11:
                        SETBIT(ADMUX,REFS1);
                        SETBIT(ADMUX,REFS0);
                break;
                case VREF_AVCC:
                        CLRBIT(ADMUX,REFS1);
                        SETBIT(ADMUX,REFS0);
                break;
                case NO_AVCC:
                        CLRBIT(ADMUX,REFS1);
                        CLRBIT(ADMUX,REFS0);
                break;
                case ADC_IZQUIERDA:
                        SETBIT(ADMUX,ADLAR); // justificacion a la izquierda
                break;
                case ADC_DERECHA:
                        CLRBIT(ADMUX,ADLAR); // justificacion a la DERECHA
                break;
        }
}



 /*   funcion Lee_canal_AD
 *    Lee el valor analogico y lo regresa
 *    parametros de entrada : canal,    canal analogico a leer puede ser 0-7
 *    parametros de salida  : resultado  : entero de 16 bits contieniendo el resultado de la conversion AD
*/


int Lee_canal_AD (char canal){

    int resultado=0;
    char ByteL,ByteH;

    Configura_ADC (canal);
    Configura_ADC (INICIA_CONVERSION_ADC);
    do {
        // esperar que termine la conversion
    }while (CHKBIT(ADCSRA,ADSC));
    ByteL= ADCL;
    ByteH = ADCH;
    resultado= ByteH<<8 | ByteL;

    return (resultado);
}
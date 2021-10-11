


char  UNIDADES=0,DECENAS=0, CENTENAS =0 , MILLAR=0,DEC_MILL=0;
unsigned char NUMEROS[22]={ 63, 6 , 91, 79, 102,109,125,7,127,103,               // codigos para el display de 7 segmentos, Representan los digitos sin DP
                             191, 134 , 219, 207, 230, 237, 253, 135, 255, 231,   // estos representan los digitos con punto decimal
                             64,64};                                                 // este valor es "-"


void Inicializa_pines(){

    // configurar pines de entrada salida
    TWI_SCL_dir = SALIDA;
    TWI_SDA_dir = SALIDA;
    Boton_OFF_dir     = ENTRADA;
    LED1_dir    = SALIDA;
    LED2_dir    = SALIDA;
    Int_opt_dir = ENTRADA;
    Boton1_dir  = ENTRADA;

// estados iniciales
   LED1= APAGADO;
   LED2= APAGADO;
    
}


/*
     funcion para transformar deun numero a unidades decenas centenas
*/

void  DEC_A_DIG(unsigned int  numero){
  unsigned int tempo1;            // variable temporal para convertir tipos

  tempo1= numero%10;
  UNIDADES = (char) tempo1;
  tempo1= (numero/10)%10;
  DECENAS = (char)tempo1 ;
  tempo1= (numero/100)%10;
  CENTENAS = (char) tempo1 ;
  tempo1= (numero/1000)%10;
  MILLAR = (char) tempo1 ;
  tempo1= (numero/10000)%10;
  DEC_MILL = (char) tempo1 ;

}
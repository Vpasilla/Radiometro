/******************************************************
*   archivo de definiciones para el driver de LCD PCF85176
*
*/


#define NEXTCMD 128     // cuando hay mas comandos
#define LASTCMD 0       // cuando ya no hay mas comandos que sigan

/* constantes definidas para control de el PCF*/
// MODO
#define MODESET 64

#define DISPLAY_DISABLED 0
#define DISPLAY_ENABLED 8

#define BIAS_THIRD 0
#define BIAS_HALF 4

#define DRIVE_STATIC 1
#define DRIVE_2 2
#define DRIVE_3 3
#define DRIVE_4 0

unsigned short set_modeset = MODESET |  DISPLAY_ENABLED | BIAS_THIRD | DRIVE_STATIC; // default init mode
unsigned short set_mode_blank = MODESET |  DISPLAY_DISABLED | BIAS_THIRD | DRIVE_STATIC; // modo apagado

//BLINK
#define BLINK  112

#define BLINKING_NORMAL 0
#define BLINKING_ALTERNATION 4

#define BLINK_FREQUENCY_OFF 0
#define BLINK_FREQUENCY2 1
#define BLINK_FREQUENCY1 2
#define BLINK_FREQUENCY05 3


unsigned short set_blink = BLINK | BLINKING_NORMAL | BLINK_FREQUENCY05;
unsigned short set_noblink = BLINK | BLINKING_NORMAL | BLINK_FREQUENCY_OFF;


//LOADDATAPOINTER
#define LOADDATAPOINTER  0

unsigned short set_datapointer = LOADDATAPOINTER | 0;


//BANK SELECT
#define BANKSELECT 120

#define BANKSELECT_O1_RAM0 0
#define BANKSELECT_O1_RAM2 2

#define BANKSELECT_O2_RAM0 0
#define BANKSELECT_O2_RAM2 1

unsigned short set_bankselect = BANKSELECT | BANKSELECT_O1_RAM0 | BANKSELECT_O2_RAM0;

#define DEVICE_SELECT 96

unsigned short set_deviceselect = DEVICE_SELECT;


#define PCF8576_ADDR 0x70   // direccion del PCF en el bus I2C

#define LETRA_B      20
#define LETRA_A      21
#define LETRA_T      22
#define ESPACIO      23
#define LETRA_J      24
#define GUION        25
#define LETRA_O      26
#define LETRA_L      27






unsigned char Numero[28]= { 246, 192, 110, 234, 216, 186, 190, 224, 254, 248,  // Numeros de 0 a 9
                            247, 193, 111, 235, 217, 187, 191, 225, 255, 249,  // Numeros de 0 a 9 con punto decimal
                            158, 252, 30, 0,194,8, 246, 22};//     'B' 'A'  'T' ' ' 'J'  '-' 'O' 'L'
/*
*   funcion init_PCF85176(void )
*   parametros de entrada: ninguno
*   parametros de salida : ninguno
*   Descripción:  Esta funcion inicializa y configura el driver PCF85176 para manejar el display LCD
*
*/
void Init_PCF85176(void ) {
       TWI_Start();
       TWI_Write(PCF8576_ADDR);
       TWI_Write(NEXTCMD | set_modeset);          //0xCD
       TWI_Write(NEXTCMD | set_datapointer);        // 0x80
       TWI_Write(NEXTCMD | set_noblink);            // 0xF0
       TWI_Write(NEXTCMD | set_deviceselect);
       TWI_Write(LASTCMD | set_bankselect);
       TWI_Write(Numero[GUION]);
       TWI_Write(Numero[GUION]);
       TWI_Write(Numero[GUION]);
       TWI_Write(Numero[GUION]);
       TWI_Stop();
}
/*
*   funcion Actualiza display(void )
*   parametros de entrada: millar, centenas , decenas, unidades
*   parametros de salida : ninguno
*   Descripción:  esta funcion recibe los digitos a desplegarse en la pantalla
*
*/

void Actualiza_display(unsigned char millar, unsigned char centenas, unsigned char decenas ,unsigned char unidades, int optional_blink) {

       TWI_Start();
       TWI_Write(PCF8576_ADDR);
       TWI_Write(NEXTCMD | set_modeset);          //0xCD
       TWI_Write(NEXTCMD | set_datapointer);        // 0x80
       if (optional_blink)
          TWI_Write(NEXTCMD | set_blink);            // 0xF0
       else
          TWI_Write(NEXTCMD | set_noblink);            // 0xF0
       TWI_Write(NEXTCMD | set_deviceselect);
       TWI_Write(LASTCMD | set_bankselect);
       if (millar>0){
          TWI_Write(Numero[ millar ]);
          TWI_Write(Numero[ centenas ]);
       }
       else {
          TWI_Write(Numero[ ESPACIO ]);
          if (centenas>0){
             TWI_Write(Numero[ centenas ]);
          }
          else {
             TWI_Write(Numero[ ESPACIO ]);
          }
       }
       TWI_Write(Numero[ decenas  ]);
          TWI_Write(Numero[ unidades ]);
    //   TWI_Write(Numero[ dec_millar ]);         // este display no tiene decenas de millar
       TWI_Stop();

}

void Apaga_display( void ) {

       TWI_Start();
       TWI_Write(PCF8576_ADDR);
       TWI_Write(NEXTCMD | set_mode_blank);          //0xCD
       TWI_Write(NEXTCMD | set_datapointer);        // 0x80
       TWI_Write(NEXTCMD | set_blink);            // 0xF0
       TWI_Write(NEXTCMD | set_deviceselect);
       TWI_Write(LASTCMD | set_bankselect);
       TWI_Write(Numero[ 0 ]);
       TWI_Write(Numero[ 0 ]);
       TWI_Write(Numero[ 0 ]);
       TWI_Write(Numero[ 0 ]);
     //  TWI_Write(Numero[ 0 ]);            // este display no tiene decenas de millar
       TWI_Stop();

}
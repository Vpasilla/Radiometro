/******************************************************
*   archivo de definicion de pines de I/O y perifericos
*   este archivo es especifico para el proyecto contador_horas_LCD
*
*/

// comentario agregado al codigo en la version 3
sbit TWI_SDA                at PORTC4_bit;
sbit TWI_SCL                at PORTC5_bit;


sbit TWI_SDA_dir            at DDC4_bit;
sbit TWI_SCL_dir            at DDC5_bit;

sbit RX                     at PORTD0_bit;
sbit TX                     at PORTD1_bit;
sbit Boton_OFF_pin          at PIND2_bit;
sbit Boton_OFF_port          at PORTD2_bit;


sbit LED1                   at PORTD3_bit;
sbit LED2                   at PORTD4_bit;
sbit Int_opt                at PIND5_bit;
sbit Boton1                 at PIND6_bit;

sbit RX_dir                 at DDD0_bit;
sbit TX_dir                 at DDD1_bit;
sbit Boton_OFF_dir          at DDD2_bit;
sbit LED1_dir               at DDD3_bit;
sbit LED2_dir               at DDD4_bit;
sbit Int_opt_dir            at DDD5_bit;
sbit Boton1_dir             at PIND6_bit;
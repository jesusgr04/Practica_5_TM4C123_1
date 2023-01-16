#include "lib/include.h"
//Se trabaja con modulo 0 , generador 1
//por lo tanto se puede trabajar con PB4 -> PMW2 o PB5_> PMW3 de acuerdo a la pág. 1233
extern void Configura_Reg_PWM1(uint16_t freq)
{
    SYSCTL->RCGCPWM |= (1<<0); // habilitar mod PWM0 
    //Habilita GPIO Puerto B porque se trabaja con gen. 1 mod. 0 
    SYSCTL->RCGCGPIO |= (1<<1);
    // desabilitar Divisor 
    //5 mil cuentas que caben en los 16 bits del contador del PWM, 50 millinoes/ 10 mil = 5 mil cuentas  
   //  frec, tarjeta / frec PWM = cuentas 
    SYSCTL->RCC &= ~(1<<20); // 
    //Deshabilitafunción alternativa para PB4 
    GPIOB->AFSEL |= (1<<4);
    // indicar como salida el PB4
    GPIOB->DIR = (1<<4); 
    /* registro PCTL le digo que es pwm Pag 689 --> valor de 4 en el pin PB4*/
    GPIOB->PCTL |= (GPIOB->PCTL&0xFFF0FFFF) | 0x00040000; 
    // Indicar si es digital o no
    GPIOB->DEN |= (1<<4); 
    PWM0->_1_CTL = (0<<0); //se le asigna 0 a 0 porque es el bit para indicar lo habilitado o desabilitado según pag. 1266-
    // Modo de configuración - modo regresivo pag. 1285, pag. 1239 para saber que valor poner, y 1248 para saber con que comparador trabaja el PWM a usar 
    PWM0->_1_GENA = 0x0000008C; //se usa el comparador A que es con el que trabaja el PWM2 según pag. 1248
    // Configuración de cargas: cuentas=fclk/fpwm  para 50MHz cuentas = (50,000,000/10,000)
    PWM0->_1_LOAD = 5000;  
    PWM0->_1_CMPA = 3750; //Para tener el 25% en el duty cicle %75 de las 5000 cuentas
    PWM0->_1_CTL = (1<<0);// habiitar generador 1
    PWM0->ENABLE = (1<<2); // habilitar el PWM que se usa PWM2 pag. 1247 y 1233
}

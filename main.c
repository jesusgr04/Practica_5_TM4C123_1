/*#include "lib/include.h"

int main(void)
{
    //Experimento 1
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 50,000,000 Hz
 * junto con el generador 1  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 10KHz  */

    /* Configurar_PLL(_50MHZ);  //Confiuracion de velocidad de reloj
    Configura_Reg_PWM1(8);  //Función para configurar el PWM 

    while (1)
    {
        
    }
    
} */
#include "lib/include.h"


volatile uint8_t red = 114;

volatile uint8_t green = 103;

volatile uint8_t blue = 98;

volatile uint16_t led;


int main (void)
{

    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj
    Configura_Reg_PWM1(8);  //Función para configurar el PWM 
    Configurar_UART0();  

    while (1)
    {
        led = readChar();

        switch (led)
        {
            //COLOR SELECCIONADO AZUL
            case 'b':
                while (blue == 98)
                {
                    //Se lee el valor mandado por el UART para cambiar el ciclo de trabajo -> intensidad del led
                    blue = (int)readChar();
                }

                //Se hace la conversión para modificar el ciclo de trabajo del PWM -> intensidad del led
                //       PE4  40000:total de cuentas,  int_rojo: valor enviado por UART, las 16,000 cuentas equivalen al 40% de las cuentas
                PWM0->_2_CMPA = 50000-((int)(blue*30000)/60); 
                blue = 98;
            break;

            //COLOR SELECCIONADO VERDE
            case 'g':
                while (green == 103)
                {
                    //Se lee el valor mandado por el UART para cambiar el ciclo de trabajo -> intensidad del led
                    green = (int)readChar();
                }

                //Se hace la conversión para modificar el ciclo de trabajo del PWM -> intensidad del led
                //       PE4  40000:total de cuentas,  int_rojo: valor enviado por UART, las 16,000 cuentas equivalen al 40% de las cuentas
                PWM0->_0_CMPB = 50000-((int)(green*30000)/60); 
                green = 98;
            break;

            //COLOR SELECCIONADO ROJO
            case 'r':
                while (red == 114)
                {
                    red = (int)readChar(); //recibe el % del uart para calcular el dc%
                }

                //Se hace la conversión para modificar el ciclo de trabajo del PWM -> intensidad del led
                //       PB4  40000:total de cuentas,  int_rojo: valor enviado por UART, las 16,000 cuentas equivalen al 40% de las cuentas 
                PWM0->_1_CMPA = 50000-((int)(red*30000)/60); //PB4 (R)
                red = 114;
            break;

        }   

    }
    





}


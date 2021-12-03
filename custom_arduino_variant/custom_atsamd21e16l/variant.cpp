/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"



/*                                                             Comments (* is for default peripheral in use)
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * + Pin number +       Board pin  |  PIN   | Label/Name      |Port EIC              REF, ADC    AC, AC1 DAC  SERCOM         SERCOM-ALT      TC/TCC       TCC
 * +------------+------------------+--------+-----------------+--------------------------------------------------------------------------------------------------------
 * | 1          |                  |  PA02  | LED 1           | *    EIC/EXTINT[2]   ADC/AIN[0]  DAC/VOUT                                              
 * | 2          |                  |  PA03  | LED 2           | *    EIC/EXTINT[3]   DAC/VREFA ADC/AIN[1]                                              
 * | 5          |                  |  PA04  | LED 3           | *    EIC/EXTINT[4]   ADC/VRFEB ADC/AIN[4] AC/AIN[0]         SERCOM0/PAD[0]  TCC0/WO[0]   
 * | 6          |                  |  PA05  | LED 4           | *    EIC/EXTINT[5]   ADC/AIN[5]  AC/AIN[1]                  SERCOM0/PAD[1]  TCC0/WO[1]  
 * | 7          |                  |  PA06  | LED 5           | *    EIC/EXTINT[6]   ADC/AIN[6]  AC/AIN[2]                  SERCOM0/PAD[2]  TCC1/WO[0]  
 * | 8          |                  |  PA07  | LED 6           | *    EIC/EXTINT[7]   ADC/AIN[7]  AC/AIN[3]  SERCOM0/PAD[3]                  TCC1/WO[1]  
 * | 11         |                  |  PA08  | LED 7           | *    EIC/NMI         ADC/AIN[16]            SERCOM0/PAD[0]  SERCOM2/PAD[0]  TCC0/WO[0]  TCC1/WO[2]  
 * | 12         |                  |  PA09  | LED 8           | *    EIC/EXTINT[9]   ADC/AIN[17]            SERCOM0/PAD[1]  SERCOM2/PAD[1]  TCC0/WO[1]  TCC1/WO[3]  
 * | 13         |                  |  PA10  | LED 9           |      EIC/EXTINT[10]  ADC/AIN[18]            SERCOM0/PAD[2]  SERCOM2/PAD[2]  TCC1/WO[0] *TCC0/WO[2]  
 * | 14         |                  |  PA11  | LED 10          |      EIC/EXTINT[11]  ADC/AIN[19]            SERCOM0/PAD[3]  SERCOM2/PAD[3]  TCC1/WO[1] *TCC0/WO[3]  
 * | 15         |                  |  PA14  | LED 11          |      EIC/EXTINT[14]                         SERCOM2/PAD[2]  SERCOM4/PAD[2]  TC3/WO[0]  *TCC0/WO[0]
 * | 16         |                  |  PA15  | LED 12          |      EIC/EXTINT[15]                         SERCOM2/PAD[3]  SERCOM4/PAD[3]  TC3/WO[1]  *TCC0/WO[1]  
 * | 17         |                  |  PA16  | SPI_MOSI        |      EIC/EXTINT[0]                         *SERCOM1/PAD[0]  SERCOM3/PAD[0]  TCC2/WO[0]  TCC0/WO[2]  
 * | 18         |                  |  PA17  | SPI_SCK         |      EIC/EXTINT[1]                         *SERCOM1/PAD[1]  SERCOM3/PAD[1]  TCC2/WO[1]  TCC0/WO[3]  
 * | 19         |                  |  PA18  | SPI_CS1         | *    EIC/EXTINT[2]                          SERCOM1/PAD[2]  SERCOM3/PAD[2]  TC3/WO[0]   TCC0/WO[2]  
 * | 20         |                  |  PA19  | SPI_MISO        |      EIC/EXTINT[3]                         *SERCOM1/PAD[3]  SERCOM3/PAD[3]  TC3/WO[1]   TCC0/WO[3]  
 * | 21         |                  |  PA22  | SPI_CS2         | *    EIC/EXTINT[6]                          SERCOM3/PAD[0]  SERCOM5/PAD[0]  TC4/WO[0]   TCC0/WO[0]  
 * | 22         |                  |  PA23  | Digital Input   | *    EIC/EXTINT[7]                          SERCOM3/PAD[1]  SERCOM5/PAD[1]  TC4/WO[1]   TCC0/WO[1]  
 * | 23         |                  |  PA24  | UART_TX         |      EIC/EXTINT[12]                        *SERCOM3/PAD[2]  SERCOM5/PAD[2]  TC5/WO[0]   TCC1/WO[2]
 * | 24         |                  |  PA25  | UART_RX         |      EIC/EXTINT[13]                        *SERCOM3/PAD[3]  SERCOM5/PAD[3]  TC5/WO[1]   TCC1/WO[3]
 * | 29         |                  |  PA30  | SWCLK           |     *SWCLK, alternate use EXTINT[10]                        SERCOM1/PAD[2]  TCC1/WO[0]  
 * | 30         |                  |  PA31  | SWDIO           |     *SWDIO, alternate use EXTINT[11]                        SERCOM1/PAD[3]  TCC1/WO[1]   
 * 
 * | 31         |                  |  PB02  | Digital Input   | *   *EIC/EXTINT[2] *ADC/AIN[10] AC1/AIN[2]                  SERCOM5/PAD[0]             
 * | 32         |                  |  PB03  | nc              |      EIC/EXTINT[3]  ADC/AIN[14] AC1/AIN[3]                  SERCOM5/PAD[1]              
 * | 3          |                  |  PB04  | nc              |      EIC/EXTINT[4]  ADC/AIN[12] AC1/AIN[0]
 * | 4          |                  |  PB05  | LED 13          | *    EIC/EXTINT[5]  ADC/AIN[13] AC1/AIN[1]
*/




/*
 * Pins descriptions
 */
const PinDescription g_APinDescription[]=
{
  // Digital Pins
  { PORTA,  2, PIO_OUTPUT, PIN_ATTR_DIGITAL, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 },
  { PORTA,  3, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG), ADC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 },
  { PORTA,  4, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER|PIN_ATTR_ANALOG), ADC_Channel1, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_4 },
  { PORTA,  5, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER|PIN_ATTR_ANALOG), ADC_Channel5, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_5 },
  { PORTA,  6, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER|PIN_ATTR_ANALOG), ADC_Channel6, PWM1_CH0, TCC1_CH0, EXTERNAL_INT_6 },
  { PORTA,  7, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER|PIN_ATTR_ANALOG), ADC_Channel7, PWM1_CH1, TCC1_CH1, EXTERNAL_INT_7 },
  { PORTA,  8, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER|PIN_ATTR_ANALOG), ADC_Channel16, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_NMI },
  { PORTA,  9, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER|PIN_ATTR_ANALOG), ADC_Channel17, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_9 },
  //PWM Pins
  { PORTA,  10, PIO_PWM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel18, PWM1_CH0, TCC1_CH0, EXTERNAL_INT_10 },
  { PORTA,  11, PIO_PWM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel19, PWM1_CH1, TCC1_CH1, EXTERNAL_INT_11 },
  { PORTA,  14, PIO_PWM_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH4, TCC0_CH4, EXTERNAL_INT_14 },
  { PORTA,  15, PIO_PWM_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH5, TCC0_CH5, EXTERNAL_INT_15 },
  //SPI
  { PORTA,  16, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH0, TCC2_CH0, EXTERNAL_INT_0 },
  { PORTA,  17, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM2_CH1, TCC2_CH1, EXTERNAL_INT_1 },
  { PORTA,  18, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH0, TC3_CH0, EXTERNAL_INT_2 },
  { PORTA,  19, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH1, TC3_CH1, EXTERNAL_INT_3 },
  { PORTA,  22, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM4_CH0, TC4_CH0, EXTERNAL_INT_6 },
  { PORTA,  23, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM4_CH1, TC4_CH1, EXTERNAL_INT_7 },
  //UART
  { PORTA,  24, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM5_CH0, TC5_CH0, EXTERNAL_INT_12 },
  { PORTA,  25, PIO_SERCOM, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM5_CH1, TC5_CH1, EXTERNAL_INT_13 },
  //SWD
  { PORTA,  30, PIO_COM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  { PORTA,  31, PIO_COM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE},
  //Input
  { PORTB,  2, PIO_INPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG), ADC_Channel10, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 },
  { PORTB,  3, PIO_INPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 },   //ADC is avaible but not configured at the moment because not defined in Arduino Core
  { PORTB,  4, PIO_INPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4 },   //ADC is avaible but not configured at the moment because not defined in Arduino Core
  { PORTB,  5, PIO_OUTPUT, (PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 },   //ADC is avaible but not configured at the moment because not defined in Arduino Core

};

extern "C" {
    unsigned int PINCOUNT_fn() {
        return (sizeof(g_APinDescription) / sizeof(g_APinDescription[0]));
    }
}

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;

Uart Serial1( &sercom3, PIN_SERIAL3_RX, PIN_SERIAL3_TX, PAD_SERIAL3_RX, PAD_SERIAL3_TX ) ;

void SERCOM3_Handler()
{
  Serial1.IrqHandler();
}


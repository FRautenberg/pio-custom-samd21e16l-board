//#include <variant.h>
#include <Arduino.h>

void setup() {
  /* 
   * use arduino pins D0..D13, A0-A4, D19-D22 as listed / mapped in 
   * custom_arduino_variant/custom_atsamd21e16l/variant.cpp 
   */
  for(int i = 0; i < 12;i++){ 
    pinMode(i, OUTPUT); /* D0 = Port A pin 8 (PA8)*/
    digitalWrite(i,HIGH);
  }
  

  /* can also use direct register accesss (see wiring_digital.c of Adafruit SAMD core) */
  //PORT->Group[PORTB].PINCFG[5].reg=(uint8_t)(PORT_PINCFG_INEN); /* PA 15 support reading back current value (even as output pin) */
  //PORT->Group[PORTB].DIRSET.reg = (1 << 5); /* PA 15 set direction to ouput */
  //PORT->Group[PORTB].OUTCLR.reg = (1 << 5); /* PA 15 to LOW (clear)*/
  //PORT->Group[PORTB].OUTSET.reg = (1 << 5); /* PA 15 to HIGH (set)*/

  //Serial.begin(115200); /* Start USB-CDC serial driver */
  Serial1.begin(115200); /* start hardware UART (TX = PA06, RX = PA07) */
  Serial1.println("Hello world!");
}

void loop() {
  /*digitalWrite(0, HIGH); 
  delay(500);
  digitalWrite(0, LOW); 
  delay(500);
  analogWrite(0,50);*/

  for(int i = 0; i < 12;i++){ 
    if(i <8)
    {      
      Serial1.println("Hello world!");
      digitalWrite(i, LOW); 
      delay(50);
      digitalWrite(i, HIGH); 
      delay(50);
    } 
    else
    {      
      Serial1.println("Hello world!");
      for(int u = 1024; u>=0;u--){
        analogWrite(i,u);
        delay(1);
      }       
      analogWrite(i, 1024); 
    }     
  }
}
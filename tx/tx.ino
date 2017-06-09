#include <util/delay.h>
#define STATUS 1
#define TX 0

void setup () {
  pinMode(TX, OUTPUT);
  pinMode(STATUS, OUTPUT);
}

void loop () {
  transmit('T');
  transmit('O');
  transmit('M');
  transmit('M');
  transmit('A');
  transmit('S');
  transmit('O');
}

void transmit (byte c) {
  
  int i;

  for (i = 0; i < 20; i++) {
    digitalWrite(TX, HIGH);
    _delay_ms(500);
    digitalWrite(TX, LOW);
    _delay_ms(500);
  }
  
  digitalWrite(TX, HIGH);
  _delay_ms(3000);
  digitalWrite(TX, LOW);
  _delay_ms(500);
  for (byte mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
    if (c & mask){ // if bitwise AND resolves to true
      digitalWrite(TX,HIGH); // send 1
    } else{ //if bitwise and resolves to false
      digitalWrite(TX,LOW); // send 0
    }
    _delay_ms(500);
  }
}


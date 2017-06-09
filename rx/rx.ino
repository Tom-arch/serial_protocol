#include <util/delay.h>
#define RX 4
#define DEBUG 5

void setup() {
  pinMode(RX, INPUT);
  pinMode(DEBUG, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready!");
}

void loop() {
  if (digitalRead(RX) == HIGH) {
    Serial.println("Runtime...");
    receive(); 
  }
}

void receive() {
  //Check if we are in the 300 us high-pull or in the 20 times for to wake up the receiver
  boolean check = 0;

  for(int i = 0; i < 100; i++){
    _delay_ms(20);
    check = 1;
    if (digitalRead(RX) == LOW){
      check = 0;
      break;
    }
  }

  if (check) {
    //If the 300 us have passed, sync to the pull-low and then wait 750 (500 + 250 offset) us
    while (1) {
      if(digitalRead(RX) == LOW) {
        break;
      }
    }
    _delay_ms(750);
    //Now receive the data: take an empty byte, read the signal and scale it to sx i times, then do bitwise or between the previous byte end the signal
    byte received = 0;
    for(int i = 0; i < 8; i++) {
      byte abit = digitalRead(RX);
      abit = abit << i;
      received = received | abit;
      _delay_ms(500);
    }

    if (received == 'T') {
      digitalWrite(DEBUG, HIGH);
    } 
    else {
      digitalWrite(DEBUG, LOW);
    }
    Serial.print(received);
  }
}

#include "LwTx.h"

byte msg[] = {4,0,3,0,5,9,3,0,1,2};
long timeout = 0;

void setup() {
  Serial.begin(9600);
#ifdef SPARK_CORE
  //Transmit on pin D2, 10 repeats,no invert, 140uSec tick)
  lwtx_setup(D2, 10, 0, 140);
#else
  //Transmit on pin 7, 10 repeats,no invert, 140uSec tick)
  lwtx_setup(7, 10, 0, 140);
#endif
}

void loop() {
  if (lwtx_free()) {
    lwtx_send(msg);
    timeout = millis();
    Serial.print(timeout);
    Serial.println(" msg start");
  }
  while(!lwtx_free() && millis() < (timeout + 1000)) {
    delay(10);
  }
  timeout = millis() - timeout;
  Serial.print(millis());
  Serial.print(" msg sent:");
  Serial.println(timeout);
  delay(100);
}


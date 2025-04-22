#include "KoroboLib_2_1.h"

KoroboLib_2_1 korobo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
  korobo.begin();
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  korobo.Voice();
}

#include <Arduino.h>
#include "OLED_GFX.h"
#include "GFX_Test.h"

OLED_GFX oled = OLED_GFX();
GFX_Test theTest(oled);

void setup()  {

  //Init UART
  Serial.begin(115200);
  oled.DeviceInit();
}

void loop() {
  theTest.RunTest();
  delay(1000);
}


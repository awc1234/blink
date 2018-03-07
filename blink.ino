#include <Blink.h>

Blink blink(LED_BUILTIN);

void setup()
{
  Serial.begin(115200);
  Serial.println("\nBlink Version 1.0 Woongchan An");
}

void loop()
{
  blink.on(500); 
  blink.off(300);
  
 
}

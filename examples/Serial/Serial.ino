#include <KMESerial.h>
KMESerial KMESerial;
int val=0;
uint8_t ledpin=53;

void switchstate(KME State){
digitalWrite(ledpin,State.value==1?true:false);
KMESerial.SetSwitch(State.id ,State.value==1?true:false);
}
void setup() {
    Serial.begin(74880);
pinMode(ledpin,OUTPUT);
KMESerial.setCallback(switchstate);
}

void loop() {
/*   KMESerial.loop();
 */  val=val+20;
/* KMESerial.SetSwitch(0 ,true);
delay(2000);
  KMESerial.loop();

KMESerial.SetSwitch(1 ,true);
KMESerial.SetSwitch(0 ,false);
delay(2000);
 */  KMESerial.loop();

/* KMESerial.setSensor(0 ,val);
delay(2000); */

}

/*
  KMESerial.h - Library for flashing KMESerial code.
  Created by adnan elabdullah, November 2, 2022.
  Released into the public domain.
*/

       
#ifndef KMESerial_h
#define KMESerial_h
#include <Arduino.h>


typedef struct Sensorupdate {
uint8_t   id = 0;
int  oldstate = 300;
int  newstate = 0;
bool changed=false;
uint8_t ratio=1;
}  Sensorupdate ; 

typedef struct KME {
uint8_t id=0;
uint8_t  value=0;


}KME;


class KMESerial
{
  public:
    
    void setCallback(void (*callback)(KME data));
    void loop();
    void setSensor(uint8_t id ,int value );
    void SetSwitch(uint8_t id ,bool value);
  private:

       
    void (*userCallback)(KME data);

};

#endif
 
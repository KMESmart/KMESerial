#include <Arduino.h>

#include "KMESerial.h"
Sensorupdate valuessensor[40]={};

  bool verifyChecksum(uint8_t *data, size_t length) {
  if (length < 2) {
    return false; // Invalid data
  }

  int checksum = 0;
  for (size_t i = 0; i < length - 1; i++) {
    checksum = (checksum + data[i]) & 0xFF;
  }

  return checksum == data[length - 1];
}
byte calculateChecksum(byte* array, int length) {
  byte checksum = 0;
  for (int i = 0; i < length; i++) {
    checksum += array[i];
  }
  return checksum;
}
void KMESerial::setCallback(void (*callback)(KME data))
{
for (size_t i = 0; i < 40; i++)
{
valuessensor[40].id=i;
}

  userCallback = callback;


}
void KMESerial::loop()
{

if (Serial.available()) {
    const int bufferSize = 6;
  byte buffer[bufferSize];
    Serial.readBytes(buffer, bufferSize);

    // Extract the components from the buffer
    byte type = buffer[0];
    if (type!=0x55)
    {Serial.print("not a valid:");

    return;
    }
    
    byte id = buffer[1];
    byte value1 = buffer[2];
    byte verification = buffer[3];
    byte version = buffer[4];
    byte checksum = buffer[5];
    if(verifyChecksum(buffer, 6)){
      KME state;
    state.id=id;
    state.value=value1;

  userCallback(state);

    }
    else{

    }

    }
}
    void KMESerial::setSensor(uint8_t id ,int value)
{
if (abs(value-valuessensor[id].oldstate)>=valuessensor[id].ratio)
{
  valuessensor[id].oldstate=value;
  valuessensor[id].changed=true;
}
else
{
  return;
}

  // Split the 16-bit value into two 8-bit bytes
  byte value1 = highByte(value);
  byte value2 = lowByte(value);


  byte buffer[6];

    // Fill the buffer with data
    buffer[0] = 96; //  type
    buffer[1] = id; //  ID
    buffer[2] = value1; //  ID
    buffer[3] = value2; //  ID
    buffer[4] = 0x96; //  verification byte
  byte checksum = calculateChecksum(buffer, 5);
    buffer[5] = checksum; //  checksum byte
    Serial.write(buffer, sizeof(buffer));
}


    void KMESerial::SetSwitch(uint8_t id ,bool value)
{
  uint8_t newval =value?1:0;
/* 
if (abs(newval-valuessensor[id].oldstate)>=valuessensor[id].ratio)
{
  valuessensor[id].oldstate=newval;
  valuessensor[id].changed=true;
}
else
{
  return;
}
 */
  byte buffer[6];

    // Fill the buffer with data
    buffer[0] = 114; //  type
    buffer[1] = id; //  ID
    buffer[2] = newval; //  ID
    buffer[3] = 0x96; //  verification byte
   buffer[4] = 0x01; //  verification byte
  byte checksum = calculateChecksum(buffer, 5);
    buffer[5] = checksum; //  checksum byte
    Serial.write(buffer, sizeof(buffer));
}
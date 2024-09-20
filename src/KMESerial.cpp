#include <Arduino.h>

#include "KMESerial.h"
#define HEADER1 0x4B
#define HEADER2 0x4D
#define APIVERSION 0x02
#define TIMEOUT_MS 40  // Set your desired timeout in milliseconds
Settings deviceinfo;
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
byte serialBuffer[64];  // Adjust buffer size as needed
int bufferIndex = 0;
unsigned long lastReceivedTime = 0;

void KMESerial::loop()
{  

  while (Serial.available() > 0) {
    int bytesAvailable = Serial.available();
    int bytesToRead = min(bytesAvailable, (int)(sizeof(serialBuffer) - bufferIndex));  // Ensure we don't overflow the buffer
    Serial.readBytes(&serialBuffer[bufferIndex], bytesToRead);
    bufferIndex += bytesToRead;
    // Process the buffer
    int i = 0;
    while (i <= bufferIndex - 8) {  // At least 8 bytes are needed for a complete command
  
      if (serialBuffer[i] == HEADER1 && serialBuffer[i + 1] == HEADER2) {  // Check for the header
              int commandLength = 8;  // Default length

      if (serialBuffer[i + 2]==23 )
      {
       commandLength=11;
      }
      
        // We have found a valid command header, now determine the length
          // We have a full command in the buffer
          byte KMECommand[12];
          memcpy(KMECommand, &serialBuffer[i], commandLength);
        if (i + commandLength <= bufferIndex) {
          // Deserialize the command
          if (commandLength==11)
          {
           
           
            
            
             byte header1 = KMECommand[0];
          byte header2 = KMECommand[1];
          byte datalength = KMECommand[2];//wifi state
          byte id = KMECommand[3];
          byte valstate = KMECommand[4];
           byte valstate1 = KMECommand[5];
            byte valstate2 = KMECommand[6];
             byte valstate3 = KMECommand[7];
          byte verify = KMECommand[8];
          byte version = KMECommand[9];
          byte checksum = KMECommand[10];
          // Verify checksum and other conditions
          if (verifyChecksum(KMECommand, 11) && verify == 0x96) {
            if (id==0)
            {
              uint32_t combinedValue = (uint32_t)valstate << 24 |
                         (uint32_t)valstate1 << 16 |
                         (uint32_t)valstate2 << 8 |
                         (uint32_t)valstate3;
              deviceinfo.currentTime=combinedValue;
            }
             else if (id==1)
            {
              uint32_t combinedValue = (uint32_t)valstate << 24 |
                         (uint32_t)valstate1 << 16 |
                         (uint32_t)valstate2 << 8 |
                         (uint32_t)valstate3;
              deviceinfo.restCount=combinedValue;
            }
   else if (id==3)
            {
              uint32_t combinedValue = (uint32_t)valstate << 24 |
                         (uint32_t)valstate1 << 16 |
                         (uint32_t)valstate2 << 8 |
                         (uint32_t)valstate3;
              deviceinfo.apiversion=combinedValue;
            }
             else if (id==4)
            {
              deviceinfo.heartbeat++;
                
              if (deviceinfo.heartbeat>5000)
              {
              deviceinfo. WIFIState=datalength==1?true:false;
                deviceinfo.heartbeat=0;
              }
              
            }


            
          } else {
          /*   // Handle invalid command or checksum
            Serial.println("Invalid command or checksum."); */
          }

          }
          else{
   byte header1 = KMECommand[0];
          byte header2 = KMECommand[1];
          byte datalength = KMECommand[2];
          byte id = KMECommand[3];
          byte valstate = KMECommand[4];
          byte verify = KMECommand[5];
          byte version = KMECommand[6];
          byte checksum = KMECommand[7];
          // Verify checksum and other conditions
          if (verifyChecksum(KMECommand, 8) && verify == 0x96) {
            KME state;
            state.id = id;
            state.value = valstate;
            userCallback(state);

          } else {
          /*   // Handle invalid command or checksum
            Serial.println("Invalid command or checksum."); */
          }

          }
       
          // Move the index forward by the length of the command
          i += commandLength;
        } else {
          // Not enough data for a full command, wait for more data
          break;
        }
      } else {
        // If we don't find a valid header, move to the next byte
        i++;
      }
    }
    // Shift the remaining bytes in the buffer to the start
    if (i < bufferIndex) {
      memmove(serialBuffer, &serialBuffer[i], bufferIndex - i);
    }
    bufferIndex -= i;
  }
 

}

/* void Xloop()
{

 if (Serial.available() ) { // Check if at least 6 bytes are available
    const int bufferSize = 6;
    byte buffer[bufferSize];
    Serial.readBytes(buffer, bufferSize);


    // Extract the components from the buffer
    byte type = buffer[0];
    if (type!=0x55)
    {

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
} */
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
  byte buffer[10];

    // Fill the buffer with data
    buffer[0] = HEADER1; //  بداية 
    buffer[1] = HEADER2; //   بداية 
    buffer[2] = 0x03; // حجم الارسال
    buffer[3] =96; //  النوع
    buffer[4] = id; //  المعرف
    buffer[5] = value1; //  القيمة الصغرة
    buffer[6] = value2; //  الكبر
    buffer[7] = 0x96; //  verification 
    buffer[8] = APIVERSION; //  اصدار التحكم
  byte checksum = calculateChecksum(buffer, 9);
    buffer[9] = checksum; //  checksum byte
    Serial.write(buffer, sizeof(buffer));
}

    void KMESerial::SetSwitch(uint8_t id ,uint8_t newval)
{

if (abs(newval-valuessensor[id].oldstate)>=valuessensor[id].ratio)
{
  valuessensor[id].oldstate=newval;
  valuessensor[id].changed=true;
}
else
{
  return;
}
 
  byte buffer[10];

    // Fill the buffer with data
    buffer[0] = HEADER1; //  type
    buffer[1] = HEADER2; //  type
    buffer[2] = 0x02; //  type
    buffer[3] = 114; //  type
    buffer[4] = id; //  ID
    buffer[5] = newval; //  ID
    buffer[6] = 0x00; //  ID
    buffer[7] = 0x96; //  verification byte
    buffer[8] = APIVERSION; //  verification byte
  byte checksum = calculateChecksum(buffer, 9);
    buffer[9] = checksum; //  checksum byte
    Serial.write(buffer, sizeof(buffer));
}

    void KMESerial::getStatus(uint8_t id)
{
 
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
  byte buffer[10];

    // Fill the buffer with data
    buffer[0] = HEADER1; //  بداية 
    buffer[1] = HEADER2; //   بداية 
    buffer[2] = 0x03; // حجم الارسال
    buffer[3] =97; //  النوع
    buffer[4] = id; //  المعرف
    buffer[5] = 0; //  القيمة الصغرة
    buffer[6] = 0; //  الكبر
    buffer[7] = 0x96; //  verification 
    buffer[8] = APIVERSION; //  اصدار التحكم
  byte checksum = calculateChecksum(buffer, 9);
    buffer[9] = checksum; //  checksum byte
    Serial.write(buffer, sizeof(buffer));
}
   void KMESerial::getSettings(uint8_t type)
{
  if (type<40)
  {
     byte buffer[10];

    // Fill the buffer with data
    buffer[0] = HEADER1; //  بداية 
    buffer[1] = HEADER2; //   بداية 
    buffer[2] = 0x03; // حجم الارسال
    buffer[3] =type; //  النوع
    buffer[4] = 0; //  المعرف
    buffer[5] = 0; //  القيمة الصغرة
    buffer[6] = 0; //  الكبر
    buffer[7] = 0x96; //  verification 
    buffer[8] = APIVERSION; //  اصدار التحكم
  byte checksum = calculateChecksum(buffer, 9);
    buffer[9] = checksum; //  checksum byte
    Serial.write(buffer, sizeof(buffer));
  }
  

}
   Settings KMESerial::info()
{
 return deviceinfo;
}

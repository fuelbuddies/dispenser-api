#include "Dispencer.h"
/**
 *  abstract class
 */
Dispencer::Dispencer(int baudRate, int pinRx, int pinTx)
{
  baud_rate = baudRate;
  pin_rx = pinRx;
  pin_tx = pinTx;
}

void Dispencer::connectDispencer()
{
  dispencerSerial.begin(baud_rate, SERIAL_8N1, pin_rx, pin_rx);
}

bool Dispencer::isConnected()
{
  return (bool)dispencerSerial;
}

void Dispencer::disconnectDispencer()
{
  dispencerSerial.end();
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void Dispencer::serialEvent()
{
  int needToRead = dispencerSerial.available();
  while (dispencerSerial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    serial_data += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      is_ready_to_read = true;
    }
  }
}


bool Dispencer::isReadyToRead()
{
  return is_ready_to_read;
}

String Dispencer::getReadData()
{
  String response = serial_data;
  serial_data = "";
  return response;
}

#include "Dispencer.h"
/**
 *  abstract class
 */
Dispencer::Dispencer(HardwareSerial serial, int baudRate, int pinRx, int pinTx)
{
  dispencerSerial = serial;
  baud_rate = baudRate;
  pin_rx = pinRx;
  pin_tx = pinTx;
}

int ASCIIHexToInt(char c)
{
  int ret = 0;
  if ((c >= '0') && (c <= '9'))
    ret = (ret << 4) + c - '0';
  else
    ret = (ret << 4) + toupper(c) - 'A' + 10;

  return ret;
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
  is_ready_to_read = false;
  while (dispencerSerial.available()>0)
  {
    // add it to the inputString:
    serial_data = String(serial_data) + String(dispencerSerial.read(), HEX);
    is_ready_to_read = true;
  }
}

HardwareSerial Dispencer::getSerial() {
  return dispencerSerial;
}

bool Dispencer::isReadyToRead()
{
  return is_ready_to_read;
}

String Dispencer::getReadData()
{
  String response = serial_data;
  //serial_data = "";
  return response;
}

#include "Dispencer.hpp"

/**
 *  abstract class
 */
Dispencer::Dispencer(HardwareSerial *serial)
{
  dispencerSerial = serial;
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

// void Dispencer::connectDispencer()
// {
//   dispencerSerial->begin(baud_rate, SERIAL_8N1, pin_rx, pin_rx);
// }

// bool Dispencer::isConnected()
// {
//   return (bool)dispencerSerial;
// }

// void Dispencer::disconnectDispencer()
// {
//   dispencerSerial->end();
// }

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void Dispencer::serialEvent()
{
  is_ready_to_read = false;
  while (dispencerSerial->available()>0)
  {
    String str = String(dispencerSerial->read(), HEX);
    // add it to the inputString:
    serial_data = String(serial_data) + str;
    is_ready_to_read = true;
  }
}

HardwareSerial *Dispencer::getSerial() {
  return dispencerSerial;
}

bool Dispencer::isReadyToRead()
{
  return is_ready_to_read;
}

String Dispencer::getReadData()
{

  String response = String(serial_data);
  serial_data = "";
  is_ready_to_read = false;
  return response;
}

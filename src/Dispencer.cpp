#include "Dispencer.hpp"

/**
 *  abstract class
 */
Dispencer::Dispencer(HardwareSerial *serial)
{
  dispencerSerial = serial;
}

// int ASCIIHexToInt(char c)
// {
//   int ret = 0;
//   if ((c >= '0') && (c <= '9'))
//     ret = (ret << 4) + c - '0';
//   else
//     ret = (ret << 4) + toupper(c) - 'A' + 10;

//   return ret;
// }

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
    if (str.length() == 1) {
      str = "0" + str;
    }
    // add it to the inputString:
    serial_data = String(serial_data) + str;
    is_ready_to_read = true;
    delay(1);
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

uint8_t Dispencer::hexStringToByte(char *printText, int needle) {
    char hexPair[3];

    hexPair[0] = printText[needle];
    hexPair[1] = printText[needle + 1];
    hexPair[2] = '\0';

    return (uint8_t) strtol(hexPair, NULL, 16);
}


double Dispencer::hexStringToDouble(const std::string& hexstr) {
    union
    {
        long long i;
        double    d;
    } value;

    value.i = std::stoll(hexstr, nullptr, 16);

    return value.d;
}

std::string Dispencer::doubleToHexString(double x) {

    union
    {
        long long i;
        double    d;
    } value;

   value.d = x;

   std::ostringstream buf;
   buf << std::hex << std::setfill('0') << std::setw(16) << value.i;

   return buf.str();

}
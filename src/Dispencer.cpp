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
    std::string str = int_to_hex(dispencerSerial->read();
    // add it to the inputString:
    serial_data += str;
    is_ready_to_read = true;
  }
}

/// Convert integer value `val` to text in hexadecimal format.
/// The minimum width is padded with leading zeros; if not
/// specified, this `width` is derived from the type of the
/// argument. Function suitable from char to long long.
/// Pointers, floating point values, etc. are not supported;
/// passing them will result in an (intentional!) compiler error.
/// Basics from: http://stackoverflow.com/a/5100745/2932052
template <typename T>
inline std::string int_to_hex(T val, size_t width=sizeof(T)*2)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(width) << std::hex << (val|0);
    return ss.str();
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

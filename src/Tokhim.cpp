#include "Tokhim.hpp"

Tokhim::Tokhim(HardwareSerial *serial) : Dispencer(serial)
{
}
void Tokhim::connectDispencer()
{
}
/**
 * disconnect dispencer from serial port.
 */
void Tokhim::disconnectDispencer()
{
}
/**
 * check if serial is connected
 */
bool Tokhim::isConnected()
{
  return true;
}

int Tokhim::readTotalizer()
{
  return dispencerSerial->write(totalizer, sizeof(totalizer));
}

int Tokhim::readDispencerStatus()
{
  return 0;
}

/**
 * authorize the sale and start dispencing
 */
int Tokhim::authorizeSale()
{
  return dispencerSerial->write(authorize, sizeof(authorize));
}
/**
 * sets the quantity to be dispencend
 * [dispencer specific]
 */
int Tokhim::sendPreset(int set)
{

  return set;
}

/**
 * gets the quantity to be dispencend
 * [dispencer specific]
 */
int Tokhim::readPreset()
{
  return dispencerSerial->write(read_preset,sizeof(read_preset));
}

/**
 * suspendDispencer, clearSale, pumpStop
 */
int Tokhim::stopDispencer()
{
  dispencerSerial->write(suspend_sale,sizeof(suspend_sale));
  dispencerSerial->write(clear_sale,sizeof(clear_sale));
  dispencerSerial->write(pump_stop,sizeof(pump_stop));
  return 0;
}
/**
 * suspend Dispencer
 */
int Tokhim::suspendDispencer()
{
  return dispencerSerial->write(suspend_sale,sizeof(suspend_sale));
}
/**
 * resume the dispencer
 */
int Tokhim::resumeDispencer()
{
  return dispencerSerial->write(pump_stop,sizeof(pump_stop));;
}
/**
 * clear sale
 */
int Tokhim::clearSale()
{
  return dispencerSerial->write(clear_sale, sizeof(clear_sale));
}
/**
 * read sale
 */
int Tokhim::readSale()
{
  return dispencerSerial->write(read_sale,sizeof(read_sale));
}
/**
 * stop the external pump
 */
int Tokhim::pumpStop()
{
  return dispencerSerial->write(pump_stop, sizeof(pump_stop));
}
/**
 * start the external pump
 */
int Tokhim::pumpStart()
{
  return dispencerSerial->write(pump_start, sizeof(pump_start));
}
/**
 * switch dispencer mode to online.
 */
int Tokhim::switchMode(bool online)
{
  return 0;
}

uint8_t * Tokhim::presetCalculate(int quantity){
  return {};
}

std::string Tokhim::getType() {
  return "Tokheim";
}

std::string Tokhim::getExternalPump()
{
    return "false";
};
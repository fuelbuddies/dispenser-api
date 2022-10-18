#include "Tokhim.h"

Tokhim::Tokhim(int buad_rate, int pin_rx, int pin_tx): Dispencer(buad_rate, pin_rx, pin_tx)
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
  return dispencerSerial.write(totalizer, sizeof(totalizer));
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
  return 0;
}
/**
 * sets the quantity to be dispencend
 * [dispencer specific]
 */
int Tokhim::sendPreset()
{
  return 0;
}
/**
 * suspendDispencer, clearSale, pumpStop
 */
int Tokhim::stopDispencer()
{
  return 0;
}
/**
 * suspend Dispencer
 */
int Tokhim::suspendDispencer()
{
  return 0;
}
/**
 * resume the dispencer
 */
int Tokhim::resumeDispencer()
{
  return 0;
}
/**
 * clear sale
 */
int Tokhim::clearSale()
{
  return 0;
}
/**
 * read sale
 */
int Tokhim::readSale()
{
  return 0;
}
/**
 * stop the external pump
 */
int Tokhim::pumpStop()
{
  return 0;
}
/**
 * start the external pump
 */
int Tokhim::pumpStart()
{
  return 0;
}
/**
 * switch dispencer mode to online.
 */
int Tokhim::switchMode(bool online)
{
  return 0;
}

/**
 * read the value from serialdata
 */
int Tokhim::getReadData()
{
  return 0;
}
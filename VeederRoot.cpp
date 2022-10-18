#ifndef VEEDERROOT_H
#include "VeederRoot.h"
#endif

VeederRoot::VeederRoot(int buad_rate, int pin_rx, int pin_tx) : Dispencer(buad_rate, pin_rx, pin_tx)
{
}

int VeederRoot::readDispencerStatus()
{
  return 0;
}

int VeederRoot::readTotalizer()
{
  return 0;
}

/**
 * authorize the sale and start dispencing
 */
int VeederRoot::authorizeSale()
{
  return 0;
}
/**
 * sets the quantity to be dispencend
 * [dispencer specific]
 */
int VeederRoot::sendPreset()
{
  return 0;
}
/**
 * suspendDispencer, clearSale, pumpStop
 */
int VeederRoot::stopDispencer()
{
  return 0;
}
/**
 * suspend Dispencer
 */
int VeederRoot::suspendDispencer()
{
  return 0;
}
/**
 * resume the dispencer
 */
int VeederRoot::resumeDispencer()
{
  return 0;
}
/**
 * clear sale
 */
int VeederRoot::clearSale()
{
  return 0;
}
/**
 * read sale
 */
int VeederRoot::readSale()
{
  return 0;
}
/**
 * stop the external pump
 */
int VeederRoot::pumpStop()
{
  return 0;
}
/**
 * start the external pump
 */
int VeederRoot::pumpStart()
{
  return 0;
}
/**
 * switch dispencer mode to online.
 */
int VeederRoot::switchMode(bool online)
{
  return 0;
}

/**
 * read the value from serialdata
 */
int VeederRoot::getReadData()
{
  return 0;
}
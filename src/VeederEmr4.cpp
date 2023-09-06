#include "VeederEmr4.hpp"

VeederEmr4::VeederEmr4(HardwareSerial *serial) : Dispencer(serial)
{
}

int VeederEmr4::readDispencerStatus()
{
  return 0;
}

int VeederEmr4::readTotalizer()
{
  return dispencerSerial->write(veeder_totalizer,sizeof(veeder_totalizer));
}

/**
 * authorize the sale and start dispencing
 */
int VeederEmr4::authorizeSale()
{
  dispencerSerial->write(veeder_authorize_on,sizeof(veeder_authorize_on));
  dispencerSerial->write(veeder_start,sizeof(veeder_start));
  return 0;
}
/**
 * sets the quantity to be dispencend
 * [dispencer specific]
 */
int VeederEmr4::sendPreset(float quantity)
{
  return dispencerSerial->write(presetCalculate(quantity), sizeof(presetCalculate(quantity)));
}
/**
 * suspendDispencer, clearSale, pumpStop
 */
int VeederEmr4::stopDispencer()
{
  dispencerSerial->write(veeder_authorize_off,sizeof(veeder_authorize_off));
  dispencerSerial->write(veeder_reset,sizeof(veeder_reset));
  return  dispencerSerial->write(veeder_finish, sizeof(veeder_finish));
}
/**
 * suspend Dispencer
 */
int VeederEmr4::suspendDispencer()
{
  return dispencerSerial->write(veeder_authorize_off,sizeof(veeder_authorize_off));
}
/**
 * resume the dispencer
 */
int VeederEmr4::resumeDispencer()
{
  return 0;
}
/**
 * clear sale
 */
int VeederEmr4::clearSale()
{
  return dispencerSerial->write(veeder_reset,sizeof(veeder_reset));
}
/**
 * read sale
 */
int VeederEmr4::readSale()
{
  return dispencerSerial->write(veeder_read_preset,sizeof(veeder_read_preset));
}
/**
 * stop the external pump
 */
int VeederEmr4::pumpStop()
{
  return dispencerSerial->write(veeder_finish,sizeof(veeder_finish));
}
/**
 * start the external pump
 */
int VeederEmr4::pumpStart()
{
  return dispencerSerial->write(veeder_start,sizeof(veeder_start));
}
/**
 * switch dispencer mode to online.
 */
int VeederEmr4::switchMode(bool online)
{
  return 0;
}

std::string VeederEmr4::getType()
{
  return "VeederEmr4";
}

uint8_t * VeederEmr4::presetCalculate(float quantity) {
  int J, K, L, P,set;
  set=quantity;
  if (set < 10)
  {
    J = 0;
    K = 0;
    L = 0;
    P = set;
  }
  if (set > 9 && set < 100)
  {
    J = 0;
    K = 0;
    L = ((set / 10));
    P = (set % 10);
  }
  if (set > 99 && set < 1000)
  {
    J = 0;
    K = ((set / 100));
    L = ((set / 10) % 10);
    P = (set % 10);
  }
  if (set > 999 && set < 10000)
  {
    J = (set / 1000);
    K = ((set / 100) % 10);
    L = ((set / 10) % 10);
    P = (set % 10);
  }

  uint8_t one = 0x30 + J;
  uint8_t two = 0x30 + K;
  uint8_t three = 0x30 + L;
  uint8_t four = 0x30 + P;

  uint8_t BCC[] = {0x01, 0x41, 0x50, 0x31, 0x30, one, two, three, four, 0x30, 0x30, 0x7F};
  uint8_t result = BCC[0] ^ BCC[1] ^ BCC[2] ^ BCC[3] ^ BCC[4] ^ BCC[5] ^ BCC[6] ^ BCC[7] ^ BCC[8] ^ BCC[9] ^ BCC[10] ^ BCC[11];
  uint8_t volume[] = {0x01, 0x41, 0x50, 0x31, 0x30, one, two, three, four, 0x30, 0x30, 0x7F, result};
  return volume;
}
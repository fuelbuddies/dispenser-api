#include "VeederEmr4.hpp"

VeederEmr4::VeederEmr4(HardwareSerial *serial) : Dispencer(serial)
{
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
  return dispencerSerial->write(veeder_start,sizeof(veeder_start));
}
/**
 * sets the quantity to be dispencend
 * [dispencer specific]
 */
int VeederEmr4::sendPreset(float quantity)
{
  Serial.println("Preset Quantity -> "+ String(quantity));
  dispencerSerial->write(veeder_preset, sizeof(veeder_preset));
  setPreset(quantity);
  return 0;
}

/**
 * gets the quantity to be dispencend
 * [dispencer specific]
 */
int VeederEmr4::readPreset()
{
  return dispencerSerial->write(veeder_read_preset,sizeof(veeder_read_preset));
}
/**
 * suspendDispencer, clearSale, pumpStop
 */
int VeederEmr4::stopDispencer()
{
  dispencerSerial->write(veeder_authorize_off,sizeof(veeder_authorize_off));
  dispencerSerial->write(veeder_reset,sizeof(veeder_reset));
  return dispencerSerial->write(veeder_finish, sizeof(veeder_finish));
}

/**
 * suspend Dispencer
 */
int VeederEmr4::suspendDispencer()
{
  return dispencerSerial->write(veeder_authorize_off,sizeof(veeder_authorize_off));
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
  digitalWrite(external_pump, HIGH);
  return 0;
}
/**
 * start the external pump
 */
int VeederEmr4::pumpStart()
{
  digitalWrite(external_pump, LOW);
  return 0;
}

std::string VeederEmr4::getType()
{
  return "VeederEmr4";
}

uint8_t * VeederEmr4::presetCalculate(float veeder_pre) {}

void VeederEmr4::setPreset(float veeder_pre) {
  char message[] = {0, 0, 0, 0, 0, 0, 0, 0};
  unsigned i;
  unsigned char *chpt;
  chpt = (unsigned char *)&veeder_pre;

  uint8_t AA = 0x7E;
  uint8_t BB = 0x01;
  uint8_t CC = 0xFF;
  uint8_t DD = 0x53;
  uint8_t EE = 0x6E;

  dispencerSerial->write(0x7E);
  dispencerSerial->write(0x01);
  dispencerSerial->write(0xFF);
  dispencerSerial->write(0x53);
  dispencerSerial->write(0x6E);

  for (i = 0; i < sizeof(veeder_pre); i++)
  {
    if (chpt[i] == 0) {
      dispencerSerial->write(0x00);
    }
    else {
      dispencerSerial->write(chpt[i]);
    }
    message[sizeof(veeder_pre) - i] = chpt[i];
  }
  //checksum
  uint8_t BCC = BB + CC + DD + EE + message[0] + message[1] + message[2] + message[3] + message[4] + message[5] + message[6] + message[7];
  BCC = (BCC ^ 0xFF);
  int x1 = BCC + 01;
  if (x1 < 10) {
    dispencerSerial->write(0);
    dispencerSerial->write(x1);
  } else {
    dispencerSerial->write(BCC + 01);
  }

  dispencerSerial->write(0x7E);
}


/**
 * resume the dispencer
 */
int VeederEmr4::resumeDispencer()
{
  return dispencerSerial->write(veeder_authorize_on,sizeof(veeder_authorize_on));
}

int VeederEmr4::switchMode(bool online)
{
  if(online) {
    return dispencerSerial->write(veeder_authorize_on,sizeof(veeder_authorize_on));
  }
  return dispencerSerial->write(veeder_authorize_off, sizeof(veeder_authorize_off));
}

int VeederEmr4::cancelPreset()
{
  return dispencerSerial->write(veeder_reset,sizeof(veeder_reset));
}

int VeederEmr4::readDispencerStatus()
{
  return dispencerSerial->write(veeder_status,sizeof(veeder_status));
}
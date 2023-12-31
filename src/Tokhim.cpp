#include "Tokhim.hpp"

Tokhim::Tokhim(HardwareSerial *serial) : Dispencer(serial)
{
}

int Tokhim::readTotalizer()
{
  return dispencerSerial->write(totalizer, sizeof(totalizer));
}

/**
 * authorize the sale and start dispencing
 */
int Tokhim::authorizeSale()
{
  return dispencerSerial->write(authorize, sizeof(authorize));
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
  return dispencerSerial->write(tokhim_read_sale,sizeof(tokhim_read_sale));
}

/**
 * read Authorization Status Bit 2 = Remote mode & 1 = Remote 0 = Manual
 */
int Tokhim::readAuth()
{
  return dispencerSerial->write(tokhim_status,sizeof(tokhim_status));
}

/**
 * cancels the previously ged Presetvol
 */
int Tokhim::cancelPreset()
{
  return dispencerSerial->write(cancel_preset,sizeof(cancel_preset));
}

/**
 * resume the dispencer
 */
int Tokhim::resumeDispencer()
{
  return dispencerSerial->write(resume_sale,sizeof(resume_sale));
}

/**
 * stop the external pump
 */
int Tokhim::pumpStop()
{
  return dispencerSerial->write(pump_stop, sizeof(pump_stop));
}
/**
 * start the Intenal/whatever pump for Tokheim
 */
int Tokhim::pumpStart()
{
  return dispencerSerial->write(pump_start, sizeof(pump_start));
}

std::string Tokhim::getType() {
  return "TOKHIEM";
}

std::string Tokhim::getExternalPump()
{
    return "false";
};

/**
 * switch dispencer mode to online.
 */
int Tokhim::switchMode(bool online)
{
  if(online) {
    // for switching to online pump_start is recommended that is happening already in future flow
    return this->pumpStart();
  }

  return dispencerSerial->write(tokhim_authorize_off, sizeof(tokhim_authorize_off));
}

int Tokhim::sendPreset(float quantity)
{
    int J = 0, K = 0, L = 0, P = 0, set;
    set = static_cast<int>(quantity);
    if (set < 10)
    {
        J = 0;
        K = 0;
        L = 0;
        P = set;
    }
    else if (set > 9 && set < 100)
    {
        J = 0;
        K = 0;
        L = ((set / 10));
        P = (set % 10);
    }
    else if (set > 99 && set < 1000)
    {
        J = 0;
        K = ((set / 100));
        L = ((set / 10) % 10);
        P = (set % 10);
    }
    else if (set > 999 && set < 10000)
    {
        J = (set / 1000);
        K = ((set / 100) % 10);
        L = ((set / 10) % 10);
        P = (set % 10);
    }

    uint8_t one   = 0x30 + J;
    uint8_t two   = 0x30 + K;
    uint8_t three = 0x30 + L;
    uint8_t four  = 0x30 + P;

    uint8_t BCC[] = {0x01, 0x41, 0x50, 0x31, 0x30, one, two, three, four, 0x30, 0x30, 0x7F};
    uint8_t result = BCC[0] ^ BCC[1] ^ BCC[2] ^ BCC[3] ^ BCC[4] ^ BCC[5] ^ BCC[6] ^ BCC[7] ^ BCC[8] ^ BCC[9] ^ BCC[10] ^ BCC[11];
    uint8_t volume[13] = {0x01, 0x41, 0x50, 0x31, 0x30, one, two, three, four, 0x30, 0x30, 0x7F, result};

    // for debugging only
    // for (int i = 0; i < 13; i++)
    // {
    //   Serial.print(volume[i], HEX);
    // }
    // Serial.println();

    return dispencerSerial->write(volume, sizeof(volume));
}

/**
  *  reads avaialble 16 byte Status report in  3 Stat banks, Status0, Status1
  */
int Tokhim::readDispencerStatus()
{
  return dispencerSerial->write(tokhim_status, sizeof(tokhim_status));
}
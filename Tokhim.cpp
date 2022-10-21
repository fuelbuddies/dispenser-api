#include "Tokhim.h"

Tokhim::Tokhim(int buad_rate, int pin_rx, int pin_tx) : Dispencer(buad_rate, pin_rx, pin_tx)
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
  return dispencerSerial.write(authorize, sizeof(authorize));
}
/**
 * sets the quantity to be dispencend
 * [dispencer specific]
 */
int Tokhim::sendPreset(int set)
{
  int J, K, L, P;
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
    ;
    K = ((set / 100) % 10);
    L = ((set / 10) % 10);
    P = (set % 10);
  }

  byte one = 0x30 + J;
  byte two = 0x30 + K;
  byte three = 0x30 + L;
  byte four = 0x30 + P;

  byte BCC[] = {0x01, 0x41, 0x50, 0x31, 0x30, one, two, three, four, 0x30, 0x30, 0x7F};
  byte result = BCC[0] ^ BCC[1] ^ BCC[2] ^ BCC[3] ^ BCC[4] ^ BCC[5] ^ BCC[6] ^ BCC[7] ^ BCC[8] ^ BCC[9] ^ BCC[10] ^ BCC[11];
  byte volume[] = {0x01, 0x41, 0x50, 0x31, 0x30, one, two, three, four, 0x30, 0x30, 0x7F, result};

  return dispencerSerial.write(volume, sizeof(volume));
}
/**
 * suspendDispencer, clearSale, pumpStop
 */
int Tokhim::stopDispencer()
{
  dispencerSerial.write(suspend_sale,sizeof(suspend_sale));
  dispencerSerial.write(clear_sale,sizeof(clear_sale));
  dispencerSerial.write(pump_stop,sizeof(pump_stop));
  return 0;
}
/**
 * suspend Dispencer
 */
int Tokhim::suspendDispencer()
{
  return dispencerSerial.write(suspend_sale,sizeof(suspend_sale));
}
/**
 * resume the dispencer
 */
int Tokhim::resumeDispencer()
{
  return dispencerSerial.write(pump_stop,sizeof(pump_stop));;
}
/**
 * clear sale
 */
int Tokhim::clearSale() 
{
  return dispencerSerial.write(clear_sale, sizeof(clear_sale));
}
/**
 * read sale
 */
int Tokhim::readSale()
{
  return dispencerSerial.write(read_sale,sizeof(read_sale));
}
/**
 * stop the external pump
 */
int Tokhim::pumpStop() 
{
  return dispencerSerial.write(pump_stop, sizeof(pump_stop));
}
/**
 * start the external pump
 */
int Tokhim::pumpStart()
{
  return dispencerSerial.write(pump_start, sizeof(pump_start));
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

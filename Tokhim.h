#ifndef TOKHIM_H
#define TOKHIM_H

#ifndef DISPENCER_H
#include "Dispencer.h"
#endif

class Tokhim:public Dispencer
{
public:
  Tokhim(int buad_rate, int pin_rx, int pin_tx);
  /**
   * connect dispencer on serial port
   */
  void connectDispencer();
  /**
   * disconnect dispencer from serial port.
   */
  void disconnectDispencer();
  /**
   * check if serial is connected
   */
  bool isConnected();

  int readDispencerStatus();
  /**
   * read totalizer reading
   */
  int readTotalizer();
  /**
   * authorize the sale and start dispencing
   */
  int authorizeSale();
  /**
   * sets the quantity to be dispencend
   * [dispencer specific]
   */
  int sendPreset();
  /**
   * suspendDispencer, clearSale, pumpStop
   */
  int stopDispencer();
  /**
   * suspend Dispencer
   */
  int suspendDispencer();
  /**
   * resume the dispencer
   */
  int resumeDispencer();
  /**
   * clear sale
   */
  int clearSale();
  /**
   * read sale
   */
  int readSale();
  /**
   * stop the external pump
   */
  int pumpStop();
  /**
   * start the external pump
   */
  int pumpStart();
  /**
   * switch dispencer mode to online.
   */
  int switchMode(bool online = true);

  /**
   * read the value from serialdata
   */
  int getReadData();

private:
  byte read_sale[5] = {0x01, 0x41, 0x52, 0x7F, 0x6D};
  byte pump_start[5] = {0x01, 0x41, 0x4F, 0x7F, 0x70};
  byte read_preset[5] = {0x01, 0x41, 0x48, 0x7F, 0x77};
  byte cancel_preset[5] = {0x01, 0x41, 0x45, 0x7F, 0x7A};
  byte authorize[5] = {0x01, 0x41, 0x41, 0x7F, 0x7E};
  byte clear_sale[5] = {0x01, 0x41, 0x46, 0x7F, 0x79};
  byte suspend_sale[5] = {0x01, 0x41, 0x44, 0x7F, 0x7B};
  byte pump_stop[5] = {0x01, 0x41, 0x5A, 0x7F, 0x65};
  byte check_nozzle_totalizer[5] = {0x01, 0x41, 0x53, 0x7F, 0x6C};
  byte totalizer[5] = {0x01, 0x41, 0x54, 0x7F, 0x6B};
};

#endif

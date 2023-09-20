#ifndef TOKHIM_H
#define TOKHIM_H

#include "Dispencer.hpp"

class Tokhim : public Dispencer
{
public:
  Tokhim(HardwareSerial *serial);
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
  int sendPreset(int set);
  /**
   * gets the quantity to be dispencend
   * [dispencer specific]
   */
  int readPreset();
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

  uint8_t * presetCalculate(int quantity);

  std::string getType();

  std::string getExternalPump();

private:
  uint8_t totalizer[5] = {0x01, 0x41, 0x54, 0x7F, 0x6B};
  uint8_t read_sale[5] = {0x01, 0x41, 0x52, 0x7F, 0x6D};
  uint8_t pump_start[5] = {0x01, 0x41, 0x4F, 0x7F, 0x70};
  uint8_t read_preset[5] = {0x01, 0x41, 0x48, 0x7F, 0x77};
  uint8_t cancel_preset[5] = {0x01, 0x41, 0x45, 0x7F, 0x7A};
  uint8_t authorize[5] = {0x01, 0x41, 0x41, 0x7F, 0x7E};
  uint8_t clear_sale[5] = {0x01, 0x41, 0x46, 0x7F, 0x79};
  uint8_t suspend_sale[5] = {0x01, 0x41, 0x44, 0x7F, 0x7B};
  uint8_t pump_stop[5] = {0x01, 0x41, 0x5A, 0x7F, 0x65};
  uint8_t check_nozzle_totalizer[5] = {0x01, 0x41, 0x53, 0x7F, 0x6C};
  uint8_t go_local[5] = {0x01, 0x41, 0x47, 0x7F, 0x78};
  uint8_t resume_sale[5] = {0x01, 0x41, 0x55, 0x7F, 0x6A};
};

#endif

#ifndef VEEDERROOT_H
#define VEEDERROOT_H

#ifndef DISPENCER_H
#include "Dispencer.h"
#endif

class VeederRoot : public Dispencer
{
public:
  VeederRoot(int buad_rate, int pin_rx, int pin_tx);

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

  byte * presetCalculate(float quantity);

private:
  byte veeder_start[8] = {0x7E, 0x01, 0xFF, 0x53, 0x75, 0x00, 0x38, 0x7E};
  byte veeder_mode[8] = {0x7E, 0x01, 0xFF, 0x53, 0x75, 0x02, 0x36, 0x7E};
  byte veeder_finish[8] = {0x7E, 0x01, 0xFF, 0x53, 0x75, 0x01, 0x37, 0x7E};
  byte veeder_totalizer[7] = {0x7E, 0x01, 0xFF, 0x47, 0x6C, 0x4D, 0x7E};
  byte veeder_read_volume[7] = {0x7E, 0x01, 0xFF, 0x47, 0x6B, 0x4E, 0x7E};
  byte veeder_read_preset[7] = {0x7E, 0x01, 0xFF, 0x47, 0x6E, 0x4B, 0x7E};
  byte veeder_reset[7] = {0x7E, 0x01, 0xFF, 0x52, 0x00, 0xAE, 0x7E};
  byte veeder_preset[8] = {0x7E, 0x01, 0xFF, 0x53, 0x75, 0x03, 0x35, 0x7E};
  byte veeder_authorize_on[8] = {0x7E, 0x01, 0xFF, 0x44, 0x25, 0x01, 0x96, 0x7E};
  byte veeder_authorize_off[8] = {0x7E, 0x01, 0xFF, 0x44, 0x25, 0x00, 0x97, 0x7E};
  byte dummy_volume[13] = {0x01, 0x41, 0x50, 0x31, 0x30, 0x30, 0x30, 0x35, 0x30, 0x30, 0x30, 0x7F, 0x6B};
};

#endif

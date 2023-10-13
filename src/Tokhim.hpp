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
  int sendPreset(float set);
  /**
   * gets the quantity to be dispencend
   * [dispencer specific]
   */
  int readPreset();
    /**
   * cancel preset
   * [dispencer specific]
   */
  int cancelPreset();
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
   * read sale realtime
   */
  int readSale();

    /**
   * read Auth status
   */
  int readAuth();
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

  std::string getType();

  std::string getExternalPump();



private:
  uint8_t totalizer[5]                      = {0x01, 0x41, 0x54, 0x7F, 0x6B};
  uint8_t pump_start[5]                     = {0x01, 0x41, 0x4F, 0x7F, 0x70};
  uint8_t pump_stop[5]                      = {0x01, 0x41, 0x5A, 0x7F, 0x65};                                                      // NTS:  used to go_remote as well from Local Mode
  uint8_t read_preset[5]                    = {0x01, 0x41, 0x48, 0x7F, 0x77};
  uint8_t cancel_preset[5]                  = {0x01, 0x41, 0x45, 0x7F, 0x7A};               // BCC checks out ✅  , TESTING ✅
  uint8_t authorize[5]                      = {0x01, 0x41, 0x41, 0x7F, 0x7E};               // BCC checks out ✅  , TESTING ;                                                      //KINDA SUS:  doc says Read Password Attempt Log*
  uint8_t go_local[5]                       = {0x01, 0x41, 0x47, 0x7F, 0x78};               // BCC checks out ✅  , TESTING ;
  uint8_t clear_sale[5]                     = {0x01, 0x41, 0x46, 0x7F, 0x79};                //BCC checks out ✅  , TESTING
  uint8_t suspend_sale[5]                   = {0x01, 0x41, 0x44, 0x7F, 0x7B};                //BCC checks out ✅  , TESTING
  uint8_t resume_sale[5]                    = {0x01, 0x41, 0x55, 0x7F, 0x6A};                //BCC checks out ✅  , TESTING
  uint8_t tokhim_read_sale[5]              =  {0x01, 0x41, 0x52, 0x7F, 0x6D};                //BCC checks out ✅  , TESTING
  uint8_t tokhim_status[5]                  = {0x01, 0x41, 0x53, 0x7F, 0x6C};                //BCC checks out ✅  , TESTING ✅
  uint8_t tokhim_authorize_on[5]            = {0x01, 0x41, 0x41, 0x7F, 0x7E};                //BCC checks out ✅  , TESTING ✅
  uint8_t tokhim_authorize_off[5]           = {0x01, 0x41, 0x47, 0x7F, 0x78};                //BCC checks out ✅  , TESTING ❌
  uint8_t tokhim_show_preset[5]             = {0x01, 0x41, 0x43, 0x7F, 0x7C};                //BCC checks out ✅  , TESTING ❌
  /*
  uint8_t tokheim_go_Remote[5]              = {0x01, 0x41, 0x00, 0x7F, };
  uint8_t tokheim_set_preset[]              = {0x01, 0x41, 0x00, 0x7F, };
  uint8_t tokheim_read_auth[2]              = {0x01, 0x41};
  uint8_t  tokhim_DU_state                  =   // Equivalent to Read_EMR

*/
};

#endif
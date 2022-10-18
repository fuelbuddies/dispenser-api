#ifndef DISPENCER_H
#define DISPENCER_H

#if (ARDUINO > 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <HardwareSerial.h>

class Dispencer
{
public:
  Dispencer(int buad_rate = 9600, int pin_rx = 17, int pin_tx = 16);
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
  /**
   * status poll
   */
  virtual int readDispencerStatus()
  {
    return 0;
  }
  /**
   * read totalizer reading
   */
  virtual int readTotalizer()
  {
    return 0;
  }
  /**
   * authorize the sale and start dispencing
   */
  virtual int authorizeSale()
  {
    return 0;
  }
  /**
   * sets the quantity to be dispencend
   * [dispencer specific]
   */
  virtual int sendPreset()
  {
    return 0;
  }
  /**
   * suspendDispencer, clearSale, pumpStop
   */
  virtual int stopDispencer()
  {
    return 0;
  }
  /**
   * suspend Dispencer
   */
  virtual int suspendDispencer()
  {
    return 0;
  }
  /**
   * resume the dispencer
   */
  virtual int resumeDispencer()
  {
    return 0;
  }
  /**
   * clear sale
   */
  virtual int clearSale()
  {
    return 0;
  }
  /**
   * read sale
   */
  virtual int readSale()
  {
    return 0;
  }
  /**
   * stop the external pump
   */
  virtual int pumpStop()
  {
    return 0;
  }
  /**
   * start the external pump
   */
  virtual int pumpStart()
  {
    return 0;
  }
  /**
   * switch dispencer mode to online.
   */
  virtual int switchMode(bool online = true)
  {
    return 0;
  }

  /**
   * read the value from serialdata
   */
  String getReadData();

  /**
   * serial Event manager
   */
  void serialEvent();

  /**
   * data has been fetched
   */
  bool isReadyToRead();

protected:
  HardwareSerial dispencerSerial = HardwareSerial(2);
  int baud_rate;
  int pin_rx;
  int pin_tx;
  String serial_data;
  bool is_ready_to_read = false;
  byte *presetCalculate(float quantity);
  virtual int internalPumpStart()
  {
    return 0;
  };
  virtual int internalPumpStop()
  {
    return 0;
  };
};

#endif

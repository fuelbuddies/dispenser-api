#ifndef DISPENCER_H
#define DISPENCER_H

#if (ARDUINO > 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <HardwareSerial.h>

class Dispencer {
public:
  Dispencer(int buad_rate=9600, int pin_rx=17, int pin_tx=16);
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
  virtual int readDispencerStatus() = 0;
  /**
   * read totalizer reading
   */
  virtual int readTotalizer() = 0;
  /**
   * authorize the sale and start dispencing
   */
  virtual int authorizeSale() = 0;
  /**
   * sets the quantity to be dispencend
   * [dispencer specific]
   */
  virtual int sendPreset() = 0;
  /**
   * suspendDispencer, clearSale, pumpStop
   */
  virtual int stopDispencer() = 0;
  /**
   * suspend Dispencer
   */
  virtual int suspendDispencer() = 0;
  /**
   * resume the dispencer
   */
  virtual int resumeDispencer() = 0;
  /**
   * clear sale
   */
  virtual int clearSale() = 0;
  /**
   * read sale
   */
  virtual int readSale() = 0;
  /**
   * stop the external pump
   */
  virtual int pumpStop() = 0;
  /**
   * start the external pump
   */
  virtual int pumpStart() = 0;
  /**
   * switch dispencer mode to online.
   */
  virtual int switchMode(bool online=true) = 0;
  
  /**
   * read the value from serialdata
   */
  virtual int getReadData() = 0;

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
  byte serial_data[];
  bool is_ready_to_read=false;
  byte * presetCalculate(float quantity);
  int internalPumpStart();
  int internalPumpStop();
};

#endif

#include "Dispencer.h"
/** 
 *  abstract class
 */
Dispencer::Dispencer(int buadRate, int pinRx, int pinTx) {
  baud_rate = baudRate;
  pin_rx = pinRx;
  pin_tx = pinTx;
}

Dispencer::connectDispencer() {
  dispencerSerial.begin(baud_rate, SERIAL_8N1, pin_rx, pin_rx);
}

Dispencer::isConnected(): bool {
  return (bool) dispencerSerial;
}

Dispencer::disconnectDispencer() {
  dispencerSerial.end();
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
Dispencer::serialEvent() {
  int needToRead = dispencerSerial.available();
  serial_data = {};
  dispencerSerial.readBytesUntil("\r", serial_data, needToRead)
  is_ready_to_read = true;
}


Dispencer::isReadyToRead(): bool {
  return is_ready_to_read;
}

Dispencer::getReadData(): byte[] {
  return serial_data;
}

#include "Tokhim.h"

Tokhim::Tokhim(int buad_rate=9600, int pin_rx=17, int pin_tx=16) {
  Dispencer::Dispencer(int buadRate, int pinRx, int pinTx);
}

Tokhim::readTotalizer(): int {
  return dispencerSerial.write(totalizer, sizeof(totalizer));
}

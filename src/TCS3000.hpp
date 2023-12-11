#ifndef TCS3000_H
#define TCS3000_H

#include "Dispencer.hpp"

class TCS3000 : public Dispencer
{
public:
  TCS3000(HardwareSerial *serial);

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
  int sendPreset(float quantity);
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
   * read sale
   */
  int readSale();
  /**
   * read sale
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
   * print reciept
   */
  int printReciept(char *printText);

  /**
   * switch dispencer mode to online.
   */
  int switchMode(bool online = true);

  std::string getType();

  std::string getExternalPump();


private:
  const uint8_t totalizer[7] =     {0x7E, 0x01, 0x00, 0x40, 0x1E, 0x00, 0x47};
  const uint8_t read_auth[7] =     {0x7E, 0x01, 0x00, 0x40, 0x35, 0x00, 0xA5};  //Duplicate
  const uint8_t pump_start[7] =    {0x7E, 0x01, 0x00, 0x40, 0x1F, 0x00, 0x83}; //DUplicate
  // const uint8_t pump_stop[7] =  {0x7E, 0x01, 0x00, 0x20, 0x3E, 0x00, 0x23};
  const uint8_t pump_stop[7] =      {0x7E, 0x01, 0x00, 0x20, 0x3B, 0x00, 0xDC};
  const uint8_t read_status[7] =    {0x7E, 0x01, 0x00, 0x40, 0x1F, 0x00, 0x83};
  const uint8_t read_sale[7] =      {0x7E, 0x01, 0x00, 0x40, 0x2B, 0x00, 0x95}; //TBD
  const uint8_t read_preset[7] =    {0x7E, 0x01, 0x00, 0x40, 0x1F, 0x00, 0x83}; //DUplicate
  const uint8_t authorize_sale[7] = {0x7E, 0x01, 0x00, 0x40, 0x1E, 0x00, 0x47};
  const uint8_t preset_dummy[18] =    {0x7E, 0x01, 0x00, 0x20, 0x38, 0x0B, 0x03, 0x03, 0xF7, 0x40, 0x51, 0x6C, 0x28, 0xF5, 0xC2, 0x8F, 0x5C, 0xD6};
  const uint8_t suspend_sale[7] =   {0x7E, 0x01, 0x00, 0x20, 0x39, 0x00, 0x4D};
  const uint8_t resume_sale[7] =    {0x7E, 0x01, 0x00, 0x20, 0x3A, 0x00, 0x18};
  const uint8_t clear_sale[7] =     {0x7E, 0x01, 0x00, 0x20, 0x3E, 0x00, 0x23};
  const uint8_t cancel_preset[7] =  {0x7E, 0x01, 0x00, 0x20, 0x36, 0x00, 0x55};
  const unsigned char crc_array[256] = {0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65, 157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220, 35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98, 190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255, 70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7, 219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154, 101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36, 248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185, 140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205, 17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80, 175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238, 50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115, 202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139, 87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22, 233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168, 116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53}; // crc_table[]
};

#endif
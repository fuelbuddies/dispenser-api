#include "TCS3000.hpp"

TCS3000::TCS3000(HardwareSerial *serial) : Dispencer(serial)
{
}

std::string TCS3000::getType()
{
  return "TCS3000";
}

std::string TCS3000::getExternalPump()
{
    return "false";
}

int TCS3000::readTotalizer()
{
    return dispencerSerial->write(totalizer,sizeof(totalizer));
}

int TCS3000::authorizeSale()
{
    return dispencerSerial->write(authorize_sale,sizeof(authorize_sale));
}

int TCS3000::readPreset() {
    return dispencerSerial->write(read_preset,sizeof(read_preset));
}

int TCS3000::stopDispencer() {
    return dispencerSerial->write(stop,sizeof(stop)); //TBD
}

int TCS3000::suspendDispencer() {
    return dispencerSerial->write(suspend_sale,sizeof(stop));
}

int TCS3000::resumeDispencer() {
    dispencerSerial->write(resume_sale,sizeof(resume_sale));
}

int TCS3000::clearSale() {
    return dispencerSerial->write(clear_sale,sizeof(clear_sale));
}

int TCS3000::readSale() {
    return dispencerSerial->write(read_sale,sizeof(read_sale));
}

int TCS3000::readAuth() {
    return dispencerSerial->write(read_auth,sizeof(read_auth)); //TBD
}

int TCS3000::pumpStart() {
    return dispencerSerial->write(pump_start,sizeof(pump_start));
}

int TCS3000::pumpStop() {
    dispencerSerial->write(pump_stop,sizeof(pump_stop));
}

int TCS3000::switchMode(bool online) {
    return 0; //TBD
}

int TCS3000::cancelPreset() {
    return dispencerSerial->write(cancel_preset,sizeof(cancel_preset));
}

int TCS3000::readDispencerStatus() {
    return dispencerSerial->write(read_status,sizeof(read_status));
}

int TCS3000::sendPreset(float quantity)
{
    int J = 0, K = 0, L = 0, P = 0, set;
    set = static_cast<int>(quantity);
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

    uint8_t one = 0x30 + J;
    uint8_t two = 0x30 + K;
    uint8_t three = 0x30 + L;
    uint8_t four = 0x30 + P;
    uint8_t BCC[20] = {0x02, 0x30, 0x30, 0x31, 0x31, 0x34, 0x32, 0x31, 0x30, 0x30, one, two, three, four, 0x31, 0x31, 0x20, 0x20, 0x20, 0x20};
    int BCC_SIZE = 20;                      //Kya scene is Checksum ka, @explain_bot

    int checksum = 0;
    for (int i = 0; i < BCC_SIZE; i++)
    {
        checksum += BCC[i];
    }
    checksum %= 256;

    char checksumHex[3];
    sprintf(checksumHex, "%02X", checksum);

    uint8_t checksum1 = checksumHex[0];
    uint8_t checksum2 = checksumHex[1];

    uint8_t volume[23] = {0x02, 0x30, 0x30, 0x31, 0x31, 0x34, 0x32, 0x31, 0x30, 0x30, one, two, three, four, 0x31, 0x31, 0x20, 0x20, 0x20, 0x20, checksum2, checksum1, 0X0D};

    // for (int i = 0; i < 23; i++)
    // {
    //     printf("%02X ", volume[i]);
    // }

    // write_command(volume);
    return dispencerSerial->write((char *)volume, sizeof(volume));

    // ESP_LOG_BUFFER_HEXDUMP(TAG, volume, sizeof(volume), ESP_LOG_DEBUG);
}

int TCS3000::printReciept(char *printText) {
    unsigned int i; unsigned char crc = 0;

    // Calculate the CRC
    for (i = 0; i < strlen(printText); i += 2)
    {
        crc = crc_array[ crc ^ this->hexStringToByte(printText, i) ];
    }

    // Send each character of the hex string over serial
    for (i = 0; i < strlen(printText); i += 2) {
        dispencerSerial->write((uint8_t) this->hexStringToByte(printText, i));
    }

    // Send the CRC
    return dispencerSerial->write(crc);
}

unsigned char TCS3000::calc_checksum_8(unsigned char * data, unsigned int len) {
    unsigned char crc = 0;
    for(unsigned int i=0; i < len; i++) {
        crc = crc_array[ crc ^ data[i] ];
    }
    return crc; 
}
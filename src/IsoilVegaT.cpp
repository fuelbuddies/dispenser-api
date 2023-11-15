#include "IsoilVegaT.hpp"

IsoilVegaT::IsoilVegaT(HardwareSerial *serial) : Dispencer(serial)
{
}

std::string IsoilVegaT::getType()
{
  return "ISOILVEGATV10";
}

std::string IsoilVegaT::getExternalPump() 
{
    return "false";
}

int IsoilVegaT::readTotalizer()
{
    return dispencerSerial->write(totalizer,sizeof(totalizer));
}

int IsoilVegaT::authorizeSale()
{
    return dispencerSerial->write(start,sizeof(start));
}

int IsoilVegaT::readPreset() {
    return dispencerSerial->write(check_nozzle_totalizer,sizeof(check_nozzle_totalizer));
}

int IsoilVegaT::stopDispencer() {
    return dispencerSerial->write(stop,sizeof(stop)); //TBD
}

int IsoilVegaT::suspendDispencer() {
    return dispencerSerial->write(stop,sizeof(stop));
}

int IsoilVegaT::resumeDispencer() {
    dispencerSerial->write(terminate,sizeof(terminate));
    return dispencerSerial->write(start,sizeof(start));
}

int IsoilVegaT::clearSale() {
    return dispencerSerial->write(transaction_close,sizeof(transaction_close));
}

int IsoilVegaT::readSale() {
    return dispencerSerial->write(check_nozzle_totalizer,sizeof(check_nozzle_totalizer));
}

int IsoilVegaT::readAuth() {
    return dispencerSerial->write(check_nozzle_totalizer,sizeof(check_nozzle_totalizer)); //TBD
}

int IsoilVegaT::pumpStart() {
    return dispencerSerial->write(transaction_enable,sizeof(transaction_enable));
}

int IsoilVegaT::pumpStop() {
    dispencerSerial->write(terminate,sizeof(terminate));
    return dispencerSerial->write(inbetween_close,sizeof(inbetween_close));
}

int IsoilVegaT::switchMode(bool online) {
    return 0; //TBD
}

int IsoilVegaT::cancelPreset() {
    return "02303031203432303039370d20";
}

int IsoilVegaT::readDispencerStatus() {
    return dispencerSerial->write(check_nozzle_totalizer,sizeof(check_nozzle_totalizer));
}

int IsoilVegaT::sendPreset(float quantity)
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
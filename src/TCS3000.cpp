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
    int res = dispencerSerial->write(pump_stop,sizeof(pump_stop)); //TBD
    delay(3000);
    return res;
}

int TCS3000::suspendDispencer() {
    return dispencerSerial->write(suspend_sale,sizeof(suspend_sale));
}

int TCS3000::resumeDispencer() {
    return dispencerSerial->write(resume_sale,sizeof(resume_sale));
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
    return dispencerSerial->write(pump_stop,sizeof(pump_stop));
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
    unsigned int i = 0;
    double set = static_cast<double>(quantity);
    unsigned char crc = 0;

    uint8_t volume_precursor[] = {0x7E, 0x01, 0x00, 0x20, 0x38, 0x0B, 0x03, 0x03, 0xF7};
    size_t volume_precursor_length = sizeof(volume_precursor) / sizeof(volume_precursor[0]);

    // calculate the partial crc based upon the precursor
    for(i=0; i < volume_precursor_length; i++) {
        crc = crc_array[ crc ^ volume_precursor[i] ];
    }

    // calculate preset hex from double
    std::string hex = this->doubleToHexString(set);
    for (i = 0; i < hex.length(); i += 2)
    {
        crc = crc_array[ crc ^ this->hexStringToByte(hex.c_str(), i) ];
    }

    // Send volume precursor over serial
    for (i = 0; i < volume_precursor_length; i++) {
        dispencerSerial->write((uint8_t) volume_precursor[i]);
    }

    // Send each character of the hex string over serial
    for (i = 0; i < hex.length(); i += 2) {
        dispencerSerial->write((uint8_t) this->hexStringToByte(hex.c_str(), i));
    }

    // Send the CRC
    return dispencerSerial->write(crc);
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
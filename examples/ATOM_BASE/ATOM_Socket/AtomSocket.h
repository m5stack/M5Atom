#ifndef _ATOMSOCKET_H_
#define _ATOMSOCKET_H_

#include "M5Atom.h"

class ATOMSOCKET {
   public:
    void Init(HardwareSerial& SerialData, int _RelayIO, int _RXD);
    void setVF(float Data);
    void setCF(float Data);
    void SerialReadLoop();
    void SetPowerOn();
    void SetPowerOff();
    float GetVol();
    float GetVolAnalog();
    float GetCurrent();
    float GetCurrentAnalog();
    float GetActivePower();
    float GetInspectingPower();
    float GetPowerFactor();
    uint16_t GetPF();
    uint32_t GetPFAll();
    float GetKWh();

    byte SerialTemps[24];
    byte SeriaDataLen = 0;
    bool SerialRead   = 0;

    uint32_t VolPar;
    uint32_t CurrentPar;
    uint32_t PowerPar;
    uint32_t CurrentData;
    float VF;
    float CF;

   private:
    HardwareSerial* AtomSerial;
    bool Checksum();

    int RelayIO;
    int RXD;
    uint8_t SysStatus;

    uint32_t VolData;

    uint32_t PowerData;
    uint16_t PF;
    uint32_t PFData = 1;
    uint32_t VolR1  = 1880000;
    uint32_t VolR2  = 1000;
    float CurrentRF = 0.001;
};

#endif
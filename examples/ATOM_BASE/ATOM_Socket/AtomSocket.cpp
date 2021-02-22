#include "AtomSocket.h"

void ATOMSOCKET::Init(HardwareSerial& SerialData, int _RelayIO, int _RXD) {
	 AtomSerial = &SerialData; 
	 RelayIO = _RelayIO;
	 RXD = _RXD;
	 AtomSerial->begin(4800,SERIAL_8E1,RXD);
	 pinMode(RelayIO,OUTPUT);
	 VF = VolR1 / VolR2 / 1000.0; 
	 CF = 1.0 / (CurrentRF *1000.0);
}


void ATOMSOCKET::SetPowerOn() {
	digitalWrite(RelayIO,HIGH);
}

void ATOMSOCKET::SetPowerOff() {
	digitalWrite(RelayIO,LOW);
}

void ATOMSOCKET::setVF(float Data)
{
	VF = Data;
}


void ATOMSOCKET::setCF(float Data)
{
	CF = Data;
}

void ATOMSOCKET::SerialReadLoop()
{
	if (AtomSerial->available()>0)
	{
		delay(55);
		SeriaDataLen = AtomSerial->available();
		
		if (SeriaDataLen !=24)
		{
			while(AtomSerial->read()>= 0){}
			return;
		}

		for (byte a = 0; a < SeriaDataLen; a++)
		{
			SerialTemps[a] =  AtomSerial->read();
		}

		if(SerialTemps[1] != 0x5A )
		{
			while(AtomSerial->read()>= 0){}
			return;
		}
		if(Checksum() == false)
		{
			return;
		}
		
		SerialRead = 1;
		VolPar = ((uint32_t)SerialTemps[2]  <<16) | ((uint32_t)SerialTemps[3] <<8) | SerialTemps[4];
		VolData = ((uint32_t)SerialTemps[5]  <<16) | ((uint32_t)SerialTemps[6] <<8) | SerialTemps[7];
		CurrentPar = ((uint32_t)SerialTemps[8]  <<16) | ((uint32_t)SerialTemps[9] <<8) | SerialTemps[10];
		CurrentData = ((uint32_t)SerialTemps[11]  <<16) | ((uint32_t)SerialTemps[12] <<8) | SerialTemps[13];
		PowerPar = ((uint32_t)SerialTemps[14]  <<16) | ((uint32_t)SerialTemps[15] <<8) | SerialTemps[16];
		PowerData = ((uint32_t)SerialTemps[17]  <<16) | ((uint32_t)SerialTemps[18] <<8) | SerialTemps[19];
		PF = ((uint32_t)SerialTemps[21] <<8) | SerialTemps[22];    
		if(bitRead(SerialTemps[20], 7) == 1)
		{
			PFData++;
		}
	}
}


float ATOMSOCKET::GetVol()
{
	float Vol = GetVolAnalog() * VF;
	return Vol;
} 

float ATOMSOCKET::GetVolAnalog()
{	
	float FVolPar = VolPar; 
	float Vol = FVolPar / VolData;
	return Vol; 
}

float ATOMSOCKET::GetCurrent()
{
	float Current = GetCurrentAnalog() * CF - 0.06f;
	return Current;

}

float ATOMSOCKET::GetCurrentAnalog()
{
	float FCurrentPar = CurrentPar;
	float Current  = FCurrentPar / (float)CurrentData;
	return Current;
}


float ATOMSOCKET::GetActivePower()
{	float FPowerPar = PowerPar;
	float FPowerData = PowerData;
	Serial.print("FPowerData:");
	Serial.println(FPowerData);
	Serial.print("FPowerPar:");
	Serial.println(FPowerPar);
	float Power = (FPowerPar/FPowerData) * VF * CF; 
	return Power;
}

float ATOMSOCKET::GetInspectingPower()
{
	float vol = GetVol();
	float current = GetCurrent();
	return vol* current;
}

float ATOMSOCKET::GetPowerFactor()
{
	float ActivePower = GetActivePower();
	float InspectingPower = GetInspectingPower();
	return ActivePower / InspectingPower ;  
}


uint16_t ATOMSOCKET::GetPF()
{
	return PF;
}


uint32_t ATOMSOCKET::GetPFAll()
{
	return PFData * PF;
}


float ATOMSOCKET::GetKWh()
{
	float InspectingPower = GetInspectingPower(); //视在功率
	uint32_t PFcnt = (1/PowerPar) *(1/InspectingPower) * 1000000000 * 3600;
	float KWh = (PFData * PF) / PFcnt;
	return KWh;

}


bool ATOMSOCKET::Checksum()
{
	byte check = 0;
	for(byte a = 2;a<=22;a++)
	{
		check = check + SerialTemps[a];
	}
	if (check  == SerialTemps[23])
	{
		return true;
	}
	else
	{
		return false;
	}
}
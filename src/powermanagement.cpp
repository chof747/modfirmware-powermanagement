#include "powermanagement.h"

using namespace ModFirmWare;

PowerManagement::PowerManagement(int chargePin, int readyPin)
:SensorComponent(), chgPin(chargePin), rdyPin(readyPin), ina219()
//******************************************************************************
{
  initializeValues();
}

PowerManagement::PowerManagement(int chargePin, int readyPin, uint8_t addr)
:SensorComponent(), chgPin(chargePin), rdyPin(readyPin), ina219(addr)
//******************************************************************************
{
  initializeValues();
}

PowerManagement::PowerManagement(int chargePin, int readyPin, uint8_t addr, time_t updateInterval)
:SensorComponent(updateInterval), chgPin(chargePin), rdyPin(readyPin), ina219(addr)
//******************************************************************************
{
  initializeValues();
}


bool PowerManagement::setup(Application *app)
//******************************************************************************
{
  if (Component::setup(app))
  {
    ina219.begin();
    pinMode(chgPin, INPUT);
    pinMode(rdyPin, INPUT);
    return true;
  }
  else
  {
    return false;
  }
}

void PowerManagement::loop()
//******************************************************************************
{
  SensorComponent::loop();
  bool newCharging = digitalRead(chgPin);
  bool newReady = digitalRead(rdyPin);
}

bool PowerManagement::measure()
//******************************************************************************
{
  float a = ina219.getCurrent_mA();
  float p = ina219.getPower_mW();

  consumptionmAs += integrate(current, a);
  consumptionmWs += integrate(power, p);

  busVoltage = ina219.getBusVoltage_V();
  current = ina219.getCurrent_mA();
  power = ina219.getPower_mW();

  return true;
}

bool PowerManagement::isCharging()
//******************************************************************************
{
  return digitalRead(chgPin);
}

bool PowerManagement::isReady()
//******************************************************************************
{
  return digitalRead(rdyPin);
}

void ModFirmWare::PowerManagement::initializeValues()
//******************************************************************************
{
  charging = false;
  ready = false;
  
  consumptionmAs = 0;
  consumptionmWs = 0;
  busVoltage = 0;
  current = 0;
  power = 0;
}

const float PowerManagement::integrate(const float oldValue, const float newValue) const
//******************************************************************************
{
  time_t currentTime = millis();
        
  float interval = (millis() - lastUpdate) / 1000.0;
  float integral = 0.5 * (oldValue + newValue) * interval;

  return integral;
}
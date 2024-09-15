#ifndef POWERMANAGEMENT_H
#define POWERMANAGEMENT_H

#include "sensor_component.h"
#include <Arduino.h>
#include <Adafruit_INA219.h>

namespace ModFirmWare
{
  class PowerManagement : public SensorComponent
  {
  public:
    PowerManagement(int chargePin, int readyPin);
    PowerManagement(int chargePin, int readyPin, uint8_t addr);
    PowerManagement(int chargePin, int readyPin, uint8_t addr, time_t updateInterval);

    bool setup(Application *app);
    virtual bool measureContinuously() override;
    bool measure() override;

    bool isCharging();
    bool isReady();

    inline const float getBusVoltage() const { return busVoltage; }
    inline const float getCurrentmA() const { return current; }
    inline const float getCurrentA() const { return current / 1000.0; }
    inline const float getPowermW() const { return power; }
    inline const float getPowerW() const { return power / 1000.0; }
    inline const float getConsumptionmAh() const { return consumptionmAs / 3600.0; }
    inline const float getConsumptionmWh() const { return consumptionmWs / 3600.0; }

  private:

    void initializeValues();
    const float integrate(const float oldValue, const float newValue) const;

    int chgPin;
    int rdyPin;
    Adafruit_INA219 ina219;

    float busVoltage;
    float current;
    float power;
    float consumptionmAs;
    float consumptionmWs;

    bool charging;
    bool ready;
  };
};

#endif // POWERMANAGEMENT_H
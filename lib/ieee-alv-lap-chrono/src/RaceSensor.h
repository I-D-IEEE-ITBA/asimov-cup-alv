#ifndef RACESENSOR_H
#define RACESENSOR_H

#include <Arduino.h>

// Aca tengo que meter los filtros de los otros modulos
#include <EMA.h>
#include <MovingSpread.h>
#include <TimedProcess.h>
#include <Range.h>

EMA<uint8_t> ema(0.2f);
MovingSpread<uint8_t> ms(0.985f, 1.23f);
// EMA<uint8_t> bigemaSpread(0.03f);
EMA<uint8_t> emaRange(0.3f);
Range<uint8_t> range(20);
MovingSpread<uint8_t> msms(0.8f, 1.5f);

uint8_t raw = 0; // sensor value
class RaceSensor
{
private:
    uint8_t sensorPin;
    
    uint8_t output = 0;

    unsigned long lastUs=0;
    unsigned long read_interval_us = 2000;

    unsigned long lastMs=0;
    unsigned long read_interval_ms = 10;

    uint8_t _read_us()
    {

        raw = (uint8_t)(analogRead(sensorPin)/4);

        ema.write(raw); // EMA Filter with alpha = 0.5
        ms.write(ema.read());


        // Serial.write(0xFF); // Sync byte  raw, ema2, spread, emaSpread, range, msms
        // Serial.write(raw);
        // Serial.write(ema.read());
        // Serial.write(ms.read());
        // Serial.write(range.read());
        // Serial.write(emaRange.read());
    }

    uint8_t _read_ms()
    {
            range.write(ms.read());
            emaRange.write(range.read());
            msms.write(range.read());
    }

public:
    RaceSensor(uint8_t sensorPin_)
    {
        this->sensorPin = sensorPin_;
    }
    ~RaceSensor(){}

    uint8_t read()
    {
        if(lastUs - micros() >= read_interval_us)
        {
            _read_us();
            lastUs = micros();
        }
        if(lastMs - millis() >= read_interval_ms)
        {
            _read_ms();
            lastMs = millis();
        }
    }

};

#endif
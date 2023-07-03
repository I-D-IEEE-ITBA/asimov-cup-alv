#ifndef RACESENSOR_H
#define RACESENSOR_H

#include <Arduino.h>

// Aca tengo que meter los filtros de los otros modulos
#include <EMA.h>
#include <Range.h>
#include <MovingSpread.h>
#include <TMA.h>
#include <SMA.h>
#include <Schmitt.h>

#define DETECTION_DEBOUNCE_MS 1100

class RaceSensor
{
private:
    EMA<uint8_t>* bigEma = NULL;
    Range<uint8_t>* range = NULL;
    Range<uint8_t>* range2 = NULL;
    MovingSpread<uint8_t>* ms = NULL;
    MovingSpread<uint8_t>* msTma = NULL;
    SMA<uint8_t>* sma = NULL;
    Schmitt<uint8_t>* schmitt = NULL;
    uint8_t pin;
    unsigned long lastDetection = 0;

    uint8_t loopCounter = 0;
    uint8_t loopCounter2 = 0;
    uint8_t raw;
    uint8_t dif;

    uint8_t out;

    void _filter();

public:
    RaceSensor(uint8_t pin);
    ~RaceSensor();

    bool read(bool calibrationMode = false);

    void tune();
};

RaceSensor::RaceSensor(uint8_t pin)
{
    this->pin = pin;
    
    bigEma = new EMA<uint8_t>(0.002f);
    range = new Range<uint8_t>(6);
    range2 = new Range<uint8_t>(6);
    // ms = new MovingSpread<uint8_t>(0.95f, 3.0f);
    // msTma = new MovingSpread<uint8_t>(0.95f, 3.0f);
    sma = new SMA<uint8_t>(25);
    schmitt = new Schmitt<uint8_t>(20, 10);
}

RaceSensor::~RaceSensor()
{
    delete bigEma;
    delete range;
    delete range2;
    // delete ms;
    // delete msTma;
    delete sma;
    delete schmitt;
}

void RaceSensor::_filter()
{
    raw = map( constrain( analogRead(pin), 0, 1023), 0, 1023, 0, 255);
    sma->write(raw);
    // bigEma->write(sma->read());

    // dif = abs(sma->read() - bigEma->read());
    // uint8_t dif2 = (dif * dif) / 5;

    if(loopCounter++ > 8)
    {
        loopCounter = 0;
        range->write( sma->read() );
        // msRange->write(sma->read());
    }

    if(loopCounter2++ > 25)
    {
        loopCounter2 = 0;
        range2->write( range->read() );
    }

    // if(dif < 3)
    // {
    //     dif = 0;
    // }
    // ms->write( (dif * dif + range2->read()) / 20);
    out = range->read() + range2->read();
}

void RaceSensor::tune()
{
    _filter();
    
    Serial.write(0xFF); // Sync byte  raw, ema2, spread, emaSpread, range, ms
    Serial.write(7);
    Serial.write(raw);                  // 1
    Serial.write(sma->read());          // 2
    Serial.write(bigEma->read());       // 3
    Serial.write(dif);                  // 4
    Serial.write(range->read());        // 5
    Serial.write(range2->read());       // 6
    Serial.write(out);           // 7

}


bool RaceSensor::read(bool calibrationMode)
{
    _filter();
    bool sch = schmitt->filter( out );

    if( !calibrationMode && sch && (millis() - lastDetection) > DETECTION_DEBOUNCE_MS)
    {
        lastDetection = millis();
        return true;
    }

    return false;
}


#endif
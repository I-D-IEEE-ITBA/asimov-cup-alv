#include <Arduino.h>

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

TimedProcessMicros samplingProcess;
TimedProcessMillis rangeProcess;

void setup()
{
    Serial.begin(2500000);

    rangeProcess.set(10, [](){
        range.write(ms.read());
        emaRange.write(range.read());
        msms.write(range.read());
    });

    samplingProcess.set(1000, [](){
        raw = (uint8_t)(analogRead(A0)/4);

        ema.write(raw); // EMA Filter with alpha = 0.5
        ms.write(ema.read());
        // bigemaSpread.write(ms.read());

        Serial.write(0xFF); // Sync byte  raw, ema2, spread, emaSpread, range, msms
        Serial.write(raw);
        Serial.write(ema.read());
        Serial.write(ms.read());
        Serial.write(range.read());
        Serial.write(emaRange.read());
    });
}

void loop()
{
    samplingProcess.run();
    rangeProcess.run();
}

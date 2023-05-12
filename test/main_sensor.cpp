#include <Arduino.h>

#include <EMA.h>
#include <Range.h>
#include <MovingSpread.h>
#include <TMA.h>
#include <Schmitt.h>


#include <TimedProcess.h>
TimedProcessMicros samplingProcess;

#include <RaceSensor.h>
RaceSensor sensor(0);

void setup()
{
    // Serial.begin(115200);
    Serial.begin(2500000);

    samplingProcess.set(1500, [](){

        // unsigned long micros = micros();
        sensor.tune();

        // if(sensor.read())
        // {
        //     Serial.println("DETECTED");
        // }
    });
}

void loop()
{
    samplingProcess.run();
}

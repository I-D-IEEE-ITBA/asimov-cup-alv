#ifndef NUMFORM_H
#define NUMFORM_H

#include "Menu.h"

// FIXME: Esta implementacion es una ranciada pero funciona bien
// TODO: Cuando tenga tiempo y ganas, rehacer el core de la librería menu, utilizar un pre-modulo

// Must be inside a menu option
class NumForm : public Menu
{
public:
    NumForm(const char* title, unsigned int memPos);
    ~NumForm();

    void set(uint8_t v);
    uint8_t get();

    void begin(uint8_t min, uint8_t max, const char* incTit = "INC",
               const char* decTit = "DEC", const char* backTit = "atras");

    virtual void run();

private:
    
    char incStr[8];
    char decStr[8];
    uint8_t val;
    uint8_t min = 0;
    uint8_t max = 0;
    unsigned int memPos = 0;
};

inline void NumForm::set(uint8_t v)
{
    if(v >= min && v <= max)
        val = v;
}

inline uint8_t NumForm::get()
{
    return val;
}

#endif
#include "NumForm.h"
#include "EEPROM.h"

static uint8_t* numFormVal = NULL;
static uint8_t minFormVal = 0;
static uint8_t maxFormVal = 0;
static char* numFormIncStr = NULL;
static char* numFormDecStr = NULL;

static void numFormIncrement();
static void numFormDecrement();

NumForm::NumForm(const char* title, unsigned int memPos) : Menu(3, title, NULL, MENU_ACTION_JUST_EXIT)
{
    this->memPos = memPos;
}

NumForm::~NumForm()
{
}

static void numFormIncrement()
{
    if( numFormIncStr != NULL && numFormDecStr != NULL && numFormVal != NULL)
    {
        if((*numFormVal)<maxFormVal) 
            (*numFormVal)++; 

        sprintf(numFormDecStr, "DEC %u", *numFormVal);
        sprintf(numFormIncStr, "INC %u", *numFormVal);
    }
}

static void numFormDecrement()
{
    if( numFormIncStr != NULL && numFormDecStr != NULL && numFormVal != NULL)
    {
        if((*numFormVal)>minFormVal) 
            (*numFormVal)--; 

        sprintf(numFormDecStr, "DEC %u", *numFormVal);
        sprintf(numFormIncStr, "INC %u", *numFormVal);
    }
}

void NumForm::run()
{
    numFormIncStr = incStr;
    numFormDecStr = decStr;
    numFormVal = &val;
    minFormVal = min;
    maxFormVal = max;
    val = EEPROM.read(memPos);
    Menu::run();
    EEPROM.update(memPos, val);
}

void NumForm::begin(uint8_t min, uint8_t max, const char* incTit,
                    const char* decTit, const char* backTit)
{
    this->min = min;
    this->max = max;
    val = EEPROM.read(memPos);
    sprintf(incStr, "INC %u", val);
    sprintf(decStr, "DEC %u", val);

	Menu::set_option(0, incStr, numFormIncrement);
	Menu::set_option(1, decStr, numFormDecrement);
	Menu::set_option(2, backTit, menu_force_close_current );
}

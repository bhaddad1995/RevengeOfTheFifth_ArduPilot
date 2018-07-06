#include "Copter.h"
#include "UserVariables.h"

AP_HAL::AnalogSource *analog_source;
AP_Button *ap_but = AP_Button::Instance();

#ifdef USERHOOK_INIT
void Copter::userhook_init()
{
    uint8_t hook_button_pin = 15;
    analog_source = hal.analogin->channel(hook_button_pin);

    // put your initialisation code here
    // this will be called once at start-up
}
#endif

#ifdef USERHOOK_FASTLOOP
void Copter::userhook_FastLoop()
{
    // put your 100Hz code here
}
#endif

#ifdef USERHOOK_50HZLOOP
void Copter::userhook_50Hz()
{
    // put your 50Hz code here
}
#endif

#ifdef USERHOOK_MEDIUMLOOP
void Copter::userhook_MediumLoop()
{
    // put your 10Hz code here
    this->hook_raw_value = analog_source->voltage_latest();
/*    if(hook_raw_value >= 3)
        this->hook_button_state = false;
    else
        this->hook_button_state = true;*/

    ap_but->setHookVal(this->hook_raw_value);
}
#endif

#ifdef USERHOOK_SLOWLOOP
void Copter::userhook_SlowLoop()
{
    // put your 3.3Hz code here
}
#endif

#ifdef USERHOOK_SUPERSLOWLOOP
void Copter::userhook_SuperSlowLoop()
{
    // put your 1Hz code here
}
#endif

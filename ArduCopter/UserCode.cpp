#include "Copter.h"
#include "UserVariables.h"
#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_HAL/I2CDevice.h>
#include <AP_Math/AP_Math.h>
#include <stdio.h>
#include <utility>
#include <AP_HAL/utility/OwnPtr.h>

AP_HAL::AnalogSource *analog_source;
AP_Button *ap_but = AP_Button::Instance();
extern const AP_HAL::HAL &hal;
AP_HAL::Semaphore *sem;
AP_HAL::OwnPtr<AP_HAL::I2CDevice> _dev;
uint16_t _temperature;

#define BATT_TEMP_SENSE (0x18)
#define AMB_TEMP_SENSE  (0x19)

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
    float hook_raw_value = analog_source->voltage_latest();
    float hook_button_state;
    if(hook_raw_value >= 3){
        hook_button_state = 0;
    }else{
        hook_button_state = 1;
    }
    ap_but->setHookVal(hook_button_state);
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

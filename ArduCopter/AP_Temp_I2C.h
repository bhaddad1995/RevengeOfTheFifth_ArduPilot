
//#pragma once

//#include <AP_HAL/AP_HAL.h>
//#include <AP_Param/AP_Param.h>
#include <AP_HAL/utility/OwnPtr.h>
#include <AP_HAL/I2CDevice.h>
#include <utility>
#include <AP_HAL/I2CDevice.h>

//class AP_Temp_I2C {

//public:
    //AP_Temp_I2C(uint16_t sensor_loc);
    //virtual ~AP_Temp_I2C(void);

    bool temp_init(uint16_t sensor_loc);

    void get_temperature(void);

    uint16_t getTemp(void);
    //uint16_t getAmbientTemp(void);

//protected:



//private:
    void _timer();

    //uint16_t _ambient_temperature;



//};


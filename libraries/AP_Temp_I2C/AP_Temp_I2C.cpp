/*
	Temperature Sensor read code rev 1

	IN GCS_MAVLink code...
	call battTempSensor->getTemp() and ambTempSensor->getTemp();
	it returns a uint16_t
	
	
*/

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_HAL/I2CDevice.h>
#include <AP_Math/AP_Math.h>
#include <stdio.h>
#include <utility>
#include "AP_Temp_I2C.h"

extern const AP_HAL::HAL &hal;

AP_Temp_I2C::AP_Temp_I2C(){

}

bool AP_Temp_I2C::init(uint16_t sensor_loc)
{
	//Grab a device handle.
	_dev = hal.i2c_mgr->get_device(1, sensor_loc);
	
	//Set retires to 2 for runtime? maybe?
    _dev->set_retries(2);
    
	// init a 50Hz timer... I think the 20000 refers to number of microseconds.
	// 50 Hz = 20000 us.
	// If we want slower, increase this number!
    _dev->register_periodic_callback(250000,
                                     FUNCTOR_BIND_MEMBER(&AP_Temp_I2C::_timer, void));
								
	// not sure if we need this to be false or not
	 _dev->set_split_transfers(true);
	
	return true;
}

// returns temp
uint16_t AP_Temp_I2C::getTemp(void){
	return _temperature;
}

// 50 Hz timer???
void AP_Temp_I2C::_timer(void)
{
    acquireTemp();
}

void AP_Temp_I2C::acquireTemp(void)
{
    uint8_t data[2];

    uint8_t conversion_data[2];

    uint8_t tempAddress = 0x05;

    // transfer 0x05, which is the register that holds ambient temp

    if(_dev->transfer(&tempAddress, 1, data, sizeof(data))){
        conversion_data[0] = data[0] & 0x1F; // Clear alert bits
        conversion_data[1] = data[1];

    // If negative***, use this conversion

    if(conversion_data[0] & 0x10){

        conversion_data[0] = conversion_data[0] & 0x0F; // Clear SIGN bit

        //_temperature is a float!!!!
        _temperature = 256 - ( 16 * ((float) conversion_data[0]) + ((float) conversion_data[1]) / 16.0 );

        // If positive, use this one
        }else{
            //_temperature is a float!!!!
            _temperature = ( 16 * ((float) conversion_data[0]) + ((float) conversion_data[1]) / 16.0 );
        }
    }


    return;
}

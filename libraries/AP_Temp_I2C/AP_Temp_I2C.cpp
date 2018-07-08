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
	 _dev->set_split_transfers(false);
	
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
	uint16_t data;
	uint8_t tempAddress = 0x05;
	
	
	// transfer 0x05, which is the register that holds ambient temp
	if(_dev->transfer(&tempAddress, 1, (uint8_t*)&data, sizeof(data)))
		_temperature = data;
	
	
	// my first attempt at scaling temp correctly... I'll fix this once we get some actual
	//		data off the sensor
	
	//if(data & 0x1000) _temperature = -1*(data&0x0FFF);
	//else _temperature = data&0xFFF;
	
	return;
}

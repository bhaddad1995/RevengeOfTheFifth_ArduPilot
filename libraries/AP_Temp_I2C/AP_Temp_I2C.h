
#ifndef __AP_TEMP_I2C_H__
#define __AP_TEMP_I2C_H__

#include <AP_HAL/AP_HAL.h>
#include <AP_Param/AP_Param.h>
#include <AP_HAL/utility/OwnPtr.h>
#include <AP_HAL/I2CDevice.h>
#include <utility>

#define BATT_TEMP_SENSE (0x18)
#define AMB_TEMP_SENSE 	(0x19)

class AP_Temp_I2C {

public:
	AP_Temp_I2C(void);
	~AP_Temp_I2C(void);
	
	bool init(uint16_t sensor_loc);
	
	uint16_t getTemp(void);
	
protected:
	
	// Don't think I need this?
	//AP_HAL::Semaphore *sem;
	
private:
	void _timer(void);
	void acquireTemp(void);
	float _temperature;
	//uint16_t _ambient_temperature;
	AP_HAL::OwnPtr<AP_HAL::I2CDevice> _dev;
	
	
};


/*AP_Temp_I2C * batt_TempSensor;
AP_Temp_I2C * amb_TempSensor;*/

#endif

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

//#include "i2c-cpp.h"

#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

#include "HMC5983.h"

//#include "Arduino-HMC5983/HMC5983.h"


int main()
{
	hmc5983 magnetometer;
	while (!magnetometer.setup())
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	while (!magnetometer.set_mode())
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	while (!magnetometer.set_gain())
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	std::vector<float> data;

	while(true)
	{
		magnetometer.single_measurment(data);
		for (float i : data)
			std::cout << i <<" ";
		std::cout<<std::endl;
		
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
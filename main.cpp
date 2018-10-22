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
    
	hmc593 magnetometer;
    
	int length, file_i2c;
	unsigned char buffer[60] ={0};

	buffer[0] = 0x1e;
	buffer[1] = 0x3c;
	buffer[2] = 0x00;
	buffer[3] = 0x70;
	length = 4;			//<<< Number of bytes to write

		if (write(file_i2c, buffer, length) != length)	{	//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
			printf("a	Failed to write to the i2c bus.\n");
			exit(1);
		}

		buffer[0] = 0x1e;
		buffer[1] = 0x3c;
		buffer[2] = 0x01;
		buffer[3] = 0xa0;
		length = 4;			//<<< Number of bytes to write
		if (write(file_i2c, buffer, length) != length){		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
			printf("b	Failed to write to the i2c bus.\n");
			exit(1);
		}

	while(true){
		buffer[0] = 0x1e;
		buffer[1] = 0x3c;
		buffer[2] = 0x02;
		buffer[3] = 0x01;
		length = 4;			//<<< Number of bytes to write
		if (write(file_i2c, buffer, length) != length)	{	//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
			printf("c	Failed to write to the i2c bus.\n");	
			exit(1);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		buffer[0] = 0x1e;
		buffer[1] = 0x3d;
		buffer[2] = 0x06;
		length = 3;			//<<< Number of bytes to write
		if (write(file_i2c, buffer, length) != length)	{	//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
			printf("d	Failed to write to the i2c bus.\n");
			exit(1);
		}

		//----- READ BYTES -----
		length = 6;			//<<< Number of bytes to read
		if (read(file_i2c, buffer, length) != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
		{
			//ERROR HANDLING: i2c transaction failed
			printf("Failed to read from the i2c bus.\n");
		}
		else
		{
			printf("Data read: %s\n", buffer);
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
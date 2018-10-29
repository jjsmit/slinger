#include "HMC5983.h"


bool hmc5983::setup() //some init thing for i2c communication
{
    char *filename = (char*)"/dev/i2c-1";
	if ((m_file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus.\n");
		return false;
	}

    std::cout<<"opened the i2c bus\n";

	
	int addr = 0x1e;          //<<<<<The I2C address of the slave
	if (ioctl(m_file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return false;
	}
	std::cout << "did something with the HMC5983 address\n";
	return true;
}

bool hmc5983::set_mode()
{
	//single read mode
	m_buffer[0] = 0x1e;
	m_buffer[1] = 0x3c;
	m_buffer[2] = 0x00;
	m_buffer[3] = 0x70;
	m_length = 4;			//<<< Number of bytes to write

		if (write(m_file_i2c, m_buffer, m_length) != m_length)	{	//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
			printf("Failed to init 8 average, 15 Hz default, normal measurement.\n");
			return false;
		}
	return true;
}

bool hmc5983::set_gain()
{
	//sets gain to 5
	m_buffer[0] = 0x1e;
	m_buffer[1] = 0x3c;
	m_buffer[2] = 0x01;
	m_buffer[3] = 0xa0;
	m_length = 4;			//<<< Number of bytes to write
	if (write(m_file_i2c, m_buffer, m_length) != m_length){		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
		printf("Failed to set gain.\n");
		return false;
	}
	return true;
}

bool hmc5983::single_measurment(std::vector<float>& data)
{
	m_buffer[0] = 0x1e;
	m_buffer[1] = 0x3c;
	m_buffer[2] = 0x02;
	m_buffer[3] = 0x01;
	m_length = 4;			//<<< Number of bytes to write
	if (write(m_file_i2c, m_buffer, m_length) != m_length)	{	//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
		printf("Failed to set device to single single_measurment mode.\n");	
		return false;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(7));

	m_buffer[0] = 0x1e;
	m_buffer[1] = 0x3d;
	m_buffer[2] = 0x06;
	m_length = 3;			//<<< Number of bytes to write
	if (write(m_file_i2c, m_buffer, m_length) != m_length)	{	//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
		printf("Failed to ask to return measurements.\n");
		return false;
	}

	m_length = 6;			//<<< Number of bytes to read
	if (read(m_file_i2c, m_buffer, m_length) != m_length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
		return false;
	}
	else
	{
		for(int i; i<m_length;i++)
			std::cout <<m_buffer[i]<<" ";
		std::cout << std::endl;
	}	
	return true;
}

hmc5983::~hmc5983()
{

}
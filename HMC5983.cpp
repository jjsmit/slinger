#include "HMC5983.h"

hmc593::hmc593()
{
    setup();
}

void hmc593::setup()
{
    char *filename = (char*)"/dev/i2c-1";
	if ((m_file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		exit(1);
	}

    std::cout<<"opened the i2c bus\n";

	
	int addr = 0x1e;          //<<<<<The I2C address of the slave
	if (ioctl(m_file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		exit(2);
	}
	std::cout << "did something with the HMC5983 address\n";

}

hmc593::~hmc593()
{

}
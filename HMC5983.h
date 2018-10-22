#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <iostream>

#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
//#include "hmc5983.cpp"


class hmc593
{
    public:

        hmc593();
        void setup();
        std::vector<int> get_data();
        void set_mode();
        ~hmc593();

    private:
        int m_length, m_file_i2c;
        unsigned char m_buffer[60] ={0};
};
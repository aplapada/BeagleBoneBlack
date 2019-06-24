#ifndef I2C_H_
#define I2C_H_

#define I2C_PATH "/sys/class/i2c-dev/"

namespace eeroSpace {

class I2C{

private:
	unsigned int bus, device;
	//unsigned char addr;
	int file;
public:
	I2C(unsigned int bus, unsigned int device);
	virtual int open();
	virtual int write(unsigned char value);
	virtual int writeReg(unsigned char reg, unsigned char value);
	virtual unsigned char read();
	virtual unsigned char* readReg(unsigned char reg, unsigned char value);
	virtual void close();
	virtual ~I2C();
};

} //eeroSpace
#endif

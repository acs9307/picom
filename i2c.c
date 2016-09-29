#include "i2c.h"

/* Opens a file descriptor to the I2C device and relate it to a specific slave. 
 * To read or write to the file descriptor, call 'read()' and 'write()' respectively.
 * 
 * Returns:
 * 		>=0: The connected file descriptor.  Should be closed with 'close()'. 
 *		 <0: Error code. 
 *
 * Error Codes:
 * 		-1: Could not open file descriptor.
 *		-2: Could not connect to slave. */
int connectToSlaveManually(uint8_t addr, const char* i2c_device_name)
{
	int fd = open(i2c_device_name, O_RDWR);
	if(fd < 0)
		return(-1);
	
	if(ioctl(fd, I2C_SLAVE, addr) < 0)
	{
		close(fd);
		return(-2);
	}
	else
		return(fd);
}
/* Opens a file descriptor and connects to a slave device.
 * To read or write to the file descriptor, call 'read()' and 'write()' respectively.
 * 
 * Returns:
 * 		>=0: The connected file descriptor.
 *		 <0: Error code.  See 'connectToSlaveManually' for error code definition. */
int connectToSlave(uint8_t addr)
{
	const char* rev1_i2c_name = "/dev/i2c-0";
	const char* rev2_i2c_name = "/dev/i2c-1";
	
	int rev = getPiBoardRev();	
	if(rev < 0)
		return(rev);
	
	switch(rev)
	{
	case 2:
		return(connectToSlaveManually(addr, rev2_i2c_name));
	case 1:
	default:
		return(connectToSlaveManually(addr, rev1_i2c_name));
	}		
}

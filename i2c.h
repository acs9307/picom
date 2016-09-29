#ifndef I2C_IS_DEFINED
#define I2C_IS_DEFINED

#ifdef __cplusplus
extern "C"
{
#endif
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <inttypes.h>

#include "rpi.h"
#ifdef __cplusplus	
}
#endif

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
int connectToSlaveManually(uint8_t addr, const char* i2c_device_name);
/* Opens a file descriptor and connects to a slave device.
 * To read or write to the file descriptor, call 'read()' and 'write()' respectively.
 * 
 * Returns:
 * 		>=0: The connected file descriptor.
 *		 <0: Error code.  See 'connectToSlaveManually' for error code definition. */
int connectToSlave(uint8_t addr);

#endif
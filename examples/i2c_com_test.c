#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

#include "../i2c.h"


int main()
{
  int file = connectToSlave(8);
  if(file < 0)
  {
    printf("I2C: Failed to access /dev/i2c-1.\n");
    return(1);
  }
  else
    printf("I2C: Acquiring bus to %d\n", file);

  int file2 = connectToSlave(8);
  if(file2 < 0)
  {
    printf("I2C: Failed to access /dev/i2c-1.\n");
    return(1);
  }
  else
    printf("I2C: Acquiring bus to %d\n", file2);


  char buff[12] = {0};
  printf("buff before: %s\n", buff);
  printf("read: %d\n", read(file, buff, sizeof(buff) - 1));
  printf("buff: %s\n", buff);
  printf("buff[11]: %d\n", buff[11]);

  memset(buff, 0, sizeof(buff));
  read(file, buff, 1);
  read(file, buff + 1, 1);
  printf("buff: %s\n", buff);

  close(file);
  close(file2);
  return(0);
}

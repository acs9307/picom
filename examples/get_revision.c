#include "../rpi.h"
#include <stdio.h>

int main()
{
	printf("revision: %d\n", getPiBoardRev()); 
	
	return(0);
}

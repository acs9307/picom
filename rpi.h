#ifndef RPI_IS_DEFINED
#define RPI_IS_DEFINED

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#ifdef __cplusplus
}
#endif

/* Returns the revision of the board. 
 * 
 * Returns:
 * 		>=0: Verion of the board.
 * 		 <0: Error code. 
 *
 * Errors:
 *		-2: Could not open '/proc/cpuinfo'. 
 *		-3: Reading file failed. 
 *		-4: Unknown hardware. */
int getPiBoardRev ();

#endif

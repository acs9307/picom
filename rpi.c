#include "rpi.h"

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
int getPiBoardRev ()
{
	const char* dataFileName = "/proc/cpuinfo";
	const char* keyHardware = "Hardware";
	const char* keyRevision = "Revision";
	const char* supportedHardware[] = {"BCM2708", "BCM2709"};
	const char* oldRevisions[] = {"0002", "0003"};
	
	/* If we already have the revision, no need to check again. */
	static int  boardRev = -1 ;
	if (boardRev > -1)
		return boardRev ;
		
	FILE* file = NULL;
	char fileSeg[1024], *fileSegEnd = fileSeg + sizeof(fileSeg);
	size_t readCount = 0;
	char* hardwareStr = NULL;
	char* dataEnd = NULL;

	if ((file = fopen (dataFileName, "r")) == NULL)
	{
		boardRev = -2;
		goto f_return;
	}
	
	/* Search the file for 'keyHardware'. */
	while(!feof(file) && (readCount = fread(fileSeg, 1, sizeof(fileSeg), file)))
	{
		char* it = fileSeg;
		for(;it < fileSegEnd; ++it)
		{
			if(*it == *keyHardware)
			{
				memmove(fileSeg, it, fileSegEnd - it);
				readCount = fileSegEnd - it;
				memset(fileSeg + readCount, 0, sizeof(fileSeg) - readCount);
				if(!feof(file))
					readCount += fread(fileSeg + (fileSegEnd - it), 1, sizeof(fileSeg) - readCount, file);
				
				if(readCount > sizeof(keyHardware))
				{					
					if(strncmp(fileSeg, keyHardware, sizeof(keyHardware) - 1) == 0)
					{
						it = fileSeg;
						
						/* Find the colon. */
						while(it < fileSegEnd && *it != ':' && *it != '\n')
							++it;						
						while(it < fileSegEnd && !isalnum(*it) && *it != '\n')
							++it;
						if(it < fileSegEnd && *it != '\n')
						{
							hardwareStr = it;
							break;
						}
					}
				}				
			}
		}
		if(it < fileSegEnd)
			break;
	}
	if(readCount == 0)
	{
		boardRev = -3;
		goto f_return;
	}

	/* Check the hardware versions and make sure we support them. */
	if(strncmp(hardwareStr, supportedHardware[1], sizeof( supportedHardware[1]) - 1) == 0)
	{
		/* This is RaspberryPi 2, we know that it uses revision 2. */
		boardRev = 2;
		goto f_return;
	}
	if(strncmp(hardwareStr, supportedHardware[0], sizeof(supportedHardware[0]) - 1) != 0)
	{
		boardRev = -4;
		goto f_return;
	}

	/* Search for the revision keywords. */
	rewind(file);
	while(!feof(file) && (readCount = fread(fileSeg, 1, sizeof(fileSeg), file)))
	{
		char* it = fileSeg;
		for(;it < fileSegEnd; ++it)
		{
			if(*it == *keyRevision)
			{
				memmove(fileSeg, it, fileSegEnd - it);
				readCount = fileSegEnd - it;
				memset(fileSeg + readCount, 0, sizeof(fileSeg) - readCount);
				if(!feof(file))
					readCount += fread(fileSeg + (fileSegEnd - it), 1, sizeof(fileSeg) - readCount, file);
				
				if(readCount > sizeof(keyRevision))
				{					
					if(strncmp(fileSeg, keyRevision, sizeof(keyRevision) - 1) == 0)
					{
						it = fileSeg;
						
						/* Find the colon. */
						while(it < fileSegEnd && *it != ':' && *it != '\n')
							++it;						
						while(it < fileSegEnd && !isalnum(*it) && *it != '\n')
							++it;
						if(it < fileSegEnd && *it != '\n')
						{
							hardwareStr = it;
							break;
						}
					}
				}				
			}
		}
		if(it < fileSegEnd)
			break;
	}
	if(readCount == 0)
	{
		boardRev = -3;
		goto f_return;
	}

	/* Read to the end of the data. */
	dataEnd = hardwareStr;
	while(dataEnd > fileSegEnd && isxdigit(*dataEnd))
		++dataEnd;
	hardwareStr = dataEnd - 4;
	if(strncmp(hardwareStr, oldRevisions[0], sizeof(oldRevisions[0]) - 1) == 0 || 
		strncmp(hardwareStr, oldRevisions[1], sizeof(oldRevisions[1]) - 1) == 0)
		boardRev = 1;
	else
		boardRev = 2;
	
f_return:
	/* Cleanup. */
	if(file)
		fclose(file);
	
	return(boardRev);
}

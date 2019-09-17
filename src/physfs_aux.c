#include <stdio.h>
#include <string.h>
#include "physfs.h"

extern int addArchive(const char* fileName)
{
	if (!PHYSFS_isInit())
	{
		if (!PHYSFS_init("."))
		{
			printf("PHYSFS_init() failed!\n  reason: %s.\n", PHYSFS_getLastError());
			return 0;
		}
	}
	return PHYSFS_mount(fileName, NULL, 0);
}

int addArchiveWithAppend(const char* fileName, int appending)
{
	if (!PHYSFS_isInit())
	{
		if (!PHYSFS_init("."))
		{
			printf("PHYSFS_init() failed!\n  reason: %s.\n", PHYSFS_getLastError());
			return 0;
		}
	}
	return PHYSFS_mount(fileName, NULL, appending);
}

extern int getFileSize(const char* fileName)
{
	PHYSFS_File* f = PHYSFS_openRead(fileName);
    if (f == 0)
	{
		printf("open read faile");
		return 0;
	}

	return PHYSFS_fileLength(f);
}

extern char* readFile(char* fileName, int* psize)
{
	PHYSFS_File* f = PHYSFS_openRead(fileName);
    if (f == 0)
	{
		printf("open read faile");
		return NULL;
	}

	PHYSFS_sint64 len = PHYSFS_fileLength(f);
	*psize = len;
	char buffer[len];

	PHYSFS_sint64 rc;
	rc = PHYSFS_readBytes(f, buffer, sizeof(buffer));

	if (rc <= sizeof(buffer))
	{
		if (!PHYSFS_eof(f))
		{
			printf("\n (Error condition in reading. Reason: [%s])\n\n",
				   PHYSFS_getLastError());
		}
		PHYSFS_close(f);

		// TODO: free it
    	const PHYSFS_Allocator *allocator = PHYSFS_getAllocator();
		char*ret = (char*)allocator->Malloc(len);
		memcpy(ret, buffer, len);

		return ret;
	}

	return NULL;
}
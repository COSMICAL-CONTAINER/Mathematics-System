#include <stdio.h>
#include <stdlib.h>
#include "memmanager.h"

Memmanager_struct Mem;

void MemWarning(char *msg)
{
    printf("%s\n", msg);
}

void MemError(char *msg)
{
    printf("%s\n", msg);
    exit(-1);
}

void MemManagerInit(size_t maxsize)
{
    if(maxsize > INIT_MAX_POOL_NUM)
    {
        MemError((char *)"MAXSIZE is too large!");
    }
    Mem.ObjectPooLMaxSize = maxsize;
    Mem.ObjectPooLUsedSize = 0;
    Mem.ObjectNodeSpace = (ObjectNode **)calloc(maxsize, sizeof(ObjectNode));
}

void MemManagerFree()
{
    for(int i = 0 ; i < Mem.ObjectPooLUsedSize; ++i)
    {
        if(Mem.ObjectNodeSpace[i]->_Memory != NULL)
        {
            Mem.ObjectNodeSpace[i]->mem_free(Mem.ObjectNodeSpace[i]->_Memory);
        }
    }
}

void MemManagerDestory()
{
    MemManagerFree();
    
}

#ifndef __Memmanager_H__
#define __Memmanager_H__

#define INIT_MAX_POOL_NUM 100

typedef enum __Memmanager_malloc
{
    //M -> methods
    M_malloc,
    M_calloc,
    M_realloc,
}Memmanager_enum;

typedef struct
{
    void *_Memory;
    void (*mem_new)(size_t _NumOfElements, size_t _SizeOfElements, Memmanager_enum Method);
    void (*mem_free)(void *);
}ObjectNode;

typedef struct __Memmanager
{
    size_t      ObjectPooLMaxSize;
    size_t      ObjectPooLUsedSize;
    ObjectNode  **ObjectNodeSpace;       //指向线程结点数组的指针
}Memmanager_struct;

typedef struct __Memmanager* Memmanager;

void MemWarning(char *msg);
void MemError(char *msg);
void MemManagerInit(size_t MAXSIZE);

void MemManagerDestory();

#endif
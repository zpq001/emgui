#ifndef __GUI_CORE_MEMORY_H_
#define __GUI_CORE_MEMORY_H_

#include <stdint.h>
#include <stddef.h>     // using size_t
#include "guiConfig.h"

void *guiCore_malloc(size_t wantedSize);
void *guiCore_calloc(size_t wantedSize);
size_t guiCore_GetFreeHeapSize(void);


#endif

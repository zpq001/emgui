/**********************************************************
    Module guiCoreMemory

    GUI core memory management functions

**********************************************************/

#include <stdint.h>
#include <string.h>     // using memset
#include "guiConfig.h"
#include "guiCore.h"
#include "guiCoreMemory.h"


// Inspired by freeRTOS heap1


#define emGUI_BYTE_ALIGNMENT_MASK ( emGUI_BYTE_ALIGNMENT - 1 )
// A few bytes might be lost to byte aligning the heap start address
#define emGUI_ADJUSTED_HEAP_SIZE	( emGUI_HEAP_SIZE - emGUI_BYTE_ALIGNMENT )

static unsigned char gui_heap[emGUI_HEAP_SIZE];
static size_t allocated_bytes_count = (size_t) 0;


void *guiCore_malloc(size_t wantedSize)
{
    static unsigned char *p_heap = 0;
    void *result = 0;

    // Make sure blocks are aligned
    #if emGUI_BYTE_ALIGNMENT != 1
        if (wantedSize & emGUI_BYTE_ALIGNMENT_MASK)
        {
            // Adjust allocated block size
            wantedSize += (emGUI_BYTE_ALIGNMENT - (wantedSize & emGUI_BYTE_ALIGNMENT_MASK));
        }
    #endif

    if (p_heap == 0)
    {
        p_heap = (unsigned char *)(((emGUI_POINTER_SIZE_TYPE)&gui_heap[emGUI_BYTE_ALIGNMENT_MASK]) & ((emGUI_POINTER_SIZE_TYPE) ~emGUI_BYTE_ALIGNMENT_MASK));
    }

    // Check if there is enough space
    if( ( ( allocated_bytes_count + wantedSize ) < emGUI_ADJUSTED_HEAP_SIZE ) &&
        ( ( allocated_bytes_count + wantedSize ) > allocated_bytes_count )	)   // Check for overflow
    {
        // Return the next free byte then increment the index past this block
        result = p_heap + allocated_bytes_count;
        allocated_bytes_count += wantedSize;
    }

    if (result == 0)
    {
        // Trace error
        guiCore_Error(emGUI_ERROR_OUT_OF_HEAP);
    }
    return result;
}


void *guiCore_calloc(size_t wantedSize)
{
    void *result = guiCore_malloc(wantedSize);
    if (result)
    {
        memset(result, 0, wantedSize);
    }
    return result;
}


size_t guiCore_GetFreeHeapSize(void)
{
    return ( emGUI_ADJUSTED_HEAP_SIZE - allocated_bytes_count );
}


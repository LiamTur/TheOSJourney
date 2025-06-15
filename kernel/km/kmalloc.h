#ifndef KMALLOC_H
#define KMALLOC_H

#include <stdint.h>

void *kmalloc(uint32_t size);
void *kmalloc_aligned(uint32_t size, uint32_t alignment);

#endif

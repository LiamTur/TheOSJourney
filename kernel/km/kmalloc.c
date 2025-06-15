#include "kmalloc.h"

extern uint32_t end;
static uint32_t placement_address = (uint32_t)&end;

void *kmalloc(uint32_t size) {
	uint32_t addr = placement_address;
	placement_address += size;
	return (void *)addr;
}

void *kmalloc_aligned(uint32_t size, uint32_t alignment) {
	if ((placement_address & (alignment - 1)) != 0) {
	placement_address &= ~(alignment - 1);
	placement_address += alignment;
	}

	uint32_t addr = placement_address;
	placement_address += size;
	return (void *)addr;
}

#pragma once

#include <stdint.h>
#include "../../thread/thread.h"

void context_switch(thread_t *current, thread_t *next);


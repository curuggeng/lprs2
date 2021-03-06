#include "kola_rgb333.h"

uint16_t kola__w = 32;
uint16_t kola__h = 32;
uint16_t kola__p[] = {
	0x0ff, 0x0ff, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x004, 0x004, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x0ff, 0x0ff, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x007, 0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x004, 0x004, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x1c0, 0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x0ff, 0x0ff, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x007, 0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x004, 0x004, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x1c0, 0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x1ff, 0x1ff, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x007, 0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x1ff, 0x1ff, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x1c0, 0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x1ff, 0x1ff, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x1c0, 0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x1ff, 0x1ff, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x007, 0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x0ff, 0x0ff, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x1c0, 0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x004, 0x004, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x007, 0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x0ff, 0x0ff, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x1c0, 0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x004, 0x004, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x007, 0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x0ff, 0x0ff, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x004, 0x004, 0x1ff, 0x000, 0x000, 0x000, 0x000, 0x1ff,
	0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x0ff, 0x0ff,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x004, 0x004,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x0ff, 0x0ff,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x004, 0x004,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x0ff, 0x0ff,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x004, 0x004,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x007, 0x007,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x007, 0x007,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x007, 0x007,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x007, 0x007,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x0ff, 0x0ff,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x004, 0x004,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x0ff, 0x0ff,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x004, 0x004,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x0ff, 0x0ff,
	0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007, 0x007,
	0x007, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x007, 0x004, 0x004,
	0x0f7, 0x0ff, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x004, 0x004, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x0f7, 0x0ff, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x004, 0x004, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x0f7, 0x0ff, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x004, 0x004, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x038, 0x038, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x038, 0x038, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x038, 0x038, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x038, 0x038, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x0f7, 0x0ff, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x004, 0x004, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x0f7, 0x0ff, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x004, 0x004, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x0f7, 0x0ff, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x004, 0x004, 0x038, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x038,
	0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038, 0x038,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x0ff, 0x0ff,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x004, 0x004,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x0ff, 0x0ff,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x004, 0x004,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x0ff, 0x0ff,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x004, 0x004,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x0ff, 0x0ff,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x004, 0x004,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x0ff, 0x0ff,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x004, 0x004,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x0ff, 0x0ff,
	0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0, 0x1c0,
	0x1c0, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1c0, 0x004, 0x004
};

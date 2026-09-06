#pragma once

#include <nds.h>

struct i3 {
	size_t x, y;
};

typedef uint16_t col_t;

extern col_t *vga;
extern const size_t vga_len;
extern int tick;

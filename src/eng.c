#include <nds.h>
#include "eng.h"

col_t *vga = VRAM_A;
const size_t vga_len = SCREEN_WIDTH * SCREEN_HEIGHT;
int tick;

void main(void)
{
	videoSetMode(MODE_FB0);
	vramSetBankA(VRAM_A_LCD);

	videoSetModeSub(MODE_5_2D);
	vramSetBankB(VRAM_B_LCD);

	lcdMainOnBottom();

	for (int i = 0; i < vga_len; i++) {
		vga[i] = 0;
		VRAM_B[i] = 0;
	}

	srand(time(NULL));

	setup();

	for (;;) {
		swiWaitForVBlank();

		loop();

		tick++;
	}
}

int rnd(int n)
{
	return rand() % n;
}

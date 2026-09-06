#include <nds.h>
#include "eng.h"

col_t *vga = VRAM_A;
const size_t vga_len = SCREEN_WIDTH * SCREEN_HEIGHT;
int tick;

void main(void)
{
	videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE);
	vramSetBankC(VRAM_C_SUB_BG);
	PrintConsole bs;
	consoleInit(&bs, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);

	videoSetMode(MODE_FB0);
	vramSetBankA(VRAM_A_LCD);

	for (int i = 0; i < vga_len; i++)
		vga[i] = RGB15(5, 5, 5);

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

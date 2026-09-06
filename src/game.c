#include <nds.h>
#include <stdbool.h>
#include "eng.h"

#define TICK_SPEED 5

#define W 32
#define H 26

const int LEN = W * H;

const int CW = SCREEN_WIDTH / W;
const int CH = SCREEN_WIDTH / H;

bool grid[W * H];

static void
fill(col_t *begin)
{
	col_t *end = begin + CW;

	for (int j = 0; j < CH; j++) {
		for (col_t *p = begin; p < end; p++)
			*p = -1;

		begin += SCREEN_WIDTH;
		end += SCREEN_WIDTH;
	}
}

void setup(void)
{
	for (int i = 0; i < LEN; i++)
		grid[i] = rnd(2);
}

void loop(void)
{
	for (int i = 0; i < vga_len; i++)
		vga[i] = 0;

	for (int j = 0; j < H; j++)
		for (int i = 0; i < W; i++)
			if (grid[i + j * W])
				fill(&vga[j * CH * SCREEN_WIDTH + i * CW]);

	if (tick % TICK_SPEED != 0)
		return;

	/* GAME OF LIFE */

	bool next_grid[LEN];

	for (int j = 0; j < H; j++) {
		for (int i = 0; i < W; i++) {
			int neighbors = 0;

			for (int dj = -1; dj <= 1; dj++) {
				for (int di = -1; di <= 1; di++) {
					if (di == 0 && dj == 0)
						continue;

					int ni = (i + di + W) % W;
					int nj = (j + dj + H) % H;

					if (grid[ni + nj * W])
						neighbors++;
				}
			}

			bool alive = grid[i + j * W];
			next_grid[i + j * W] = (neighbors == 3) || (alive && neighbors == 2);
		}
	}

	for (int i = 0; i < LEN; i++)
		grid[i] = next_grid[i];
}

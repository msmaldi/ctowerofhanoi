#include <stdio.h>

#include "towerofhanoi.h"

void
human_move_generator (const HanoiBase *game, TowerOption *src, TowerOption *dst)
{
	do
	{
		printf ("Enter a move:\n");
		char buffer[256];
		scanf ("%s", buffer);
		*src = buffer[0] - 'a';
		*dst = buffer[1] - 'a';
	}
	while (!toh_hanoibase_can_move (game, *src, *dst));
}

void
humam_play_new_game (HanoiBase *game)
{
	toh_hanoibase_gameplay (game, human_move_generator);
}
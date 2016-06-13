#include <stdio.h>

#include "towerofhanoi.h"
#include "hanoihumanplayer.h"

int
main(int argc, char *argv[])
{
	HanoiBase *game = toh_hanoibase_new (3);
	
	humam_play_new_game (game);
		
	toh_hanoibase_free (game);

	return 0;
}

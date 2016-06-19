#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "towerofhanoi.h"

Tower
toh_tower_new (int count)
{
	Tower tower;
	tower.disks = (int*)malloc (sizeof(int) * count);
	tower.disk_count = 0;
		
	return tower;
}

Tower
toh_tower_new_with_disks (int count)
{
	Tower tower = toh_tower_new (count);
	tower.disk_count = count;
	
	int disk = 1;	
	while (--count >= 0)
		tower.disks[count] = disk++;
	
	return tower;
}

void
toh_tower_free (const Tower *this)
{
	free(this->disks);
}

HanoiBase*
toh_hanoibase_new (int disks)
{
	HanoiBase *this = (HanoiBase*)malloc (sizeof(HanoiBase));
	this->tower[A] = toh_tower_new_with_disks (disks);
	this->tower[B] = toh_tower_new (disks);
	this->tower[C] = toh_tower_new (disks);
	
	this->count = disks;
		
	return this;
}

void
toh_hanoibase_free (HanoiBase* this)
{
	toh_tower_free (&this->tower[A]);
	toh_tower_free (&this->tower[B]);
	toh_tower_free (&this->tower[C]);
	
	free (this);
}

void
toh_hanoibase_print (const HanoiBase* this)
{
	int i;
	for (i = this->count - 1; i >= 0; i--)
		printf("%d\t%d\t%d\n", this->tower[A].disks[i], this->tower[B].disks[i], this->tower[C].disks[i]);
}

int
toh_tower_peek_disk (const Tower *tower)
{
	if (tower->disk_count == 0)
		return INT_MAX;
	
	return tower->disks[tower->disk_count - 1];
}

int
toh_tower_pop_disk (Tower *tower)
{
	tower->disk_count -= 1;
	int result = tower->disks[tower->disk_count];
	tower->disks[tower->disk_count] = 0;
	return result;
}

void
toh_tower_push_disk (Tower *tower, int disk)
{
	tower->disks[tower->disk_count] = disk;
	tower->disk_count += 1;
}

void
toh_tower_move (Tower *tower_src, Tower *tower_dst)
{
  int disk_src = toh_tower_pop_disk (tower_src);
	toh_tower_push_disk (tower_dst, disk_src);
}

bool
toh_hanoibase_can_move (const HanoiBase *this, TowerOption src, TowerOption dst)
{
	if (src == dst)
		return false;
	
	if (src != A && src != B && src != C)
		return false;
		
	if (dst != A && dst != B && dst != C)
		return false;
	
	int disk_src = toh_tower_peek_disk (&this->tower[src]);
	int disk_dst = toh_tower_peek_disk (&this->tower[dst]);
	if (disk_src >= disk_dst)
		return false;
	
	return true;
}

bool
toh_hanoibase_make_move (HanoiBase *this, TowerOption src, TowerOption dst)
{
	if (toh_hanoibase_can_move (this, src, dst))
	{		
		toh_tower_move (&this->tower[src], &this->tower[dst]);
		return true;
	}
	return false;
}

bool
toh_hanoibase_is_finished (const HanoiBase *this)
{
	if (this->tower[B].disk_count == this->count || this->tower[C].disk_count == this->count)
		return true;
	return false;
}

void
toh_hanoibase_gameplay (HanoiBase *game, 
												void (*move_generator) (const HanoiBase *this, TowerOption *src, TowerOption *dst))
{
	int total_moves = 0;

	while (!toh_hanoibase_is_finished (game))
	{
		printf("Total moviments %d\n", total_moves++);
		toh_hanoibase_print (game);

		TowerOption src, dst;
		move_generator (game, &src, &dst);

		if (!toh_hanoibase_make_move (game, src, dst))
			printf ("Invalid move.\n");
	}

	toh_hanoibase_print (game);
	printf ("You win with %d moviments.\n", total_moves);
}
#ifndef TOWEROFHANOI_H
#define TOWEROFHANOI_H

#include <stdbool.h>

typedef enum
{
	A, B, C
} TowerOption;

typedef struct
{
	int disk_count;
	int *disks;
} Tower;

typedef struct 
{
	Tower tower[3];
	int count;	
} HanoiBase;

Tower					toh_tower_new							(int count);
Tower					toh_tower_new_with_disks	(int count);
void					toh_tower_free						(const Tower *this);

HanoiBase*		toh_hanoibase_new					(int disks);
void					toh_hanoibase_free				(HanoiBase *this);
void					toh_hanoibase_print				(const HanoiBase *this);

bool					toh_hanoibase_can_move		(const HanoiBase *this, TowerOption src, TowerOption dst);
bool					toh_hanoibase_make_move		(HanoiBase *this, TowerOption src, TowerOption dst);

bool					toh_hanoibase_is_finished (const HanoiBase *this);

void					toh_hanoibase_gameplay		(HanoiBase *this, 
																				 void (*move_generator) (const HanoiBase *game, TowerOption *src, TowerOption *dst));

#endif
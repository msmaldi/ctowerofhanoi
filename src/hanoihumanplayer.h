#ifndef HANOIHUMANPLAYER_H
#define HANOIHUMANPLAYER_H

#include "towerofhanoi.h"

void          human_move_generator  (const HanoiBase *game, TowerOption *src, TowerOption *dst);
void          humam_play_new_game   (HanoiBase *game);

#endif
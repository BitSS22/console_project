#pragma once

#include "Entity.h"

void EntityWait();
void EntityMove(IntVec2& position, IntVec2 entity_direction, Direction move_direction, int length);
void EntityTurn(IntVec2& direction, IntVec2Rotate rotate);
void SpawnEntity(IntVec2& position, IntVec2 direction, char id);
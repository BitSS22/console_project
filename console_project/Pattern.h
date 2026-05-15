#pragma once

#include "Entity.h"

void EntityWait();
void EntityMove(IntVec2& position, IntVec2& direction, IntVec2 vector);
void EnemyAttack(Enemy& data, AttackType attack);
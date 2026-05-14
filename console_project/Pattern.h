#pragma once

#include "Enemy.h"

void EnemyWait();
void EnemyMove(Enemy& data, IntVec2 vector);
void EnemyAttack(Enemy& data, AttackType attack);
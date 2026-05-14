#include "Pattern.h"
#include "LogHelper.h"

void EnemyWait()
{
	return;
}

void EnemyMove(Enemy& data, IntVec2 vector)
{
	if (vector.x == 0 && vector.y == 0)
	{
		Log("Enemy move function called by Zero Vector.\n");
		return;
	}

	data.position += vector;
	data.direction = GetDirection(vector);
}

void EnemyAttack(IntVec2 spawnPosition, IntVec2 direction, char bullet)
{
	
}

#include "Pattern.h"
#include "LogHelper.h"

void EntityWait()
{
	return;
}

void EntityMove(IntVec2& position, IntVec2& direction, IntVec2 vector)
{
	if (vector.x == 0 && vector.y == 0)
	{
		Log("Enemy move function called by Zero Vector.\n");
		return;
	}

	position += vector;
	direction = GetDirection(vector);
}

void SpawnEntity(IntVec2& position, IntVec2 direction, ObjectType object_type, char id, size_t current_pattern_index = 0)
{
	// TODO. entity을 찾아 가져온다.
	// object type 정의 pool에서 id를 검색하고, id가 존재하지 않는다면 에러.
	// 찾았다면 패턴 정의를 가져오고, 생성한 entity를 적절한 컨테이너에서 활성화.

	Entity entity;
	entity.id = id;
	entity.enable = true;
	entity.object_type = object_type;
	entity.position = position;
	entity.direction = direction;
	entity.pattern = 
	entity.current_pattern_index = current_pattern_index;
	


}

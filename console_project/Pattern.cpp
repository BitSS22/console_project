#include "Pattern.h"
#include "LogHelper.h"
#include "structs.h"
#include "ConsoleDatas.h"

void EntityWait()
{
	return;
}

void EntityMove(IntVec2& position, IntVec2 entity_direction, Direction move_direction, int length)
{
	if (length == 0)
	{
		Log("EntityMove function called, length argument is zero.\n");
		return;
	}

	IntVec2Rotate rotate = IntVec2Rotate::C0;

	switch (move_direction)
	{
	case Direction::FORWARD:
		rotate = IntVec2Rotate::C0;
		break;
	case Direction::RIGHT:
		rotate = IntVec2Rotate::C90;
		break;
	case Direction::BACK:
		rotate = IntVec2Rotate::C180;
		break;
	case Direction::LEFT:
		rotate = IntVec2Rotate::C270;
		break;
	default:
		Log("EntityMove function called, direction argument is invalid.\n");
		break;
	}

	position += IntVec2::Rotate(entity_direction, rotate) * length;
}

void EntityTurn(IntVec2& direction, IntVec2Rotate rotate)
{
	direction = IntVec2::Rotate(direction, rotate);
}

void SpawnEntity(IntVec2& position, IntVec2 direction, char id)
{
	// 설계

	// 이 함수 내에서 적절한 위치의 index를 찾을 것인가?
	// 아니면 직접 적절한 index를 넣을 것인가?
	// 두가지 다 가능하게 만들 것인가?
	// 아니면 그냥 함수 없이 알아서 하던지.



	//// TODO. entity을 찾아 가져온다.
	//// object type 정의 pool에서 id를 검색하고, id가 존재하지 않는다면 에러.
	//// 찾았다면 패턴 정의를 가져오고, 생성한 entity를 적절한 컨테이너에서 활성화.
	//auto iter = entity_datas.find(id);
	//if (iter == entity_datas.end())
	//{
	//	Log("SpawnEntity Function Error. Not found entity id. id:", id, ".\n");
	//	return;
	//}

	//const EntityData& find_data = iter->second;

	//Entity new_entity;
	//new_entity.id = id;
	//new_entity.enable = true;
	//new_entity.object_type = find_data.object_type;
	//new_entity.position = position;
	//new_entity.direction = direction == IntVec2::ZERO() ? find_data.default_direction : direction;
	//new_entity.pattern = find_data.pattern;
	//new_entity.instruct_iterator = 0;
	


}

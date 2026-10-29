#include <iostream>
using namespace std;


// 인벤토리 시스템 -> 완?
// 장비 시스템
// 아이템 시스템


// 플레이어의 인벤토리(장비 슬롯, 일반 슬롯 포함) 테이블이 존재한다.
// 장비만을 저장하는 고유한 테이블이 존재한다.
// 일반 아이템을 저장하는 고유한 테이블이 존재한다. 


// 몬스터는 죽을 때 장비를 떨어뜨린다.
// 플레이어는 장비를 착용할 수 있다.


// 인벤토리에는 장비를 착용하는 슬롯과 아이템을 저장하는 슬롯이 개별로 있다


// 아이템 조합 시스템 보류
// 스킬은 보류
// 아이템 크기 시스템, 무게 시스템 보류

enum CHRACTER_NUMBER
{
	KNIGHT = 1,
	ARCHOR,
	MAGE
};

enum MONSTER_NUMBER
{
	SKELETON = 1,
	SLIME,
	ORC
};

enum LOBBY_STATE
{
	LOBBY_CHOOSECHARACTER = 1,
	LOBBY_TOWN,
	LOBBY_GAMEEXIT
};

enum TOWN_STATE
{
	TOWN_FIELD = 1,
	TOWN_LOBBY
};

enum FIELD_STATE
{
	FIELD_FIGHT = 1,
	FIELD_SEARCH,
	FIELD_TOWN,
};

enum ITEM_NUMBER
{
	BOTTOM_ITEM = 0,
	MID_ITEM,
	HIGH_ITEM
};

enum WEAPON_NUMBER
{
	LONG_SWORD = 100,
	GOOD_ARROW,
	GOOD_WAND,
};

enum ARMOR_NUMBER
{
	BOTTOM_ARMOR = 200,
	MID_ARMOR,
	HIGH_ARMOR,
};

enum ITEM_TYPE
{
	ITEM = 0,
	WEAPON,
	ARMOR

};

// Item의 기본 정보를 담고있는 구조체
struct ItemInfo
{
	// 인벤토리에 저장하기 위해서는 ID가 있어야할까
	char name[64] = {};
	int id = -1;
	int price = 0;
	int type = -1; 
	int att = 0;
	int hp = 0;
	int def = 0;
};

//// 장비(무기, 방어구 등)의 기본 정보를 담고있는 구조체
//struct WeaponInfo : ItemInfo
//{
//	// 유형별로 착용 가능하도록 해야함. 즉 타입이 필요함
//	int att;
//};
//
//struct ArmorInfo : ItemInfo
//{
//	int hp;
//	int def;
//};

// 스택과 힙의 차이를 알아야한다.
// 스택은 함수가 끝나면 자동으로 사라짐..
// 힙은 프로그래머가 delete 하기전에 계속 남아있음. 하지만 주소만 들고 다닐 수 있다 ! 즉 메모리 절약.
struct InventorySlot
{
	ItemInfo item;
	int count = 0;

};

// 장신구나 다른 개념들 보류 

// padding = 16 + 4 + 4 + 4 + 4 + 4 + 4= 40
struct CreatureInfo
{
	char name[16] = {};
	int exp = 0;
	int level = 1;
	int type = 0;
	int hp = 0;
	int att = 0;
	int def = 0;
};

// 이미 아이템 테이블이 있는데 굳이 또 아이템을 통쨰로 상속받는 이유가 있을까 ?
// 드롭 아이템은 어떤 아이템을 드롭할지에 대한 id와, 확률뿐. 나머지는 아이템 테이블에서 직접 찾는다.
struct DropItem
{
	int itemId = -1;
	int dropRate = 0;
};

struct PlayerInfo : CreatureInfo
{
	// 초기화 하지 않아도 내가 의도한 값으로 이미 채워져있음
	InventorySlot inventory[10][10];
};

struct MonsterInfo : CreatureInfo
{
	DropItem dropTable[5];
	int dropCount = 0;
};

// 생성자를 배우면 가장 먼저 해결해야할 부분들중에 하나
// 뭐가 뭘 가리키는지 알아보기가 너무 힘들다.

// 초기 몬스터 스탯 테이블(설계도)
const MonsterInfo monsterStatTable[] =
{
	{ "해골", 50, 1, MONSTER_NUMBER::SKELETON, 80, 15, 5, 
		{
			{ WEAPON_NUMBER::LONG_SWORD, 15},
			{ WEAPON_NUMBER::GOOD_ARROW, 20},
		}, 2
	},
	{ "슬라임", 80, 1, MONSTER_NUMBER::SLIME, 100, 10, 8,
		{
			{ ITEM_NUMBER::BOTTOM_ITEM, 10},
			{ ITEM_NUMBER::MID_ITEM, 5}
		}, 2
	},
	{ "오크", 110, 1, MONSTER_NUMBER::ORC, 120, 11, 10,
		{
			{ ITEM_NUMBER::BOTTOM_ITEM, 20 },
			{ ITEM_NUMBER::MID_ITEM, 15 },
			{ ITEM_NUMBER::HIGH_ITEM, 10 }
		}, 3
	}
};
	

// 변수가 만들어지는 생성 시점에 초기화(중괄호 초기화)
// 

// 초기 플레이어 스탯 테이블(설계도)
const PlayerInfo playerStatTable[] =
{
	{ "기사", 0, 1, 1, 150, 15, 10, {}, },
	{ "아처", 0, 1, 2, 120, 21, 7, {},  },
	{ "마법사", 0, 1, 3, 100, 25, 5, {}, }
};



// 아이템 테이블 
const ItemInfo itemTable[] =
{
	{"물건1", 0, 50, ITEM_TYPE::ITEM , 0, 0, 0},
	{"물건2", 1, 100, ITEM_TYPE::ITEM, 0, 0, 0},
	{"물건3", 2, 150, ITEM_TYPE::ITEM, 0, 0, 0},

	{ "장검", WEAPON_NUMBER::LONG_SWORD, 100, ITEM_TYPE::WEAPON, 5, 0, 0 },
	{ "좋은 활", WEAPON_NUMBER::GOOD_ARROW, 100, ITEM_TYPE::WEAPON, 7, 0, 0 },
	{ "좋은 지팡이", WEAPON_NUMBER::GOOD_WAND, 100,ITEM_TYPE::WEAPON, 7, 0, 0 },

	{ "방어구1", ARMOR_NUMBER::BOTTOM_ARMOR, 100, ITEM_TYPE::ARMOR, 0, 10, 5 },
	{ "방어구2", ARMOR_NUMBER::MID_ARMOR, 200, ITEM_TYPE::ARMOR, 0, 15, 10 },
	{ "방어구3", ARMOR_NUMBER::HIGH_ARMOR, 300, ITEM_TYPE::ARMOR, 0, 20, 15 }
};

bool exitGame = false;
bool isMadeCharacter = false;
bool isPlayerDead = false;

void CreateMonster(MonsterInfo* monsterInfo);
void GenerateCharacter(PlayerInfo* playerInfo);
void ChooseCharacter(PlayerInfo* playerInfo);

void CheckDropItem(PlayerInfo* playerInfo, MonsterInfo* monsterInfo);

void FightMonster(PlayerInfo* playerInfo, MonsterInfo* monsterInfo);
void EnterField(PlayerInfo* playerInfo);
void EnterTown(PlayerInfo* playerInfo);



// Helper Function
const ItemInfo GetItemInfo(int itemId);
int GetPlayerMaxHP(PlayerInfo* playerInfo);
int GetCurrentMaxExp(int playerLevel) { return playerLevel * 100; };
//void CleanInventoryData(PlayerInfo* playerInfo);
const int GetMonsterDropItemId(const MonsterInfo* monsterInfo);
void CalculateLevelUpStat(PlayerInfo* playerInfo);


// 자식 구조체는 더 덩치가 크다.
// 즉 큰 애를 작은애로 반환하니까.. 잘릴 수 있음. 실제로 잘림.
const ItemInfo GetItemInfo(int itemId)
{
	for (int i = 0; i < sizeof(itemTable) / sizeof(itemTable[0]); i++)
	{
		// 일반 아이템
		if (itemId >= 0 && itemId < 100)
		{
			if (itemId == itemTable[i].id)
				return itemTable[i];
		}
		// 무기
		else if (itemId >= 100 && itemId < 200)
		{
			if (itemId == itemTable[i].id)
				return itemTable[i];
		}
		// 방어구
		else if (itemId >= 200 && itemId < 300)
		{
			if (itemId == itemTable[i].id)
				return itemTable[i];
		}
	}
	return ItemInfo{};
}
int GetPlayerMaxHP(PlayerInfo* playerInfo)
{
	int baseHp = playerStatTable[playerInfo->type - 1].hp;
	float growthRate = (playerInfo->level - 1) * 0.3f;
	return baseHp + (int)(baseHp * growthRate);
};

const int GetMonsterDropItemId(const MonsterInfo* monsterInfo)
{
	// 드롭 테이블의 dropRate에는 확률이 들어가있다.
	int randomRate = 1 + (rand() % 100);

	// 확률 누적
	int accumulateRate = 0;
	
	// 드롭 테이블을 순회하기
	for (int i = 0; i < monsterInfo->dropCount; i++)
	{
		// 개별 독립 시행 방식
		//{
		//		// 1부터 100까지의 경우의 수
		//		int randomRate = 1 + (rand() % 100);
		//
		//		// 0부터 100까지의 경우안에서, 15라는 숫자보다 작거나 같은 경우는 총 15개다. 즉 15%의 확률을 가진다.
		//		if (randomRate <= monsterInfo->droptable[i].dropRate)
		//		{
		//			// return말고 인벤토리에 넣어야한다.
		//			// 매개변수로 배열을 넘겨주거나.. 해야할 듯
		//		} 
		//}
		
		// 가중치 선택 방식
		{
			accumulateRate += monsterInfo->dropTable[i].dropRate;

			if (randomRate <= accumulateRate)
			{
				return monsterInfo->dropTable[i].itemId;
			}
		}
	}

	// 아무것도 없는 경우
	return -1;
}

// 마스터 테이블을 그대로 긁어와야하는 문제.

// 아이템 타입 분리
void CheckDropItem(PlayerInfo* playerInfo, MonsterInfo* monsterInfo)
{
	// 포인터 크기는 고정, 구조체 크기는 데이터 통쨰로
	// 몬스터 드롭 테이블에서 아이템 한개의 id를 뽑아온다.
	const int droppedItemId = GetMonsterDropItemId(monsterInfo);

	if (droppedItemId == -1) return;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			// 빈 슬롯인 경우에는 그냥 추가
			if (playerInfo->inventory[i][j].item.id == -1)
			{
				playerInfo->inventory[i][j].item = GetItemInfo(droppedItemId);
				playerInfo->inventory[i][j].count = 1;

				cout << "---------------------------------" << endl;
				cout << playerInfo->inventory[i][j].item.name << " 아이템을 흭득했다 !" << endl;
				cout << "---------------------------------" << endl;

				return;
			}
			// 이미 존재하는 아이템이라면 개수 추가
			else if (playerInfo->inventory[i][j].item.id == droppedItemId)
			{
				playerInfo->inventory[i][j].count += 1;

				cout << "---------------------------------" << endl;
				cout << playerInfo->inventory[i][j].item.name << " 아이템을 추가 흭득했다 !" << endl;
				cout << "현재 해당 아이템 개수 : " << playerInfo->inventory[i][j].count << "개" << endl;
				cout << "---------------------------------" << endl;

				return;
			}
		}
	}
}

void CreateMonster(MonsterInfo* monsterInfo)
{
	int monsterType = monsterInfo->type;
	monsterType = 1 + (rand() % 3);

	// 몬스터 유형별 스탯 설정
	*monsterInfo = monsterStatTable[monsterType - 1];

	cout << "---------------------------------" << endl;
	cout << monsterInfo->name << " 몬스터가 나타났다 ! " << endl;
	cout << "Level : " << monsterInfo->level << endl;
	cout << "Exp   : " << monsterInfo->exp << endl;
	cout << "HP    : " << monsterInfo->hp << endl;
	cout << "ATT   : " << monsterInfo->att << endl;
	cout << "DEF   : " << monsterInfo->def << endl;

	
}

// 캐릭터 유형에 따라 스탯 배분
void GenerateChracter(PlayerInfo* playerInfo)
{
	int playerType = playerInfo->type;

	int tempInput;
	while (!isMadeCharacter)
	{
		// 플레이어 유형별 스탯 설정
		PlayerInfo tempInfo = playerStatTable[playerType - 1];

		cout << "캐릭터 선택을 확정하시겠습니까 ?(확정 이후 중도 변경할 수 없습니다)" << endl << endl;
		cout << "---------------------------------" << endl;
		cout << "유형 : " << tempInfo.name << endl;
		cout << "체력 : " << tempInfo.hp << endl;
		cout << "공격력 : " << tempInfo.att << endl;
		cout << "방어력 : " << tempInfo.def << endl;
		cout << "---------------------------------" << endl;
		cout << "(1) 확정하기 (2) 변경하기" << endl;
		cout << ">";

		cin >> tempInput;

		switch (tempInput)
		{
		case 1:
			// 임시 데이터를 원본 데이터로 복사
			*playerInfo = tempInfo;
			// 인벤토리 데이터 초기화
			//CleanInventoryData(playerInfo);
			isMadeCharacter = true;
			break;
		case 2:
			cout << "처음 상태로 되돌아갑니다." << endl << endl;
			return;
		default:
			cout << "잘못된 번호입니다. 다시 선택해주세요" << endl;
			continue;

		}

	}
}
// 캐릭터 선택
void ChooseCharacter(PlayerInfo* playerInfo)
{
	if (playerInfo->type != -1)
		playerInfo->type = -1;

	while (!isMadeCharacter)
	{
		int input;
		cout << "---------------------------------" << endl;
		cout << "환영합니다 ! 게임에 처음 입장하셨네요" << endl << endl;
		cout << "본인의 캐릭터를 생성해주세요 !" << endl;
		cout << "---------------------------------" << endl;
		cout << "직업을 선택해주세요 ! " << endl << endl;
		cout << "(1) 기사 (2) 궁수 (3) 법사" << endl;
		cout << "---------------------------------" << endl;
		cout << ">";

		cin >> input;

		if (input >= 1 && input <= 3)
		{
			playerInfo->type = input;
			GenerateChracter(playerInfo);
		}
		else
		{
			cout << "잘못된 번호입니다. 다시 선택해주세요. " << endl << endl;
			continue;
		}
	}
	cout << "---------------------------------" << endl;
	cout << "캐릭터 선택이 완료되었습니다 !" << endl << endl;
	cout << "광장으로 자동 이동됩니다. " << endl;
	cout << "---------------------------------" << endl;
}



// 몬스터와 전투
void FightMonster(PlayerInfo* playerInfo, MonsterInfo* monsterInfo)
{
	short playerType = playerInfo->type;

	while (true)
	{
		cout << "몬스터 남은 체력 : " << monsterInfo->hp << endl;
		cout << "플레이어 남은 체력 : " << playerInfo->hp << endl;

		int playerDamage = (playerInfo->att - monsterInfo->def);

		if (playerDamage <= 0)
			playerDamage = 1;

		monsterInfo->hp -= playerDamage;


		// 어떤 몬스터 고유의 아이템 드롭 확률을 통해 특정 아이템을 골라내고. 그걸 플레이어 인벤토리 빈자리에 넣는 로직

		// 몬스터가 죽은 경우
		if (monsterInfo->hp <= 0)
		{
			cout << "몬스터를 처치했습니다!" << endl;
			playerInfo->exp += monsterInfo->exp;

			// 드롭 아이템 확인
			CheckDropItem(playerInfo, monsterInfo);

			// 레벨업 하는 경우
			while (playerInfo->exp >= GetCurrentMaxExp(playerInfo->level))
			{

				// 현재 경험치에서 최대 경험치를 뺌.
				playerInfo->exp -= GetCurrentMaxExp(playerInfo->level);
				CalculateLevelUpStat(playerInfo);
				cout << "---------------------------------" << endl;
				cout << "플레이어 레벨업 !" << endl << endl;
				cout << "기본 스탯이 강해졌습니다 ! " << endl;
				cout << "---------------------------------" << endl;
			}
			break;
		}
		int monsterDamage = (monsterInfo->att - playerInfo->def);
		if (monsterDamage <= 0)
			monsterDamage = 1;

		playerInfo->hp -= monsterDamage;

		if (playerInfo->hp <= 0)
		{
			// 죽었을 때의 패널티?
			// 경험치 감소, 레벨 감소 등

			cout << "플레이어는 사망했습니다. 광장으로 리스폰됩니다. " << endl << endl;
			isPlayerDead = true;
			break;
		}
	}
}

// 레벨업 구현
void CalculateLevelUpStat(PlayerInfo* playerInfo)
{
	short playerType = playerInfo->type - 1;

	// 플레이어 레벨업(레벨업을 한 이후의 
	playerInfo->level += 1;

	// 체력을 최대치로 채우며 최대 체력도 증가
	playerInfo->hp = GetPlayerMaxHP(playerInfo);
	playerInfo->att += (int)(playerStatTable[playerType].att * 0.2f);
	playerInfo->def += (int)(playerStatTable[playerType].def * 0.2f);
}


// 필드 
// - 몬스터와 전투
// - 광장 이동
// - 추후 추가 예정
void EnterField(PlayerInfo* playerInfo)
{
	bool exitField = false;
	while (isPlayerDead == false && exitField == false)
	{
		MonsterInfo monsterInfo;
		cout << "---------------------------------" << endl;;
		cout << "필드에 입장했습니다!" << endl << endl;
		cout << "필드에서는 몬스터를 처치할 수 있습니다." << endl;
		cout << "---------------------------------" << endl;

		cout << "[PLAYER]" << endl;
		cout << "Name  : " << playerInfo->name << endl;
		cout << "Level : " << playerInfo->level << endl;
		cout << "Exp   : " << playerInfo->exp << endl;
		cout << "HP    : " << playerInfo->hp << endl;
		cout << "ATT   : " << playerInfo->att << endl;
		cout << "DEF   : " << playerInfo->def << endl;

		CreateMonster(&monsterInfo);

		cout << "(1) 전투 하기 (2) 몬스터 재탐색 (3) 광장으로 이동" << endl;
		cout << "> ";

		int input;
		cin >> input;

		switch (input)
		{
		case FIELD_STATE::FIELD_FIGHT:
			FightMonster(playerInfo, &monsterInfo);
			break;

		case FIELD_STATE::FIELD_SEARCH:
			cout << "몬스터를 재탐색 하는중입니다.." << endl;
			continue;

		case FIELD_STATE::FIELD_TOWN:
			cout << "광장으로 이동합니다 !" << endl;
			exitField = true;
			break;
		}
	}
}

// 광장
// - 전투 필드 이동
// - 추후 추가 예정
void EnterTown(PlayerInfo* playerInfo)
{
	bool exitLobby = false;
	while (!exitLobby)
	{
		if (playerInfo != nullptr && isPlayerDead)
		{
			cout << "플레이어의 체력이 회복되었습니다 ! " << endl;
			playerInfo->hp = GetPlayerMaxHP(playerInfo);
			isPlayerDead = false;
		}

		cout << "---------------------------------" << endl;
		cout << "광장에 오신걸 환영합니다 !" << endl << endl;
		cout << "원하시는 행동을 선택해주세요." << endl;
		cout << "---------------------------------" << endl;
		cout << "(1) 필드 입장 (2) 로비로 이동" << endl;
		cout << ">";

		int input;
		cin >> input;

		switch (input)
		{
		case TOWN_STATE::TOWN_FIELD:
			cout << "필드로 이동합니다." << endl;
			EnterField(playerInfo);
			break;
		case TOWN_STATE::TOWN_LOBBY:
			cout << "로비로 이동합니다." << endl;
			exitLobby = true;
			break;
		default:
			cout << "잘못된 번호입니다. 다시 선택해주세요. " << endl;
			continue;
		}
	}
}
int main()
{
	srand((unsigned int)time(0));
	PlayerInfo player;

	int input;
	// 포인터로 하면 원본 데이터 자체를 그냥 가져온다는 문제. 위험함.
	// WeaponInfo wepaon123 = weaponTable[0];
	// inventory[0][0].pnum = &weaponTable[0];

	while (!exitGame)
	{
		cout << "---------------------------------" << endl;
		cout << "게임 로비에 오신걸 환영합니다 !" << endl << endl;
		cout << "원하시는 행동을 선택해주세요." << endl;
		cout << "---------------------------------" << endl;
		cout << "(1) 캐릭터 생성 (2) 광장 이동 (3) 게임 종료" << endl;
		cout << ">";

		cin >> input;

		switch (input)
		{
		case LOBBY_STATE::LOBBY_CHOOSECHARACTER:
			if (isMadeCharacter)
			{
				cout << "이미 생성된 캐릭터가 있습니다 !" << endl << endl;
				cout << "광장으로 이동해주세요. " << endl;
				break;
			}
			ChooseCharacter(&player);
			break;

		case LOBBY_STATE::LOBBY_TOWN:
			if (!isMadeCharacter)
			{
				cout << "현재 생성된 캐릭터가 없습니다." << endl << endl;
				cout << "캐릭터를 먼저 생성해주세요." << endl;
				break;
			}
			EnterTown(&player);
			break;
		case LOBBY_STATE::LOBBY_GAMEEXIT:
			cout << "게임을 종료합니다." << endl;
			exitGame = true;
			break;
		default:
			cout << "잘못된 번호입니다. 다시 선택해주세요" << endl;
			continue;
		}

	}
	return 0;
}

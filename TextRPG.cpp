#include <iostream>
using namespace std;

// 장비 시스템

// 장비 시스템 추가해야함
// 장비 장착 시스템 !
// 상점 시스템 구현
// 인벤토리 매니저 구현

// 플레이어는 장비를 착용할 수 있다.

// 인벤토리에는 장비를 착용하는 슬롯과 아이템을 저장하는 슬롯이 개별로 있다

// 광장 -> 상점
// 광장 -> 필드
// 광장 -> 내 상태 보기

// 상점
// - 아이템 리스트 전부 출력
// - 번호로 구매.
// -- 개수 지정
// --- 지정한 아이템 임시값으로 받아온 뒤 count 증가
// --- 장비라면.. 지정한 개수만큼 인벤토리 슬롯 채우기?


// 내 상태보기
// - 캐릭터 스탯 확인
// - 인벤토리 확인
// - 현재 장비 확인
// 인벤토리 - 장비 기능
// - 현재 인벤토리 확인 
// -- 현재 착용중인 장비 리스트
// -- 보유중인 아이템 리스트?

// 인벤토리 슬롯 번호 입력 ?
// 장비를 장착하시겠습니까?
// 장비를 교체하시겠습니까?

// 상점은 나중에. 장비 먼저 ㄱㄱ

// 아이템 리스트 완

// 장비 장착 해제 기능
// 인벤토리 아이템 버리기(삭제).. 일단 이정도? 위치 교체는 굳이?
// 상점(아이템 구매(개수 지정 구매), 판매(?))
// 판매는 가격을 가진다..
// 플레이어한테 현재 돈을 나타내는 속성 만들기. 돈은 상점에서 확인 가능. 몬스터는 돈을 드롭하지않음. 아이템 팔아서 돈벌기


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
	TOWN_MYROOM,
	TOWN_SHOP,
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

enum ARMOR_HELMET_NUMBER
{
	BOTTOM_HELMET = 200,
	MID_HELMET,
	HIGH_HELMET,
};
enum ARMOR_CHEST_NUMBER
{
	BOTTOM_CHEST = 300,
	MID_CHEST,
	HIGH_CHEST,
};
enum ARMOR_GAUNTLETS_NUMBER
{
	BOTTOM_GAUNTLETS = 400,
	MID_GAUNTLETS,
	HIGH_GAUNTLETS,
};
enum ARMOR_LEGGINGS_NUMBER
{
	BOTTOM_LEGGINGS = 500,
	MID_LEGGINGS,
	HIGH_LEGGINGS,
};
enum ARMOR_BOOTS_NUMBER
{
	BOTTOM_BOOTS = 600,
	MID_BOOTS,
	HIGH_BOOTS,
};

enum ITEM_TYPE
{
	ITEM = 0,
	WEAPON = 1,
};

enum ARMOR_TYPE
{
	HELMET = 2,
	CHEST,
	GAUNTLETS,
	LEGGINGS,
	BOOTS
};


// Item의 기본 정보를 담고있는 구조체
struct ItemInfo
{
	char name[64] = {};
	int instanceId = -1;
	int id = -1;
	int price = 0;
	int type = -1; 
	int att = 0;
	int hp = 0;
	int def = 0;
	bool stackable = true;
	bool hasShop = false;
};

struct InventorySlot
{
	ItemInfo item;
	int count = 0;
};

// 장신구나 다른 개념들 보류
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
	// 초기화 하더라도 0으로 밀지않음. 내가 의도한 값으로 채워져있음
	InventorySlot inventory[10][10] = {};

	// 장착한 장비의 정보?
	ItemInfo equipmentList[6] = {};

	// 플레이어가 가진 돈
	int money = 0;
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

// 초기 플레이어 스탯 테이블(설계도)
const PlayerInfo playerStatTable[] =
{
	{ "기사", 0, 1, 1, 150, 15, 10,{},{} },
	{ "아처", 0, 1, 2, 120, 21, 7,{},{} },
	{ "마법사", 0, 1, 3, 100, 25, 5,{},{} }
};


// 아이템 테이블 
// 상점은 아이템 테이블의 이름을 전부 보여주는 기능
// 그중 선택하면 복사본을 플레이어 자리에 놓기
const ItemInfo itemTable[] =
{
	{"물건1", -1, 0, 50, ITEM_TYPE::ITEM , 0, 0, 0, true, true},
	{"물건2", -1, 1, 100, ITEM_TYPE::ITEM, 0, 0, 0, true, true},
	{"물건3", -1, 2, 150, ITEM_TYPE::ITEM, 0, 0, 0, true, true},

	{ "장검", -1, WEAPON_NUMBER::LONG_SWORD, 100, ITEM_TYPE::WEAPON, 5, 0, 0, false, true},
	{ "좋은 활", -1, WEAPON_NUMBER::GOOD_ARROW, 100, ITEM_TYPE::WEAPON, 7, 0, 0, false, true},
	{ "좋은 지팡이", -1, WEAPON_NUMBER::GOOD_WAND, 100,ITEM_TYPE::WEAPON, 7, 0, 0, false, false},

	{ "헬멧 방어구", -1, ARMOR_HELMET_NUMBER::BOTTOM_HELMET, 100, ARMOR_TYPE::HELMET, 0, 10, 5, false, true},
	{ "갑옷 방어구", -1, ARMOR_CHEST_NUMBER::BOTTOM_CHEST, 100, ARMOR_TYPE::CHEST, 0, 15, 5, false, true},
	{ "팔목 방어구", -1, ARMOR_GAUNTLETS_NUMBER::BOTTOM_GAUNTLETS, 100, ARMOR_TYPE::GAUNTLETS, 0, 10, 5, false, true},
	{ "바지 방어구", -1, ARMOR_LEGGINGS_NUMBER::BOTTOM_LEGGINGS, 100, ARMOR_TYPE::LEGGINGS, 0, 15, 5, false, true},
	{ "신발 방어구", -1, ARMOR_BOOTS_NUMBER::BOTTOM_BOOTS, 100, ARMOR_TYPE::BOOTS, 0, 10, 5, false, true}
};

int newInstanceID = 0;

bool exitGame = false;
bool isMadeCharacter = false;
bool isPlayerDead = false;





// 전방 선언

// Helper Function
ItemInfo GetItemInfo(int itemId);


// Main Branch
void ChooseCharacter(PlayerInfo* playerInfo);
void GenerateCharacter(PlayerInfo* playerInfo);
void EnterTown(PlayerInfo* playerInfo);

// Town Branch
void EnterField(PlayerInfo* playerInfo);
void EnterMyRoom(PlayerInfo* playerInfo);
void EnterShop(PlayerInfo* playerInfo);

// Field Branch
void CreateMonster(MonsterInfo* monsterInfo);
void FightMonster(PlayerInfo* playerInfo, MonsterInfo* monsterInfo);
// Field Helper
void CalculateLevelUpStat(PlayerInfo* playerInfo);
void CheckDropItem(PlayerInfo* playerInfo, MonsterInfo* monsterInfo);
int GetPlayerMaxHP(PlayerInfo* playerInfo);
int GetMonsterDropItemId(const MonsterInfo* monsterInfo);
int GetCurrentMaxExp(int playerLevel) { return playerLevel * 100; };

// MyRoom Branch
void CheckPlayerInventoryItem(PlayerInfo* playerInfo);
void CheckPlayerEquipment(PlayerInfo* playerInfo);
void CheckPlayerStat(PlayerInfo* playerInfo);

// MyRoom Helper
// -- Inventory & Stat
void CheckInventoryItemInfo(PlayerInfo* playerInfo, int itemIndex);
void CheckInventoryItemPosition(PlayerInfo* playerInfo, int oldIndex, int newIndex, int itemCount);
void CleanInventoryItem(ItemInfo* item);
void ChangeItemPosition(ItemInfo* oldItem, ItemInfo* newItem);
bool CanStack(const ItemInfo& item) { return item.stackable; }
// -- Equipment
void EquipArmor(PlayerInfo* playerInfo, int itemIndex);
void UnEquipArmor(PlayerInfo* playerInfo, int equipmentIndex);
void CheckChangeEquipment(PlayerInfo* playerInfo, ItemInfo* oldItem, ItemInfo* newItem);
void ChangeEquipment(PlayerInfo* playerInfo, ItemInfo* oldItem, ItemInfo* newItem);
void CheckCurrentEquipmentInfo(ItemInfo equipment);

// Shop Branch
void EnterItemBuyingState(PlayerInfo* playerInfo);
void EnterItemSellingState(PlayerInfo* playerInfo);
// Shop Helper
void BuyItemToShop(PlayerInfo* playerInfo, int realIndex, int buyCount);
void SellItemToShop(PlayerInfo* playerInfo, int realIndex, int sellCount);


// 구현부

// Helper Function
ItemInfo GetItemInfo(int itemId)
{
	for (int i = 0; i < sizeof(itemTable) / sizeof(itemTable[0]); i++)
	{
		if (itemId == itemTable[i].id)
			return itemTable[i];
	}
	return ItemInfo{};
}




// Main Branch
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
			GenerateCharacter(playerInfo);
		}
		else
		{
			cout << "잘못된 번호입니다. 다시 선택해주세요. " << endl << endl;
			continue;
		}
	}
	cout << "---------------------------------" << endl;
	cout << "캐릭터 선택이 완료되었습니다 !" << endl << endl;
	cout << "로비로 자동 이동됩니다. " << endl;
	cout << "---------------------------------" << endl;
}
void GenerateCharacter(PlayerInfo* playerInfo)
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
		cout << "(1) 필드 입장 (2) 개인룹 이동 (3) 상점 이동 (4) 로비로 이동" << endl;
		cout << ">";

		int input;
		cin >> input;

		switch (input)
		{
		case TOWN_STATE::TOWN_FIELD:
			cout << "필드로 이동합니다." << endl;
			EnterField(playerInfo);
			break;
		case TOWN_STATE::TOWN_MYROOM:
			cout << "개인룸으로 이동합니다." << endl;
			EnterMyRoom(playerInfo);
			break;
		case TOWN_STATE::TOWN_SHOP:
			cout << "상점으로 이동합니다." << endl;
			EnterShop(playerInfo);
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

// Town Branch
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
void EnterMyRoom(PlayerInfo* playerInfo)
{
	bool exitMyRoom = false;
	while (!exitMyRoom)
	{
		cout << "---------------------------------" << endl;
		cout << "개인룸에 오신걸 환영합니다 !" << endl << endl;
		cout << "확인하고싶은 부분을 선택해주세요." << endl;
		cout << "---------------------------------" << endl;
		cout << "(1) 현재 장비 확인 (2) 인벤토리 확인 (3) 내 스탯 확인 (4) 광장 이동" << endl;
		cout << ">";

		int input;
		cin >> input;

		switch (input)
		{
		case 1:
			// 현재 장비를 확인한다.
			CheckPlayerEquipment(playerInfo);
			break;
		case 2:
			// 현재 인벤토리 확인한다.
			CheckPlayerInventoryItem(playerInfo);
			break;
		case 3:
			// 현재 플레이어의 스탯을 확인한다.
			CheckPlayerStat(playerInfo);
			break;
		case 4:
			// 광장으로 이동한다.
			cout << "광장으로 이동합니다" << endl;
			exitMyRoom = true;
			break;
		default:
			cout << "잘못된 번호입니다. 다시 선택해주세요. " << endl;
			continue;
		}

	}

}
void EnterShop(PlayerInfo* playerInfo)
{
	bool exitShop = false;

	while (!exitShop)
	{
		cout << "---------------------------------" << endl;
		cout << "상점에 오신걸 환영합니다 !" << endl << endl;
		cout << "상점에서는 돈으로 아이템을 구매하거나, 아이템을 판매하여 돈을 얻을 수 있습니다. " << endl;
		cout << "현재 소유한 금액 : " << playerInfo->money << "원" << endl;
		cout << "원하시는 행동을 선택해주세요" << endl;
		cout << "---------------------------------" << endl;
		cout << "(1) 구매하기 (2) 판매하기 (3) 나가기" << endl;
		cout << ">";

		int input;
		cin >> input;

		switch (input)
		{
		case 1:
			// 구매하기
			EnterItemBuyingState(playerInfo);
			break;
		case 2:
			// 판매하기
			EnterItemSellingState(playerInfo);
			break;
		case 3:
			cout << "광장으로 돌아갑니다." << endl;
			exitShop = true;
			break;
		}
	}

}

// Field Branch
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
// Field Helper
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
			// 인벤토리에 드롭된 아이템이 이미 존재하고 드롭된 아이템이 스택이 가능한경우
			if (playerInfo->inventory[i][j].item.id == droppedItemId && CanStack(GetItemInfo(droppedItemId)) == true)
			{
				playerInfo->inventory[i][j].count += 1;

				cout << "---------------------------------" << endl;
				cout << playerInfo->inventory[i][j].item.name << " 아이템을 추가 흭득했다 !" << endl;
				cout << "현재 해당 아이템 개수 : " << playerInfo->inventory[i][j].count << "개" << endl;
				cout << "---------------------------------" << endl;

				return;
			}
			// 빈 슬롯인 경우
			else if(playerInfo->inventory[i][j].item.id == -1)
			{
				playerInfo->inventory[i][j].item = GetItemInfo(droppedItemId);
				// 스택이 불가능한 경우에만 고유한 ID 부여
				if (CanStack(playerInfo->inventory[i][j].item) == false)
					playerInfo->inventory[i][j].item.instanceId = newInstanceID++;

				playerInfo->inventory[i][j].count = 1;

				cout << "---------------------------------" << endl;
				cout << playerInfo->inventory[i][j].item.name << " 아이템을 흭득했다 !" << endl;
				cout << "---------------------------------" << endl;

				return;
			}
		}
	}
	// 다 돌았는데 빈 슬롯이 없는 경우
	cout << "빈 슬롯이 없어 장비를 추가할 수 없습니다 !" << endl;
}
int GetPlayerMaxHP(PlayerInfo* playerInfo)
{
	int baseHp = playerStatTable[playerInfo->type - 1].hp;
	float growthRate = (playerInfo->level - 1) * 0.3f;
	return baseHp + (int)(baseHp * growthRate);
};
int GetMonsterDropItemId(const MonsterInfo* monsterInfo)
{
	// 드롭 테이블의 dropRate에는 확률이 들어가있다.
	int randomRate = 1 + (rand() % 100);

	// 확률 누적
	int accumulateRate = 0;

	// 드롭 테이블을 순회하기
	for (int i = 0; i < monsterInfo->dropCount; i++)
	{
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

// MyRoom Branch
void CheckPlayerInventoryItem(PlayerInfo* playerInfo)
{
	bool exitCheckInventoryState = false;
	while (!exitCheckInventoryState)
	{
		cout << "---------------------------------" << endl;
		cout << "현재 플레이어의 인벤토리를 확인 할 수 있습니다." << endl << endl;
		cout << "---------------------------------" << endl;

		int count = 0;
		int itemMap[100] = {};
		bool noneItem = true;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (playerInfo->inventory[i][j].item.id == -1)
				{
					cout << "[" << ++count << "] " << "빈 슬롯 " << "\t";
					continue;
				}
				if (playerInfo->inventory[i][j].item.id != -1)
				{
					// 아이템이 없는지 체크용
					if (noneItem)
						noneItem = false;

					cout << "[" << ++count << "] " << playerInfo->inventory[i][j].item.name << "\t";
					itemMap[count] = ((i * 10) + j);
				}

			}
			cout << endl << endl;
		}
		if (noneItem)
		{
			cout << "---------------------------------" << endl;
			cout << "아이템이 없습니다 ! 아이템을 먼저 흭득해주세요. " << endl;
			cout << "---------------------------------" << endl;
			return;
		}

		cout << "---------------------------------" << endl;
		cout << "아이템을 선택하여 정보를 확인할 수 있습니다." << endl;
		cout << "아이템을 선택하시겠습니까 ?" << endl;
		cout << "(1) 예 (2) 아니요" << endl;
		cout << "---------------------------------" << endl;
		cout << ">";


		int input;
		cin >> input;

		switch (input)
		{
		case 1:
		{
			// 여기 있는 인벤토리를 기준으로 선택.
			// 분기점
			// 아이템 상세 정보 확인(갯수 확인하기?)
			cout << "---------------------------------" << endl;
			cout << "아이템을 선택하여 정보를 확인할 수 있습니다." << endl;
			cout << "아이템 번호를 선택해주세요 !" << endl;
			cout << "---------------------------------" << endl;
			cout << ">";

			int itemIndex;
			cin >> itemIndex;

			int realIndex = itemMap[itemIndex];

			while (!exitCheckInventoryState)
			{
				cout << "---------------------------------" << endl;
				cout << "아이템 번호를 선택하셨습니다. 어떻게 하시겠습니까 ?" << endl;
				cout << "(1) 상세 정보 확인 (2) 아이템 위치 변경 (3) 아이템 버리기 (4) 아무것도 하지 않기" << endl;
				cout << "---------------------------------" << endl;
				cout << ">";

				int input;
				cin >> input;

				// 상세 정보 확인
				// 아이템 위치 변경
				// 아이템 버리기 정도
				switch (input)
				{
					// 상세 정보 확인
				case 1:
					CheckInventoryItemInfo(playerInfo, realIndex);
					break;
					// 아이템 위치 변경
				case 2:
				{
					int moveItemCount = -1;
					// 개수가 한 개를 초과하는 경우
					if (playerInfo->inventory[realIndex / 10][realIndex % 10].count > 1)
					{
						while (moveItemCount <= 0)
						{
							cout << "---------------------------------" << endl;;
							cout << "이동하려는 아이템의 총 개수가 " << playerInfo->inventory[realIndex / 10][realIndex % 10].count << "개 입니다" << endl;
							cout << "몇 개를 이동시키시겠습니까 ?" << endl;
							cout << "---------------------------------" << endl;
							cout << ">";
							int count;
							cin >> count;

							if (count <= 0)
							{
								cout << "잘못된 번호입니다. 다시 입력해주세요. " << endl;
								continue;
							}
							else if (count > playerInfo->inventory[realIndex / 10][realIndex % 10].count)
							{
								cout << "현재 가지고있는 수량보다 많은 개수의 아이템을 이동시킬 수 없습니다. 다시 입력해주세요." << endl;
								continue;
							}
							moveItemCount = count;
						}
					}

					cout << "---------------------------------" << endl;
					cout << "선택한 아이템을 몇 번으로 이동시키시겠습니까 ?" << endl;
					cout << "선택한 아이템의 번호 : " << itemIndex << endl;
					cout << "---------------------------------" << endl;

					int count = 0;
					int itemMap[100] = {};
					bool noneItem = true;
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							if (playerInfo->inventory[i][j].item.id == -1)
							{
								cout << "[" << ++count << "] " << "빈 슬롯 " << "\t";
								continue;
							}
							if (playerInfo->inventory[i][j].item.id != -1)
							{
								// 아이템이 없는지 체크용
								if (noneItem)
									noneItem = false;

								cout << "[" << ++count << "] " << playerInfo->inventory[i][j].item.name << "\t";
								itemMap[count] = ((i * 10) + j);
							}

						}
						cout << endl << endl;
					}
					// 아이템 리스트가 쫙 펼쳐진상황.
					cout << ">";
					int posIndex;
					cin >> posIndex;
					int newIndex = itemMap[posIndex];

					cout << "---------------------------------" << endl;
					cout << "이전 위치 번호: " << itemIndex << endl;
					cout << "신규 위치 번호: " << posIndex << endl;
					cout << "이동 시키시겠습니까 ?(이 선택은 되돌릴 수 없습니다)" << endl;
					cout << "(1) 예 (2) 아니요" << endl;
					cout << "---------------------------------" << endl;

					int posModifyChoice;
					cin >> posModifyChoice;

					if (posModifyChoice == 1)
					{
						CheckInventoryItemPosition(playerInfo, realIndex, newIndex, moveItemCount);
					}
					else if (posModifyChoice == 2)
					{
						cout << "이전으로 돌아갑니다." << endl;
						continue;
					}
					else
					{
						cout << "잘못된 번호입니다. 이전으로 돌아갑니다. " << endl;
						continue;
					}
				}
				break;
				// 아이템 버리기
				case 3:
					cout << "---------------------------------" << endl;
					cout << "선택한 아이템을 버리시겠습니까 ? (이 선택은 되돌릴 수 없습니다)" << endl;
					cout << "(1) 예 (2) 아니요" << endl;
					cout << "---------------------------------" << endl;

					int deleteChoice;
					cin >> deleteChoice;

					if (deleteChoice == 1)
					{
						CleanInventoryItem(&playerInfo->inventory[realIndex / 10][realIndex % 10].item);
					}
					else if (deleteChoice == 2)
					{
						cout << "이전으로 돌아갑니다." << endl;
						continue;
					}
					else
					{
						cout << "잘못된 번호입니다. 이전으로 돌아갑니다. " << endl;
						continue;
					}
					break;

					// 아무것도 하지 않기(되돌아가기)
				case 4:
					cout << "개인룸으로 되돌아갑니다." << endl;
					exitCheckInventoryState = true;
					break;
				}
			}
		}
		break;
		case 2:
			cout << "개인룸으로 되돌아갑니다." << endl;
			exitCheckInventoryState = true;
			break;
		}
	}
}
void CheckPlayerStat(PlayerInfo* playerInfo)
{
	cout << "현재 플레이어의 스탯을 확인할 수 있습니다." << endl << endl;
	cout << "---------------------------------" << endl;

	cout << "[PLAYER]" << endl;
	cout << "Name  : " << playerInfo->name << endl << endl;

	cout << "Level : " << playerInfo->level << endl;
	cout << "Exp   : " << playerInfo->exp << endl;
	cout << "HP    : " << playerInfo->hp << endl;
	cout << "ATT   : " << playerInfo->att << endl;
	cout << "DEF   : " << playerInfo->def << endl;
}
void CheckPlayerEquipment(PlayerInfo* playerInfo)
{
	bool exitEquipState = false;
	while (!exitEquipState)
	{
		cout << "---------------------------------" << endl;
		cout << "현재 플레이어가 장착한 장비를 확인하는 공간입니다." << endl;
		cout << "기존 장비를 해제하거나 새로 장착할 수있고, 장비의 상세 정보를 확인할 수 있습니다." << endl;
		cout << "---------------------------------" << endl;
		cout << "[PLAYER]" << endl;
		cout << "[1] 무기 : " << ((playerInfo->equipmentList[0].id == -1) ? "빈 슬롯" : playerInfo->equipmentList[0].name) << endl;
		cout << "[2] 투구 : " << ((playerInfo->equipmentList[1].id == -1) ? "빈 슬롯" : playerInfo->equipmentList[1].name) << endl;
		cout << "[3] 갑옷 : " << ((playerInfo->equipmentList[2].id == -1) ? "빈 슬롯" : playerInfo->equipmentList[2].name) << endl;
		cout << "[4] 팔목 : " << ((playerInfo->equipmentList[3].id == -1) ? "빈 슬롯" : playerInfo->equipmentList[3].name) << endl;
		cout << "[5] 다리 : " << ((playerInfo->equipmentList[4].id == -1) ? "빈 슬롯" : playerInfo->equipmentList[4].name) << endl;
		cout << "[6] 신발 : " << ((playerInfo->equipmentList[5].id == -1) ? "빈 슬롯" : playerInfo->equipmentList[5].name) << endl;
		cout << "---------------------------------" << endl;
		cout << "(1) 장비 해제하기 (2) 장비 장착하기 (3) 상세 정보 확인하기 (4) 돌아가기" << endl;
		cout << ">";
		// 장비 장착 해제
		// 장비별 상태 확인(굳이?) -> 텍스트로 스탯을 전부 그려줘야하는데 너무 불편하다. 장비 단일 상태

		int choice;
		cin >> choice;

		switch (choice)
		{
			// 장비 장착 해제
		case 1:
			UnEquipArmor(playerInfo, choice);
			break;

			// 장비 장착하기(교체 포함)
		case 2:
		{
			// 현재 장비 리스트가 전부 뜸
			int count = 0;
			int armorMap[100] = {};
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					// 빈 슬롯이 아니고 겹칠 수 없는(장비)인 경우
					if (playerInfo->inventory[i][j].item.id != -1 && !playerInfo->inventory[i][j].item.stackable)
					{
						cout << "[" << ++count << "] " << playerInfo->inventory[i][j].item.name << "\t";
						// 실제 인벤토리 배열의 위치.
						armorMap[count] = ((i * 10) + j);
					}
				}
				cout << endl << endl;
			}
			if (count <= 0)
			{
				cout << "---------------------------------" << endl;
				cout << "인벤토리에 장비가 없습니다 ! 장비를 먼저 흭득해주세요. " << endl;
				cout << "---------------------------------" << endl;
				break;
			}

			cout << "---------------------------------" << endl;
			cout << "장비를 선택하여 정보를 확인하거나, 장착할 수 있습니다." << endl;
			cout << "장비 번호를 선택해주세요 !" << endl;
			cout << "---------------------------------" << endl;
			cout << ">";

			int armorIndex;
			cin >> armorIndex;
			// 인벤토리 실제 인덱스
			int realIndex = armorMap[armorIndex];

			// 이 상태에서 특정 아이템(장비)를 골라야함.
			// 상세 정보를 확인할껀지, 장착할껀지 ?
			cout << "---------------------------------" << endl;
			cout << "장비 번호를 선택하셨습니다. 어떻게 하시겠습니까 ?" << endl;
			cout << "(1) 상세 정보 확인 (2) 장착 하기" << endl;
			cout << "---------------------------------" << endl;
			cout << ">";

			int input;
			cin >> input;

			switch (input)
			{
			case 1:
				// 장비 상세 정보만 확인하고 나옴.
				CheckInventoryItemInfo(playerInfo, realIndex);
				break;
			case 2:
				// 장비를 착용하려고 시도.
				EquipArmor(playerInfo, realIndex);
				break;
			}
		}
		break;

		// 현재 장착한 장비 상세 정보 확인하기
		case 3:
		{
			// 장비를 한개라도 장착하고있는지
			bool noneEquip = false;
			for (int i = 0; i < 6; i++)
			{
				// 한 개라도 빈 슬롯이 아니라면
				if (playerInfo->equipmentList[i].id != -1)
				{
					break;
				}
				else
				{
					if (!noneEquip)
						noneEquip = true;
				}
			}
			// 전부 빈 슬롯이라면
			if (noneEquip)
			{
				cout << "현재 착용중인 장비가 없습니다 !" << endl;
				cout << "먼저 장비를 착용해주세요. " << endl;
				break;
			}
			while (true)
			{
				cout << "확인 할 장비 번호를 선택해주세요 !" << endl;
				int index;
				cin >> index;

				// 장비 번호중에 하나이고 빈 슬롯이 아닌 경우 
				if ((index >= 1 && index <= 6) && playerInfo->equipmentList[index - 1].id != -1)
				{
					CheckCurrentEquipmentInfo(playerInfo->equipmentList[index - 1]);
					break;
				}
				else
				{
					cout << "장비를 확인할 수 없는 번호입니다. 다시 입력해주세요" << endl;
				}
			}
		}
		break;
		// 개인룸으로 돌아가기
		case 4:
			cout << "개인룸으로 돌아갑니다." << endl;
			exitEquipState = true;
			break;

		}
	}
}
// MyRoom Helper
// -- Inventory & Stat
void CheckInventoryItemInfo(PlayerInfo* playerInfo, int itemIndex)
{
	ItemInfo item = playerInfo->inventory[itemIndex / 10][itemIndex % 10].item;


	if (item.stackable)
	{
		cout << "해당 아이템의 상세 정보를 확인합니다" << endl << endl;
		cout << "---------------------------------" << endl;
		cout << "NAME  : " << item.name << endl;
		cout << "COUNT : " << playerInfo->inventory[itemIndex / 10][itemIndex % 10].count << endl;
		cout << "---------------------------------" << endl;
	}
	else
	{
		cout << "해당 장비의 상세 정보를 확인합니다" << endl << endl;
		cout << "---------------------------------" << endl;
		cout << "NAME : " << item.name << endl;
		cout << "HP : " << item.hp << endl;
		cout << "ATT : " << item.att << endl;
		cout << "DEF : " << item.def << endl;
		cout << "---------------------------------" << endl;
	}
}
void CheckInventoryItemPosition(PlayerInfo* playerInfo, int oldIndex, int newIndex, int itemCount)
{
	// newIndex는 새로 이동할 위치의 인덱스
	// oldIndex는 기존에 있던 아이템의 위치 인덱스
	// itemCount는 이동할 아이템의 개수(장비라면 -1)

	// 개수가 여러개인 경우라면
	if (itemCount > 0)
	{
		// 이동하려는 위치가 빈 슬롯이 아니다 -> 겹칠 수 있는 아이템이 이미 존재한다. 
		if (playerInfo->inventory[newIndex / 10][newIndex % 10].item.id != -1)
		{
			// 새로운 위치에 개수 더하고, 이전 위치 개수 빼기
			playerInfo->inventory[newIndex / 10][newIndex % 10].count += itemCount;
			playerInfo->inventory[oldIndex / 10][oldIndex % 10].count -= itemCount;
			// 만약 전체 이동이라서 이전 위치에 개수가 0개라면?
			if (playerInfo->inventory[oldIndex / 10][oldIndex % 10].count <= 0)
			{
				// 이전 위치 아이템 없애기
				CleanInventoryItem(&playerInfo->inventory[oldIndex / 10][oldIndex % 10].item);
			}
			return;
		}
		// 이동하려는 아이템 개수만큼 이전 위치에서 마이너스 이후 새로운 위치(빈슬롯 X)에 통째로 복사
		playerInfo->inventory[oldIndex / 10][oldIndex % 10].count -= itemCount;
		playerInfo->inventory[newIndex / 10][newIndex % 10].item = playerInfo->inventory[oldIndex / 10][oldIndex % 10].item;
		return;
	}
	// 아이템 위치 이동
	// 새롭게 이동할 공간이 빈슬롯이라면, 이전에 있던 위치가 빈슬롯으로 바뀜. 빈슬롯 위치는 이동한 아이템으로 채워진다.
	ChangeItemPosition(&playerInfo->inventory[oldIndex / 10][oldIndex % 10].item, &playerInfo->inventory[newIndex / 10][newIndex % 10].item);
}
void CleanInventoryItem(ItemInfo* item)
{
	ItemInfo temp;
	*item = temp;
}
void ChangeItemPosition(ItemInfo* oldItem, ItemInfo* newItem)
{
	ItemInfo temp = *oldItem;
	*oldItem = *newItem;
	*newItem = temp;
}
// -- Equipment
void EquipArmor(PlayerInfo* playerInfo, int itemIndex)
{
	// 아이템의 원본 정보?
	// 플레이어의 장비에 장착을 시켜야함.
	// 선택한 아이템의 타입을 확인한다.

	// Weapon : 1
	// Helmet : 2
	// ...
	// Boots : 6
	int slotIndex = (playerInfo->inventory[itemIndex / 10][itemIndex % 10].item.type) - 1;
	// 사용자가 고른 타입 번호와 장비 슬롯 배열의 인덱스를 매칭시킨다.

	// 빈 슬롯이라면?
	if (playerInfo->equipmentList[slotIndex].id == -1)
	{
		playerInfo->equipmentList[slotIndex] = playerInfo->inventory[itemIndex / 10][itemIndex % 10].item;
		cout << "새로운 장비를 장착하셨습니다 !" << endl;

		// 스탯 반영
		playerInfo->hp += playerInfo->equipmentList[slotIndex].hp;
		playerInfo->att += playerInfo->equipmentList[slotIndex].att;
		playerInfo->def += playerInfo->equipmentList[slotIndex].def;

		// 인벤토리 아이템 삭제? -> 싹 밀어버리기.
		CleanInventoryItem(&playerInfo->inventory[itemIndex / 10][itemIndex % 10].item);
	}

	// 이미 장비가 있는 경우
	else
	{
		// 교체 함수(장착중인 아이템과 인벤토리 아이템 교체)
		CheckChangeEquipment(playerInfo, &playerInfo->equipmentList[slotIndex], &playerInfo->inventory[itemIndex / 10][itemIndex % 10].item);
	}
}
void UnEquipArmor(PlayerInfo* playerInfo, int equipmentIndex)
{
	bool fullItem = true;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			// 빈슬롯인 경우
			if (playerInfo->inventory[i][j].item.id == -1)
			{
				if (fullItem)
					fullItem = false;

				// 장비에 달려있던 스탯을 플레이어 스탯에서 뺴준다.
				// 이미 착용중인 장비를 스탯에서 빼는거라 음수가 나올 수 없음
				playerInfo->hp -= playerInfo->equipmentList[equipmentIndex - 1].hp;
				playerInfo->att -= playerInfo->equipmentList[equipmentIndex - 1].att;
				playerInfo->def -= playerInfo->equipmentList[equipmentIndex - 1].def;

				// 위치 변경
				ChangeItemPosition(&playerInfo->equipmentList[equipmentIndex - 1], &playerInfo->inventory[i][j].item);
				return;
			}
		}
	}

	// 빈 슬롯이 한개도 없는 경우
	if (fullItem)
	{
		cout << "인벤토리에 빈 슬롯이 없습니다 !" << endl;
		cout << "먼저 인벤토리에 빈 슬롯을 확보해주세요. " << endl;
		return;
	}

}
void CheckChangeEquipment(PlayerInfo* playerInfo, ItemInfo* oldItem, ItemInfo* newItem)
{
	cout << "---------------------------------" << endl;;
	cout << "이미 착용중인 장비가 존재합니다 !" << endl << endl;
	cout << "장비를 교체하시겠습니까 ?" << endl;
	cout << "---------------------------------" << endl;

	cout << "이전 장비" << endl << endl;
	cout << "---------------------------------" << endl;
	cout << "NAME : " << oldItem->name << endl;
	cout << "HP : " << oldItem->hp << endl;
	cout << "ATT : " << oldItem->att << endl;
	cout << "DEF : " << oldItem->def << endl;
	cout << "---------------------------------" << endl << endl;

	cout << "새로운 장비" << endl << endl;
	cout << "---------------------------------" << endl;
	cout << "NAME : " << newItem->name << endl;
	cout << "HP :" << newItem->hp << endl;
	cout << "ATT : " << newItem->att << endl;
	cout << "DEF : " << newItem->def << endl;
	cout << "---------------------------------" << endl << endl;
	cout << "(1) 교체한다 (2) 교체하지않는다." << endl;
	cout << ">";

	int input;
	cin >> input;

	switch (input)
	{
	case 1:
		cout << "장비를 교체합니다. 이전 장비는 새로운 장비가 있던 인벤토리 위치에 저장됩니다." << endl;
		ChangeEquipment(playerInfo, oldItem, newItem);
		cout << "장비 상태창으로 되돌아갑니다. " << endl;
		break;
	case 2:
		cout << "장비를 교체하지 않습니다. 장비 상태창으로 되돌아갑니다. " << endl;
		break;
	}

}
void ChangeEquipment(PlayerInfo* playerInfo, ItemInfo* oldItem, ItemInfo* newItem)
{
	playerInfo->hp += ((newItem->hp - oldItem->hp) <= 0 ? 0 : (newItem->hp - oldItem->hp));
	playerInfo->att += ((newItem->att - oldItem->att) <= 0 ? 0 : (newItem->att - oldItem->att));
	playerInfo->def += ((newItem->def - oldItem->def) <= 0 ? 0 : (newItem->def - oldItem->def));

	ChangeItemPosition(oldItem, newItem);
}
void CheckCurrentEquipmentInfo(ItemInfo equipment)
{
	cout << "해당 장비의 상세 정보를 확인합니다" << endl << endl;
	cout << "---------------------------------" << endl;
	cout << "NAME : " << equipment.name << endl;
	cout << "HP : " << equipment.hp << endl;
	cout << "ATT : " << equipment.att << endl;
	cout << "DEF : " << equipment.def << endl;
	cout << "---------------------------------" << endl;
}


// Shop Branch
void EnterItemBuyingState(PlayerInfo* playerInfo)
{
	cout << "---------------------------------" << endl;
	cout << "원하는 아이템을 구매하여 인벤토리에 추가할 수 있습니다." << endl << endl;
	cout << "상점에서 구매 할 아이템을 선택해주세요. " << endl;
	cout << "---------------------------------" << endl;

	int count = 0;
	int itemMap[100] = {};
	bool noneItem = true;
	for (int i = 0; i < (sizeof(itemTable) / sizeof(itemTable[0])); i++)
	{
		// 판매 가능한 아이템인 경우
		if (itemTable[i].hasShop)
		{
			if (noneItem)
				noneItem = false;

			cout << "[" << ++count << "] " << itemTable[i].name << endl;
			// 실제 아이템 테이블에서의 인덱스
			itemMap[count] = i;
		}
	}
	if (noneItem)
	{
		cout << "---------------------------------" << endl;
		cout << "현재 상점에 판매 가능한 아이템이 없습니다 ! " << endl;
		cout << "나중에 다시 방문해주세요. " << endl;
		cout << "---------------------------------" << endl;
		return;
	}
	cout << ">";
	int index;
	cin >> index;

	// 현재 선택한 아이템의 인덱스
	int realIndex = itemMap[index];
	int buyCount = -1;

	// 여러개를 구매할 수 있는 아이템이라면
	if (itemTable[realIndex].stackable)
	{
		while (buyCount <= 0)
		{
			cout << "---------------------------------" << endl;
			cout << "해당 아이템은 여러개 구매할 수 있습니다." << endl;
			cout << "해당 아이템의 가격은 : " << itemTable[realIndex].price << "원 입니다" << endl;
			cout << "현재 보유한 플레이어의 돈은 : " << playerInfo->money << "원 입니다" << endl;
			cout << "총 몇 개를 구매하시겠습니까 ?" << endl;
			cout << "---------------------------------" << endl;
			cout << ">";

			int input;
			cin >> input;

			if (input <= 0)
			{
				cout << "잘못된 수량입니다. 다시 입력해주세요" << endl;
				continue;
			}

			// 돈 보다 많이 구매한경우. 딱 맞춰 구매한건 제외 
			if ((playerInfo->money - (itemTable[realIndex].price * input) < 0))
			{
				cout << "구매하려는 아이템 총 금액보다 현재 플레이어의 돈이 부족합니다. 다시 입력해주세요" << endl;
				cout << "구매할 아이템의 총 금액 : " << (itemTable[realIndex].price * input) << "원" << endl;
				cout << "현재 플레이어의 돈 : " << playerInfo->money << "원" << endl;
				continue;
			}

			buyCount = input;
		}
	}

	// 아이템 개수
	cout << "---------------------------------" << endl;
	cout << "아이템 번호를 선택하셨습니다." << endl;
	cout << "현재 선택한 아이템의 가격은 : " << itemTable[realIndex].price << "원 입니다." << endl;
	if (buyCount > 0)
	{
		cout << "현재 선택한 아이템의 개수는 : " << buyCount << "개 입니다." << endl;
		cout << "구매 할 아이템의 총 금액은 : " << (itemTable[realIndex].price * buyCount) << "원 입니다." << endl;
	}
	cout << "아이템을 구매하시겠습니까?(이 선택은 되돌릴 수 없습니다)" << endl;
	cout << "(1) 구매하기 (2) 취소하기" << endl;
	cout << "---------------------------------" << endl;
	cout << ">";

	int input;
	cin >> input;

	switch (input)
	{
	case 1:
		// 구매
		BuyItemToShop(playerInfo, realIndex, buyCount);
		cout << "아이템을 구매하였습니다. 상점으로 되돌아갑니다." << endl;
		break;
	case 2:
		cout << "상점으로 되돌아갑니다." << endl;
		return;
	}
}
void EnterItemSellingState(PlayerInfo* playerInfo)
{
	cout << "---------------------------------" << endl;
	cout << "아이템을 판매하여 상점 주인에게 돈을 받을 수 있습니다." << endl << endl;
	cout << "인벤토리에서 판매 할 아이템을 선택하여주세요" << endl;
	cout << "---------------------------------" << endl;

	int count = 0;
	int itemMap[100] = {};
	bool noneItem = true;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (playerInfo->inventory[i][j].item.id != -1)
			{
				// 아이템이 없는지 체크용
				if (noneItem)
					noneItem = false;

				cout << "[" << ++count << "] " << playerInfo->inventory[i][j].item.name << "\t";
				itemMap[count] = ((i * 10) + j);
			}
		}
		cout << endl;
	}
	if (noneItem)
	{
		cout << "---------------------------------" << endl;
		cout << "아이템이 없습니다 ! 아이템을 먼저 흭득해주세요. " << endl;
		cout << "---------------------------------" << endl;
		return;
	}

	cout << ">";
	int index;
	cin >> index;

	// 현재 선택한 아이템의 인덱스
	int realIndex = itemMap[index];


	int sellCount = -1;
	// 한 개 초과인 경우
	if (playerInfo->inventory[realIndex / 10][realIndex % 10].count > 1)
	{
		while (sellCount <= 0)
		{
			cout << "---------------------------------" << endl;
			cout << "아이템이 한 개보다 많습니다. 몇 개를 판매하시겠습니까 ? " << endl;
			cout << "현재 선택한 아이템의 가격은 : " << playerInfo->inventory[realIndex / 10][realIndex % 10].item.price << "원 입니다" << endl;
			cout << "현재 보유한 해당 아이템의 총 개수는 : " << playerInfo->inventory[realIndex / 10][realIndex % 10].count << "개 입니다" << endl;
			cout << "---------------------------------" << endl;
			cout << ">";

			int input;
			cin >> input;

			// 입력한 아이템을 초과한다면
			if (input > playerInfo->inventory[realIndex / 10][realIndex % 10].count)
			{
				cout << "현재 가진 개수를 초과한 수량을 판매할 수 없습니다. 다시 선택해주세요." << endl;
				continue;
			}
			else if (input <= 0)
			{
				cout << "잘못된 수량입니다. 다시 선택해주세요" << endl;
				continue;
			}

			// 판매할 개수를 입력받는다.
			sellCount = input;
		}
	}

	// 아이템 개수
	cout << "---------------------------------" << endl;
	cout << "아이템 번호를 선택하셨습니다." << endl;
	cout << "현재 선택한 아이템의 가격은 : " << playerInfo->inventory[realIndex / 10][realIndex % 10].item.price << "원 입니다" << endl;
	if (sellCount > 0)
	{
		cout << "전체 개수 : " << playerInfo->inventory[realIndex / 10][realIndex % 10].count << "개 중 " << sellCount << "개를 선택하셨습니다." << endl;
		cout << "판매할 아이템의 총 금액 : " << (itemTable[realIndex].price * sellCount) << "원" << endl;
	}

	cout << "아이템을 판매하시겠습니까?(이 선택은 되돌릴 수 없습니다)" << endl;
	cout << "(1) 판매하기 (2) 취소하기" << endl;
	cout << "---------------------------------" << endl;
	cout << ">";

	int input;
	cin >> input;

	switch (input)
	{
	case 1:
		// 판매
		SellItemToShop(playerInfo, realIndex, sellCount);
		cout << "아이템을 판매하였습니다. 상점으로 되돌아갑니다." << endl;
		break;
	case 2:
		cout << "상점으로 되돌아갑니다." << endl;
		return;
	}
}

// Shop Helper
void BuyItemToShop(PlayerInfo* playerInfo, int realIndex, int buyCount)
{
	// 플레이어 인벤토리 순회
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			// 이미 존재하는 아이템이고, 겹칠 수 있는 아이템이라면
			if (playerInfo->inventory[i][j].item.id == itemTable[realIndex].id && itemTable[realIndex].stackable)
			{
				// 구매한 아이템 개수가 여러개라면
				if (buyCount > 0)
				{
					playerInfo->money -= (itemTable[realIndex].price * buyCount);
					playerInfo->inventory[i][j].count += buyCount;
					return;
				}
				playerInfo->money -= itemTable[realIndex].price;
				playerInfo->inventory[i][j].count++;
				return;
			}
			// 이미 존재하는 아이템이 아니거나, 겹칠 수 없는 아이템인 경우에는 그냥 빈슬롯에 추가하면 됨.
			else if (playerInfo->inventory[i][j].item.id == -1)
			{
				// 구매한 개수가 여러개라면
				if (buyCount > 0)
				{
					playerInfo->money -= (itemTable[realIndex].price * buyCount);
					playerInfo->inventory[i][j].item = itemTable[realIndex];
					// 초기 수량은 1개라서 더하면 안됨.
					playerInfo->inventory[i][j].count = buyCount;
					return;
				}
				playerInfo->money -= itemTable[realIndex].price;
				playerInfo->inventory[i][j].item = itemTable[realIndex];
				return;
			}
		}
	}
}
void SellItemToShop(PlayerInfo* playerInfo, int realIndex, int sellCount)
{
	// 원본값 주소 받기
	ItemInfo* sellItem = &(playerInfo->inventory[realIndex / 10][realIndex % 10].item);

	// 아이템이 여러개인 경우
	if (sellCount > 0)
	{
		playerInfo->money += ((sellItem->price) * sellCount);

		// 판매 수량만큼 인벤토리 개수 제거
		playerInfo->inventory[realIndex / 10][realIndex % 10].count -= sellCount;

		// 만약 현재 수량이 1보다 작다면 아이템 삭제
		if(playerInfo->inventory[realIndex / 10][realIndex % 10].count < 1)
			CleanInventoryItem(sellItem);
		return;
	}

	// 플레이어 돈 증가
	playerInfo->money += sellItem->price;

	// 인벤토리 아이템 삭제(인벤토리에서 없어짐
	CleanInventoryItem(sellItem);
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

		// 문자 입력 시 무한 루프가 생김
		// 굳이 당장 고칠 필요는 없어보임
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

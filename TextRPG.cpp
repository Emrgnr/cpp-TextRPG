#include <iostream>
using namespace std;


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

// padding = 16 + 4 + 4 + 4 + 4 + 4 + 4= 40
struct ObjectInfo
{
	char name[16];
	int exp;
	int level;
	int type;
	int hp;
	int att;
	int def;
};

// 초기 스탯 테이블(설계도)
const ObjectInfo monsterStatTable[] =
{
	{"해골",	50, 1, 1, 80, 15, 5},			
	{"슬라임", 80, 1, 2, 100, 10, 8},
	{"오크", 110, 1, 3, 120, 11, 10 }			
};


// 초기 스탯 테이블(설계도)
const ObjectInfo playerStatTable[] =
{
	{"기사", 0, 1, 1, 150, 15, 10},			
	{"아처", 0, 1, 2, 120, 21, 7},			
	{"마법사", 0, 1, 3, 100, 25, 5 }		
};


bool exitGame = false;
bool isMadeCharacter = false;
bool isPlayerDead = false;

void CreateMonster(ObjectInfo* monsterInfo);
void GenerateCharacter(ObjectInfo* playerInfo);
void ChooseCharacter(ObjectInfo* playerInfo);
void FightMonster(ObjectInfo* playerInfo, ObjectInfo* monsterInfo);
void EnterField(ObjectInfo* playerInfo);
void EnterTown(ObjectInfo* playerInfo);

void CalculateLevelUpStat(ObjectInfo* playerInfo);

// helper
int GetCurrentMaxExp(int playerLevel){ return playerLevel * 100; };
int GetPlayerMaxHP(ObjectInfo* playerInfo) 
{ 
	int baseHp = playerStatTable[playerInfo->type - 1].hp;
	float growthRate = (playerInfo->level - 1) * 0.3f;

	return baseHp + (int)(baseHp * growthRate);
};


void CreateMonster(ObjectInfo* monsterInfo)
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
void GenerateChracter(ObjectInfo* playerInfo)
{
	int playerType = playerInfo->type;

	int tempInput;
	while (!isMadeCharacter)
	{
		// 플레이어 유형별 스탯 설정
		ObjectInfo tempInfo = playerStatTable[playerType - 1];

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
// 캐릭터 선택
void ChooseCharacter(ObjectInfo* playerInfo)
{
	if (playerInfo->type != 0)
		playerInfo->type = NULL;

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
void FightMonster(ObjectInfo* playerInfo, ObjectInfo* monsterInfo)
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

		if (monsterInfo->hp <= 0)
		{
			cout << "몬스터를 처치했습니다!" << endl;
			playerInfo->exp += monsterInfo->exp;

			// 레벨을 기준으로 최대 경험치 책정
			while(playerInfo->exp >= GetCurrentMaxExp(playerInfo->level))
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
void CalculateLevelUpStat(ObjectInfo* playerInfo)
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
void EnterField(ObjectInfo* playerInfo)
{
	bool exitField = false;
	while (isPlayerDead == false && exitField == false)
	{
		ObjectInfo monsterInfo;
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
void EnterTown(ObjectInfo* playerInfo)
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

	ObjectInfo player;
	int input;

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

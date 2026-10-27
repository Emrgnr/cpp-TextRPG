#include <iostream>
using namespace std;

#define ENTERFIELD 1
#define EXITGAME 2

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
	ORC,
};

struct ObjectInfo
{
	short type;
	int hp;
	int att;
	int def;
};

bool exitGame = false;
bool playerAllive = true;

ObjectInfo player;
ObjectInfo monster;

void EnterLobby();
void ChooseChracter();
void CreateMonster();
void EnterField();
void FightMonster();

void EnterLobby()
{
	int input;

	cout << "-------------------" << endl;
	cout << "로비에 입장했습니다 !" << endl;
	cout << "-------------------" << endl;

	cout << "-------------------" << endl;
	cout << "직업을 골라주세요!" << endl;
	cout << "(1) 기사 (2) 궁수 (3) 법사" << endl;
	cout << ">";

	cin >> player.type;

	ChooseChracter();

	while (true)
	{
		cout << "-------------------" << endl;
		cout << "(1) 필드 입장 (2) 게임 종료" << endl;
		cout << ">";

		cin >> input;
		if (input == ENTERFIELD)
		{
			EnterField();
			break;
		}
		else if (input == EXITGAME)
		{
			exitGame = true;
			break;
		}

	}
}

void ChooseChracter()
{
	switch (player.type)
	{
	case KNIGHT:
		cout << "기사 생성중... !" << endl;
		player.hp = 150;
		player.att = 15;
		player.def = 10;
		break;
	case ARCHOR:
		cout << "궁수 생성중... !" << endl;
		player.hp = 80;
		player.att = 20;
		player.def = 3;
		break;
	case MAGE:
		cout << "법사 생성중... !" << endl;
		player.hp = 80;
		player.att = 25;
		player.def = 0;
	}
	playerAllive = true;
}

void CreateMonster()
{
	monster.type = 1 + (rand() % 3);
	switch (monster.type)
	{
	case SKELETON:
		cout << "해골 생성중... ! ";
		monster.hp = 80;
		monster.att = 15;
		monster.def = 5;
		break;
	case SLIME:
		cout << "슬라임 생성중... ! ";
		monster.hp = 100;
		monster.att = 10;
		monster.def = 8;
		break;
	case ORC:
		cout << "오크 생성중... ! ";
		monster.hp = 200;
		monster.att = 20;
		monster.def = 10;
		break;

	}

}

void EnterField()
{
	while (playerAllive)
	{

		cout << "-------------------" << endl;
		cout << "필드에 입장했습니다!" << endl;
		cout << "-------------------" << endl;

		cout << "[PLAYER] HP : " << player.hp << " / " << "ATT: " << player.att << " / " << "DEF: " << player.def << endl;

		CreateMonster();

		cout << "(HP: " << monster.hp << " / " << "ATT: " << monster.att << " / " << "DEF: " << monster.def << ")" << endl;
		cout << "-------------------" << endl;
		cout << "(1) 전투 (2) 도주" << endl;
		cout << "> ";

		int input;
		cin >> input;

		if (input == 1)
		{
			FightMonster();
		}
		else if (input == 2)
			continue;
	}
}

void FightMonster()
{
	while (true)
	{
		cout << "몬스터 남은 체력 : " << monster.hp << endl;
		cout << "플레이어 남은 체력 : " << player.hp << endl;

		int playerDamage = (player.att - monster.def);

		if (playerDamage <= 0)
			playerDamage = 1;

		monster.hp -= playerDamage;

		if (monster.hp <= 0)
		{
			cout << "몬스터를 처치했습니다!" << endl;
			break;
		}
		int monsterDamage = (monster.att - player.def);
		if (monsterDamage <= 0)
			monsterDamage = 1;
		player.hp -= monsterDamage;

		if (player.hp <= 0)
		{
			playerAllive = false;
			cout << "플레이어는 사망했습니다. 로비로 돌아갑니다. " << endl;
			break;
		}
	}
}
int main()
{
	srand(time(0));

	while (!exitGame)
	{
		EnterLobby();
	}
	return 0;
}

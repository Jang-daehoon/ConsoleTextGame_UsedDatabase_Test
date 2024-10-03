#include<string>
#include "DatabaseManager.h"
#pragma once
class Monster
{
protected:
	DatabaseManager& dbManager;

	int monster_Id;
	std::string monster_Name;
	std::string monster_Desc;
	int monster_MaxHp;
	int monster_curHp;
	int monster_AttackDMG;
	int monster_Shield;
	int monster_Cost;
	int monster_Initial_Funds;
public:
	std::string get_Name()const;
	std::string get_Desc()const;
	int get_Maxhp()const;
	int get_curhp()const;
	int get_Attackdmg()const;
	int get_Shield()const;
	int get_Initialfunds()const;
	Monster(DatabaseManager& db);
	void Hit(int damage);
	bool Dead() const;
	void MonsterInfo() const;
	void loadMonsterInfo(int id);	//DB에서 캐릭터 정보 로드
};


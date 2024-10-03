#include<string>
#include "DatabaseManager.h"
#pragma once
class Character
{
protected:
	DatabaseManager& dbManager;

	int character_Id;
	std::string character_Name;
	std::string character_Desc;
	int character_MaxHp;
	int character_curHp;
	int character_AttackDMG;
	int character_Shield;
	int character_curShield;
	int character_Cost;
	int character_Initial_Funds;
public:
	std::string get_Name()const;
	std::string get_Desc()const;
	int get_Maxhp()const;
	void Set_Maxhp(int AddHp);
	int get_curhp()const;
	void Set_Curhp(int heal);
	int get_Attackdmg()const;
	int get_Shield()const;
	void set_Shield(int addShield);

	int get_Cost()const;
	void set_Cost();
	void recovery_Cost();	//코스트회복
	int get_Initialfunds()const;
	Character(DatabaseManager& db);
	void Hit(int damage);
	void CharacterInfo() const;
	void loadCharacterInfo(int id);	//DB에서 캐릭터 정보 로드
};


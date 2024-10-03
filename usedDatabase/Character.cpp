#include "Character.h"
#include<iostream>

Character::Character(DatabaseManager& db) :dbManager(db) {
	character_Id = 0;
	character_Name = "";
	character_Desc = "";
	character_MaxHp = 0;
	character_curHp = character_MaxHp;
	character_AttackDMG = 0;
	character_Shield = 0;
	character_Cost = 0;
	character_Initial_Funds = 0;
}

void Character::Hit(int damage) {
	character_curHp -= damage;
	if (character_curHp < 0)
	{
		character_curHp = 0; // 체력 최소화
		std::cout << character_Name << "이(가) 사망하였습니다." << std::endl;
		std::cout<<"GAME OVER..."<<std::endl;
	}
}

void Character::CharacterInfo() const {
	std::cout << "캐릭터 이름: " << character_Name << "\n"
		<< "설명: " << character_Desc << "\n"
		<< "최대 체력: " << character_MaxHp << "\n"
		<< "현재 체력: " << character_curHp << "\n"
		<< "공격력: " << character_AttackDMG << "\n"
		<< "방어력: " << character_Shield << "\n"
		<< "비용: " << character_Cost << "\n"
		<< "초기 자금: " << character_Initial_Funds << "\n";
}

void Character::loadCharacterInfo(int id) {
	// ID에 따라 캐릭터 정보를 가져오는 SELECT 쿼리 준비
	std::string query = "SELECT * FROM CharacterTable WHERE character_Id = " + std::to_string(id);

	if (dbManager.ExecuteQuery(query)) {
		MYSQL_RES* result = dbManager.QueryResult();
		if (result && mysql_num_rows(result) > 0) {
			MYSQL_ROW row = mysql_fetch_row(result);
			character_Id = std::stoi(row[0]); // 첫 번째 열이 ID라고 가정
			character_Name = row[1];          // 두 번째 열이 이름
			character_Desc = row[2];          // 세 번째 열이 설명
			character_MaxHp = std::stoi(row[3]); // 최대 HP
			character_curHp = character_MaxHp; // 현재 HP 초기화
			character_AttackDMG = std::stoi(row[4]); // 공격 데미지
			character_Shield = std::stoi(row[5]); // 방어구
			character_Cost = std::stoi(row[6]); // 비용
			character_Initial_Funds = std::stoi(row[7]); // 초기 자금
		}
		mysql_free_result(result); // 결과 집합 해제
	}
	else {
		std::cerr << "Error fetching character info: " << dbManager.GetError() << std::endl;
	}
}

std::string Character::get_Name()const
{
	return character_Name;
}

std::string Character::get_Desc()const
{
	return character_Desc;
}

int Character::get_Maxhp()const
{
	return character_MaxHp;
}

void Character::Set_Maxhp(int AddHp)
{
	character_MaxHp += AddHp;
}

int Character::get_curhp()const
{
	return character_curHp;
}

void Character::Set_Curhp(int heal)
{
	character_curHp += heal;
	if (character_curHp > character_MaxHp)
	{
		character_curHp = character_MaxHp;	//최대 체력보다 커지는 것을 방지
	}
}

int Character::get_Attackdmg()const
{
	return character_AttackDMG;
}

int Character::get_Shield()const
{
	return character_Shield;
}

void Character::set_Shield(int addShield)
{
	character_Shield += addShield;
}

int Character::get_Cost()const
{
	return character_Cost;
}

void Character::set_Cost()
{
	character_Cost--;
}

void Character::recovery_Cost()
{
	character_Cost = 5;
}

int Character::get_Initialfunds()const
{
	return character_Initial_Funds;
}

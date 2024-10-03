#include "Monster.h"
#include<iostream>

Monster::Monster(DatabaseManager& db) :dbManager(db) {
	monster_Id = 0;
	monster_Name = "";
	monster_Desc = "";
	monster_MaxHp = 0;
	monster_curHp = monster_MaxHp;
	monster_AttackDMG = 0;
	monster_Shield = 0;
	monster_Cost = 0;
	monster_Initial_Funds = 0;
}

void Monster::Hit(int damage) {
	monster_curHp -= damage;
	if (monster_curHp < 0)
	{
		monster_curHp = 0; // 체력 최소화
		std::cout << monster_Name << "이(가) 사망하였습니다." << std::endl;
		std::cout << "GAME OVER..." << std::endl;
	}
}


bool Monster::Dead() const {
	return monster_curHp <= 0;
}

void Monster::MonsterInfo() const {
	std::cout << "캐릭터 이름: " << monster_Name << "\n\n"
		<< "설명: " << monster_Desc << "\n\n"
		<< "최대 체력: " << monster_MaxHp << "\n\n"
		<< "현재 체력: " << monster_curHp << "\n\n"
		<< "공격력: " << monster_AttackDMG << "\n\n"
		<< "방어력: " << monster_Shield << "\n\n"
		<< "몬스터 처치 시 획득 가능 금액: " << monster_Initial_Funds << "\n";
}

void Monster::loadMonsterInfo(int id) {
	// ID에 따라 캐릭터 정보를 가져오는 SELECT 쿼리 준비
	std::string query = "SELECT * FROM MonsterTable WHERE monster_Id = " + std::to_string(id);

	if (dbManager.ExecuteQuery(query)) {
		MYSQL_RES* result = dbManager.QueryResult();
		if (result && mysql_num_rows(result) > 0) {
			MYSQL_ROW row = mysql_fetch_row(result);
			monster_Id = std::stoi(row[0]); // 첫 번째 열이 ID라고 가정
			monster_Name = row[1];          // 두 번째 열이 이름
			monster_Desc = row[2];          // 세 번째 열이 설명
			monster_MaxHp = std::stoi(row[3]); // 최대 HP
			monster_curHp = monster_MaxHp; // 현재 HP 초기화
			monster_AttackDMG = std::stoi(row[4]); // 공격 데미지
			monster_Shield = std::stoi(row[5]); // 방어구
			monster_Initial_Funds = std::stoi(row[6]); // 초기 자금
		}
		mysql_free_result(result); // 결과 집합 해제
	}
	else {
		std::cerr << "Error fetching character info: " << dbManager.GetError() << std::endl;
	}
}

std::string Monster::get_Name()const
{
	return monster_Name;
}

std::string Monster::get_Desc()const
{
	return monster_Desc;
}

int Monster::get_Maxhp()const
{
	return monster_MaxHp;
}

int Monster::get_curhp()const
{
	return monster_curHp;
}

int Monster::get_Attackdmg()const
{
	return monster_AttackDMG;
}

int Monster::get_Shield()const
{
	return monster_Shield;
}

int Monster::get_Initialfunds()const
{
	return monster_Initial_Funds;
}

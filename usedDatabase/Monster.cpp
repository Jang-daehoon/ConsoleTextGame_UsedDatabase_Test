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
		monster_curHp = 0; // ü�� �ּ�ȭ
		std::cout << monster_Name << "��(��) ����Ͽ����ϴ�." << std::endl;
		std::cout << "GAME OVER..." << std::endl;
	}
}


bool Monster::Dead() const {
	return monster_curHp <= 0;
}

void Monster::MonsterInfo() const {
	std::cout << "ĳ���� �̸�: " << monster_Name << "\n\n"
		<< "����: " << monster_Desc << "\n\n"
		<< "�ִ� ü��: " << monster_MaxHp << "\n\n"
		<< "���� ü��: " << monster_curHp << "\n\n"
		<< "���ݷ�: " << monster_AttackDMG << "\n\n"
		<< "����: " << monster_Shield << "\n\n"
		<< "���� óġ �� ȹ�� ���� �ݾ�: " << monster_Initial_Funds << "\n";
}

void Monster::loadMonsterInfo(int id) {
	// ID�� ���� ĳ���� ������ �������� SELECT ���� �غ�
	std::string query = "SELECT * FROM MonsterTable WHERE monster_Id = " + std::to_string(id);

	if (dbManager.ExecuteQuery(query)) {
		MYSQL_RES* result = dbManager.QueryResult();
		if (result && mysql_num_rows(result) > 0) {
			MYSQL_ROW row = mysql_fetch_row(result);
			monster_Id = std::stoi(row[0]); // ù ��° ���� ID��� ����
			monster_Name = row[1];          // �� ��° ���� �̸�
			monster_Desc = row[2];          // �� ��° ���� ����
			monster_MaxHp = std::stoi(row[3]); // �ִ� HP
			monster_curHp = monster_MaxHp; // ���� HP �ʱ�ȭ
			monster_AttackDMG = std::stoi(row[4]); // ���� ������
			monster_Shield = std::stoi(row[5]); // ��
			monster_Initial_Funds = std::stoi(row[6]); // �ʱ� �ڱ�
		}
		mysql_free_result(result); // ��� ���� ����
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

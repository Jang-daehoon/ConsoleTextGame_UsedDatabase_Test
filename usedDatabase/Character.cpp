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
		character_curHp = 0; // ü�� �ּ�ȭ
		std::cout << character_Name << "��(��) ����Ͽ����ϴ�." << std::endl;
		std::cout<<"GAME OVER..."<<std::endl;
	}
}

void Character::CharacterInfo() const {
	std::cout << "ĳ���� �̸�: " << character_Name << "\n"
		<< "����: " << character_Desc << "\n"
		<< "�ִ� ü��: " << character_MaxHp << "\n"
		<< "���� ü��: " << character_curHp << "\n"
		<< "���ݷ�: " << character_AttackDMG << "\n"
		<< "����: " << character_Shield << "\n"
		<< "���: " << character_Cost << "\n"
		<< "�ʱ� �ڱ�: " << character_Initial_Funds << "\n";
}

void Character::loadCharacterInfo(int id) {
	// ID�� ���� ĳ���� ������ �������� SELECT ���� �غ�
	std::string query = "SELECT * FROM CharacterTable WHERE character_Id = " + std::to_string(id);

	if (dbManager.ExecuteQuery(query)) {
		MYSQL_RES* result = dbManager.QueryResult();
		if (result && mysql_num_rows(result) > 0) {
			MYSQL_ROW row = mysql_fetch_row(result);
			character_Id = std::stoi(row[0]); // ù ��° ���� ID��� ����
			character_Name = row[1];          // �� ��° ���� �̸�
			character_Desc = row[2];          // �� ��° ���� ����
			character_MaxHp = std::stoi(row[3]); // �ִ� HP
			character_curHp = character_MaxHp; // ���� HP �ʱ�ȭ
			character_AttackDMG = std::stoi(row[4]); // ���� ������
			character_Shield = std::stoi(row[5]); // ��
			character_Cost = std::stoi(row[6]); // ���
			character_Initial_Funds = std::stoi(row[7]); // �ʱ� �ڱ�
		}
		mysql_free_result(result); // ��� ���� ����
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
		character_curHp = character_MaxHp;	//�ִ� ü�º��� Ŀ���� ���� ����
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

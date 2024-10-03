#include "Event.h"
#include"GameManager.h"
Event::Event(DatabaseManager& db) : dbManager(db)
{
	event_Id = 0;
	event_Name = "";
	event_Desc = "";
	event_AddMaxHp = 0;
	event_GetHp = 0;
	event_AttackDamage = 0;
	event_Shield = 0;
	event_Cost = 0;
	event_GetGold = 0;
	story_Id = 0;
	story_Name = "";
	story_Desc = "";

}
std::string Event::get_Name() const
{
	return event_Name;
}

std::string Event::get_Desc() const
{
	return event_Desc;
}

int Event::AddMaxHp() const
{
	return event_AddMaxHp;
}

int Event::GetHp()const
{
	return event_GetHp;
}

int Event::AddAtkDmg()const
{
	return event_AttackDamage;
}

int Event::getShield()const
{
	return event_Shield;
}

int Event::AddCost()const
{
	return event_Cost;
}

int Event::getGold()const
{
	return event_GetGold;
}

void Event::loadEventInfo(int id)
{
	// ID�� ���� ĳ���� ������ �������� SELECT ���� �غ�
	std::string query = "SELECT * FROM EventTable WHERE event_Id = " + std::to_string(id);

	if (dbManager.ExecuteQuery(query)) {
		MYSQL_RES* result = dbManager.QueryResult();
		if (result && mysql_num_rows(result) > 0) {
			MYSQL_ROW row = mysql_fetch_row(result);
			event_Id = std::stoi(row[0]); // ù ��° ���� ID
			event_Name = row[1];          // �� ��° ���� �̸�
			event_Desc = row[2];          // �� ��° ���� ����
			event_AddMaxHp = std::stoi(row[3]); // �ִ� ü�� ����
			event_GetHp = std::stoi(row[4]); // HP ȸ����
			event_AttackDamage = std::stoi(row[5]); // ������ ������
			event_Shield = std::stoi(row[6]); // �� ����
			event_Cost = std::stoi(row[7]); // Cost �ִ�ġ ����
			event_GetGold = std::stoi(row[8]);	//Goldȹ��
		}
		mysql_free_result(result); // ��� ���� ����
	}
	else {
		std::cerr << "Error fetching character info: " << dbManager.GetError() << std::endl;
	}
}

void Event::PrintEvent()
{
	system("cls");
	std::cout << "�̺�Ʈ �߻�!!" << std::endl;
	std::cout << event_Name << std::endl;
	std::cout << event_Desc << std::endl;
	std::cout << "�ִ� ü�� ����: " << event_AddMaxHp;
	std::cout << event_GetHp << "��ŭ ü�� ȸ��" << std::endl;
	std::cout << event_AttackDamage << "��ŭ ���ݷ� ����"<<std::endl;
	std::cout << event_Shield << "��ŭ �� ����" << std::endl;
	std::cout << event_Cost << "��ŭ Cost �ִ�ġ ����" << std::endl;
	std::cout << event_GetGold << "��ŭ ��� ȹ��" << std::endl;
	Sleep(3000);
}

void Event::loadStory(int id)
{
	// ID�� ���� ĳ���� ������ �������� SELECT ���� �غ�
	std::string query = "SELECT * FROM GameStoryTable WHERE Story_Id = " + std::to_string(id);

	if (dbManager.ExecuteQuery(query)) {
		MYSQL_RES* result = dbManager.QueryResult();
		if (result && mysql_num_rows(result) > 0) {
			MYSQL_ROW row = mysql_fetch_row(result);
			event_Id = std::stoi(row[0]); // ù ��° ���� ID
			story_Name = row[1];          // �� ��° ���� �̸�
			story_Desc = row[2];          // �� ��° ���� ����
		}
		mysql_free_result(result); // ��� ���� ����
	}
	else {
		std::cerr << "Error fetching character info: " << dbManager.GetError() << std::endl;
	}
}

void Event::PrintStory()
{
	system("cls");
	std::cout << story_Name << std::endl;
	std::cout << story_Desc << std::endl;
	Sleep(5000);
}

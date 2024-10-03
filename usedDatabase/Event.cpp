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
	// ID에 따라 캐릭터 정보를 가져오는 SELECT 쿼리 준비
	std::string query = "SELECT * FROM EventTable WHERE event_Id = " + std::to_string(id);

	if (dbManager.ExecuteQuery(query)) {
		MYSQL_RES* result = dbManager.QueryResult();
		if (result && mysql_num_rows(result) > 0) {
			MYSQL_ROW row = mysql_fetch_row(result);
			event_Id = std::stoi(row[0]); // 첫 번째 열이 ID
			event_Name = row[1];          // 두 번째 열이 이름
			event_Desc = row[2];          // 세 번째 열이 설명
			event_AddMaxHp = std::stoi(row[3]); // 최대 체력 증가
			event_GetHp = std::stoi(row[4]); // HP 회복량
			event_AttackDamage = std::stoi(row[5]); // 데미지 증가량
			event_Shield = std::stoi(row[6]); // 방어도 증가
			event_Cost = std::stoi(row[7]); // Cost 최대치 증가
			event_GetGold = std::stoi(row[8]);	//Gold획득
		}
		mysql_free_result(result); // 결과 집합 해제
	}
	else {
		std::cerr << "Error fetching character info: " << dbManager.GetError() << std::endl;
	}
}

void Event::PrintEvent()
{
	system("cls");
	std::cout << "이벤트 발생!!" << std::endl;
	std::cout << event_Name << std::endl;
	std::cout << event_Desc << std::endl;
	std::cout << "최대 체력 증가: " << event_AddMaxHp;
	std::cout << event_GetHp << "만큼 체력 회복" << std::endl;
	std::cout << event_AttackDamage << "만큼 공격력 증가"<<std::endl;
	std::cout << event_Shield << "만큼 방어도 증가" << std::endl;
	std::cout << event_Cost << "만큼 Cost 최대치 증가" << std::endl;
	std::cout << event_GetGold << "만큼 골드 획득" << std::endl;
	Sleep(3000);
}

void Event::loadStory(int id)
{
	// ID에 따라 캐릭터 정보를 가져오는 SELECT 쿼리 준비
	std::string query = "SELECT * FROM GameStoryTable WHERE Story_Id = " + std::to_string(id);

	if (dbManager.ExecuteQuery(query)) {
		MYSQL_RES* result = dbManager.QueryResult();
		if (result && mysql_num_rows(result) > 0) {
			MYSQL_ROW row = mysql_fetch_row(result);
			event_Id = std::stoi(row[0]); // 첫 번째 열이 ID
			story_Name = row[1];          // 두 번째 열이 이름
			story_Desc = row[2];          // 세 번째 열이 설명
		}
		mysql_free_result(result); // 결과 집합 해제
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

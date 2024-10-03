#include<string>
#include "DatabaseManager.h"

#pragma once
class Event
{
protected:
	DatabaseManager& dbManager;

	int event_Id;
	std::string event_Name;
	std::string event_Desc;
	int event_AddMaxHp;
	int event_GetHp;
	int event_AttackDamage;
	int event_Shield;
	int event_Cost;
	int event_GetGold;

	//Story
	int story_Id;
	std::string story_Name;
	std::string story_Desc;

public:
	Event(DatabaseManager& db);
	std::string get_Name()const;
	std::string get_Desc()const;
	int AddMaxHp() const;
	int GetHp()const;
	int AddAtkDmg()const;
	int getShield()const;
	int AddCost()const;
	int getGold()const;
	void loadEventInfo(int id);	//DB에서 캐릭터 정보 로드
	void PrintEvent();
	void loadStory(int id);	//DB에서 Story정보 로드
	void PrintStory();
};


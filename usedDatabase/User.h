#include "DatabaseManager.h"

#pragma once
class User
{
private:
	DatabaseManager& dbManager;

public:
	User(DatabaseManager& db);
	bool registerUser(const std::string& loginId, const std::string& password, const std::string& name,
		const std::string& age, const std::string& Birth, const std::string& nickname);
	bool logIn(std::string& loginId, std::string& password);
};


#include "User.h"

/// <summary>
/// User에 대한 정보 DB에 추가 및 로그인기능
/// </summary>
/// <param name="db"></param>
User::User(DatabaseManager& db) : dbManager(db){}

//회원가입
bool User::registerUser(const std::string& loginId, const std::string& password, const std::string& name, const std::string& age, const std::string& Birth, const std::string& nickname)
{
	// INSERT 쿼리 준비
	std::string insertQuery = "INSERT INTO usertable (user_Loginid, user_Pw, user_Name, user_age, birthday, user_Nickname) VALUES ('"
		+ loginId + "', '" + password + "', '" + name + "', '" + age + "', '" + Birth + "', '" + nickname + "')";
	return dbManager.ExecuteQuery(insertQuery);
}

//로그인
bool User::logIn(std::string& loginId, std::string& password)
{
	// 로그인 쿼리 준비 (WHERE을 사용해 특정 조건에 부합하는 데이터만 조회 + 논리연산자 AND(좌우를 동시에 만족)를 통해 PW도 있다면 로그인)
	std::string loginQuery = "SELECT * FROM usertable WHERE user_Loginid = '" + loginId + "' AND user_Pw = '" + password + "'";
	if (dbManager.ExecuteQuery(loginQuery))
	{
		MYSQL_RES* result = dbManager.QueryResult();//쿼리 성공 시 결과를 담는 구조체 포인터에 Query결과로 초기화
		return mysql_num_rows(result) > 0;
	}
	return false;
}

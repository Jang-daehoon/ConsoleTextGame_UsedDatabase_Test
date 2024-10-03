#include<mysql.h>
#include<iostream>
#pragma comment(lib, "libmysql.lib")	//명시적인 라이브러리의 링크

#pragma once
/// <summary>
/// 데이터베이스 관리 매니저
/// </summary>
class DatabaseManager
{
private:
	MYSQL Conn;	//MySQL정보를 담을 구조체
	MYSQL* ConnPtr;	//MySQL 핸들
public:
	DatabaseManager();
	~DatabaseManager();
	
	bool Connect(const char* host, const char* user, const char* password, const char* database);	//DB 연결
	void Close();	//DB연결 해제
	bool ExecuteQuery(const std::string& query);	// DB로 쿼리문 전송
	MYSQL_RES* QueryResult();	//쿼리문 전송 성공 시 결과를 담는 구조체 포인터
	const char* GetError();	//에러 정보
};


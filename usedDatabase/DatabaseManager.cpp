#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
{
	mysql_init(&Conn);	//MySQL정보 초기화
	ConnPtr = nullptr;
}

DatabaseManager::~DatabaseManager()
{
	Close();
}
//DB 연결
bool DatabaseManager::Connect(const char* host, const char* user, const char* password, const char* database)
{
	ConnPtr = mysql_real_connect(&Conn, host, user, password, database, 3306, nullptr, 0);
	if (ConnPtr) {
		// 문자셋을 UTF-8로 설정 ->mysql 데이터를 받아왔을 때 받아온 데이터가 깨진다.
		// UTF-8과 euckr의 인코딩 방법이 달라 euckr로 변환하면 데이터가 문제없이 출력된다.
		mysql_set_character_set(ConnPtr, "euckr");
	}
	return ConnPtr != nullptr;
}

//DB 연결 종료
void DatabaseManager::Close()
{
	if (ConnPtr) {
		mysql_close(ConnPtr);
		ConnPtr = nullptr;
	}
}

bool DatabaseManager::ExecuteQuery(const std::string& query)
{
	return mysql_query(ConnPtr, query.c_str()) == 0;	//쿼리 요청 및 성공 여부 받아오기
}

MYSQL_RES* DatabaseManager::QueryResult()
{
	return mysql_store_result(ConnPtr);	//결과 확인하기
}

const char* DatabaseManager::GetError()
{
	return mysql_error(&Conn);	//Error
}

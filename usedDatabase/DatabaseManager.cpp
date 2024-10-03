#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
{
	mysql_init(&Conn);	//MySQL���� �ʱ�ȭ
	ConnPtr = nullptr;
}

DatabaseManager::~DatabaseManager()
{
	Close();
}
//DB ����
bool DatabaseManager::Connect(const char* host, const char* user, const char* password, const char* database)
{
	ConnPtr = mysql_real_connect(&Conn, host, user, password, database, 3306, nullptr, 0);
	if (ConnPtr) {
		// ���ڼ��� UTF-8�� ���� ->mysql �����͸� �޾ƿ��� �� �޾ƿ� �����Ͱ� ������.
		// UTF-8�� euckr�� ���ڵ� ����� �޶� euckr�� ��ȯ�ϸ� �����Ͱ� �������� ��µȴ�.
		mysql_set_character_set(ConnPtr, "euckr");
	}
	return ConnPtr != nullptr;
}

//DB ���� ����
void DatabaseManager::Close()
{
	if (ConnPtr) {
		mysql_close(ConnPtr);
		ConnPtr = nullptr;
	}
}

bool DatabaseManager::ExecuteQuery(const std::string& query)
{
	return mysql_query(ConnPtr, query.c_str()) == 0;	//���� ��û �� ���� ���� �޾ƿ���
}

MYSQL_RES* DatabaseManager::QueryResult()
{
	return mysql_store_result(ConnPtr);	//��� Ȯ���ϱ�
}

const char* DatabaseManager::GetError()
{
	return mysql_error(&Conn);	//Error
}

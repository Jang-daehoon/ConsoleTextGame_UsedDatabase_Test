#include<mysql.h>
#include<iostream>
#pragma comment(lib, "libmysql.lib")	//������� ���̺귯���� ��ũ

#pragma once
/// <summary>
/// �����ͺ��̽� ���� �Ŵ���
/// </summary>
class DatabaseManager
{
private:
	MYSQL Conn;	//MySQL������ ���� ����ü
	MYSQL* ConnPtr;	//MySQL �ڵ�
public:
	DatabaseManager();
	~DatabaseManager();
	
	bool Connect(const char* host, const char* user, const char* password, const char* database);	//DB ����
	void Close();	//DB���� ����
	bool ExecuteQuery(const std::string& query);	// DB�� ������ ����
	MYSQL_RES* QueryResult();	//������ ���� ���� �� ����� ��� ����ü ������
	const char* GetError();	//���� ����
};


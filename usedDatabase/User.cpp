#include "User.h"

/// <summary>
/// User�� ���� ���� DB�� �߰� �� �α��α��
/// </summary>
/// <param name="db"></param>
User::User(DatabaseManager& db) : dbManager(db){}

//ȸ������
bool User::registerUser(const std::string& loginId, const std::string& password, const std::string& name, const std::string& age, const std::string& Birth, const std::string& nickname)
{
	// INSERT ���� �غ�
	std::string insertQuery = "INSERT INTO usertable (user_Loginid, user_Pw, user_Name, user_age, birthday, user_Nickname) VALUES ('"
		+ loginId + "', '" + password + "', '" + name + "', '" + age + "', '" + Birth + "', '" + nickname + "')";
	return dbManager.ExecuteQuery(insertQuery);
}

//�α���
bool User::logIn(std::string& loginId, std::string& password)
{
	// �α��� ���� �غ� (WHERE�� ����� Ư�� ���ǿ� �����ϴ� �����͸� ��ȸ + �������� AND(�¿츦 ���ÿ� ����)�� ���� PW�� �ִٸ� �α���)
	std::string loginQuery = "SELECT * FROM usertable WHERE user_Loginid = '" + loginId + "' AND user_Pw = '" + password + "'";
	if (dbManager.ExecuteQuery(loginQuery))
	{
		MYSQL_RES* result = dbManager.QueryResult();//���� ���� �� ����� ��� ����ü �����Ϳ� Query����� �ʱ�ȭ
		return mysql_num_rows(result) > 0;
	}
	return false;
}

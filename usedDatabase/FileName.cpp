#include<iostream>
#include<mysql.h>
#pragma comment(lib, "libmysql.lib")	//������� ���̺귯���� ��ũ
using namespace std;

int main()
{
	cout << mysql_get_client_info() << "\n";	//mySQL client ���� ->���� �� �Ȱ��� Ȯ�ο�

	MYSQL Conn;	//MySQL������ ���� ����ü
	MYSQL* ConnPtr = NULL;	//MySQL �ڵ�

	MYSQL_RES* Result;	//���� ���� �� ����� ��� ����ü ������
	MYSQL_ROW Row;	//���� ���� �� ����� ���� ���� ������ ��� ����ü
	int Stat;	//���� ��û �� ���(����, ����)

	mysql_init(&Conn);	//MySQL���� �ʱ�ȭ

	//�����ͺ��̽��� ����
	ConnPtr = mysql_real_connect(&Conn, "127.0.0.1", "root", "1234", "userdata", 3306, (char*)NULL, 0);
	//���� ��� Ȯ��, NULL�� ��� ���� ����
	if (ConnPtr == NULL)
	{
		cout << stderr << "Mysql connection error : " << mysql_error(&Conn);
		return 1;
	}

	//���� ������ (����� ���̺��� ������ ��ȸ)
	const char* Query = "SELECT * FROM usertable";
	Stat = mysql_query(ConnPtr, Query);	//���� ��û �� ���� ���� �޾ƿ���
	if (Stat != 0)
	{
		cout << stderr << "Mysql query error : \n" << mysql_error(&Conn);	//���۾��� �ٷ�����ϴ� stderr�� ����� ����ϱ⿡ ���� ������ �����޽��� ��°���.
		return 1;
	}
	Result = mysql_store_result(ConnPtr);	//��� Ȯ���ϱ�
	while ((Row = mysql_fetch_row(Result)) != NULL)	//��� ����ϱ�
	{
		cout << "-----------------------------------------" << endl;
		//user_Id, user_Loginid ,user_Pw, user_Name, user_age, birthday, user_Nickname
		cout << "UID: " << Row[0] << "\n" << "Login_Id: " << Row[1] << "\n" << "User PW: " << Row[2] << "\n" << "User Name : " << Row[3] << "\n" << "User Age: "
			<< Row[4] << "\n" << "User Birthday:" << Row[5] << "\n" << "User Nickname : " << Row[6] << "\n";
		cout << "-----------------------------------------"<<endl;
	}
	mysql_free_result(Result);	//��� ����

	// ����� �Է� �ޱ� ->DB�� ������ �����ϱ� ������ �̴� ȸ������ ����Դϴ�.
	/*
	string loginId, userPw, userName, userAge, birthday, userNickname;
	cout << "Login ID�� �Է��ϼ���(�ִ� 20�� - �������� ����� �� �����ϴ�.): ";
	cin >> loginId;
	cout << "User Password�� �Է��ϼ���(�ִ� 10�� - �������� ����� �� �����ϴ�.): ";
	cin >> userPw;
	cout << "User Name�� �Է��ϼ���(�ִ� 10�� - �������� ����� �� �����ϴ�.): ";
	cin >> userName;
	cout << "User Age�� �Է��ϼ���(����� �Է°���): ";
	cin >> userAge;
	cout << "Birthday (YYYY-MM-DD)�� �Է��ϼ���(�������� ����� �� �����ϴ�.): ";
	cin >> birthday;
	cout << "User Nickname�� �Է��ϼ���(�ִ� 10�� - �������� ����� �� �����ϴ�.): ";
	cin >> userNickname;

	// INSERT ���� �غ�
	string insertQuery = "INSERT INTO usertable (user_Loginid, user_Pw, user_Name, user_age, birthday, user_Nickname) VALUES ('"
		 + loginId + "', '" + userPw + "', '" + userName + "', '" + userAge + "', '" + birthday + "', '" + userNickname + "')";

	// INSERT ���� ����
	Stat = mysql_query(ConnPtr, insertQuery.c_str()); // ���� ����
	if (Stat != 0) {
		cerr << "MySQL ���� ����: " << mysql_error(&Conn) << endl;
	}
	else {
		cout << "����ڰ� ���������� �߰��Ǿ����ϴ�!" << endl;
	}
	*/

	// �α��� ��� �߰� ��й�ȣ�� �Ⱥ��̰�
	string loginIdInput, userPwInput;
	cout << "\n�α��� �Ͻ÷��� Login ID�� Password�� �Է��ϼ���.\n";
	cout << "Login ID: ";
	cin >> loginIdInput;
	cout << "Password: ";
	cin >> userPwInput;

	// �α��� ���� �غ� (WHERE�� ����� Ư�� ���ǿ� �����ϴ� �����͸� ��ȸ + �������� AND(�¿츦 ���ÿ� ����)�� ���� PW�� �ִٸ� �α���)
	string loginQuery = "SELECT * FROM usertable WHERE user_Loginid = '" + loginIdInput + "' AND user_Pw = '" + userPwInput + "'";

	// �α��� ���� ����
	Stat = mysql_query(ConnPtr, loginQuery.c_str());
	if (Stat != 0) {
		cerr << "Mysql query error: " << mysql_error(&Conn) << endl;
	}
	else {
		Result = mysql_store_result(ConnPtr);
		if (mysql_num_rows(Result) > 0) {
			cout << "�α��� ����!\n";
			// �α��� ���� �� �߰� ����
			while ((Row = mysql_fetch_row(Result)) != NULL) {
				cout << "Welcome, " << Row[3] << "!" << endl; // ������� �̸� ���
			}
		}
		else {
			cout << "�α��� ����: �߸��� ID �Ǵ� ��й�ȣ�Դϴ�." << endl;
		}
	}

	//�����ͺ��̽��� ���� ����
	mysql_close(ConnPtr);
	//������ -> 

	//1. ȸ������
	//2. �α���
	//3. pwã��
	//-----
	//4. ������ ĳ���� ���� ���� ->playerChar_data(Stat) || MosterData(stat), itemTalbe(info) 
	// 
	//  �� ĳ���͸��� �ɷ� �� ������ ī�尡 
	// ĳ���� ID 1. ���, 2.������, 3. ����
	// �� ���� ĳ������ Cost�� ȸ���Ǹ� ���� �ൿ�� �����ϰ� ���õȴ�. Cost�ѵ� ������ ��ų�� ����� ���� ����Ʈ�� �� �ִ�. �÷��̾ ���� �����ϸ� ���� �ൿ�� ���۵ȴ�.
	// SavePoint�� ����. ��������.
	// ����Ǵ� ���� -> �÷��̾�ĳ���� ����, �������� ī���� ����, ���� ���൵�� ���� ����.
	// ������ ����Ǹ� ������ ȹ�� -> 3���� ������ �ϳ��� ���� - ������ ������ ���� Gold�� ��� ���󿡼� ȹ���� ���������� �ε� �ְ� Status�� �����ϰų� ���ο� ��ų�� ȹ���ϰų� �Ѵ�.
	// ������ ����Ǹ� ���� ���������� �̵��Ǵµ� Ȯ�������� ���� Ȥ�� �̺�Ʈ�� �߻��Ѵ�. ���Ϳ����� ü���� ȸ���� �� �ִ�. �̺�Ʈ�� �������ͽ��� �����Ҽ��� ������ �ɷ� ���ظ� �԰ų� ������ ȹ���� ��带 ȹ���ϴ� �� �������� ���丮���� ��Ȳ�� �����Ѵ�.
	// ������������ ������ ���͵��� ��ȯ�Ǹ� �����ϸ� �� ���������� �������� ������ �ִ�. 
	// ��� �� ����� ������ ����
	// 
	// Database ������ ĳ����
	//5 ->���� -> ��������
	//6. �ε� -> DB-> Console�� ������ �ҷ�����

}

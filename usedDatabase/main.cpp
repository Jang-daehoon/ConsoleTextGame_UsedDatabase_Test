#include<iostream>
#include"DatabaseManager.h"
#include"GameManager.h"
#include"User.h"
#include"Character.h"
#pragma comment(lib, "libmysql.lib")	//������� ���̺귯���� ��ũ


int main()
{
	//�α��� �� ȸ�������� ���� userData DB����
	DatabaseManager dbManager;
	GameManager gameManager(dbManager);


	//�ܼ� Size ����
	system("mode con: cols=100 lines=50");
	system("title Welcome to Dungeon Express");	//�̸� ����
	gameManager.gotoxy(30, 0); std::cout << "Game Database Ver." << mysql_get_client_info() << "\n";	//mySQL client ���� ->���� �� �Ȱ��� Ȯ�ο�

	gameManager.GameStart();

	if (!dbManager.Connect("127.0.0.1", "root", "1234", "userdata"))
	{
		//���۾��� �ٷ�����ϴ� stderr�� ����� ����ϱ⿡ ���� ������ �����޽��� ��°���.
		std:: cout<< stderr << "Database connection error"<< std::endl;
		return 1;
	}
	

	//ȸ������
	gameManager.GameRegister();
	//�α���
	gameManager.GameLogin();
	dbManager.Close();

	// �����ͺ��̽� ����
	if (!dbManager.Connect("127.0.0.1", "root", "1234", "CharacterInfo"))
	{
		dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
		//���۾��� �ٷ�����ϴ� stderr�� ����� ����ϱ⿡ ���� ������ �����޽��� ��°���.
		std::cout << stderr << "Database connection error" << std::endl;
		return 1;
	}

	system("cls");
	gameManager.SelectCharacter();	// ĳ���� ���� �޼ҵ� ȣ��	
	Sleep(500);
	system("cls");
	gameManager.CharacterStatus();//  ȭ�� ǥ��

	dbManager.Close();
	// �����ͺ��̽� ����
	if (!dbManager.Connect("127.0.0.1", "root", "1234", "MonsterData"))
	{
		dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
		//���۾��� �ٷ�����ϴ� stderr�� ����� ����ϱ⿡ ���� ������ �����޽��� ��°���.
		std::cout << stderr << "Database connection error" << std::endl;
		return 1;
	}

	gameManager.SelectMonster();	//���� ����
	dbManager.Close();

	//���ѷα� ���
//DB�� �ִ� ���ѷα� ��ũ��Ʈ�� �����ͼ� ���
	if (!dbManager.Connect("127.0.0.1", "root", "1234", "EVENTDATA"))
	{
		dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
		//���۾��� �ٷ�����ϴ� stderr�� ����� ����ϱ⿡ ���� ������ �����޽��� ��°���.
		std::cout << stderr << "Database connection error" << std::endl;
		return 1;
	}
	gameManager.SelectTutoStory();
	dbManager.Close();
	//std::cout << gameManager.selectedCharacter.get_curhp() << std::endl;	//->ü�� Ȯ��
	
	//ĳ���� ���� �� Main Game����
	while (gameManager.getcurStage() != gameManager.getlastStage())
	{
		gameManager.BattleUI();
		if (gameManager.selectedMonster.get_curhp() <= 0)
		{
			Sleep(1000);
			//���� óġ �Ϸ�
			std::cout << "���� óġ�߽��ϴ�.(������ �����Ͻʽÿ�.)" << std::endl;
			// �����ͺ��̽� ����
			if (!dbManager.Connect("127.0.0.1", "root", "1234", "EVENTDATA"))
			{
				dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
				//���۾��� �ٷ�����ϴ� stderr�� ����� ����ϱ⿡ ���� ������ �����޽��� ��°���.
				std::cout << stderr << "Database connection error" << std::endl;
				return 1;
			}
			gameManager.selectedCharacter.recovery_Cost();
			//���� ���� �޼��� ȣ��
			gameManager.SelectEvent();
			dbManager.Close();
			//���� Stage Event ȣ�� ���� -> �ٷ� ����, �̺�Ʈ Stage ->�̺�Ʈ ���� �� ����
			gameManager.setcurStage();	//�������� ����
			gameManager.setMonsterIndex();
			// �����ͺ��̽� ����
			if (!dbManager.Connect("127.0.0.1", "root", "1234", "MonsterData"))
			{
				dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
				//���۾��� �ٷ�����ϴ� stderr�� ����� ����ϱ⿡ ���� ������ �����޽��� ��°���.
				std::cout << stderr << "Database connection error" << std::endl;
				return 1;
			}

			gameManager.SelectMonster();	//���� ����
			dbManager.Close();
		}
		else if (gameManager.selectedCharacter.get_curhp() <= 0)
		{
			//DB ->> ��� ���� ���
			if (!dbManager.Connect("127.0.0.1", "root", "1234", "EVENTDATA"))
			{
				dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
				//���۾��� �ٷ�����ϴ� stderr�� ����� ����ϱ⿡ ���� ������ �����޽��� ��°���.
				std::cout << stderr << "Database connection error" << std::endl;
				return 1;
			}
			gameManager.SelectEnding(2);
			dbManager.Close();
			//Save Data ����

			//���� ��������
			gameManager.GameExit();
		}

		//����


		//���� �߰��� ����
		//���� ->���� -> ����Stage ���� (�ݺ�)
		// ����-> 3���� ���� �� �Ѱ��� 1, 2, 3 �Է��� ���� ȹ��
		// �� ������ ���� ���� �������� �����Ǹ� ���� ���� �� MonsterDB�� ���� ������ �������� ��ġ�ϴ� MonsterID�� ���� 
		// ���͸� ��ȯ�Ѵ�. ��ó�� EVENT�� �����ϴ�. �������� EVENT DB�� ���� ��ġ�ϴ� EVENT�� ȣ���Ѵ�. 
		// �̺�Ʈ���� ->Event�� ���� ���� ���� ����, ���� ����, ������ ���� ���ظ� �Դ´�. ���� ����� �ܼ��� ������ ������ �̺�Ʈ�� ���
		// �̺�Ʈ�� ������ ���� ������ ���� ���� �ƴ� ���Ϳ��� ������ ����ȴ�.
		//STAGE-> �����Ѵ�. ���� STAGE ���� �� Boss���Ϳ� ���� 
		// ������ Cost�� ��� �Ҹ�� �� ���� �����ൿ ���� ���� Cost�� �������� ��� �� �ѱ�� �ൿ�� ���� Turn�� ������ �� �ִ�.
		//BOSS MONSTER�� óġ�ϸ� ����
		//�����ϸ� �й迣�� �� ���� ������ ����.
	}
	std::cout << "��� ���� óġ�� ����� ������ ��Ż ���� ������ ����Ʈ���� Ż���� �����մϴ�." << std::endl;
	//Nomal Ending - A
	if (!dbManager.Connect("127.0.0.1", "root", "1234", "EVENTDATA"))
	{
		dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
		//���۾��� �ٷ�����ϴ� stderr�� ����� ����ϱ⿡ ���� ������ �����޽��� ��°���.
		std::cout << stderr << "Database connection error" << std::endl;
		return 1;
	}
	gameManager.SelectEnding(3);
	dbManager.Close();
}

#include "GameManager.h"



GameManager::GameManager(DatabaseManager& db)
    : dbManager(db), user(db), selectedCharacter(db), selectedMonster(db), selectEvent(db), curDungeonStage(0), lastDungeonStage(10), MonsterIndex(1){}

void GameManager::GameStart()
{
    gotoxy(20, 1); std::cout << "���������������������" << "\n";
    gotoxy(20, 2); std::cout << "========================================" << "\n";
    gotoxy(20, 3); std::cout << "|  #       #   ########   ######       |" << "\n";
    gotoxy(20, 4); std::cout << "|  #  #   #       ##      #     #      |" << "\n";
    gotoxy(20, 5); std::cout << "|  # # # #        ##      #     #      |" << "\n";
    gotoxy(20, 6); std::cout << "|  ##   ##        ##      #    #       |" << "\n";
    gotoxy(20, 7); std::cout << "|  #    #         ##      #####        |" << "\n";
    gotoxy(20, 8); std::cout << "========================================" << "\n";
    gotoxy(20, 9); std::cout << "���������������������" << "\n";
    gotoxy(25, 11); std::cout << "Welcome to Dungeon Express" << "\n";
    gotoxy(35, 13); std::cout << "Game Start" << "\n";
    gotoxy(35, 14); std::cout << "Game Exit" << "\n";
    gotoxy(35, 15); std::cout << "\n";
    gotoxy(20, 16); std::cout << "���������������������" << "\n";
}

void GameManager::GameLogin()
{
    std::string loginIdInput, userPwInput;
    std::cout << "\n�α��� �Ͻ÷��� Login ID�� Password�� �Է��ϼ���.\n";
    std::cout << "Login ID: ";
    std::cin >> loginIdInput;
    std::cout << "Password: ";
    std::cin >> userPwInput;

    if (user.logIn(loginIdInput, userPwInput))
    {
        std::cout << "�α��� �Ϸ�!" << std::endl;
    }
    else
    {
        std::cerr << "�α��� ����: " << dbManager.GetError() << "\n"; // ���� ���� ���
        std::cout << "�ٽ� �α����ϼ���." << std::endl;
        GameLogin();
    }
}

void GameManager::GameRegister()
{
    std::string loginId, userPw, userName, userAge, birthday, userNickname;
    std::cout << "ȸ�������� �����մϴ�." << "\n";
    std::cout << "Login ID�� �Է��ϼ���(�ִ� 20�� - �������� ����� �� �����ϴ�.): ";
    std::cin >> loginId;
    std::cout << "User Password�� �Է��ϼ���(�ִ� 10�� - �������� ����� �� �����ϴ�.): ";
    std::cin >> userPw;
    std::cout << "User Name�� �Է��ϼ���(�ִ� 10�� - �������� ����� �� �����ϴ�.): ";
    std::cin >> userName;
    std::cout << "User Age�� �Է��ϼ���(����� �Է°���): ";
    std::cin >> userAge;
    std::cout << "Birthday (YYYY-MM-DD)�� �Է��ϼ���(�������� ����� �� �����ϴ�.): ";
    std::cin >> birthday;
    std::cout << "User Nickname�� �Է��ϼ���(�ִ� 10�� - �������� ����� �� �����ϴ�.): ";
    std::cin >> userNickname;

    if (user.registerUser(loginId, userPw, userName, userAge, birthday, userNickname))
    {
        std::cout << "ȸ�������� �Ϸ�Ǿ����ϴ�.\n";
    }
    else
    {
        std::cerr << "ȸ������ ���� : " << dbManager.GetError() << "\n"; // ���� �����ڵ� ���
        std::cout << "�ٽ� �Է��ϼ���." << std::endl;
        GameRegister();
    }
}

void GameManager::SelectCharacter()
{
    int choice;

    std::cout << "���������������������" << "\n";
    std::cout << "ĳ���͸� �������ּ���." << "\n";
    std::cout << "1. ����" << "\n";
    std::cout << "2. ������ ĳ�����Դϴ�." << "\n";
    std::cout << "������..." << "\n";
    std::cout << "���������������������" << "\n";
    std::cin >> choice; // ĳ���� ����

    switch (choice)
    {
    case 1:
        std::cout << "���縦 �����Ͽ����ϴ�." << std::endl;
        SaveSelectData(choice);
        break;
    case 2:
    case 3:
        SaveSelectData(choice);
        std::cout << "������ ĳ�����Դϴ�." << std::endl;
        break;
    default:
        std::cout << "�߸��� ��ȣ�� �����߽��ϴ�. �ٽ� �Է��ϼ���."<<::std::endl;
        SelectCharacter();
    }
}

void GameManager::SelectMonster()
{
    LoadMonsterInitData(MonsterIndex);
}

void GameManager::SelectEvent()
{
    // ������ �õ带 �����Ͽ� �Ź� �ٸ� ���� �������� ����
    std::srand(static_cast<unsigned int>(std::time(0)));

    // 1���� 3 ������ ������ eventId ����
    int eventId = std::rand() % 3 + 1;

    selectEvent.loadEventInfo(eventId);

    //�޾ƿ� id�� ���� �ɷ�ġ�� ���� �ڱ� ����
    switch (eventId)
    {
    case 1:
        selectedCharacter.Set_Maxhp(selectEvent.AddMaxHp());
        break;
    case 2:
        selectedCharacter.set_Shield(selectEvent.getShield());
        break;
    case 3:
        selectedCharacter.Set_Curhp(selectEvent.GetHp());
        break;
    }
    selectEvent.PrintEvent();

}

void GameManager::SelectTutoStory()
{
    selectEvent.loadStory(1);
    selectEvent.PrintStory();   //Ʃ�丮�� ���
}

void GameManager::SelectEnding(int EndingId)
{
    selectEvent.loadStory(EndingId);
    selectEvent.PrintStory();   //Ʃ�丮�� ���
}

void GameManager::SaveSelectData(int choiceData)
{
    std::cout << "�����մϴ�.\n";
    selectedCharacter.loadCharacterInfo(choiceData); // ������ ĳ������ ���� �ε�
    // ������ ���� CharacterInfoData�� ������ ĳ���� ����ID, userData�� �ִ� UID, userData�� �ִ� userNickname
}

void GameManager::LoadCharacterInitData(int characterId)
{
    selectedCharacter.loadCharacterInfo(characterId); // ����: �ӽ� Character �ν��Ͻ� ��� selectedCharacter ���
    selectedCharacter.CharacterInfo(); // ĳ���� ������ ����ϴ� �޼ҵ� ȣ��
}
void GameManager::LoadMonsterInitData(int monsterId)
{
    selectedMonster.loadMonsterInfo(monsterId);
    selectedMonster.MonsterInfo();
}

void GameManager::GameExit()
{
    exit(0);
}

void GameManager::gotoxy(int x, int y)
{
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) }; // x, y ��ǥ ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // pos ��ġ�� Ŀ���� �̵�
}

void GameManager::CharacterStatus()
{
    std::cout << "������������������������" << "\n";
    std::cout << "ĳ���� �̸�: " << selectedCharacter.get_Name() << "\n";
    std::cout << "�ִ� ü��: " << selectedCharacter.get_Maxhp() << " / " << "���� ü��: " << selectedCharacter.get_curhp() << "\n";
    std::cout << "������: " << selectedCharacter.get_Attackdmg() << "\n";
    std::cout << "�������� ���差: " << selectedCharacter.get_Shield() << "\n";
    std::cout << "Cost: " << selectedCharacter.get_Cost() << "\n";
    std::cout << "�������� �ݾ�: " << selectedCharacter.get_Initialfunds() << "\n";
    std::cout << "������������������������" << "\n";
}

void GameManager::MonsterStatus()
{
    std::cout << "������������������������" << "\n";
    std::cout << "���� �̸�: " << selectedMonster.get_Name() << "\n"; // ����: ĳ���� �̸����� ���� �̸����� ����
    std::cout << "�ִ� ü��: " << selectedMonster.get_Maxhp() << " / " << "���� ü��: " << selectedMonster.get_curhp() << "\n";
    std::cout << "������: " << selectedMonster.get_Attackdmg() << "\n";
    std::cout << "�������� ���差: " << selectedMonster.get_Shield() << "\n";
    std::cout << "�����: " << selectedMonster.get_Initialfunds() << "\n";
    std::cout << "������������������������" << "\n";
}

void GameManager::PrinStory()
{
}

void GameManager::BattleUI()
{
    system("cls");
    CharacterStatus();
    MonsterStatus();
    std::cout << "����(cost1 �Ҹ�): 1 ���(cost1 �Ҹ�):2 (�����ൿ�� �����ϼ���.) -  ���� Cost: " << selectedCharacter .get_Cost()<< std::endl;
    if (selectedCharacter.get_Cost() > 0)
    {
        BattleChoice();
        Sleep(500);
    }
    else
    {
        //�� ����
        std::cout << "��� Cost�� �Ҹ��� ���� ����˴ϴ�." << std::endl;
        Sleep(1000);
        //���� �ൿ
        std::cout << selectedMonster.get_Name() << "�̰� " << selectedCharacter.get_Name() << "���� " << selectedMonster.get_Attackdmg() << "�� ���ظ� �������ϴ�." << std::endl;
        selectedCharacter.Hit(selectedMonster.get_Attackdmg());
        //���� �ൿ ���� �� Cost �ʱ�ȭ
        selectedCharacter.recovery_Cost();
        Sleep(1000);
        system("cls");
    }

}

void GameManager::BattleChoice()
{
    int battleChoice = 0;
    std::cin >> battleChoice;

    switch (battleChoice)
    {
    case 1:
        std::cout << selectedCharacter.get_Name() << "��(��) " << selectedMonster.get_Name() << "���� " << selectedCharacter.get_Attackdmg() << "�� ���ظ� �������ϴ�." << std::endl;
        selectedCharacter.set_Cost();   //Cost�Ҹ�
        selectedMonster.Hit(selectedCharacter.get_Attackdmg());
        break;
    case 2:
        std::cout << selectedCharacter.get_Name() << "��(��) " << "2 ��ŭ�� ���� ȹ���Ͽ����ϴ�." << std::endl;
        selectedCharacter.set_Cost();   //Cost�Ҹ�
        selectedCharacter.set_Shield(2);    
        break;
    
    default:
        std::cout << "�߸��� Ű �Է��� �߽��ϴ�." << std::endl;
    }

}

int GameManager::getcurStage() const
{
    return curDungeonStage;
}

int GameManager::getlastStage() const
{
    return lastDungeonStage;
}

void GameManager::setcurStage()
{
    curDungeonStage++;
}

void GameManager::setMonsterIndex()
{
    MonsterIndex++;
}

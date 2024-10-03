#include "GameManager.h"



GameManager::GameManager(DatabaseManager& db)
    : dbManager(db), user(db), selectedCharacter(db), selectedMonster(db), selectEvent(db), curDungeonStage(0), lastDungeonStage(10), MonsterIndex(1){}

void GameManager::GameStart()
{
    gotoxy(20, 1); std::cout << "■■■■■■■■■■■■■■■■■■■■" << "\n";
    gotoxy(20, 2); std::cout << "========================================" << "\n";
    gotoxy(20, 3); std::cout << "|  #       #   ########   ######       |" << "\n";
    gotoxy(20, 4); std::cout << "|  #  #   #       ##      #     #      |" << "\n";
    gotoxy(20, 5); std::cout << "|  # # # #        ##      #     #      |" << "\n";
    gotoxy(20, 6); std::cout << "|  ##   ##        ##      #    #       |" << "\n";
    gotoxy(20, 7); std::cout << "|  #    #         ##      #####        |" << "\n";
    gotoxy(20, 8); std::cout << "========================================" << "\n";
    gotoxy(20, 9); std::cout << "■■■■■■■■■■■■■■■■■■■■" << "\n";
    gotoxy(25, 11); std::cout << "Welcome to Dungeon Express" << "\n";
    gotoxy(35, 13); std::cout << "Game Start" << "\n";
    gotoxy(35, 14); std::cout << "Game Exit" << "\n";
    gotoxy(35, 15); std::cout << "\n";
    gotoxy(20, 16); std::cout << "■■■■■■■■■■■■■■■■■■■■" << "\n";
}

void GameManager::GameLogin()
{
    std::string loginIdInput, userPwInput;
    std::cout << "\n로그인 하시려면 Login ID와 Password를 입력하세요.\n";
    std::cout << "Login ID: ";
    std::cin >> loginIdInput;
    std::cout << "Password: ";
    std::cin >> userPwInput;

    if (user.logIn(loginIdInput, userPwInput))
    {
        std::cout << "로그인 완료!" << std::endl;
    }
    else
    {
        std::cerr << "로그인 실패: " << dbManager.GetError() << "\n"; // 현재 에러 출력
        std::cout << "다시 로그인하세요." << std::endl;
        GameLogin();
    }
}

void GameManager::GameRegister()
{
    std::string loginId, userPw, userName, userAge, birthday, userNickname;
    std::cout << "회원가입을 시작합니다." << "\n";
    std::cout << "Login ID를 입력하세요(최대 20자 - 공란으로 비워둘 수 없습니다.): ";
    std::cin >> loginId;
    std::cout << "User Password를 입력하세요(최대 10자 - 공란으로 비워둘 수 없습니다.): ";
    std::cin >> userPw;
    std::cout << "User Name을 입력하세요(최대 10자 - 공란으로 비워둘 수 없습니다.): ";
    std::cin >> userName;
    std::cout << "User Age를 입력하세요(양수만 입력가능): ";
    std::cin >> userAge;
    std::cout << "Birthday (YYYY-MM-DD)를 입력하세요(공란으로 비워둘 수 없습니다.): ";
    std::cin >> birthday;
    std::cout << "User Nickname을 입력하세요(최대 10자 - 공란으로 비워둘 수 없습니다.): ";
    std::cin >> userNickname;

    if (user.registerUser(loginId, userPw, userName, userAge, birthday, userNickname))
    {
        std::cout << "회원가입이 완료되었습니다.\n";
    }
    else
    {
        std::cerr << "회원가입 실패 : " << dbManager.GetError() << "\n"; // 현재 에러코드 출력
        std::cout << "다시 입력하세요." << std::endl;
        GameRegister();
    }
}

void GameManager::SelectCharacter()
{
    int choice;

    std::cout << "■■■■■■■■■■■■■■■■■■■■" << "\n";
    std::cout << "캐릭터를 선택해주세요." << "\n";
    std::cout << "1. 전사" << "\n";
    std::cout << "2. 관리자 캐릭터입니다." << "\n";
    std::cout << "구현중..." << "\n";
    std::cout << "■■■■■■■■■■■■■■■■■■■■" << "\n";
    std::cin >> choice; // 캐릭터 선택

    switch (choice)
    {
    case 1:
        std::cout << "전사를 선택하였습니다." << std::endl;
        SaveSelectData(choice);
        break;
    case 2:
    case 3:
        SaveSelectData(choice);
        std::cout << "관리자 캐릭터입니다." << std::endl;
        break;
    default:
        std::cout << "잘못된 번호를 선택했습니다. 다시 입력하세요."<<::std::endl;
        SelectCharacter();
    }
}

void GameManager::SelectMonster()
{
    LoadMonsterInitData(MonsterIndex);
}

void GameManager::SelectEvent()
{
    // 무작위 시드를 설정하여 매번 다른 값이 나오도록 설정
    std::srand(static_cast<unsigned int>(std::time(0)));

    // 1에서 3 사이의 랜덤한 eventId 생성
    int eventId = std::rand() % 3 + 1;

    selectEvent.loadEventInfo(eventId);

    //받아온 id에 따라 능력치및 보유 자금 증가
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
    selectEvent.PrintStory();   //튜토리얼 출력
}

void GameManager::SelectEnding(int EndingId)
{
    selectEvent.loadStory(EndingId);
    selectEvent.PrintStory();   //튜토리얼 출력
}

void GameManager::SaveSelectData(int choiceData)
{
    std::cout << "저장합니다.\n";
    selectedCharacter.loadCharacterInfo(choiceData); // 선택한 캐릭터의 정보 로드
    // 저장할 정보 CharacterInfoData의 선택한 캐릭터 직업ID, userData에 있는 UID, userData에 있는 userNickname
}

void GameManager::LoadCharacterInitData(int characterId)
{
    selectedCharacter.loadCharacterInfo(characterId); // 수정: 임시 Character 인스턴스 대신 selectedCharacter 사용
    selectedCharacter.CharacterInfo(); // 캐릭터 정보를 출력하는 메소드 호출
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
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) }; // x, y 좌표 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // pos 위치에 커서를 이동
}

void GameManager::CharacterStatus()
{
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■" << "\n";
    std::cout << "캐릭터 이름: " << selectedCharacter.get_Name() << "\n";
    std::cout << "최대 체력: " << selectedCharacter.get_Maxhp() << " / " << "현재 체력: " << selectedCharacter.get_curhp() << "\n";
    std::cout << "데미지: " << selectedCharacter.get_Attackdmg() << "\n";
    std::cout << "보유중인 쉴드량: " << selectedCharacter.get_Shield() << "\n";
    std::cout << "Cost: " << selectedCharacter.get_Cost() << "\n";
    std::cout << "보유중인 금액: " << selectedCharacter.get_Initialfunds() << "\n";
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■" << "\n";
}

void GameManager::MonsterStatus()
{
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■" << "\n";
    std::cout << "몬스터 이름: " << selectedMonster.get_Name() << "\n"; // 수정: 캐릭터 이름에서 몬스터 이름으로 변경
    std::cout << "최대 체력: " << selectedMonster.get_Maxhp() << " / " << "현재 체력: " << selectedMonster.get_curhp() << "\n";
    std::cout << "데미지: " << selectedMonster.get_Attackdmg() << "\n";
    std::cout << "보유중인 쉴드량: " << selectedMonster.get_Shield() << "\n";
    std::cout << "현상금: " << selectedMonster.get_Initialfunds() << "\n";
    std::cout << "■■■■■■■■■■■■■■■■■■■■■■■" << "\n";
}

void GameManager::PrinStory()
{
}

void GameManager::BattleUI()
{
    system("cls");
    CharacterStatus();
    MonsterStatus();
    std::cout << "공격(cost1 소모): 1 방어(cost1 소모):2 (전투행동을 선택하세요.) -  남은 Cost: " << selectedCharacter .get_Cost()<< std::endl;
    if (selectedCharacter.get_Cost() > 0)
    {
        BattleChoice();
        Sleep(500);
    }
    else
    {
        //턴 종료
        std::cout << "모든 Cost를 소모해 턴이 종료됩니다." << std::endl;
        Sleep(1000);
        //몬스터 행동
        std::cout << selectedMonster.get_Name() << "이가 " << selectedCharacter.get_Name() << "에게 " << selectedMonster.get_Attackdmg() << "의 피해를 입혔습니다." << std::endl;
        selectedCharacter.Hit(selectedMonster.get_Attackdmg());
        //몬스터 행동 종료 시 Cost 초기화
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
        std::cout << selectedCharacter.get_Name() << "이(가) " << selectedMonster.get_Name() << "에게 " << selectedCharacter.get_Attackdmg() << "의 피해를 입혔습니다." << std::endl;
        selectedCharacter.set_Cost();   //Cost소모
        selectedMonster.Hit(selectedCharacter.get_Attackdmg());
        break;
    case 2:
        std::cout << selectedCharacter.get_Name() << "이(가) " << "2 만큼의 방어도를 획득하였습니다." << std::endl;
        selectedCharacter.set_Cost();   //Cost소모
        selectedCharacter.set_Shield(2);    
        break;
    
    default:
        std::cout << "잘못된 키 입력을 했습니다." << std::endl;
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

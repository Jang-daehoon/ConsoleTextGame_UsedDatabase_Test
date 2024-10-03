#include<iostream>
#include"DatabaseManager.h"
#include"GameManager.h"
#include"User.h"
#include"Character.h"
#pragma comment(lib, "libmysql.lib")	//명시적인 라이브러리의 링크


int main()
{
	//로그인 및 회원가입을 위한 userData DB연결
	DatabaseManager dbManager;
	GameManager gameManager(dbManager);


	//콘솔 Size 설정
	system("mode con: cols=100 lines=50");
	system("title Welcome to Dungeon Express");	//이름 설정
	gameManager.gotoxy(30, 0); std::cout << "Game Database Ver." << mysql_get_client_info() << "\n";	//mySQL client 정보 ->연동 잘 된건지 확인용

	gameManager.GameStart();

	if (!dbManager.Connect("127.0.0.1", "root", "1234", "userdata"))
	{
		//버퍼없이 바로출력하는 stderr을 사용해 출력하기에 가장 빠르게 에러메시지 출력가능.
		std:: cout<< stderr << "Database connection error"<< std::endl;
		return 1;
	}
	

	//회원가입
	gameManager.GameRegister();
	//로그인
	gameManager.GameLogin();
	dbManager.Close();

	// 데이터베이스 변경
	if (!dbManager.Connect("127.0.0.1", "root", "1234", "CharacterInfo"))
	{
		dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
		//버퍼없이 바로출력하는 stderr을 사용해 출력하기에 가장 빠르게 에러메시지 출력가능.
		std::cout << stderr << "Database connection error" << std::endl;
		return 1;
	}

	system("cls");
	gameManager.SelectCharacter();	// 캐릭터 선택 메소드 호출	
	Sleep(500);
	system("cls");
	gameManager.CharacterStatus();//  화면 표시

	dbManager.Close();
	// 데이터베이스 변경
	if (!dbManager.Connect("127.0.0.1", "root", "1234", "MonsterData"))
	{
		dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
		//버퍼없이 바로출력하는 stderr을 사용해 출력하기에 가장 빠르게 에러메시지 출력가능.
		std::cout << stderr << "Database connection error" << std::endl;
		return 1;
	}

	gameManager.SelectMonster();	//몬스터 선택
	dbManager.Close();

	//프롤로그 출력
//DB에 있는 프롤로그 스크립트를 가져와서 출력
	if (!dbManager.Connect("127.0.0.1", "root", "1234", "EVENTDATA"))
	{
		dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
		//버퍼없이 바로출력하는 stderr을 사용해 출력하기에 가장 빠르게 에러메시지 출력가능.
		std::cout << stderr << "Database connection error" << std::endl;
		return 1;
	}
	gameManager.SelectTutoStory();
	dbManager.Close();
	//std::cout << gameManager.selectedCharacter.get_curhp() << std::endl;	//->체력 확인
	
	//캐릭터 선택 후 Main Game시작
	while (gameManager.getcurStage() != gameManager.getlastStage())
	{
		gameManager.BattleUI();
		if (gameManager.selectedMonster.get_curhp() <= 0)
		{
			Sleep(1000);
			//몬스터 처치 완료
			std::cout << "적을 처치했습니다.(보상을 선택하십시오.)" << std::endl;
			// 데이터베이스 변경
			if (!dbManager.Connect("127.0.0.1", "root", "1234", "EVENTDATA"))
			{
				dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
				//버퍼없이 바로출력하는 stderr을 사용해 출력하기에 가장 빠르게 에러메시지 출력가능.
				std::cout << stderr << "Database connection error" << std::endl;
				return 1;
			}
			gameManager.selectedCharacter.recovery_Cost();
			//랜덤 보상 메서드 호출
			gameManager.SelectEvent();
			dbManager.Close();
			//다음 Stage Event 호출 전투 -> 바로 전투, 이벤트 Stage ->이벤트 종료 후 전투
			gameManager.setcurStage();	//스테이지 증가
			gameManager.setMonsterIndex();
			// 데이터베이스 변경
			if (!dbManager.Connect("127.0.0.1", "root", "1234", "MonsterData"))
			{
				dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
				//버퍼없이 바로출력하는 stderr을 사용해 출력하기에 가장 빠르게 에러메시지 출력가능.
				std::cout << stderr << "Database connection error" << std::endl;
				return 1;
			}

			gameManager.SelectMonster();	//몬스터 선택
			dbManager.Close();
		}
		else if (gameManager.selectedCharacter.get_curhp() <= 0)
		{
			//DB ->> 사망 엔딩 출력
			if (!dbManager.Connect("127.0.0.1", "root", "1234", "EVENTDATA"))
			{
				dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
				//버퍼없이 바로출력하는 stderr을 사용해 출력하기에 가장 빠르게 에러메시지 출력가능.
				std::cout << stderr << "Database connection error" << std::endl;
				return 1;
			}
			gameManager.SelectEnding(2);
			dbManager.Close();
			//Save Data 삭제

			//게임 강제종료
			gameManager.GameExit();
		}

		//전투


		//추후 추가될 내용
		//전투 ->보상 -> 랜덤Stage 선택 (반복)
		// 보상-> 3개의 보상 중 한가지 1, 2, 3 입력을 통해 획득
		// 각 보상은 범위 내의 랜덤값이 지정되며 몬스터 조우 시 MonsterDB의 값은 지정된 랜덤값과 일치하는 MonsterID를 통해 
		// 몬스터를 소환한다. 이처럼 EVENT도 동일하다. 랜덤값이 EVENT DB의 값과 일치하는 EVENT를 호출한다. 
		// 이벤트종류 ->Event를 통한 즉정 스텟 증가, 몬스터 조우, 함정에 의해 피해를 입는다. 몬스터 조우는 단순히 전투만 하지만 이벤트의 경우
		// 이벤트가 끝나면 다음 보상을 고르는 것이 아닌 몬스터와의 전투가 진행된다.
		//STAGE-> 증가한다. 일정 STAGE 도달 시 Boss몬스터와 조우 
		// 전투는 Cost가 모두 소모될 때 까지 전투행동 선택 가능 Cost가 남아있을 경우 턴 넘기기 행동을 통해 Turn을 종료할 수 있다.
		//BOSS MONSTER를 처치하면 엔딩
		//실패하면 패배엔딩 및 저장 데이터 삭제.
	}
	std::cout << "모든 적을 처치한 당신은 마지막 포탈 앞의 보스를 쓰러트리면 탈출이 가능합니다." << std::endl;
	//Nomal Ending - A
	if (!dbManager.Connect("127.0.0.1", "root", "1234", "EVENTDATA"))
	{
		dbManager.ExecuteQuery("SET NAMES 'utf8mb4'");
		//버퍼없이 바로출력하는 stderr을 사용해 출력하기에 가장 빠르게 에러메시지 출력가능.
		std::cout << stderr << "Database connection error" << std::endl;
		return 1;
	}
	gameManager.SelectEnding(3);
	dbManager.Close();
}

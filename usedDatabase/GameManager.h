#include "User.h"
#include "Character.h"
#include "Monster.h"
#include "Event.h"
#include <cstdlib>
#include <iostream>
#include <windows.h> // Sleep 함수 및 SetConsoleCursorPosition 사용을 위해 필요

#pragma once

class GameManager
{
private:
    DatabaseManager& dbManager;
    User user;
    int choice = 0;
    int curDungeonStage;
    int lastDungeonStage;
    int MonsterIndex;

public:
    Character selectedCharacter; // 캐릭터 정보를 저장할 멤버 변수 추가    
    Monster selectedMonster;      // 선택된 몬스터 저장 멤버변수
    Event selectEvent;  //선택된 이벤트 저장

    GameManager(DatabaseManager& db);
    void GameStart();              // 게임 시작
    void GameLogin();             // 로그인
    void GameRegister();          // 회원가입
    void SelectCharacter();        // 캐릭터 선택
    void SaveSelectData(int choice); // 선택한 캐릭터 초기저장

    void LoadCharacterInitData(int characterId); // 저장한 캐릭터의 직업 ID를 가지고 기본 스텟 불러오기
    void LoadMonsterInitData(int monsterId); // 저장한 몬스터의 id를 가지고 기본 스텟 불러오기

    void SelectMonster();        // 몬스터 선택
    void GameExit();            // 게임 종료
    void gotoxy(int x, int y);  // 화면 좌표 지정
    // 인 게임 화면 UI(플레이어 정보 출력)
    void CharacterStatus();
    void MonsterStatus();
    void PrinStory();   //스토리 출력
    void BattleUI();

    //플레이 가능한 메서드
    void BattleChoice();

    //event 출력
    void SelectEvent(); //이벤트 선택 ->랜덤
    void SelectTutoStory(); //시작 스토리 출력
    void SelectEnding(int EndingId);    //엔딩 출력
    //getter
    int getcurStage() const;
    int getlastStage() const;
    void setcurStage();  
    void setMonsterIndex();
};

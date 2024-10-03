#include "User.h"
#include "Character.h"
#include "Monster.h"
#include "Event.h"
#include <cstdlib>
#include <iostream>
#include <windows.h> // Sleep �Լ� �� SetConsoleCursorPosition ����� ���� �ʿ�

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
    Character selectedCharacter; // ĳ���� ������ ������ ��� ���� �߰�    
    Monster selectedMonster;      // ���õ� ���� ���� �������
    Event selectEvent;  //���õ� �̺�Ʈ ����

    GameManager(DatabaseManager& db);
    void GameStart();              // ���� ����
    void GameLogin();             // �α���
    void GameRegister();          // ȸ������
    void SelectCharacter();        // ĳ���� ����
    void SaveSelectData(int choice); // ������ ĳ���� �ʱ�����

    void LoadCharacterInitData(int characterId); // ������ ĳ������ ���� ID�� ������ �⺻ ���� �ҷ�����
    void LoadMonsterInitData(int monsterId); // ������ ������ id�� ������ �⺻ ���� �ҷ�����

    void SelectMonster();        // ���� ����
    void GameExit();            // ���� ����
    void gotoxy(int x, int y);  // ȭ�� ��ǥ ����
    // �� ���� ȭ�� UI(�÷��̾� ���� ���)
    void CharacterStatus();
    void MonsterStatus();
    void PrinStory();   //���丮 ���
    void BattleUI();

    //�÷��� ������ �޼���
    void BattleChoice();

    //event ���
    void SelectEvent(); //�̺�Ʈ ���� ->����
    void SelectTutoStory(); //���� ���丮 ���
    void SelectEnding(int EndingId);    //���� ���
    //getter
    int getcurStage() const;
    int getlastStage() const;
    void setcurStage();  
    void setMonsterIndex();
};

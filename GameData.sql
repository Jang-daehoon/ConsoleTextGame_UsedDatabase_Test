/*
CREATE TABLE UserTable (
     user_Id int AUTO_INCREMENT PRIMARY KEY, 	
     user_Loginid varchar(20) NOT NULL,	
     user_Pw varchar(10) NOT NULL,	
     user_Name varchar(10) NOT NULL,	
     user_age TINYINT UNSIGNED,	
     birthday date NOT NULL,	
     user_Nickname varchar(10)unique NOT NULL	
     );
  */ 
  ALTER TABLE UserTable
    CONVERT TO CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
  /*
  insert into usertable(user_Loginid, user_Pw, user_Name, user_age, birthday, user_Nickname)
  values('admin', '1234', 'admin', 25, '2024-09-25', 'admin');
  */
CREATE DATABASE MonsterData;
CREATE DATABASE SaveData;
CREATE DATABASE CharacterInfo;
CREATE DATABASE EVENTDATA;

CREATE TABLE EventTable(
	event_Id int AUTO_INCREMENT PRIMARY KEY,
	event_Name varchar(20) NOT NULL, 
	event_Desc TEXT NOT NULL,
	event_AddMaxHp int NOT NULL,	#.최대 체력 증가 이벤트
    event__GetHp int Not NULL,	#.체력 회복 이벤트
	event_AttackDamage int NOT NULL,	#. 공격력 증가 이벤트
	event_Shield int NOT NULL,	#. 방어도 획득 이벤트
	event_Cost int NOT NULL,	#.Cost증가 이벤트
	event_GetGold int NOT NULL #.골드획득
);
INSERT INTO EventTable(event_Name, event_Desc, event_AddMaxHp, event__GetHp, event_AttackDamage, event_Shield, event_Cost, event_GetGold)
values('체력증진은 역시 유산소', '던전 속에서도 운동을 하며 정신력을 가다듬습니다.', 20, 0, 0, 0,0,0);
INSERT INTO EventTable(event_Name, event_Desc, event_AddMaxHp, event__GetHp, event_AttackDamage, event_Shield, event_Cost, event_GetGold)
values('이게 웬 떡??', '던전 속에서도 쓸만한 방패를 주웠습니다.', 0, 0, 0, 10, 0, 0);
INSERT INTO EventTable(event_Name, event_Desc, event_AddMaxHp, event__GetHp, event_AttackDamage, event_Shield, event_Cost, event_GetGold)
values('구사일생', '원래 세계로 돌아갈 수 없는 던전 속에서 획득이 불가능한 회복 포션을 운이 좋게 발견해 마셨습니다.
맛은 딸기맛이 나는군요 (HP + 30 회복). ', 0, 30, 0, 0, 0, 0);
INSERT INTO EventTable(event_Name, event_Desc, event_AddMaxHp, event__GetHp, event_AttackDamage, event_Shield, event_Cost, event_GetGold)
values('나 좀 강해진건가?', '당신은 수차례의 전투를 통해 깨달음을 얻었습니다. (Cost + 2)', 0, 0, 0, 0, 2, 0);


drop table eventtable;



CREATE TABLE GameStoryTable(
	Story_Id int AUTO_INCREMENT PRIMARY KEY,
    Story_Name varchar(20) NOT NULL, 
	Story_Desc1 TEXT
    );

INSERT INTO GameStoryTable(Story_Name, Story_Desc1) 
value('프롤로그', '이세계의 차원에는 수상한 던전이 있다고 한다. 다른 차원의 존재를 불러와 던전속에 가둬버리는 특이한 던전이 있는데...
이 던전은 왜 다른 차원의 존재를 불러오는 것이며, 던전 내부에는 무엇이 있는지 아무도 모른다. 운이 좋게 탈출한 사람들의 말에 의하면
평범한 던전같은데, 무언가 이질적인 느낌이 들며, 생각보다 수입이 짭짤하다고 하니 기회가 된다면 한번 더 다녀오고 싶다더라.
그리고 여기 또 한명의 사람이 던전 속에 소환되었습니다. 그 한명은 바로 당신입니다. 당신은 이 던전에서 살아남아 탈출할 수 있을까요?
행운을 빌겠습니다.'); 
INSERT INTO GameStoryTable(Story_Name, Story_Desc1) 
value('Ending - D (무력한 존재)', '당신은 던전속에서 생존하기 위해 고군분투했지만, 너무나 무력한 존재였습니다.
던전 내부의 강력한 몬스터들은 그런 당신을 가지고 놀며 끔찍하게 죽여버렸습니다. 조금 더 성장하거나 좋은 아이템을 발견했다면
생존했을지도 모르지만 운 또한 당신의 운명인 것이죠.'); 
INSERT INTO GameStoryTable(Story_Name, Story_Desc1) 
value('Ending - A (복귀)', '당신은 던전 속에서 강력한 적들과 싸우며 생존했습니다.
압도적인 적의 앞에서도 물러서지 않고 목숨을 결고 전투한 결과 당신의 무력또한 인간의 범주를 넘어섰습니다. 
던전의 유일한 탈출구인 포탈앞의 만티코어를 처치하고 갈무리해서 왕국으로 복귀한 당신은 던전에서 획득한 재료를 가지고 새로운 갑옷과 무기를 제작하였고,
장기간 실종되어 실직의 위기에 놓였지만, 여왕은 당신을 기다렸습니다. 이로인해 당신은 왕국에서 기사단장직을 이어가기로 했습니다.
훗날 압도적인 무력으로 역사서에 왕국의 전설의 기사단장으로 이름이 새겨졌습니다. '); 

CREATE TABLE CharacterTable(
	character_Id int AUTO_INCREMENT PRIMARY KEY,
    character_Name varchar(20) NOT NULL, 
    character_Desc TEXT NOT NULL,
	character_MaxHp int NOT NULL,
	character_AttackDMG int NOT NULL,
	character_Shield int NOT NULL,
    character_Cost int NOT NULL,
    character_Initial_Funds int NOT NULL #.캐릭터 초기 자금
);
ALTER DATABASE CharacterInfo DEFAULT CHARACTER SET utf8mb4;

ALTER TABLE CharacterTable
    CONVERT TO CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;

INSERT INTO CharacterTable(character_Name, character_Desc, character_MaxHp, character_AttackDMG, character_Shield,
character_Cost, character_Initial_Funds) values('라하르트', '라하르트는 태양의 기사단의 기사단장이다. 갑옷을 입고있어 그의 얼굴을 본 자는 많지 않지만, 
그의 따듯한 마음과 용맹스러움은 은빛 갑옷에서 느껴진다고 한다. 어느 날 던전에 갑작스럽게 전이된 라하르트는 무력과 체력이 상대적으로 약해지고말았다. 
하지만 신체가 약해졌다고 해서 그의 정신력까지 약해진 것은 아니기에 적이 강해도 수많은 전장에서 승리한 그는 백전불굴의 의지를 가지고 전투에 임한다.',100, 20, 10, 5, 100);

INSERT INTO CharacterTable(character_Name, character_Desc, character_MaxHp, character_AttackDMG, character_Shield,
character_Cost, character_Initial_Funds) values('관리자', '관리자계정입니다.',9999, 9999, 9999, 9999, 9999);


CREATE TABLE MonsterTable(
	monster_Id int AUTO_INCREMENT PRIMARY KEY,
    monster_Name varchar(20) NOT NULL, 
    monster_Desc TEXT NOT NULL,
	monster_MaxHp int NOT NULL,
	monster_AttackDMG int NOT NULL,
	monster_Shield int NOT NULL,
    moster_RetainedGold int NOT NULL
);

ALTER TABLE MonsterTable
    CONVERT TO CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
    
DROP TABLE MonsterTable;
INSERT INTO MonsterTable(monster_Name, monster_Desc, monster_MaxHp, monster_AttackDMG, monster_Shield, moster_RetainedGold)
values('슬라임', '던전에 자주 출몰하는 슬라임이다. 생각보다 온순해 위험한 몬스터는 아니긴 하나 개체 수가 많다보니 슬라임의 점액으로 인해 전투를 하고 나면 장비를 닦아야 하는 불편함이 있다. 
슬라임은 검으로 베어도 죽지 않으며, 슬라임 내부에 있는 슬라임의 핵을 부숴야 처치가 가능한 몬스터이다.',50, 5, 0, 20);
INSERT INTO MonsterTable(monster_Name, monster_Desc, monster_MaxHp, monster_AttackDMG, monster_Shield, moster_RetainedGold)
values('떠돌이 고블린', '길을 잃어 부락에서 떨어져 나온 고블린다. 초록색 피부에 푸른 피를 지니고 있으며, 
날렵하지만 나약한 몬스터이다.',75, 20, 0, 10);
INSERT INTO MonsterTable(monster_Name, monster_Desc, monster_MaxHp, monster_AttackDMG, monster_Shield, moster_RetainedGold)
values('해골 병사', '언데드인 해골병사는 몸이 뼈로 이루어져 있어 단순히 부수기만 하면 되는 하급 몬스터이지만, 
이곳의 해골병사는 갑옷을 입고 있어 상당히 단단하다. 무기 또한 지니고 있어 왕국의 병사만큼 강한 몬스터이다.',150, 50, 15, 60);
INSERT INTO MonsterTable(monster_Name, monster_Desc, monster_MaxHp, monster_AttackDMG, monster_Shield, moster_RetainedGold)
values('오크 주술사', '오크 주술사는 오크종족의 특유의 무력을 지니고 있으며, 마법까지 사용하는 이질적인 존재이다.
오크종족의 질긴 살가죽과 단단한 뼈는 상대하기 까다로우며, 오크주술사의 마법은 모험가들에게 많은 피해를 줄 수 있다.',300, 80, 40, 250);
INSERT INTO MonsterTable(monster_Name, monster_Desc, monster_MaxHp, monster_AttackDMG, monster_Shield, moster_RetainedGold)
values('리치왕', '리치왕은 수백년을 넘게 생존한 리치로 마법이면 마법 검술이면 검술 사령술까지 모두 극의에 달한 몬스터 이다.
대부분의 모험가들도 리치왕을 보면 도망가기 바쁘며, 리치왕에게 사망하면 사령술로 인해 시체가 꼭두각시가 된다. 
강력한 몬스터인 만큼 당신의 실력이 출중하다면 처치할 수 있을 것 이다.',500, 120, 50, 500);
INSERT INTO MonsterTable(monster_Name, monster_Desc, monster_MaxHp, monster_AttackDMG, monster_Shield, moster_RetainedGold)
values('트롤', '트롤은 육중한 몸을 가지고 있어 체력은 낮으며, 거대한 손을 휘두르며 파괴적인 공격을 가한다.
몸의 피부가죽은 평범한 검과 마법으로는 상처도 낼 수 없다.
지능이 낮은 만큼 전투스타일은 단조롭다. 공격을 막거나 피하지 못하면 즉사한다.',50, 200, 100, 1000);
INSERT INTO MonsterTable(monster_Name, monster_Desc, monster_MaxHp, monster_AttackDMG, monster_Shield, moster_RetainedGold)
values('미믹킹', '일반 미믹과 다른 미믹킹이다. 미믹들의 왕으로서 걸어다닐때마다 금은보화가 흘러넘친다.
이 미믹은 단순한 미믹과 다르게 공격성이 뛰어나다. 미스릴 상자이기에 미믹킹의 상자를 부수려면 압도적인 힘을 가지고 있거나,
성검급으로 좋은 무기를 사용하면 된다. 공격성은 뛰어나지만 방어력은 뛰어나지만 공격력은 크게 높지 않다.
전투가 길어지면 위험할지도...',300, 100, 80, 3000);
INSERT INTO MonsterTable(monster_Name, monster_Desc, monster_MaxHp, monster_AttackDMG, monster_Shield, moster_RetainedGold)
values('알립', '던전에서 탈출하지 못해 괴로움에 미쳐 자살한 자가 유령이 된 존재이다. 
원래는 복수를 갈망하며, 원한이 있는 사람들을 공격해 죽이는 몬스터지만, 던전에서 미쳐버렸기 때문에,
던전에 보이는 모든 생물체를 보면 공격한다. 방심하다간 생명력을 흡수당할 수 있다.
물리적인 공격 자체는 위험하지 않다고 한다.',150, 80, 200, 3200);
INSERT INTO MonsterTable(monster_Name, monster_Desc, monster_MaxHp, monster_AttackDMG, monster_Shield, moster_RetainedGold)
values('비홀더', '둥둥 떠다니는 크고 커다란 구체에, 눈이 한가운데 박혀져 있고, 날카로운 이빨이 돋은 입이 아래에 있다.
위쪽에는 작은 눈이 달린 촉수가 잔뜩 돋아있는 기괴한 형상이다. 생긴 건 좀 우습지만 엄청나게 강력하고 사악한 몬스터이다.
비홀더의 눈이 비치는 곳은 주의할것! ',400, 300, 150, 4800);
INSERT INTO MonsterTable(monster_Name, monster_Desc, monster_MaxHp, monster_AttackDMG, monster_Shield, moster_RetainedGold)
values('만티코어', '거대한 사자의 몸뚱이에 인간 노인의 얼굴, 그리고 전갈의 꼬리, 
날개를 갖춘 몬스터. 그로테스크한 얼굴로 등장하며 피부색이
오렌지색이다. 전갈처럼 꼬리에는 상대방을 찔러서 공격할 수 있는 뾰족한 가시가 있다.
목소리는 피리와 트럼펫을 합친 것처럼 들리며 사람 고기를 좋아한다. 
공격력과 방어력이 모두 높으며 만티코어의 갈퀴, 꼬리, 피 모두 귀중한 재료이기에 
엄청난 희귀성을 자랑한다.',1000, 500, 500, 9999);

Delete from CharacterTable WHERE character_Id >0;
drop table CharacterTable;

# 데이터 조회
select *from CharacterTable;
select *from usertable;
select *from MonsterTable;
select *from EventTable;
select *from GameStoryTable;
SELECT * FROM CharacterTable WHERE character_Id = 1;
SHOW VARIABLES LIKE 'c%';
SHOW VARIABLES LIKE 'character_set%';
SHOW CREATE TABLE CharacterTable;


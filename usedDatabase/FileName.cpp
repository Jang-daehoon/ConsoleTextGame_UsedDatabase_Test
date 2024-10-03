#include<iostream>
#include<mysql.h>
#pragma comment(lib, "libmysql.lib")	//명시적인 라이브러리의 링크
using namespace std;

int main()
{
	cout << mysql_get_client_info() << "\n";	//mySQL client 정보 ->연동 잘 된건지 확인용

	MYSQL Conn;	//MySQL정보를 담을 구조체
	MYSQL* ConnPtr = NULL;	//MySQL 핸들

	MYSQL_RES* Result;	//쿼리 성공 시 결과를 담는 구조체 포인터
	MYSQL_ROW Row;	//쿼리 성공 시 결과로 나온 행의 정보를 담는 구조체
	int Stat;	//쿼리 요청 후 결과(성공, 실패)

	mysql_init(&Conn);	//MySQL정보 초기화

	//데이터베이스와 연결
	ConnPtr = mysql_real_connect(&Conn, "127.0.0.1", "root", "1234", "userdata", 3306, (char*)NULL, 0);
	//연결 결과 확인, NULL일 경우 연결 실패
	if (ConnPtr == NULL)
	{
		cout << stderr << "Mysql connection error : " << mysql_error(&Conn);
		return 1;
	}

	//쿼리 보내기 (사용자 테이블에서 데이터 조회)
	const char* Query = "SELECT * FROM usertable";
	Stat = mysql_query(ConnPtr, Query);	//쿼리 요청 및 성공 여부 받아오기
	if (Stat != 0)
	{
		cout << stderr << "Mysql query error : \n" << mysql_error(&Conn);	//버퍼없이 바로출력하는 stderr을 사용해 출력하기에 가장 빠르게 에러메시지 출력가능.
		return 1;
	}
	Result = mysql_store_result(ConnPtr);	//결과 확인하기
	while ((Row = mysql_fetch_row(Result)) != NULL)	//결과 출력하기
	{
		cout << "-----------------------------------------" << endl;
		//user_Id, user_Loginid ,user_Pw, user_Name, user_age, birthday, user_Nickname
		cout << "UID: " << Row[0] << "\n" << "Login_Id: " << Row[1] << "\n" << "User PW: " << Row[2] << "\n" << "User Name : " << Row[3] << "\n" << "User Age: "
			<< Row[4] << "\n" << "User Birthday:" << Row[5] << "\n" << "User Nickname : " << Row[6] << "\n";
		cout << "-----------------------------------------"<<endl;
	}
	mysql_free_result(Result);	//결과 비우기

	// 사용자 입력 받기 ->DB로 데이터 전송하기 때문에 이는 회원가입 기능입니다.
	/*
	string loginId, userPw, userName, userAge, birthday, userNickname;
	cout << "Login ID를 입력하세요(최대 20자 - 공란으로 비워둘 수 없습니다.): ";
	cin >> loginId;
	cout << "User Password를 입력하세요(최대 10자 - 공란으로 비워둘 수 없습니다.): ";
	cin >> userPw;
	cout << "User Name을 입력하세요(최대 10자 - 공란으로 비워둘 수 없습니다.): ";
	cin >> userName;
	cout << "User Age를 입력하세요(양수만 입력가능): ";
	cin >> userAge;
	cout << "Birthday (YYYY-MM-DD)를 입력하세요(공란으로 비워둘 수 없습니다.): ";
	cin >> birthday;
	cout << "User Nickname을 입력하세요(최대 10자 - 공란으로 비워둘 수 없습니다.): ";
	cin >> userNickname;

	// INSERT 쿼리 준비
	string insertQuery = "INSERT INTO usertable (user_Loginid, user_Pw, user_Name, user_age, birthday, user_Nickname) VALUES ('"
		 + loginId + "', '" + userPw + "', '" + userName + "', '" + userAge + "', '" + birthday + "', '" + userNickname + "')";

	// INSERT 쿼리 실행
	Stat = mysql_query(ConnPtr, insertQuery.c_str()); // 쿼리 실행
	if (Stat != 0) {
		cerr << "MySQL 삽입 오류: " << mysql_error(&Conn) << endl;
	}
	else {
		cout << "사용자가 성공적으로 추가되었습니다!" << endl;
	}
	*/

	// 로그인 기능 추가 비밀번호는 안보이게
	string loginIdInput, userPwInput;
	cout << "\n로그인 하시려면 Login ID와 Password를 입력하세요.\n";
	cout << "Login ID: ";
	cin >> loginIdInput;
	cout << "Password: ";
	cin >> userPwInput;

	// 로그인 쿼리 준비 (WHERE을 사용해 특정 조건에 부합하는 데이터만 조회 + 논리연산자 AND(좌우를 동시에 만족)를 통해 PW도 있다면 로그인)
	string loginQuery = "SELECT * FROM usertable WHERE user_Loginid = '" + loginIdInput + "' AND user_Pw = '" + userPwInput + "'";

	// 로그인 쿼리 실행
	Stat = mysql_query(ConnPtr, loginQuery.c_str());
	if (Stat != 0) {
		cerr << "Mysql query error: " << mysql_error(&Conn) << endl;
	}
	else {
		Result = mysql_store_result(ConnPtr);
		if (mysql_num_rows(Result) > 0) {
			cout << "로그인 성공!\n";
			// 로그인 성공 시 추가 동작
			while ((Row = mysql_fetch_row(Result)) != NULL) {
				cout << "Welcome, " << Row[3] << "!" << endl; // 사용자의 이름 출력
			}
		}
		else {
			cout << "로그인 실패: 잘못된 ID 또는 비밀번호입니다." << endl;
		}
	}

	//데이터베이스와 연결 해제
	mysql_close(ConnPtr);
	//데이터 -> 

	//1. 회원가입
	//2. 로그인
	//3. pw찾기
	//-----
	//4. 선택한 캐릭터 정보 저장 ->playerChar_data(Stat) || MosterData(stat), itemTalbe(info) 
	// 
	//  각 캐릭터마다 능력 및 지정된 카드가 
	// 캐릭터 ID 1. 기사, 2.마법사, 3. 도적
	// 턴 마다 캐릭터의 Cost가 회복되며 적의 행동이 랜덤하게 선택된다. Cost한도 내에서 스킬을 사용해 적을 쓰러트릴 수 있다. 플레이어가 턴을 종료하면 적의 행동이 시작된다.
	// SavePoint는 없다. 수동저장.
	// 저장되는 정보 -> 플레이어캐릭터 정보, 보유중인 카드의 정보, 게임 진행도에 대한 정보.
	// 전투가 종료되면 보상을 획득 -> 3개의 보상중 하나를 선택 - 보상은 랜덤한 보상 Gold는 모든 보상에서 획득이 가능하지만 꽝도 있고 Status가 증가하거나 새로운 스킬을 획득하거나 한다.
	// 전투가 종료되면 다음 스테이지로 이동되는데 확률적으로 쉼터 혹은 이벤트가 발생한다. 쉼터에서는 체력을 회복할 수 있다. 이벤트는 스테이터스가 증가할수도 함정에 걸려 피해를 입거나 보물을 획득해 골드를 획득하는 등 여러가지 스토리적인 상황이 존재한다.
	// 스테이지마다 랜덤한 몬스터들이 소환되며 전투하며 각 스테이지의 마지막은 보스가 있다. 
	// 사망 시 저장된 데이터 삭제
	// 
	// Database 저장할 캐릭터
	//5 ->저장 -> 수동저장
	//6. 로드 -> DB-> Console로 데이터 불러오기

}

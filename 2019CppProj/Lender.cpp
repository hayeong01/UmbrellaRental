#pragma comment (lib, "libmysql.lib")
#include<mysql.h>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <string.h>
#include <time.h>
#define USER "root"				//유저 이름
#define PASSWORD "mirim2"		//비밀번호
#define HOST "localhost"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
class DB {
public:
	DB(const char mysqlip[], MYSQL *cons) {
		if (cons == NULL)
		{
			fprintf(stderr, "%s\n", mysql_error(cons));
			Sleep(1000);
			exit(1);
		}
		if (!(mysql_real_connect(cons, mysqlip, USER, PASSWORD, "2019cpp", 0, NULL, 0) == NULL))
		{
			//			printf("\n성공");
			mysql_set_character_set(cons, "euckr");	//MySQL 문자를 지정 안하면 한글 짤림
		}
		else {
			fprintf(stderr, "연결 오류 : %s\n", mysql_error(cons));
			getchar();
		}
	}

	MYSQL_RES* select_sql(const char mysqlip[], MYSQL *cons) {
		char s[200];//sql문 넣을거
		MYSQL_RES *res;

		sprintf_s(s, 200, "select * from user; ");

		if (mysql_query(cons, s))// 테이블의 모든 레코드 선택
		{
			fprintf(stderr, "%s\n", mysql_error(cons));
			mysql_close(cons);

			cout << "실패";
			//exit(1);
		}
		res = mysql_store_result(cons);  // 모든 출력 결과를 서버에서 한번에 다 받아옴

		return res;

	}
	int login_sql(const char mysqlip[], MYSQL *cons, const char* id, const char* pw, int& userType) {

		char s[200];//sql문 넣을거
		MYSQL_RES *res;
		MYSQL_ROW row;

		int fields;

		sprintf_s(s, 200, "select * from user; ");

		if (mysql_query(cons, s))// 테이블의 모든 레코드 선택
		{
			fprintf(stderr, "%s\n", mysql_error(cons));
			mysql_close(cons);

			cout << "실패";
			//exit(1);
		}
		res = mysql_store_result(cons);  // 모든 출력 결과를 서버에서 한번에 다 받아옴
		fields = mysql_num_fields(res);

		int result = 0;
		while ((row = mysql_fetch_row(res)) != NULL) // 한 행을 구함
		{
			if (strcmp(row[0], id) == 0) {// 아이디가 있을때 1

				if (strcmp(row[8], pw) == 0) {//비밀번호도 같을때 2
					if (strcmp(row[9], "1") == 0) userType = 1;
					else if (strcmp(row[9], "2") == 0) userType = 2;
					result = 2;
				}
				else result = 1;

				break;
			}
			else result = 0; //아이디 없을 때 0

		}

		return result;

		mysql_free_result(res);
		mysql_close(cons);

	}

	bool insertspl(const char mysqlip[], MYSQL *cons, const char* id, const char* pw, int type, const char* name) {

		MYSQL_RES* res = select_sql(HOST, cons);
		MYSQL_ROW row;

		while ((row = mysql_fetch_row(res)) != NULL) // 한 행을 구함
		{
			if (strcmp(row[0], id) == 0) {
				return false;
			}

		}
		char s[200];//sql문 넣을거
		sprintf_s(s, 200, "insert into user values('%s','%s',0,0,0,0,0,0,'%s',%d); ", id, name, pw, type);

		if (mysql_query(cons, s))
		{
			fprintf(stderr, "%s\n", mysql_error(cons));
			mysql_close(cons);

			cout << "실패";
		}


		return true;

	}
	void loadmysql(const char mysqlip[], MYSQL *cons, const char * id, int choice)
	{

		char s[200];//sql문 넣을거
		char s1[200];//예외적인 부분 확인하기위한 select문을 넣을 방
		int Fyear;//DB에 year이라는 컬럼명이 있어서 헷갈릴까봐 F붙인 거임
		int Fmon;
		int Fday;
		int plus_check = 0;
		switch (choice)
		{
		case 1://우산대여신청
			time_t timer;
			struct tm t;

			timer = time(NULL);
			localtime_s(&t, &timer);//현재시간 구하는 것
			Fyear = t.tm_year + 1900;
			Fmon = t.tm_mon + 1;
			Fday = t.tm_mday;
			sprintf_s(s, 200, "UPDATE user SET year = %d, month=%d, day=%d, return1 =0, plusday=0, lendok=1  WHERE Id = %s ", Fyear, Fmon, Fday, id);
			sprintf_s(s1, 200, "select lendok from user where lendok >0 && id = %s", id); //우산 반납 안 한사람
			break;

		case 2://우산반납기간 연장신청
			sprintf_s(s, 100, "UPDATE user SET plusday=1 WHERE Id = %s ", id);
			sprintf_s(s1, 200, "select plusday from user where plusday =1 && id = %s", id);//이미 한 번 연장신청을 했는지 확인
			break;

		case 3://우산대여 현황
			sprintf_s(s, 100, "select *from user where return1 =0 && id = %s", id);
			break;
		}


		if (choice < 3) {
			MYSQL_RES *res = nullptr;
			MYSQL_ROW row;
			int fields = 0;
			int check = 3;
			mysql_query(cons, s1);
			res = mysql_store_result(cons);  // 모든 출력 결과
			while (row = mysql_fetch_row(res)) // 한 행을 구함
			{
				check = atoi(row[0]);
				mysql_free_result(res);
				mysql_close(cons);
			}

			if (choice == 1 && check != 3)cout << "이미 우산을 빌리셨습니다" << endl;// "우산대여신청" 예외 경우

			else if (choice == 2 && check != 3)cout << "이미 한번 연장신청을 하셨습니다" << endl;// "우산연장신청" 예외 경우

			else {//해결~!~!
				if (mysql_query(cons, s) && choice != 3 && plus_check == 0)
				{
					fprintf(stderr, "%s\n", mysql_error(cons));
					mysql_close(cons);
					exit(1);
				}
			}//else문 닫기
		}//1,2

		else if (choice == 3) {//3하는 문장
			mysql_query(cons, s);
			MYSQL_RES *res = nullptr;
			MYSQL_ROW row;
			int fields = 0;
			int count = 0;
			mysql_query(cons, s);
			int returnYear, returnMonth, returnDate;

			time_t timer;
			struct tm t;




			res = mysql_store_result(cons);  // 모든 출력 결과
			fields = mysql_num_fields(res); // 필드 갯수 구함
			while (row = mysql_fetch_row(res)) // 한 행을 구함
			{
				int day = atoi(row[4]);//캐릭터를 인트형으로
				int check = atoi(row[6]);

				if (check == 0) timer = time(NULL) + 7 * (24 * 60 * 60);//plusDay를 체크해서 연장신청을 안했으면 0, 했으면 else로 한다
				else timer = time(NULL) + 14 * (24 * 60 * 60);

				localtime_s(&t, &timer);//현재시간 구하는 것
				returnYear = t.tm_year + 1900;
				returnMonth = t.tm_mon + 1;
				returnDate = t.tm_mday;

				cout << "아이디 : " << row[0] << "\n이름 : " << row[1] << "\n대여기간 : " << row[2] << "년" << row[3] << "월" << row[4] << "일 ~ " << returnYear << "년" << returnMonth << "월" << returnDate << "일" << endl;
				mysql_free_result(res);
				mysql_close(cons);
				count++;
			}
			if (count == 0)cout << "반납할 우산이 없습니다.";


		}
		return;
	}

};
class Lender
{
public:
	Lender(const char* id) {
		int select;
		while (1) {
			system("cls");
			cout << "1.우산대여신청" << endl;
			cout << "2.우산 반납 기간 연장신청" << endl;
			cout << "3.우산 대여 현황" << endl;
			cout << "4.종료" << endl;
			cout << ">>";
			cin >> select;

			switch (select)
			{
			case 1: system("cls"); Askfor(id); break;
			case 2: system("cls"); Plus(id); break;
			case 3: system("cls"); userNow(id); break;
			case 4: return; break;
			default:
				break;
			}
		}
	}
	void Askfor(const char * id) {
		cout << "우산대여신청 중..." << endl;
		
		MYSQL * cons = mysql_init(NULL);
		DB d(HOST,cons);
		d.loadmysql(HOST, cons, id, 1);	//마지막에 1은 우산대여신청하려는지 반납하려는지 그런거  구분하려고 넣음
		cout << "\n완료!" << endl;
		system("pause");
	}
	void Plus(const char *id) {
		cout << "우산 반납기간 연장신청 중..." << endl;
		MYSQL * cons = mysql_init(NULL);
		DB d(HOST, cons);
		d.loadmysql(HOST, cons, id, 2);	//마지막에 2는 우산대여신청하려는지 반납하려는지 그런거 구분하려고 넣음
		cout << "\n완료!" << endl;
		system("pause");
	}
	void userNow(const char *id) {
		cout << "우산대여 현황" << endl;
		MYSQL * cons = mysql_init(NULL);
		DB d(HOST, cons);
		d.loadmysql(HOST, cons, id, 3);	//마지막에 3은 우산대여신청하려는지 반납하려는지 그런거  구분하려고 넣음
		cout << "\n완료!" << endl;
		system("pause");
	}

};





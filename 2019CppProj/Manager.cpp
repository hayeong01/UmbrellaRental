#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h> 
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include<mysql.h>
#define USER "root"				//유저 이름
#define PASSWORD "mirim2"		//비밀번호
#define HOST "localhost"

using namespace std;
class DB2 {
public:
	DB2(const char mysqlip[], MYSQL *cons) {
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

	MYSQL_RES* select_sql(const char mysqlip[], MYSQL *cons,int type,int lendok) {
		char s[200];//sql문 넣을거
		MYSQL_RES *res;

		sprintf_s(s, 200, "select * from user where type=%d and lendok=%d; ",type,lendok);

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
};
class Manager {
public:
	int x, y;
	int cho;
	void ShowAllRental() {
		while (true) {
			system("cls");
			draw_background();

			gotoxy(32, 6);
			cout << "****** 전체 대여 현황 ******";

			MYSQL * cons = mysql_init(NULL);
			DB2 all(HOST, cons);
			MYSQL_RES* res = all.select_sql(HOST, cons,2,2);
			MYSQL_ROW row;
			int returnYear, returnMonth, returnDate;

			time_t timer;
			struct tm t;
			int count = 0;

			int fields = mysql_num_fields(res); // 필드 갯수 구함
			x = 10, y = 12;
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
				
				
				gotoxy(x, y);
				cout << "아이디 : " << row[0] << "   이름 : " << row[1] << "  대여기간 : " << row[2] << "년" << row[3] << "월" << row[4] << "일 ~ " << returnYear << "년" << returnMonth << "월" << returnDate << "일";
				
				count++;
				y++;
			}

			x = 20, y = 25;
			gotoxy(x - 2, y);
			cout << ">";
			gotoxy(x, y);
			cout << "우산 반납 관리" << endl;
			gotoxy(x, y + 2);
			cout << "연장 신청 수락" << endl;
			gotoxy(x, y + 4);
			cout << "뒤로 가기" << endl;

			draw_arrow();

			switch (cho) {
			case 1: ReturnUmb(); break;
			case 2:	PlusDay_Accept(); break;
			case 3: return;  break;
			}
			if (count == 0)cout << "대여된 우산이 없습니다.";
		}
	}
	void RentalApply_Accept() {
		system("cls");
		draw_background();

		MYSQL * cons = mysql_init(NULL);
		DB2 apply(HOST, cons);
		MYSQL_RES* res = apply.select_sql(HOST, cons, 2, 1);
		MYSQL_ROW row;
		int returnYear, returnMonth, returnDate;

		time_t timer;
		struct tm t;
		int count = 1;
		int selectNum;

		int fields = mysql_num_fields(res); // 필드 갯수 구함
		x = 10, y = 12;
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


			gotoxy(x, y);
			
			cout << count<<". 이름 : " << row[1] << "  대여기간 : " << row[2] << "년" << row[3] << "월" << row[4] << "일 ~ " << returnYear << "년" << returnMonth << "월" << returnDate << "일";

			count++;
			y++;
		}

		y += 3;
		gotoxy(x, y);
		cout << "대여 수락할 번호를 입력하세요 >>";
		cin >> selectNum;

		count = 1;
		while (row = mysql_fetch_row(res)) // 한 행을 구함
		{
			if (count == selectNum) {
				
			}
			count++;
		}

		system("pause");
	}
	void ReturnUmb() {
		system("cls");
		draw_background();
	}
	void PlusDay_Accept() {
		system("cls");
		draw_background();
	}

	Manager() {
		while (true) {

			system("cls");
			draw_umbrella();
			x = 20, y = 25;
			gotoxy(x - 2, y);
			cout << ">";
			gotoxy(x, y);
			cout << "전체 대여 현황" << endl;
			gotoxy(x, y + 2);
			cout << "대여 신청 수락" << endl;
			gotoxy(x, y + 4);
			cout << "로그아웃" << endl;
			draw_arrow();
			//cin >> cho;
			switch (cho) {
			case 1: ShowAllRental(); break;
			case 2: RentalApply_Accept(); break;
			case 3: return;  break;
			}

		}
	}
	
	void draw_background() {
		gotoxy(2, 3);
		cout << "┌";
		for (int i = 0; i < 75; i++) {
			cout << "─";
		}
		cout << "┐";

		int b_y = 4, b_x = 2;
		for (int i = 0; i < 30; i++) {
			gotoxy(b_x, b_y);
			cout << "│";
			gotoxy(b_x + 76, b_y);
			cout << "│";
			b_y++;
		}

		gotoxy(2, 9);
		cout << "├";
		for (int i = 0; i < 75; i++) {
			cout << "─";
		}
		cout << "┤";


		gotoxy(2, 34);
		cout << "└";
		for (int i = 0; i < 75; i++) {
			cout << "─";
		}
		cout << "┘";

	}
	void draw_arrow() {
		gotoxy(x, y);
		int key;
		do {
			key = _getch();
			move_arrow_key(key, 43, 22);
		} while (key != 32);

	}

	void move_arrow_key(char key, int x_b, int y_b) {
		switch (key) {
		case 72://위
			if (y > 25) {
				gotoxy(x - 2, y);
				cout << " ";
				y -= 2;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case 80: //아래
			if (y < 29) {
				
				gotoxy(x - 2, y);
				cout << " ";
				y += 2;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;
		case 32:
			switch (y)
			{
			case 25: cho = 1;  break;
			case 27: cho = 2; break;
			case 29: cho = 3; break;
			}
		default:
			return;
		}
	}

	void gotoxy(int x, int y) {
		COORD Pos = { x - 1, y - 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	void draw_umbrella() {
		x = 35, y = 1;
		for (int j = 0; j < 9; j++) {
			gotoxy(x, y);
			for (int i = 0; i < 81 - x; i++) {
				cout << "#";
			}
			x -= 4;
			y++;
		}

		y = 10, x = 70;
		for (int i = 0; i < 20; i++) {
			gotoxy(x, y);
			cout << "|";
			gotoxy(x + 3, y);
			cout << "|";
			y++;
		}

		int n = 15;
		//x--;
		for (int i = 0; i < 6; i++) {
			gotoxy(x - n, y);
			cout << "■■■";
			for (int j = 0; j < n - 11; j++) {
				cout << "  ";
			}
			cout << "■■■";
			y++;
			if (i % 2 != 0) {
				n -= 2;
			}
		}
		gotoxy(x - n, y);
		cout << "■■■■";

		x = 1; y = 12;
		gotoxy(x, y);
		cout << "   ▨  ▨    ▨▨▨    ▨▨    ▨▨▨   ▨▨▨  ▨     ▨       ▨▨  " << endl;
		cout << "   ▨  ▨  ▨▨▨▨▨  ▨  ▨  ▨   ▨  ▨      ▨     ▨      ▨  ▨ " << endl;
		cout << "   ▨  ▨  ▨  ▨  ▨  ▨▨▨  ▨▨▨   ▨▨▨  ▨     ▨     ▨▨▨▨" << endl;
		cout << "   ▨  ▨  ▨  ▨  ▨  ▨  ▨  ▨  ▨   ▨      ▨     ▨     ▨    ▨" << endl;
		cout << "   ▨▨▨  ▨  ▨  ▨  ▨▨▨  ▨   ▨  ▨▨▨  ▨▨▨ ▨▨▨ ▨    ▨" << endl;

	}
};
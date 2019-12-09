#pragma comment (lib, "libmysql.lib")
#include<mysql.h>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <string.h>
#include <time.h>
#include <conio.h>

#define USER "root"				//���� �̸�
#define PASSWORD "mirim2"		//��й�ȣ
#define HOST "localhost"
#define _CRT_SECURE_NO_WARNINGS

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 
using namespace std;
class DB {
public:
	int x, y;
	DB(const char mysqlip[], MYSQL *cons) {
		if (cons == NULL)
		{
			fprintf(stderr, "%s\n", mysql_error(cons));
			Sleep(1000);
			exit(1);
		}
		if (!(mysql_real_connect(cons, mysqlip, USER, PASSWORD, "2019cpp", 0, NULL, 0) == NULL))
		{
			//			printf("\n����");
			mysql_set_character_set(cons, "euckr");	//MySQL ���ڸ� ���� ���ϸ� �ѱ� ©��
		}
		else {
			fprintf(stderr, "���� ���� : %s\n", mysql_error(cons));
			getchar();
		}
	}

	MYSQL_RES* select_sql(const char mysqlip[], MYSQL *cons) {
		char s[200];//sql�� ������
		MYSQL_RES *res;

		sprintf_s(s, 200, "select * from user; ");

		if (mysql_query(cons, s))// ���̺��� ��� ���ڵ� ����
		{
			fprintf(stderr, "%s\n", mysql_error(cons));
			mysql_close(cons);

			cout << "����";
			//exit(1);
		}
		res = mysql_store_result(cons);  // ��� ��� ����� �������� �ѹ��� �� �޾ƿ�

		return res;

	}
	int login_sql(const char mysqlip[], MYSQL *cons, const char* id, const char* pw, int& userType) {

		char s[200];//sql�� ������
		MYSQL_RES *res;
		MYSQL_ROW row;

		int fields;

		sprintf_s(s, 200, "select * from user; ");

		if (mysql_query(cons, s))// ���̺��� ��� ���ڵ� ����
		{
			fprintf(stderr, "%s\n", mysql_error(cons));
			mysql_close(cons);

			cout << "����";
			//exit(1);
		}
		res = mysql_store_result(cons);  // ��� ��� ����� �������� �ѹ��� �� �޾ƿ�
		fields = mysql_num_fields(res);

		int result = 0;
		while ((row = mysql_fetch_row(res)) != NULL) // �� ���� ����
		{
			if (strcmp(row[0], id) == 0) {// ���̵� ������ 1

				if (strcmp(row[8], pw) == 0) {//��й�ȣ�� ������ 2
					if (strcmp(row[9], "1") == 0) userType = 1;
					else if (strcmp(row[9], "2") == 0) userType = 2;
					result = 2;
				}
				else result = 1;

				break;
			}
			else result = 0; //���̵� ���� �� 0

		}

		return result;

		mysql_free_result(res);
		mysql_close(cons);

	}

	bool insertspl(const char mysqlip[], MYSQL *cons, const char* id, const char* pw, int type, const char* name) {

		MYSQL_RES* res = select_sql(HOST, cons);
		MYSQL_ROW row;

		while ((row = mysql_fetch_row(res)) != NULL) // �� ���� ����
		{
			if (strcmp(row[0], id) == 0) {
				return false;
			}

		}
		char s[200];//sql�� ������
		sprintf_s(s, 200, "insert into user values('%s','%s',0,0,0,1,0,0,'%s',%d); ", id, name, pw, type);

		if (mysql_query(cons, s))
		{
			fprintf(stderr, "%s\n", mysql_error(cons));
			mysql_close(cons);

			cout << "����";
		}


		return true;

	}
	int loadmysql(const char mysqlip[], MYSQL *cons, const char * id, int choice)
	{

		char s[200];//sql�� ������
		char s1[200];//�������� �κ� Ȯ���ϱ����� select���� ���� ��
		int Fyear;//DB�� year�̶�� �÷����� �־ �򰥸���� F���� ����
		int Fmon;
		int Fday;
		int plus_check = 0;
		int check;
		switch (choice)
		{
		case 1://���뿩��û
			time_t timer;
			struct tm t;

			timer = time(NULL);
			localtime_s(&t, &timer);//����ð� ���ϴ� ��
			Fyear = t.tm_year + 1900;
			Fmon = t.tm_mon + 1;
			Fday = t.tm_mday;
			sprintf_s(s, 200, "UPDATE user SET year = %d, month=%d, day=%d, return1 =0, plusday=0, lendok=1  WHERE Id = %s ", Fyear, Fmon, Fday, id);
			sprintf_s(s1, 200, "select lendok from user where lendok =(1||2) && id = %s", id); //��� �ݳ� �� �ѻ��
			break;

		case 2://���ݳ��Ⱓ �����û
			sprintf_s(s, 100, "UPDATE user SET plusday=1 WHERE Id = %s ", id);
			sprintf_s(s1, 200, "select plusday  from (select * from user where id=%s) c where plusday =1 || lendok=0", id);
			//sprintf_s(s1, 200, "select plusday from user where plusday =1 && id = %s", id);//�̹� �� �� �����û�� �ߴ��� Ȯ��
			break;

		case 3://���뿩 ��Ȳ
			sprintf_s(s, 100, "select *from user where lendok=2&&return1 =0 && id = %s", id);
			break;
		}


		if (choice < 3) {
			MYSQL_RES *res = nullptr;
			MYSQL_ROW row;
			int fields = 0;
			check = 3;
			mysql_query(cons, s1);
			res = mysql_store_result(cons);  // ��� ��� ���
			while (row = mysql_fetch_row(res)) // �� ���� ����
			{
				check = atoi(row[0]);
				mysql_free_result(res);
				mysql_close(cons);
			}
			
			x = 8, y = 14;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);

			if (choice == 1 && check != 3) {  gotoxy(x, y); cout << "�̹� ����� �����̽��ϴ�." << endl; }// "���뿩��û" ���� ���


			else if (choice == 2 && check != 3) {
				gotoxy(x, y);
				cout << "�����û �Ұ��� (�̹� �����û�� �߰ų�, ����� ������ �ʾҽ��ϴ�.)" << endl;// "��꿬���û" ���� ���
			}
			
			else {//�ذ�~!~!
				if (mysql_query(cons, s) && choice != 3 && plus_check == 0)
				{
					fprintf(stderr, "%s\n", mysql_error(cons));
					mysql_close(cons);
					exit(1);
				}
			}//else�� �ݱ�
		}//1,2


		else if (choice == 3) {//3�ϴ� ����
			mysql_query(cons, s);
			MYSQL_RES *res = nullptr;
			MYSQL_ROW row;
			int fields = 0;
			int count = 0;
			mysql_query(cons, s);
			int returnYear, returnMonth, returnDate;

			time_t timer;
			struct tm t;




			res = mysql_store_result(cons);  // ��� ��� ���
			fields = mysql_num_fields(res); // �ʵ� ���� ����
			x = 8, y = 12;
			while (row = mysql_fetch_row(res)) // �� ���� ����
			{
				int day = atoi(row[4]);//ĳ���͸� ��Ʈ������
				int check = atoi(row[6]);

				if (check == 0) timer = time(NULL) + 7 * (24 * 60 * 60);//plusDay�� üũ�ؼ� �����û�� �������� 0, ������ else�� �Ѵ�
				else timer = time(NULL) + 14 * (24 * 60 * 60);

				localtime_s(&t, &timer);//����ð� ���ϴ� ��
				returnYear = t.tm_year + 1900;
				returnMonth = t.tm_mon + 1;
				returnDate = t.tm_mday;
				gotoxy(x, y);
				cout << "���̵� : " << row[0] << "  �̸� : " << row[1];
				y+=2;
				gotoxy(x, y);
				cout<<"�뿩�Ⱓ : " << row[2] << "��" << row[3] << "��" << row[4] << "�� ~ " << returnYear << "��" << returnMonth << "��" << returnDate << "��" << endl;
				mysql_free_result(res);
				mysql_close(cons);
				count++;
			}
			x = 8, y = 12;
			if (count == 0) {
				gotoxy(x, y);
				cout << "�ݳ��� ����� �����ϴ�.";
			}


		}
		return check;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

	}
	void gotoxy(int x, int y) {
		COORD Pos = { (short)x - 1, (short)y - 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

};




class Lender
{
public:

	int x, y;
	int cho = 0;
	void draw_background() {
		gotoxy(2, 3);
		cout << "��";
		for (int i = 0; i < 75; i++) {
			cout << "��";
		}
		cout << "��";

		int b_y = 4, b_x = 2;
		for (int i = 0; i < 30; i++) {
			gotoxy(b_x, b_y);
			cout << "��";
			gotoxy(b_x + 76, b_y);
			cout << "��";
			b_y++;
		}

		gotoxy(2, 9);
		cout << "��";
		for (int i = 0; i < 75; i++) {
			cout << "��";
		}
		cout << "��";


		gotoxy(2, 34);
		cout << "��";
		for (int i = 0; i < 75; i++) {
			cout << "��";
		}
		cout << "��";

	}
	void draw_arrow() {
		gotoxy(x, y);
		int key;
		do {
			key = _getch();
			move_arrow_key(key, 100, 22);//43
		} while (key != 32);

	}

	void move_arrow_key(char key, int x_b, int y_b) {
		switch (key) {
		case 72://��
			if (y > 25) {
				gotoxy(x - 2, y);
				cout << " ";
				y -= 2;
				gotoxy(x - 2, y);
				cout << ">";
			}
			break;

		case 80: //�Ʒ�
			if (y < 31) {
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
			case 25:  cho = 1;  break;
			case 27: cho = 2; break;
			case 29: cho = 3; break;
			case 31: cho = 4; break;
			}
		default:
			return;
		}
	}

	void gotoxy(int x, int y) {
		COORD Pos = { (short)x - 1, (short)y - 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	Lender(const char* id) {
		while (!(cho == 4)) {

			system("cls");
			draw_umbrella();
			x = 20, y = 25;

			gotoxy(x - 2, y);
			cout << ">";
			gotoxy(x , y);
			cout << "��� �뿩 ��û" << endl;
			gotoxy(x, y+2);
			cout << "��� �ݳ� �Ⱓ �����û" << endl;
			gotoxy(x , y+4);
			cout << "��� �뿩 ��Ȳ" << endl;
			gotoxy(x , y+6);
			cout << "�α׾ƿ�" << endl;
			draw_arrow();
			switch (cho)
			{
			case 1: system("cls"); Askfor(id); break;
			case 2: system("cls"); Plus(id); break;
			case 3: system("cls"); userNow(id); break;
			case 4: return; break;
			}
		}
	}
	void Askfor(const char * id) {
		draw_background();
		gotoxy(27, 6);
		cout << "****** ��� �뿩 ��û ******";

		x = 8, y = 12;
		gotoxy(x, y);
		cout << "���뿩��û ��..." << endl;
		
		MYSQL * cons = mysql_init(NULL);
		DB d(HOST,cons);
		if (d.loadmysql(HOST, cons, id, 1) == 3) {	//�������� 1�� ���뿩��û�Ϸ����� �ݳ��Ϸ����� �׷���  �����Ϸ��� ����
			y += 2;
			gotoxy(x, y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			cout << "�Ϸ�!" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			y-=2;
		}
		y += 4;
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		system("pause");
	}
	void Plus(const char *id) {
		draw_background();
		gotoxy(27, 6);
		cout << "****** ��� ���� ��û ******";
		x = 8, y = 12;
		gotoxy(x, y);
		cout << "��� �ݳ��Ⱓ �����û ��..." << endl;
		MYSQL * cons = mysql_init(NULL);
		DB d(HOST, cons);
		if (d.loadmysql(HOST, cons, id, 2) == 3) {	//�������� 2�� ���뿩��û�Ϸ����� �ݳ��Ϸ����� �׷���  �����Ϸ��� ����
			y += 2;
			gotoxy(x, y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			cout << "�Ϸ�!" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			y-=2;
		}
		y += 4;
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		system("pause");
	}
	void userNow(const char *id) {
		draw_background();
		gotoxy(27, 6);
		cout << "****** ��� �뿩 ��Ȳ ******";
		x = 8, y = 12;
		MYSQL * cons = mysql_init(NULL);
		DB d(HOST, cons);
		if (d.loadmysql(HOST, cons, id, 3) == 3) {	//�������� 3�� ���뿩��û�Ϸ����� �ݳ��Ϸ����� �׷���  �����Ϸ��� ����
			y += 2;
			gotoxy(x, y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			cout << "�Ϸ�!" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			y-=2;
		}
		y += 4;
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		system("pause");
	}



	void draw_umbrella() {
		x = 35, y = 1;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
		for (int j = 0; j < 9; j++) {
			gotoxy(x, y);
			for (int i = 0; i < 81 - x; i++) {
				cout << "#";
			}
			x -= 4;
			y++;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKGRAY);
		for (int i = 0; i < 6; i++) {
			gotoxy(x - n, y);
			cout << "����";
			for (int j = 0; j < n - 11; j++) {
				cout << "  ";
			}
			cout << "����";
			y++;
			if (i % 2 != 0) {
				n -= 2;
			}
		}
		gotoxy(x - n, y);
		cout << "�����";

		x = 1; y = 12;
		gotoxy(x, y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		cout << "   ��  ��    �ɢɢ�    �ɢ�    �ɢɢ�   �ɢɢ�  ��     ��       �ɢ�  " << endl;
		cout << "   ��  ��  �ɢɢɢɢ�  ��  ��  ��   ��  ��      ��     ��      ��  �� " << endl;
		cout << "   ��  ��  ��  ��  ��  �ɢɢ�  �ɢɢ�   �ɢɢ�  ��     ��     �ɢɢɢ�" << endl;
		cout << "   ��  ��  ��  ��  ��  ��  ��  ��  ��   ��      ��     ��     ��    ��" << endl;
		cout << "   �ɢɢ�  ��  ��  ��  �ɢɢ�  ��   ��  �ɢɢ�  �ɢɢ� �ɢɢ� ��    ��" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);



	}

};





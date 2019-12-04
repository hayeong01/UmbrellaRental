#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h> 
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include<mysql.h>
#define USER "root"				//���� �̸�
#define PASSWORD "mirim2"		//��й�ȣ
#define HOST "localhost"

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
			//			printf("\n����");
			mysql_set_character_set(cons, "euckr");	//MySQL ���ڸ� ���� ���ϸ� �ѱ� ©��
		}
		else {
			fprintf(stderr, "���� ���� : %s\n", mysql_error(cons));
			getchar();
		}
	}

	MYSQL_RES* select_sql(const char mysqlip[], MYSQL *cons, int type, int lendok, int return1) {
		char s[200];//sql�� ������
		MYSQL_RES *res;

		if (return1 == -1)
			sprintf_s(s, 200, "select * from user where type=%d and lendok=%d; ", type, lendok);
		else  sprintf_s(s, 200, "select * from user where type=%d and lendok=%d and return1=%d; ", type, lendok, return1);

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
};
class Manager {
public:
	int x, y;
	int cho;

	int ShowAllRental() {
		MYSQL_RES* res;
		int count;
		while (true) {
			system("cls");
			draw_background();

			gotoxy(27, 6);
			cout << "****** ��ü �뿩 ��Ȳ ******";

			MYSQL * cons = mysql_init(NULL);
			DB2 all(HOST, cons);
			res = all.select_sql(HOST, cons, 2, 2, 0);
			MYSQL_ROW row;
			int returnYear, returnMonth, returnDate;

			time_t timer;
			struct tm t;
			count = 0;

			int fields = mysql_num_fields(res); // �ʵ� ���� ����
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
				cout << row[0] << " " << row[1] << "  �뿩�Ⱓ : " << row[2] << "��" << row[3] << "��" << row[4] << "�� ~ " << returnYear << "��" << returnMonth << "��" << returnDate << "��";

				count++;
				y+=2;
			}
			if (count == 0) {
				gotoxy(x, y);
				cout << "�뿩�� ����� �����ϴ�";
			}
			y += 3;
			x = 20;
			gotoxy(x , y);
			cout << ">";
			gotoxy(x+1, y);
			cout << " ��� �ݳ� ����" << endl;
			gotoxy(x+18, y);
			cout << " �ڷ� ����" << endl;

			draw_arrow1();

			switch (cho) {
			case 1: ReturnUmb(); break;
			case 3: return 0;  break;
			}
		}
	}
	void RentalApply_Accept() {

		

		MYSQL * cons = mysql_init(NULL);
		DB2 apply(HOST, cons);
		MYSQL_RES* res;
		MYSQL_ROW row;
		int returnYear, returnMonth, returnDate;

		time_t timer;
		struct tm t;
		int count = 1;
		int selectNum = 0;

		while (1) {
			system("cls");
			draw_background();
			gotoxy(27, 6);
			cout << "****** �뿩 ��û ���� ******";

			res = apply.select_sql(HOST, cons, 2, 1, -1);

			count = 1;
			int fields = mysql_num_fields(res); // �ʵ� ���� ����
			x = 10, y = 12;
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

				cout << row[0] << " " << row[1] << "  �뿩�Ⱓ : " << row[2] << "��" << row[3] << "��" << row[4] << "�� ~ " << returnYear << "��" << returnMonth << "��" << returnDate << "��";

				count++;
				y+=2;
			}
			if (count == 1) {// while�� �ȿ� ���� �ʾ��� ��
				gotoxy(x, y);
				cout << "�뿩 ��û�� ����� �����ϴ�.";

				y += 3;
				gotoxy(x, y);
				system("pause");
				break;
			}

			y += 3;
			gotoxy(x, y);
			char selectID[20];
			cout << "�뿩 ������ �л��� �й��� �Է��ϼ��� >> ";
			cin >> selectID;

			char s[200];//sql�� ������

			sprintf_s(s, 100, "UPDATE user SET lendok=2 WHERE Id = %s;", selectID);

			if (mysql_query(cons, s)) {
				fprintf(stderr, "%s\n", mysql_error(cons));
				mysql_close(cons);
			}
			y += 2;
			gotoxy(x, y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			cout << "�뿩 ��û�� �����߽��ϴ�.";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);


			y += 2;
			gotoxy(x, y);
			cout << "��� �ϰ� �ʹٸ� 1, �ڷ� ����� 2�� �Է����ּ��� >> ";
			cin >> selectNum;

			if (selectNum == 1) continue;
			else if (selectNum == 2) break;
		}
	}
	void ReturnUmb() {
		MYSQL * cons = mysql_init(NULL);
		DB2 all(HOST, cons);
		MYSQL_RES* res;
		MYSQL_ROW row;
		int returnYear, returnMonth, returnDate;

		time_t timer;
		struct tm t;
		int count = 1;
		int selectNum = 0;

		while (1) {
			count = 1;
			system("cls");
			draw_background();

			res = all.select_sql(HOST, cons, 2, 2, 0);
			gotoxy(27, 6);
			cout << "****** ��� �ݳ� ���� ******";

			int fields = mysql_num_fields(res); // �ʵ� ���� ����
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
				cout << row[0] << " " << row[1] << "  �뿩�Ⱓ : " << row[2] << "��" << row[3] << "��" << row[4] << "�� ~ " << returnYear << "��" << returnMonth << "��" << returnDate << "��";

				count++;
				y+=2;
			}
			if (count == 1) {// while�� �ȿ� ���� �ʾ��� ��
				gotoxy(x, y);
				cout << "�뿩�� ����� �����ϴ�.";

				y += 3;
				gotoxy(x, y);
				system("pause");
				break;
			}

			y += 3;
			gotoxy(x, y);
			char selectID[20];
			cout << "��� �ݳ� ó���� �л��� �й��� �Է��ϼ��� >> ";
			cin >> selectID;

			char s[200];//sql�� ������

			sprintf_s(s, 100, "UPDATE user SET return1=1 WHERE Id = %s;", selectID);

			if (mysql_query(cons, s)) {
				fprintf(stderr, "%s\n", mysql_error(cons));
				mysql_close(cons);
			}
			y += 2;
			gotoxy(x, y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			cout << "��� �ݳ��� �Ϸ��߽��ϴ�. ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);


			y += 2;
			gotoxy(x, y);
			cout << "��� �ϰ� �ʹٸ� 1, �ڷ� ����� 2�� �Է����ּ��� >> ";
			cin >> selectNum;

			if (selectNum == 1) continue;
			else return;
		}

	}

	Manager() {
		while (true) {

			system("cls");
			draw_umbrella();
			x = 20, y = 25;
			gotoxy(x - 2, y);
			cout << ">";
			gotoxy(x, y);
			cout << "��ü �뿩 ��Ȳ" << endl;
			gotoxy(x, y + 2);
			cout << "�뿩 ��û ����" << endl;
			gotoxy(x, y + 4);
			cout << "�α׾ƿ�" << endl;
			draw_arrow();
			switch (cho) {
			case 1: ShowAllRental(); break;
			case 2: RentalApply_Accept(); break;
			case 3: return;  break;
			}

		}
	}

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
			move_arrow_key(key, 43, 22);
		} while (key != 32);
	}

	void draw_arrow1() {
		gotoxy(x, y);
		int key;
		do {
			key = _getch();
			move_arrow_key_no(key, 43, 22);
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

	void move_arrow_key_no(char key, int x_b, int y_b) {
		switch (key) {
		case 75://����
			if (x > 20) {
				gotoxy(x, y);
				cout << " ";
				x -= 17;
				gotoxy(x, y);
				cout << ">";
			}
			break;

		case 77://������
			if (x < 37) {
			gotoxy(x, y);
			cout << " ";
			x += 17;
			gotoxy(x, y);
			cout << ">";
		}
			break;
		case 32:
			switch (x)
			{
			case 20: cho = 1;  break;
			case 37: cho = 3; break;
			}
		default:
			return;
		}
	}



	void gotoxy(int x, int y) {
		COORD Pos = { (short)x - 1, (short)y - 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
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
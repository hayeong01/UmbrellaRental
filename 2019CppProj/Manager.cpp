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

	MYSQL_RES* select_sql(const char mysqlip[], MYSQL *cons,int type,int lendok) {
		char s[200];//sql�� ������
		MYSQL_RES *res;

		sprintf_s(s, 200, "select * from user where type=%d and lendok=%d; ",type,lendok);

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
	void ShowAllRental() {
		while (true) {
			system("cls");
			draw_background();

			gotoxy(32, 6);
			cout << "****** ��ü �뿩 ��Ȳ ******";

			MYSQL * cons = mysql_init(NULL);
			DB2 all(HOST, cons);
			MYSQL_RES* res = all.select_sql(HOST, cons,2,2);
			MYSQL_ROW row;
			int returnYear, returnMonth, returnDate;

			time_t timer;
			struct tm t;
			int count = 0;

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
				cout << "���̵� : " << row[0] << "   �̸� : " << row[1] << "  �뿩�Ⱓ : " << row[2] << "��" << row[3] << "��" << row[4] << "�� ~ " << returnYear << "��" << returnMonth << "��" << returnDate << "��";
				
				count++;
				y++;
			}

			x = 20, y = 25;
			gotoxy(x - 2, y);
			cout << ">";
			gotoxy(x, y);
			cout << "��� �ݳ� ����" << endl;
			gotoxy(x, y + 2);
			cout << "���� ��û ����" << endl;
			gotoxy(x, y + 4);
			cout << "�ڷ� ����" << endl;

			draw_arrow();

			switch (cho) {
			case 1: ReturnUmb(); break;
			case 2:	PlusDay_Accept(); break;
			case 3: return;  break;
			}
			if (count == 0)cout << "�뿩�� ����� �����ϴ�.";
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
			
			cout << count<<". �̸� : " << row[1] << "  �뿩�Ⱓ : " << row[2] << "��" << row[3] << "��" << row[4] << "�� ~ " << returnYear << "��" << returnMonth << "��" << returnDate << "��";

			count++;
			y++;
		}

		y += 3;
		gotoxy(x, y);
		cout << "�뿩 ������ ��ȣ�� �Է��ϼ��� >>";
		cin >> selectNum;

		count = 1;
		while (row = mysql_fetch_row(res)) // �� ���� ����
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
			cout << "��ü �뿩 ��Ȳ" << endl;
			gotoxy(x, y + 2);
			cout << "�뿩 ��û ����" << endl;
			gotoxy(x, y + 4);
			cout << "�α׾ƿ�" << endl;
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
		cout << "   ��  ��    �ɢɢ�    �ɢ�    �ɢɢ�   �ɢɢ�  ��     ��       �ɢ�  " << endl;
		cout << "   ��  ��  �ɢɢɢɢ�  ��  ��  ��   ��  ��      ��     ��      ��  �� " << endl;
		cout << "   ��  ��  ��  ��  ��  �ɢɢ�  �ɢɢ�   �ɢɢ�  ��     ��     �ɢɢɢ�" << endl;
		cout << "   ��  ��  ��  ��  ��  ��  ��  ��  ��   ��      ��     ��     ��    ��" << endl;
		cout << "   �ɢɢ�  ��  ��  ��  �ɢɢ�  ��   ��  �ɢɢ�  �ɢɢ� �ɢɢ� ��    ��" << endl;

	}
};
#define _CRT_SECURE_NO_WARNINGS
#pragma comment (lib, "libmysql.lib")

#include <iostream>
#include <time.h> 
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#include "Lender.cpp"
#include "Manager.cpp"
#define USER "root"				//���� �̸�
#define PASSWORD "mirim2"		//��й�ȣ
#define HOST "localhost"
using namespace std;

class main_screen {
	int c = 0;
	int sign_user_num;

public:
	char id[20];
	int x, y;
	int cho = 0;
	void draw_background() {
		gotoxy(2, 3);
		cout << "��";
		for (int i = 0; i < 75; i++) {
			cout << "��";
		}
		cout << "��";

		//gotoxy(30, 3);
		//cout << "  �ٿ�� �뿩 ���α׷��� ";

		int b_y = 4,b_x=2;
		for (int i = 0; i < 30; i++) {
			gotoxy(b_x, b_y);
			cout << "��";
			gotoxy(b_x + 76, b_y);
			cout << "��";
			b_y ++;
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
			case 25:  cho = 1;  break;
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

	int choice_sign() {

		int re = 0;
		while (1) {
			system("cls");
			draw_umbrella();
			//draw_background();
			x = 20, y = 25;
			
			
			gotoxy(x-2, y);
			cout << ">";
			gotoxy(x, y);
			cout << "�α���" << endl;
			gotoxy(x, y + 2);
			cout << "ȸ������" << endl;
			gotoxy(x, y + 4);
			cout << "�����ϱ�" << endl;
			draw_arrow();
			//cin >> cho;
			switch (cho) {
			case 1: system("cls"); re = sign_in(); break;
			case 2: system("cls"); re = sign_up(); break;
			case 3: return 0; break;
			}

			if (re == 0) continue;
			else return re;
		}
	}
	int sign_up() {
		char id[10];
		char password[10];
		char name[10];
		int t;
		draw_background();
		x = 23, y = 9;

		gotoxy(x+9,6);
		cout << "****** ȸ������ ******";
		y += 2;
		gotoxy(x, y);
		cout << "���̵� (2019+�ڽ��� �й�) >> ";
		cin >> id;
		y += 2;
		gotoxy(x, y);
		cout << "��й�ȣ >> ";
		cin >> password;
		y += 2;
		gotoxy(x, y);
		cout << "�̸� >> ";
		cin >> name;
		y += 2;
		gotoxy(x, y);
		cout << "������ : 1 / �뿩�� : 2 >> ";
		cin >> t;

		MYSQL * cons = mysql_init(NULL);
		DB insert(HOST,cons);
		
		if (insert.insertspl(HOST, cons, id, password, t, name)) {
			y += 2;
			gotoxy(x, y);
			cout << "ȸ�������� ���������� �Ϸ�Ǿ����ϴ�!";
			y += 2;
			gotoxy(x, y);
			system("pause");
			return 0;
		}
		else {
			y += 2;
			gotoxy(x, y);
			cout << "!!�̹� ���Ե� ���̵��Դϴ�!!";
			system("pause");
			return 0;
		}
	}

	int sign_in() {
		
		char password[20];
		system("cls");
		draw_background();
		
		x = 23, y = 9;

		gotoxy(x + 9, 6);
		cout << "****** �α��� ******";

		y += 2;
		gotoxy(x, y);
		cout << "���̵� (2019�й�) >> ";
		cin >> id;
		y += 2;
		gotoxy(x, y);
		cout << "��й�ȣ >> ";
		cin >> password;
		
		MYSQL * cons = mysql_init(NULL);
		DB search(HOST,cons);
		int userType;
		int result=search.login_sql(HOST, cons, id,password,userType);

		if (result==2) {//�н�������� ������
			y += 2;
			gotoxy(x, y);
			cout << "!! �α��� ���� !!" << endl;
			y += 2;
			gotoxy(x, y);
			system("pause");
			return userType;

		}
		else if(result==1){
			y += 2;
			gotoxy(x, y);
			cout << "!! ��й�ȣ�� Ʋ�Ƚ��ϴ� !!" << endl;
			y += 2;
			gotoxy(x, y);
			system("pause");
			return 0;
		}
		else if(result==0) {
			y += 2;
			gotoxy(x, y);
			cout << "���̵� �������� �ʽ��ϴ�" << endl;
			y += 2;
			gotoxy(x, y);
			system("pause");
			return 0;
		}

		return 0;
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
			gotoxy(x,y);
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
	char* get_id() {
		return id;
	}
};


int main() {
	main_screen main;
	
	while (1) {
		int i = main.choice_sign(); //1 - ������ 2 - �뿩��
		if (i == 2) { 
			Lender person(main.get_id());
		}
		else if (i == 1) {
			Manager Mperson;
		}
	}
}
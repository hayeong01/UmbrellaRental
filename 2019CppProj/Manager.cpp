#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h> 
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

class Manager {
public:
	int x, y;
	int cho;
	void ShowAllRental() {
		while (true) {
			system("cls");
			draw_background();
			x = 35, y = 15;
			gotoxy(x - 2, y);
			cout << ">";
			gotoxy(x, y);
			cout << "우산 반납 관리" << endl;
			gotoxy(x, y + 1);
			cout << "연장 신청 수락" << endl;
			gotoxy(x, y + 2);
			cout << "뒤로 가기" << endl;

			draw_arrow();

			switch (cho) {
			case 1: ReturnUmb(); break;
			case 2:	PlusDay_Accept(); break;
			case 3: return;  break;
			}
		}
	}
	void RentalApply_Accept() {
		system("cls");
		draw_background();
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

		gotoxy(30, 3);
		cout << "  ☆우산 대여 프로그램☆ ";

		int b_y = 4, b_x = 2;
		for (int i = 0; i < 30; i++) {
			gotoxy(b_x, b_y);
			cout << "│";
			gotoxy(b_x + 76, b_y);
			cout << "│";
			b_y++;
		}

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
			if (y < 28) {
				
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
			case 28: cho = 3; break;
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
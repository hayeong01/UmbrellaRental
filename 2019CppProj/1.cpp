#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h> 
#include <string>
#include <Windows.h>
#include <stdio.h>
using namespace std;
class main_screen {
	string user_id[10];
	string user_pw[10];
	string user_name[10];
	int c = 0;
	int type[10];
	int sign_user_num;

public:
	int choice_sign() {
		int cho;
		int re=0;
		while (1) {
			system("cls");
			cout << "1. 로그인" << endl;
			cout << "2. 회원가입" << endl;
			cout << "3. 종료하기" << endl;
			cout << " 선택 > ";
			cin >> cho;
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
		string id;
		string password;
		string name;
		int t;
		cout << "****** 회원가입 ******" << endl;
		cout << "아이디 (2019+자신의 학번) >> ";
		cin >> id;
		cout << "비밀번호 >> ";
		cin >> password;
		cout << "이름 >> ";
		cin >> name;
		cout << "관리자 : 1 / 대여자 : 2 >> ";
		cin >> t;
		for (int i = 0; i < c; i++) {
			if (id == user_id[i]) {
				cout << "이미 가입된 아이디입니다." << endl;
				system("pause");
				return 0;
			}
		}
		user_id[c] = id;
		user_pw[c] = password;
		type[c] = t;
		user_name[c] = name;
		c++;
		cout << "회원가입이 성공적으로 완료되었습니다!" << endl;
		system("pause");
		return 0;
	}
	int sign_in() {
		string id;
		string password;
		cout << "아이디 (2019학번) >> ";
		cin >> id;
		cout << "비밀번호 >> ";
		cin >> password;
		for (int i = 0; i < c; i++) {
			if (id == user_id[i]) {
				if (password == user_pw[i]) {
					sign_user_num = i;
					cout << "** 로그인 성공 **" << endl;
					system("pause");
					if (type[i] == 1) { //관리자
						return 1;
					}
					else {//대여자
						return 2;
					}
				}
				else {
					cout << "비밀번호가 틀렸습니다" << endl;
					system("pause");
					return 0;
				}
			}
		}
		cout << "아이디가 존재하지 않습니다" << endl;
		system("pause");
		return 0;
	}
	string get_user_name() {
		return user_name[sign_user_num];
	}
};

class rental_person_main {
	int choice;
	string name;
	char rentyn;
	char extension;
	string person_date;
public:
	/*rental_person_main() {
		person_choice();
	}*/

	int person_choice(string user_name) {
		name = user_name;
		while (true) {
			system("cls");
			cout << "1. 우산대여신청" << endl;
			cout << "2. 반납연장신청" << endl;
			cout << "3. 대여자 대여 현황" << endl;
			cout << "4. 로그아웃" << endl;
			cout << "선택 : ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				system("cls");
				rental_umbrella();
				break;
			case 2:
				system("cls");
				umbrella_return();
				break;
			case 3:
				system("cls");
				my_umbrella_status();
				break;
			case 4:
				return 0;
				break;
			}

		}

	}
	void rental_umbrella() {
		cout << name << "님" << endl;
		date();
		cout << "보증금 : 500원" << endl;
		cout << "반납 시간 : 16:10 ~ 17:00" << endl;
		cout << "반납 장소  : 학생쉼터\n\n" << endl;
		cout << "주의사항" << endl;
		cout << "1. 연장신청은 4일까지 가능" << endl;
		cout << "2. 우산분실, 훼손시 벌금 5000원 부과" << endl;
		cout << "3. 반드시 본인만 대여, 반납가능" << endl;
		cout << "4. 연체시 1일당 500원씩 벌금부과\n\n" << endl;

		cout << "대여하시겠습니까?  Y/N" << endl;
		cin >> rentyn;
		if (rentyn == 'Y' || rentyn == 'y') {
			cout << "대여신청 완료." << endl;
		}
		else
			cout << "대여신청 취소." << endl;

		system("pause");
	}

	void umbrella_return() {
		cout << name << "님" << endl;
		cout << "우산 반납 기간 연장신청하시겠습니까? Y/N" << endl;
		cin >> extension;
		if (extension == 'Y' || extension == 'y') {
			cout << "연장신청 완료." << endl;

			date();
		}
		else
			cout << "연장신청 취소." << endl;

		system("pause");
	}
	void my_umbrella_status() {
		cout << name << "님 대여 현황" << endl;

	}


	int date() {
		time_t timer;
		struct tm *t;
		timer = time(NULL) - (24 * 60 * 60);
		t = localtime(&timer);
		cout << "대여기간 : " << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday + 1 << " ~ " << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday + 8 << endl;
		return 0;
	}


};
int main() {
	main_screen main;
	while (1) {
		int i = main.choice_sign();
		if (i == 2) {
			rental_person_main person;
			person.person_choice(main.get_user_name());
		}
		else if (i == 0) {
			break;
		}
	}
}
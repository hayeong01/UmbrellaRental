#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h> 
#include <string>
#include <Windows.h>
#include <stdio.h>
using namespace std;

class Render {
	
public:
	int choice;
	string name;
	char rentyn;
	char extension;
	string person_date;

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


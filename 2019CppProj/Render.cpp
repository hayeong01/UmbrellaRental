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
			cout << "1. ���뿩��û" << endl;
			cout << "2. �ݳ������û" << endl;
			cout << "3. �뿩�� �뿩 ��Ȳ" << endl;
			cout << "4. �α׾ƿ�" << endl;
			cout << "���� : ";
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
		cout << name << "��" << endl;
		date();
		cout << "������ : 500��" << endl;
		cout << "�ݳ� �ð� : 16:10 ~ 17:00" << endl;
		cout << "�ݳ� ���  : �л�����\n\n" << endl;
		cout << "���ǻ���" << endl;
		cout << "1. �����û�� 4�ϱ��� ����" << endl;
		cout << "2. ���н�, �Ѽս� ���� 5000�� �ΰ�" << endl;
		cout << "3. �ݵ�� ���θ� �뿩, �ݳ�����" << endl;
		cout << "4. ��ü�� 1�ϴ� 500���� ���ݺΰ�\n\n" << endl;

		cout << "�뿩�Ͻðڽ��ϱ�?  Y/N" << endl;
		cin >> rentyn;
		if (rentyn == 'Y' || rentyn == 'y') {
			cout << "�뿩��û �Ϸ�." << endl;
		}
		else
			cout << "�뿩��û ���." << endl;

		system("pause");
	}

	void umbrella_return() {
		cout << name << "��" << endl;
		cout << "��� �ݳ� �Ⱓ �����û�Ͻðڽ��ϱ�? Y/N" << endl;
		cin >> extension;
		if (extension == 'Y' || extension == 'y') {
			cout << "�����û �Ϸ�." << endl;

			date();
		}
		else
			cout << "�����û ���." << endl;

		system("pause");
	}
	void my_umbrella_status() {
		cout << name << "�� �뿩 ��Ȳ" << endl;

	}


	int date() {
		time_t timer;
		struct tm *t;
		timer = time(NULL) - (24 * 60 * 60);
		t = localtime(&timer);
		cout << "�뿩�Ⱓ : " << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday + 1 << " ~ " << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday + 8 << endl;
		return 0;
	}


};


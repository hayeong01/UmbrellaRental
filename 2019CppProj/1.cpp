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
			cout << "1. �α���" << endl;
			cout << "2. ȸ������" << endl;
			cout << "3. �����ϱ�" << endl;
			cout << " ���� > ";
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
		cout << "****** ȸ������ ******" << endl;
		cout << "���̵� (2019+�ڽ��� �й�) >> ";
		cin >> id;
		cout << "��й�ȣ >> ";
		cin >> password;
		cout << "�̸� >> ";
		cin >> name;
		cout << "������ : 1 / �뿩�� : 2 >> ";
		cin >> t;
		for (int i = 0; i < c; i++) {
			if (id == user_id[i]) {
				cout << "�̹� ���Ե� ���̵��Դϴ�." << endl;
				system("pause");
				return 0;
			}
		}
		user_id[c] = id;
		user_pw[c] = password;
		type[c] = t;
		user_name[c] = name;
		c++;
		cout << "ȸ�������� ���������� �Ϸ�Ǿ����ϴ�!" << endl;
		system("pause");
		return 0;
	}
	int sign_in() {
		string id;
		string password;
		cout << "���̵� (2019�й�) >> ";
		cin >> id;
		cout << "��й�ȣ >> ";
		cin >> password;
		for (int i = 0; i < c; i++) {
			if (id == user_id[i]) {
				if (password == user_pw[i]) {
					sign_user_num = i;
					cout << "** �α��� ���� **" << endl;
					system("pause");
					if (type[i] == 1) { //������
						return 1;
					}
					else {//�뿩��
						return 2;
					}
				}
				else {
					cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�" << endl;
					system("pause");
					return 0;
				}
			}
		}
		cout << "���̵� �������� �ʽ��ϴ�" << endl;
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
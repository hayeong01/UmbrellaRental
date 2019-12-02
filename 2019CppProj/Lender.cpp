#pragma comment (lib, "libmysql.lib")
#include<mysql.h>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <string.h>
#include <time.h>
#define USER "root"				//���� �̸�
#define PASSWORD "mirim2"		//��й�ȣ
#define HOST "localhost"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
class DB {
public:
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
		sprintf_s(s, 200, "insert into user values('%s','%s',0,0,0,0,0,0,'%s',%d); ", id, name, pw, type);

		if (mysql_query(cons, s))
		{
			fprintf(stderr, "%s\n", mysql_error(cons));
			mysql_close(cons);

			cout << "����";
		}


		return true;

	}
	void loadmysql(const char mysqlip[], MYSQL *cons, const char * id, int choice)
	{

		char s[200];//sql�� ������
		char s1[200];//�������� �κ� Ȯ���ϱ����� select���� ���� ��
		int Fyear;//DB�� year�̶�� �÷����� �־ �򰥸���� F���� ����
		int Fmon;
		int Fday;
		int plus_check = 0;
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
			sprintf_s(s1, 200, "select lendok from user where lendok >0 && id = %s", id); //��� �ݳ� �� �ѻ��
			break;

		case 2://���ݳ��Ⱓ �����û
			sprintf_s(s, 100, "UPDATE user SET plusday=1 WHERE Id = %s ", id);
			sprintf_s(s1, 200, "select plusday from user where plusday =1 && id = %s", id);//�̹� �� �� �����û�� �ߴ��� Ȯ��
			break;

		case 3://���뿩 ��Ȳ
			sprintf_s(s, 100, "select *from user where return1 =0 && id = %s", id);
			break;
		}


		if (choice < 3) {
			MYSQL_RES *res = nullptr;
			MYSQL_ROW row;
			int fields = 0;
			int check = 3;
			mysql_query(cons, s1);
			res = mysql_store_result(cons);  // ��� ��� ���
			while (row = mysql_fetch_row(res)) // �� ���� ����
			{
				check = atoi(row[0]);
				mysql_free_result(res);
				mysql_close(cons);
			}

			if (choice == 1 && check != 3)cout << "�̹� ����� �����̽��ϴ�" << endl;// "���뿩��û" ���� ���

			else if (choice == 2 && check != 3)cout << "�̹� �ѹ� �����û�� �ϼ̽��ϴ�" << endl;// "��꿬���û" ���� ���

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

				cout << "���̵� : " << row[0] << "\n�̸� : " << row[1] << "\n�뿩�Ⱓ : " << row[2] << "��" << row[3] << "��" << row[4] << "�� ~ " << returnYear << "��" << returnMonth << "��" << returnDate << "��" << endl;
				mysql_free_result(res);
				mysql_close(cons);
				count++;
			}
			if (count == 0)cout << "�ݳ��� ����� �����ϴ�.";


		}
		return;
	}

};
class Lender
{
public:
	Lender(const char* id) {
		int select;
		while (1) {
			system("cls");
			cout << "1.���뿩��û" << endl;
			cout << "2.��� �ݳ� �Ⱓ �����û" << endl;
			cout << "3.��� �뿩 ��Ȳ" << endl;
			cout << "4.����" << endl;
			cout << ">>";
			cin >> select;

			switch (select)
			{
			case 1: system("cls"); Askfor(id); break;
			case 2: system("cls"); Plus(id); break;
			case 3: system("cls"); userNow(id); break;
			case 4: return; break;
			default:
				break;
			}
		}
	}
	void Askfor(const char * id) {
		cout << "���뿩��û ��..." << endl;
		
		MYSQL * cons = mysql_init(NULL);
		DB d(HOST,cons);
		d.loadmysql(HOST, cons, id, 1);	//�������� 1�� ���뿩��û�Ϸ����� �ݳ��Ϸ����� �׷���  �����Ϸ��� ����
		cout << "\n�Ϸ�!" << endl;
		system("pause");
	}
	void Plus(const char *id) {
		cout << "��� �ݳ��Ⱓ �����û ��..." << endl;
		MYSQL * cons = mysql_init(NULL);
		DB d(HOST, cons);
		d.loadmysql(HOST, cons, id, 2);	//�������� 2�� ���뿩��û�Ϸ����� �ݳ��Ϸ����� �׷��� �����Ϸ��� ����
		cout << "\n�Ϸ�!" << endl;
		system("pause");
	}
	void userNow(const char *id) {
		cout << "���뿩 ��Ȳ" << endl;
		MYSQL * cons = mysql_init(NULL);
		DB d(HOST, cons);
		d.loadmysql(HOST, cons, id, 3);	//�������� 3�� ���뿩��û�Ϸ����� �ݳ��Ϸ����� �׷���  �����Ϸ��� ����
		cout << "\n�Ϸ�!" << endl;
		system("pause");
	}

};





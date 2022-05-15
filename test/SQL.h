#pragma once
#include "/usr/include/mysql/mysql.h"

#define SQL_ADDRESS "localhost"
#define SQL_ID      "root"
#define SQL_PW      "ycj650213"


// ���� ����� SQl�Դϴ�!
MYSQL* SQLConnection;

// SQL���� ;"����"�� �մϴ�! SQL�� �������� "���" ������!
mySQL_RES* SQLResponse;

//�˻��� �ؼ� ����� ���� ���� ���⿡�ٰ� �ӽô�!
MYSQL_ROW resultRow;

//mysql�� ������ �����ϴ� �Լ��� �ʿ��� �ſ���!
int SQLConnect()
{
	// ���� ���� ���� �ؾ��ϴ� ���� mySQL�� �����ϱ� ���� "�ʱ�ȭ"�� �õ��մϴ�!
	if (!(SQLConnection = mysql_init((MYSQL*)NULL)))
	{
		cout << "mysql initiate failed" << endl;
		return -1;
	};

	// �ʱ�ȭ�� �����ϱ� �� ��ġ���ٰ� "���� ����"�� ��Ű�� �̴ϴ�!
	if (!(mysql_real_connect(SQLConnection, SQL_ADDRESS, SQL_ID, SQL_PW, NULL, 3306, NULL, 0)))
	{                     // ��� ������,   �ּ�(�� ��ǻ��), ���̵�, ���,      ,��Ʈ,      , 
		cout << "MYSQL Connection failed" << endl;
		return -1;
	}

	cout << "MYSQL Connection Succeed" << endl;
	return 0;
}
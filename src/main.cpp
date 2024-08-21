#include<iostream>
#include"Book.h"
#include"Student.h"
#include"ManagementBooks.h"
#include"Teacher.h"
#include<fstream>
#include"Administrator.h"
#include"OperationManagement.h"
#include "chrange.h"
using namespace std;
int main()
{
	ManagementBooks manageb;
	User* user = nullptr;
	OperationManagement operation;
	operation.init(manageb);
	
	cout<<"***********************************************************************************"<<endl;
	cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ��ӭ����ͼ��� <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" <<endl;
	cout<<"***********************************************************************************"<<endl;
	cout << "ע����������:" << endl;
	cout<<"1.ѧ����๲�ɽ�������,��ʦ��๲�ɽ�˱���"<<endl;
	cout<<"2.�����һ��Ҫ��ʱ���� 3�β���ʱ���������ͼ��ݺ�������" <<endl;
	cout<<"3.ÿ��ע���˺ź��ʼ������Ϊ100"<<endl; 
	cout<<"4.��ʱ����������+2�����ڻ���������-10�������ֵ���75��������ͼ��ݺ������������ٽ���" <<endl;
	cout<<"************************************************************************************"<<endl;
	
	cout << "������ѡ�����ĵ�¼��ʽ:"<<endl;
	cout<<"a)��ʦ"<<endl;
	cout<<"b)ѧ��"<<endl;
	cout<<"c)����Ա" <<endl;
	cout<<"����ѡ��";
	string msg="������a~c֮�����ĸ���������룺";
	char choice;
	CharRange input('A','C',msg);
	choice=input.getChar();
	switch(choice)
	{
		case 'A':
			user = new Teacher;
			break;
		case 'B':
			user = new Student;
			break;
		case 'C':
			Administrator admin;
			operation.adminLogin(admin);
			admin.showInfo();
			operation.adminOperation(admin, manageb);
			return 0;		
	}

	cout<<"���Ƿ��Ѿ�ע����˺ţ�(y/n):" ;
	char ch;
	cin>>ch;
	if (ch =='Y'||ch=='y')
	{
		operation.login(user,choice);
		user->showInfo();
	}
	else
	{
		cout << "���ڿ��Ը�����ʾ,�����ѧ����ע��һ���˺�!" << endl;
		operation.Register(user,choice);
	}
	operation.userOperation(user, manageb);
	delete user;
	return 0;
}

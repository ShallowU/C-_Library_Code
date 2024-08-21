#include "OperationManagement.h"
#include <stdlib.h>
#include "chrange.h"
#include <fstream>

void OperationManagement::login(User* user,char choice)
{
	ifstream readFile;
	ifstream readFile1;
	if (choice == 'A')
	{
		readFile.open("teacherLogin.txt");//�� 
		readFile1.open("teacher.txt");
	}
	else
	{
		readFile1.open("student.txt");
		readFile.open("studentLogin.txt");
	}
	if (!readFile.is_open())
	{
		cout << "��¼���ݶ�ȡ����" << endl;
	}
	if (!readFile1.is_open())
	{
		cout << "�û����ݶ�ȡ����" << endl;
	}
	cout << "�����������˺ţ�ѧ���ţ�:";
	string account, password;
	cin >> account;
	int flag = 0;
	int temp=0;
	while (!readFile.eof())
	{
		string act;
		readFile >> act;
		if (act == account)//ƥ���˺� 
		{
			flag=1; 
			cout << "����������:";
			cin >> password;
			string pwd;
			readFile >> pwd;
			if (pwd == password)
			{
				cout << "��¼�ɹ�!";
				flag = 1;
				while (!readFile1.eof())
				{
					
					readFile1 >> user;
					if(user->getId() == act)
					{
						cout<<"�����˺��������Ϣ��֤�ɹ���"<<endl;
						temp=1; 
						break;
					}
				}
				if(!temp)
				{
					cout<<"�˻��ͱ�����Ϣ��֤���ɹ������Ժ�ȥ�޸���Ϣ��"<<endl;
				}
				break;
			}
			else
			{
				cout << "������������µ�¼" << endl;
				login(user, choice);
			}
		}

	}
	if (!flag)//�������� 
	{
		cout << "ѧ���Ŵ����������룡����" << endl;
		login(user, choice);
	}
	readFile.close();
	readFile1.close();
}

void OperationManagement::Register(User* user, char choice)//ע��һ���˺� 
{
	ofstream writeFile;
	ofstream writeFile1;
	if (choice == 'A')
	{
		writeFile1.open("teacher.txt", ios::app);
		writeFile.open("teacherLogin.txt",ios::app);
	}
	else
	{
		writeFile1.open("student.txt", ios::app);
		writeFile.open("studentLogin.txt",ios::app);
	}
	string pwd, act;
	cout << "����������ѧ������Ϊע���˺�:";
	cin >> act;
	user->setId(act);
	cout << "����������ע������:";
	cin >> pwd;
	user->setPassword(pwd);
	writeFile << endl << act << " " << pwd;
	cout << "������������Ӧ��Ϣ!" << endl;
	string  name, department, gender;
	cout << "��������:";
	cin >> name;
	user->setName(name);
	cout << "�����Ա�:";
	cin >> gender;
	user->setGender(gender);
	cout << "�����ڵ�Ժϵ:";
	cin >> department;
	user->setDepartment(department);
	writeFile1 <<endl<< act << " " << name << " " << gender << " " << department;//���ﲻ����user,��Ϊ�ڵ�¼ʱ���ã����Ҳ�û�г�ʼ��
	writeFile.close();
	writeFile1.close();
	
	int point=100;
	ofstream filec("creditpoint.txt",ios::app);
	filec<<endl<<act<<" "<<point;
	filec.close();
	
	cout << "ע��ɹ����Ͻ���¼����ͼ��ܰ�!" << endl;
	login(user, choice);
}

void OperationManagement::userOperation(User* user, ManagementBooks mb)
{
	while (1)
	{
		OperationManagement action;
		cout<<"**************************************************************************************"<<endl;
		cout<<"**********************�����ߡ��������ʾ��ɸ��������*******************************"<<endl;
		cout<<"\n\ta)���н���" ;
		cout<<"\n\tb)�鿴���˵�ǰ�������" ;
		cout<<"\n\tc)���л���";
		cout<<"\n\td)��ѯ�鼮";
		cout<<"\n\te)�޸ĸ�����Ϣ" ;
		cout<<"\n\tf)�����ܻ�ӭͼ���"; 
		cout<<"\n\tg)�鿴������������";
		cout<<"\n\th)�˳�����"<<endl;;
		
		string msg="������a~h֮�����ĸ���������룺";
		char choice;
		CharRange input('A','H',msg);
		cout<<"���������ѡ��" ;
		choice=input.getChar();
		switch(choice)
		{
			case 'A':
				cout << "��ǰͼ���������£�" << endl;
				mb.showCurrentAllBook();
				cout << "�Ƿ�������Ҫ���ĵ�ͼ��(y/n)��";
				char s;
				cin >> s;
				if (s == 'y'||s=='Y')
				{
					user->borrowBookFromLibrary(mb);
				}
				break;
			case 'B':
				mb.checkBorrowedBook(user->getId());
				break;
			case 'C':
				user->returnBook(mb);
				break;
			case 'D':
				mb.findBook();
				break;
			case 'E':
				user->modifyinfo();
				break;
			case 'F':
				mb.popularbook();
				break;
			case 'G' :
				user->checkcredit();
				break;
			case 'H':
				cout<<"��ӭ�´ι��ٱ�ͼ��ݣ�" <<endl;
				exit(0);
		}
	}
}

void OperationManagement::adminLogin(Administrator& admin)
{
	ifstream readFile("adminLogin.txt");
	ifstream readFile1("admin.txt");
	cout << "���������Ĺ���:" ;
	string account, password;
	cin >> account;
	int flag = 0;
	int temp=0;
	while (!readFile.eof())
	{
		string act;
		readFile >> act;
		if (act == account)
		{
			flag=1;
			cout << "����������:";
			cin >> password;
			string pwd;
			readFile >> pwd;
			if (pwd == password)
			{
				cout << "��¼�ɹ�,��ӭ��!" << endl;
				flag = 1;

				while (!readFile1.eof())
				{
					readFile1 >> admin;
					if(admin.getId() == act)
					{
						cout<<"�����˻��ͱ�����Ϣ��֤�ɹ�!"<<endl;
						temp=1;
						break;
					}
				}
				if(!temp)
				{
					cout<<"�˻��ͱ�����Ϣ��֤���ɹ������Ժ�ȥ�޸���Ϣ��"<<endl;
				}
				break;
			}
			else
			{
				cout << "������������µ�¼" << endl;
				adminLogin(admin);
			}
		}

	}
	if (!flag)//�˴��������� 
	{
		cout << "ѧ���Ŵ�����������" << endl;
		adminLogin(admin);
	}
	readFile.close();
	readFile1.close();

}

void OperationManagement::init(ManagementBooks& mb)
{
	mb.initBooks();//��ʼ�������鼮��Ϣ����m_books 
	mb.initOutBook();//����Ϣ����m_outBookMap 
}

void OperationManagement::adminOperation(Administrator admin, ManagementBooks mb)
{
	while (1)
	{
		OperationManagement action;
		cout<<"***************************************************************************************"<<endl;
		cout<<"**********************������Ա���������ʾ��ɸ��������*******************************"<<endl;
		cout<<"\n\ta)�������" ;
		cout<<"\n\tb)�鿴��ǰ�������" ;
		cout<<"\n\tc)�鿴��������ϸ��Ϣ";
		cout<<"\n\td)�鿴��ǰ����ͼ����Ϣ���" ;
		cout<<"\n\te)�����鼮"; 
		cout<<"\n\tf)ɾ���鼮";
		cout<<"\n\tg)�޸�ͼ����Ϣ";
		cout<<"\n\th)�鿴����ͼ����ܻ�ӭͼ��";
		cout<<"\n\ti)�鿴ͼ��ݽ��������";
		cout<<"\n\tj)���ͼ���ͼ��";
		cout<<"\n\tk)�˳�����"<<endl;;
		
	    string msg="������a~j֮�����ĸ���������룺";
		char choice;
		CharRange input('A','K',msg);
		cout<<"����ѡ��" ;
		choice=input.getChar();
		string id;
		switch(choice)
		{
			case 'A':
				admin.addBook(mb);
				break;
			case 'B':
				mb.checekOutBook();
				break;
			case 'C':
				cout << "��������Ҫ�鿴�����˵�ѧ����:" ;
				cin >> id;
				mb.viewBorrowerDetails(id);
				break;
			case 'D':
				mb.showAllBooksInfo();
				break;
			case 'E':
				mb.findBook();
				break;
			case 'F':
				admin.deleteBook(mb);
				mb.clearallbook();
				action.init(mb);
				break;
			case 'G':
				admin.modifyBook(mb);
				mb.clearallbook();
				action.init(mb);
				break;
			case 'H':
				mb.popularbook();
				break;
			case 'I' :
				admin.checkblacklist();
				break;
			case 'J':
				mb.clearallbook();
				mb.outclear() ;
				cout<<"ͼ�������ϣ�"<<endl ;
			case 'K':
				cout<<"��ӭ����Ա�´ι��٣�"<<endl; 
				exit(0);
				break;
			
		}
	}
}



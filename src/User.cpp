#include "User.h"
#include "Student.h"
#include "Teacher.h"
#include<iostream>
#include<fstream>
#include"ManagementBooks.h"
using namespace std;

User::User()
{
	
}

void User::setId(string id)
{
    m_id = id;
}

void User::setName(string name)
{
    m_name = name;
}

void User::setGender(string gender)
{
    m_gender = gender;
}

void User::setDepartment(string department)
{
    m_department = department;
}

void User::setPassword(string pas)
{
	password=pas;
}

User::~User()
{
}

void User::returnBook(ManagementBooks& mb)
{
    int all = mb.checkBorrowedBook(m_id);
    if (all == 0)
    {
        cout << "����δ����,����黹" << endl;
    }
    else
    {
        cout << "��������Ҫ�黹������:" ;
        string bookName;
        cin >> bookName;
        if (mb.checkTrueBorrow(m_id, bookName))//����Ƿ�����Ȿ�� 
        {
        	if(isdue())
        	{
	            mb.Return(m_id, bookName);
	            cout << "�ڹ涨���޻���ɹ�ѽ!������+2��" << endl;
	            ifstream file("creditpoint.txt");
	            string account[60];
	            int point[60];
	            int i=0,j=0;
	            while(!file.eof())
	            {
	            	file>>account[i]>>point[i];
	            	i++;
				}
				file.close();
				for(j=0;j<i;j++)
				{
					if(account[j]==m_id)
					{
						point[j]=point[j]+2;
						break;
					}
				}
				ofstream file1("creditpoint.txt");
				for(j=0;j<i;j++)
				{
					file1<<endl<<account[j]<<" "<<point[j];
				}
				file1.close();
        	}
        	else
        	{
        		cout<<"����ٵ���δ������ǰ��ɻ���,������-10������"<<endl;
        		mb.Return(m_id, bookName);
        		cout << "���λ���ɹ����´����ڹ涨ʱ�仹�飡" << endl;
        		ifstream file("creditpoint.txt");
	            string account[60];
	            int point[60];
	            int i=0,j=0;
	            while(!file.eof())
	            {
	            	file>>account[i]>>point[i];
	            	i++;
				}
				file.close();
				for(j=0;j<i;j++)
				{
					if(account[j]==m_id)
					{
						point[j]=point[j]-10;
						break;
					}
				}
				ofstream file1("creditpoint.txt");
				for(j=0;j<i;j++)
				{
					file1<<endl<<account[j]<<" "<<point[j];
				}
				file1.close();
			}
        }
        else
        {
            cout << "����δ���Ĵ���" << endl;
        }
    }
}
bool User::isdue()
{
	
	ifstream readFile("borrowedtimeStu.txt");
	ifstream readFile1("borrowedtimeTea.txt");
	string name;
	string strtimeToReturn;
	char ch;
	cout<<"���ٴ�ȷ��������ʦ��t)����ѧ����s��t/s:";
	cin>>ch;
	if(ch=='S'||ch=='s')
	{
		while(!readFile.eof())
		{
			readFile>>name;
			if(name==m_id)
			{
				readFile>>strtimeToReturn;
				break;
			}
		}
	}
	else
	{
		while(!readFile1.eof())
		{
			readFile1>>name;
			if(name==m_id)
			{
				readFile1>>strtimeToReturn;
				break;
			}
		}
	}
	time_t now = time(NULL);
	tm *local_time = localtime(&now);
	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_time);
	readFile.close();
	readFile1.close();
	return buffer<strtimeToReturn;
}
void User::modifyinfo()
{
	ifstream file;
	ofstream filew;
	string oldid;
	string space;
	User *p[50];
	int i=0;
	int flag=0;
	char ch;
	cout<<"����������ʦ����ѧ����t/s����";
	cin>>ch;
	cout<<"��������Ŀǰ��ѧ���ţ�" ;
	cin>>oldid;
	if(ch=='S'||ch=='s')
	{
		file.open("student.txt");
		cout<<"�򿪳ɹ���"<<endl; 
		for(int m=0;m<50;m++)
		{
			p[m]=new Student;
		}
	}
	else
	{
		 file.open("teacher.txt");
		for(int m=0;m<50;m++)
		{
			p[m]=new Teacher;
		}
	}
	if(file.fail())
		cout<<"�޸���Ϣʱ��ȡ���ݴ��ļ�ʧ��"<<endl;
	while(!file.eof())
	{
		file>>p[i];
		if(p[i]->getId() == oldid)
			flag=i;
		i++;
	}
	file.close();
	cout<<"���������ԭ����Ϣ��"<<endl;
	p[flag]->showInfo();
	string newid,newname,newgender,newdepartment;
	int t=0;
	cout<<"��ѡ����Ҫ�޸ĵ���Ϣ��"<<endl;
	cout<<"1.ѧ����"<<endl;
	cout<<"2.����"<<endl;
	cout<<"3.�Ա�"<<endl;
	cout<<"4.ѧԺ" <<endl;
	cout<<"5.����" <<endl;
	cout<<"����ѡ��";
	cin>>t;
	if(t==1)
	{
		cout<<"�µ�ѧ��Ϊ��";
		cin>>newid;
		p[flag]->setId(newid);
	}
	else if(t==2)
	{
		cout<<"�µ�����Ϊ��";
		cin>>newname;
		p[flag]->setName(newname);
	}
	else if(t==3)
	{
		cout<<"�µ��Ա�";
		cin>>newgender;
		p[flag]->setGender(newgender);
	}
	else if(t==4)
	{
		cout<<"�µ�ѧԺ�����ţ���";
		cin>>newdepartment;
		p[flag]->setDepartment(newdepartment);
	}
	else
	{
		
	}
	file.close();
	if(ch=='S'||ch=='s')
	{
		 filew.open("student.txt");
	}
	else
	{
		 filew.open("teacher.txt");
	}
	if(filew.fail())
		cout<<"�޸���Ϣʱд���ݴ��ļ�ʧ��"<<endl;
	for(int j=0;j<i;j++)
	{
		filew<<p[j];
	}
	filew.close();
	if(t==5)
	{
		ifstream filea;
		ofstream fileb;
		string oldaccount,newkey;
		string account[50];
		string key[50];
		int n=0,k=0;
		char ch1;
		if(ch=='S'||ch=='s')
		{
			filea.open("studentLogin.txt");
		}
		else
		{
			filea.open("teacherLogin.txt");
		}
		cout<<"���������ѧ���ţ�";
		cin>>oldaccount;
		while(!filea.eof())
		{
			filea>>account[n]>>key[n];
			if(account[n]==oldaccount)
			{
				k=n;
			}
			n++;
		}
		filea.close();
		cout<<"���ԭ����Ϊ��"<<key[k]<<endl;
		cout<<"ȷ���Ƿ��޸ģ�y/n����";
		cin>>ch1;
		if(ch1=='y'||ch1=='Y')
		{
			cout<<"����������Ϊ��";
			cin>>newkey;
			key[k]=newkey;
		}
		else
			cout<<"�õ����ǲ��޸������أ�"<<endl;
		if(ch=='S'||ch=='s')
		{
			fileb.open("studentLogin.txt");
		}
		else
		{
			fileb.open("teacherLogin.txt");
		}
		for(int a=0;a<n;a++)
		{
			fileb<<endl<<account[a]<<" "<<key[a];
		}
		fileb.close();
	}
	cout<<"�޸���Ϣ��ϣ�"<<endl; 
	
}
void User::checkcredit()
{
    ifstream file("creditpoint.txt");
	string account[60];
    int point[60];
	int i=0,j=0;
	int flag=0;
	while(!file.eof())
	{
	    file>>account[i]>>point[i];
	    i++;
	}
	file.close();
	for(j=0;j<i;j++)
	{
		if(account[j]==m_id)
		{
			flag=j;
			break;
		}
	}
	cout<<"��ǰ���������Ϊ��"<<point[flag]<<"��"<<endl;
}

string User::getId()
{
    return m_id;
}

string User::getName()
{
    return m_name;
}

string User::getGender()
{
    return m_gender;
}


string User::getDepartment()
{
    return m_department;
}

string User::getPassword()
{
	return password;
}
string User::get_borrowTime()
{
	string time=asctime(&borrowTime);
	return time;
}

string User::get_returnTime()
{
	string time=asctime(&returnTime);
	return time;
}
tm* User::get_returnTime_tm()
{
	return &returnTime; 
}
std::ostream& operator<<(std::ostream& os, const User* user)//����<<���û���Ϣ��ʽ��д���ļ� 
{
    os<< endl << user->m_id << " " << user->m_name << " " << user->m_gender << " " << user->m_department;
    return os;
}

std::istream& operator>>(std::istream& is, User* user)//����>>���û���Ϣ������ 
{

   is >> user->m_id >> user->m_name >> user->m_gender >> user->m_department;
   return is;
}



#include "Student.h"
#include<fstream>
#include <ctime>
using  namespace std;

Student::Student()
{
    m_class="��Ϣ��ȫ";
}

void Student::showInfo()
{
    cout << "����:" << m_name << " " << "ѧ��:" << m_id << " " << "�Ա�:" << m_gender << " " << "Ժϵ:" << m_department << " "<<"�༶:"<<m_class<<endl;
}

void Student::borrowBookFromLibrary(ManagementBooks& mb)
{
    int all = mb.checkBorrowedBook(m_id);
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
    if (all < 6&&point[flag]>=75)
    {
        string name;
        cout << "��������Ҫ�������:" ;
        cin >> name;
        if (mb.borrow(name))
        {
        	time_t timenow;
        	time(&timenow);
        	tm *p=localtime(&timenow);
        	borrowTime=*p;
        	returnTime=*p;
        	returnTime.tm_mon++;
        	if(returnTime.tm_mon==12)
        	{
        		returnTime.tm_mon=0;
        		returnTime.tm_year++;
			}
			cout<<"���Ľ���ʱ��Ϊ��" <<get_borrowTime();//�˴�����������
			cout<<"���Ļ���ʱ��Ϊ��" << get_returnTime();
			char buffer[20];
 			strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S",&returnTime ); 
 			
			ofstream file("borrowedtimeStu.txt", ios::app);
            ofstream writeFile("borrowedBook.txt", ios::app);//��׷�ӷ�ʽ  
            
            ifstream filepopular("popularbook.txt");
            string popularbook[50];
            int a[50];
            int i=0,flag=0;
            while(!filepopular.eof())
            {
            	filepopular>>popularbook[i]>>a[i];
            	i++;
			}
			for(int j=0;j<i;j++)
			{
				if(name==popularbook[j])
				{
					a[j]++;
					flag=1;
					break;
				}
			}
			filepopular.close();
			ofstream filepopular1;
			if(flag)
			{
				filepopular1.open("popularbook.txt",ios::out);
				for(int k=0;k<i;k++)
				{
					filepopular1<<endl<<popularbook[k]<<" "<<a[k];
				}
			}
			else
			{
				filepopular1.open("popularbook.txt",ios::app);
				popularbook[i]=name;
				a[i]=1;
				
				filepopular1<<endl<<popularbook[i]<<" "<<a[i];
			}
			filepopular1.close();
            mb.setMapValue(m_id, name);//�������˺��鼮����ϵһ�� 
            writeFile << endl << m_id << " " << name;//�½�������Ϣд�� borrowedBook.txt
            file<<endl<<m_id<<" "<<buffer;
            file.close();
            writeFile.close();
        }
    }
    else
    {
        cout << "��Ŀǰ���ܽ��飬�������Ѿ����������ɽ��������������ֵ���75��" << endl;
    }
    
}

void Student::setClass(string Class)
{
    m_class = Class;
}

string Student::getClass()
{
    return m_class;
}



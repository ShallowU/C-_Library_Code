#include "Teacher.h"
#include<fstream>

Teacher::Teacher()
{
    m_name = "������";
}

void Teacher::borrowBookFromLibrary(ManagementBooks& mb)
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
        if (all < 8&&point[flag]>=75)
        {
            string name;
            cout << "��������Ҫ�������:";
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
				cout<<"����ʱ��Ϊ��" <<get_borrowTime();//�˴�����������
				cout<<"����ʱ��Ϊ��" << get_returnTime();
				char buffer[20];
 				strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S",&returnTime );
 				
                ofstream writeFile("borrowedBook.txt", ios::app);
                ofstream file("borrowedtimeTea.txt", ios::app);
                
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
					ofstream filepopular2("popularbook.txt",ios::app);
				if(flag)
				{
					filepopular1.open("popularbook.txt");
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
					for(int k=0;k<i+1;k++)
					{
						filepopular1<<endl<<popularbook[k]<<" "<<a[k];
					}
				}
				filepopular1.close();
                mb.setMapValue(m_id, name);
                writeFile << endl << m_id << " " << name;
                file<<endl<<m_id<<" "<<buffer;
            	file.close();
                writeFile.close();
            }
        }
        else
        {
            cout << "���Ѿ����������ɽ���������������С��75��" << endl;
        }
}
void Teacher::showInfo()
{
    cout << "����:" << m_name<<" " << "����:" << m_id<<" " << "�Ա�:" << m_gender<<" " << "Ժϵ:" << m_department << endl;
}



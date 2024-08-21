#include "ManagementBooks.h"
#include <string>
using namespace std;

void ManagementBooks::showCurrentAllBook()	//�鿴�鼮��ʣ���� 
{
	for (int i = 0; i < m_allBookNum; i++)
	{
		cout << "����:" << m_books[i].getName() <<" " << "ʣ������" << m_books[i].getNum() << endl;
	}
}

ManagementBooks::ManagementBooks()
{
	m_allBookNum = 0;	//��ʼΪ0 
}

void ManagementBooks::addBook(Book book)
{
	int flag = 0;//���ڱ��ͼ����Ƿ��д��� 
	for (int i = 0; i < m_allBookNum; i++)
	{
		if (m_books[i].getName() == book.getName())//Ϊ���� 
		{
			flag = 1;
			m_books[i].setNum(m_books[i].getNum() + book.getNum());
			ofstream writeFile("library.txt", ios::out);//���ļ������޸���� 
			for (int i = 0; i < m_allBookNum; i++)
			{
				writeFile << m_books[i];//�Ѿ�������<< 
			}
			writeFile.close();
			break;
		}
	}
	if (!flag)//Ϊ���� 
	{
		ofstream writeFile("library.txt", ios::app);
		m_books.push_back(book);//�鼮��push_back�¼�һ�� 
		m_allBookNum++;
		writeFile << book;//�Ѿ�����<< 
		writeFile.close();
	}
}
bool ManagementBooks::modifyBook(Book book,string oldname)
{
	int flag=0;
	for (int i = 0; i < m_allBookNum; i++)
	{
		if (m_books[i].getName() == oldname)//Ϊ���� 
		{
			m_books[i]=book;
			flag=1;
			break;
		}
	}
	ofstream writeFile("library.txt", ios::out);//���ļ������޸���� 
	for (int i = 0; i < m_allBookNum; i++)
	{
		writeFile << m_books[i];//�Ѿ�������<< 
	}
	writeFile.close();
	if(flag)
		return true;
	else 
		return false;
}
bool ManagementBooks::deleteBook(string bookname)
{
	int temp=0;
	int flag=0;
	for (int i = 0; i < m_allBookNum; i++)
	{
		if (m_books[i].getName() == bookname)//Ϊ���� 
		{
			temp=i;
			flag=1;
			break;
		}
	}
	ofstream writeFile("library.txt");//���ļ������޸����
	for (int i = 0; i < m_allBookNum; i++)
	{
		if(i==temp)
			continue;
		writeFile << m_books[i];//�Ѿ�������<<
	}
	writeFile.close();
	if(flag)
		return true;
	else
		return false;
}
void ManagementBooks::findBook()
{
	string bookname;
	int flag=0;
	cout<<"��������鼮����";
	cin>>bookname; 
	for (int i = 0; i < m_allBookNum; i++)
	{
		if (m_books[i].getName() == bookname)
		{
			cout<<"�����Ѿ���ѯ��������Ϊ�����Ϣ��"<<endl; 
			m_books[i].showInfo();
			flag=1;
			break;
		}	
	}
	if(!flag)
	{
		cout<<"��Ǹ ͼ���û�д��������Ϣ��"<<endl;
	}	
}

int ManagementBooks::getAllBookNum()
{
	return m_allBookNum;
}

void ManagementBooks::showAllBooksInfo()
{
	for (int i = 0; i < m_allBookNum; i++)
	{
		m_books[i].showInfo();//չʾ�鼮������Ϣ 
	}
}

bool ManagementBooks::borrow(string name)
{

	for (int i =0; i <m_allBookNum; i++)
	{
		if (m_books[i].getName() == name)
		{
			if (m_books[i].getNum() >= 1)
			{
				m_books[i].setNum(m_books[i].getNum() - 1);
				cout << "      ����ɹ�ѽ��" << endl;
				ofstream writeFile("library.txt");//�����޸�ͼ��� 
				for (int i = 0; i < m_allBookNum; i++)
				{
					writeFile << m_books[i];
				}
				writeFile.close();
				return true;//����ɹ� 
			}
			else
			{
				cout << "������������" << endl;
				return false;
			}
		}

	}
	cout << "�ܱ�Ǹ�����޴���" << endl;
	return false;
}

void ManagementBooks::Return(string id,string bookName)
{
	Book book;
	book.setName(bookName);
	addBook(book);
	ofstream writeFile("borrowedBook.txt",ios::out);
	for (auto iter =m_outBookMap.begin(); iter != m_outBookMap.end(); ++iter)//����auto������������ѭ�� m_outBookMap
	{
		if (iter->first == id && iter->second == bookName)//��Ϣ�ȶԾ����� 
		{
			m_outBookMap.erase(iter);
			break;
		}
	}
	for (auto map : m_outBookMap)//ֱ�ӱ��������޸Ľ�������Ϣ���ļ� 
	{
		writeFile << endl << map.first << " " << map.second;
	}
	writeFile.close();
}

void ManagementBooks::initOutBook()//�������˵������� m_outBookMap��ϵ 
{
	ifstream readFile("borrowedBook.txt");
	if (!readFile.is_open())
	{
		cout << "�鿴ȫ�����������ݶ�ȡ����" << endl;
	}
	else
	{
		while (!readFile.eof())
		{
			string studentId, bookName;
			readFile >> studentId >> bookName;
			m_outBookMap.insert(pair<string, string>(studentId, bookName));//�������˺ͽ�������ϵһ����ڲ��� 
		}
	}
	readFile.close();

}

void ManagementBooks::checekOutBook()//�鿴��������������˼���Ӧ���鼮���� 
{
	for (auto map : m_outBookMap)	//for(auto map: m_outBookMap)
	{
		cout << "������ѧ����:" << map.first<<" " << "��������:" << map.second << endl;
	}
}

void ManagementBooks::initBooks()
{
	ifstream readFile;
	readFile.open("library.txt");
	if (!readFile.is_open())
	{
		cout << "ͼ�����ݶ�ȡ����" << endl;
		readFile.close();
		return ;
	}
	m_allBookNum=0;
	while (!readFile.eof())
	{
		
		Book book;
		readFile >> book;//�Ѿ�����<< 
		m_allBookNum++;
		m_books.push_back(book);//����m-books�� 
	}
	readFile.close();
}
void ManagementBooks::clearallbook()
{
	m_books.clear();
}
void ManagementBooks::outclear()
{
	ofstream writeFile("library.txt");
	writeFile<<" ";
	writeFile.close();
}
int ManagementBooks::checkBorrowedBook(string userId)//չʾ���˽��ȫ���鼮 ,��Ҫ�����鼮һ�����ٱ� 
{
	
	int flag = 0;
	for (auto map : m_outBookMap)
	{
		if (userId == map.first)
		{
			if (!flag)
			{
				cout << "���Ѿ����ȫ��ͼ�����£�" << endl;
				flag++;
			}
			else
			{
				flag++;
			}
			cout << map.second << " ";
		}
	}
	if (!flag)
	{
		cout << "       ����Ŀǰû�н��� ��        " << endl;
	}
	cout << "����ǰһ�����飺" << flag << "   ��";
	cout << endl;
	return flag;
}

void ManagementBooks::popularbook()
{
	ifstream filepopular("popularbook.txt");
    string popularbook[50];
    int a[50];
    int i=0,j=0,flag1=0;
    int flag2=0,flag3=0;
    while(!filepopular.eof())
    {
		filepopular>>popularbook[i]>>a[i];
  		i++;
	}
	filepopular.close();
	int maxfirst=a[0];
	int maxsecond=a[0];
	int maxthird=a[0];
	for(j=0;j<i;j++)
	{
		if(a[j]>maxfirst)
		{
			maxfirst=a[j];
			flag1=j;
		}
	}
	for(j=0;j<i;j++)
	{
		if(j==flag1)
			continue;
		if(a[j]>maxsecond)
		{
			maxsecond=a[j];
			flag2=j;
		}
	}
	for(j=0;j<i;j++)
	{
		if(j==flag1||j==flag2)
			continue;
		if(a[j]>maxthird)
		{
			maxthird=a[j];
			flag3=j;
		}
	}
	cout<<"ͼ��ǰ��popular���а����£�"<<endl;
	cout<<"top1:"<<popularbook[flag1]<<endl;
	cout<<"top2:"<<popularbook[flag2]<<endl;
	cout<<"top3:"<<popularbook[flag3]<<endl;
}

void ManagementBooks::viewBorrowerDetails(string id)//�鿴�����˾������Ϣ 
{
	ifstream readFile("teacher.txt");
	ifstream readFile1("student.txt");
	int flag = 0;//�����ж�ʱѧ��������ʦ 
	if (!readFile1.is_open()|| readFile.fail()) 
	{
		cout << "�û����ݶ�ȡ����" << endl;
	}
	while (!readFile1.eof())
	{
		string act1, name, department, gender;
		readFile1 >> act1 >> name >> gender >> department;
		if (id == act1)
		{
			cout<<"�û����:"<<"ѧ��"<<" " << "�û�����:" << name << " " << "�û��Ա�:" << gender << " " << "�û����ڲ���:" << department << endl;
			flag = 1;
		}
	
	}
	if (!flag)
	{
		while (!readFile.eof())
		{
			string act1, name, department, gender;
			readFile >> act1 >> name >> gender >> department;
			if (id == act1)
			{
				flag = 1;
				cout << "�û����:"<<"��ʦ"<<" " << "�û�����:" << name << " " << "�û��Ա�:" << gender << " " << "�û����ڲ���:" << department << endl;
			}

		}
	}
	if (!flag)
	{
		cout << "�޴��û���" << endl;
	}
	readFile.close();
	readFile1.close();
}

bool ManagementBooks::checkTrueBorrow(string id, string bookName)//�鿴ĳ���Ƿ����ĳ�� 
{
	
	for (auto map : m_outBookMap)//���������� 
	{
		if (map.first == id && map.second == bookName)
		{
			return true;
		}
	}
	return false;
}

void ManagementBooks::setMapValue(string userId,string bookName)//�����µ�һ�������˼������鼮 
{
	m_outBookMap.insert(pair<string, string>(userId, bookName));
}



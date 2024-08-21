#include "Administrator.h"
void Administrator::addBook(ManagementBooks& mb)
{
	Book book;
	cout << "��ǰͼ����������:" << endl;
	mb.showAllBooksInfo();
	cout << "��������Ҫ���ӵ�ͼ����Ϣ!" << endl;
	string name, author;
	string press;
	int pages;
	double price;
	int num;
	cout << "���������ӵ�ͼ��������" ;
	cin >> name;
	cout << "���������ӵ�ͼ������ߣ�";
	cin >> author;
	cout << "���������ӵ�ͼ��۸�" ;
	cin >> price;
	cout << "���������ӵ�ͼ��ĳ����磺";
	cin >> press;
	cout << "����������ͼ�����ҳ����";
	cin >> pages;
	cout << "���������ӵ�ͼ��ı�����" ;
	cin >> num;
	book.setName(name);
	book.setAuthor(author);
	book.setPressInfo(press);
	book.setPage(pages);
	book.setNum(num);
	book.setPrice(price);
	mb.addBook(book);
	cout << "����ͼ��ɹ�!" << endl;
}
void Administrator::modifyBook(ManagementBooks& mb)
{
	Book book;
	mb.findBook();
	cout<<"�����������µ�ͼ����Ϣ��"<<endl;
	string name, author;
	string press;
	int pages;
	double price;
	int num;
	cout << "�������µĵ�ͼ��������" ;
	cin >> name;
	cout << "�������µĵ�ͼ������ߣ�";
	cin >> author;
	cout << "�������µĵ�ͼ��۸�" ;
	cin >> price;
	cout << "�������µĵ�ͼ��ĳ����磺";
	cin >> press;
	cout << "�������µ�ͼ�����ҳ����";
	cin >> pages;
	cout << "�������µĵ�ͼ��ı�����" ;
	cin >> num;
	book.setName(name);
	book.setAuthor(author);
	book.setPressInfo(press);
	book.setPage(pages);
	book.setNum(num);
	book.setPrice(price);
	string oldname;
	cout<<"���ٴ�����ԭͼ������ȷ����";
	cin>>oldname;
	if(mb.modifyBook(book,oldname))
		cout<<"�޸�ͼ����Ϣ�ɹ���"<<endl;
	else
		cout<<"�޸�ͼ����Ϣʧ�ܣ�"<<endl;
}
void Administrator::deleteBook(ManagementBooks& mb)
{
	string bookname;
	mb.findBook();
	char ch;
	cout<<"�Ƿ�ȷ��ɾ�����飿��y/n):";
	cin>>ch;
	if(ch=='y'||ch=='Y') 
	{
		cout<<"���ٴ�������Ҫɾ����������";
		cin>>bookname;
		if(mb.deleteBook(bookname))
			cout<<"ɾ���鼮��"<<bookname<<"�ɹ���"<<endl;
		else
			cout<<"ɾ��ʧ�ܣ�δ�ҵ����飡"<<endl;
	}
	else
		cout<<"�õģ�ɾ��ȡ��"<<endl;
}
void Administrator::checkblacklist()
{
	ifstream file("creditpoint.txt");
	string account[60];
    int point[60];
	int i=0,j=0,k=0;
	string badaccount[30];
	int badpoint[30];
	while(!file.eof())
	{
	    file>>account[i]>>point[i];
	    i++;
	}
	file.close();
	for(j=0;j<i;j++)
	{
		if(point[j]<75)
		{
			badaccount[k]=account[j];
			badpoint[k]=point[j];
			k++;
		}
	}
	cout<<"ͼ��ݺ��������£�"<<endl;
	for(j=0;j<k;j++)
	{
		cout<<"ѧ���ţ�"<<badaccount[j]<<"  "<<"�����֣�"<<badpoint[j]<<endl;
	} 
}
void  Administrator::setId(string id)
{
	m_id = id;
}

void Administrator::setName(string name)
{
	m_name = name;
}

void Administrator::setGender(string gender)
{
	m_gender = gender;
}
void Administrator::setDepartment(string department)
{
	m_department = department;
}
void Administrator::showInfo()
{
	cout << "����:" << m_name << " " << "����:" << m_id << " " << "�Ա�:" << m_gender << " " << "����:" << m_department <<endl;
}

std::istream& operator>>(std::istream& is, Administrator& admin)//����>>���ڶ��ļ� 
{
	is >> admin.m_id >> admin.m_name >> admin.m_gender >> admin.m_department;
	return is;
}
string Administrator::getId()
{
	return m_id;
}

string Administrator::getName()
{
	return m_name;
}

string Administrator::getGender()
{
	return m_gender;
}

string Administrator::getDepartment()
{
	return m_department;
}

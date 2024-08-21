#ifndef MANAGEMENTBOOKS_H
#define MANAGEMENTBOOKS_H
#include<iostream>
#include"Book.h"
#include<vector>		//ʹ��vector�����Ķ�̬�����������鼮��Ϣ 
#include<unordered_map>	//��������������Լ����������Ϣ 
#include<fstream>
#include<string>
using namespace std;
class ManagementBooks
{
private:
	vector<Book> m_books;//����Ϊ����Book������ݶ�̬���� 
	int m_allBookNum;  	 //�鼮���� 
	unordered_multimap<string, string>m_outBookMap;//���ù�ϣ���ڲ��ҽ�����������鼮����ϵ 

public:
	void showCurrentAllBook();
	ManagementBooks();
	void addBook(Book book);
	void findBook();
	bool deleteBook(string bookname) ;
	bool modifyBook(Book book,string oldname) ;
	void clearallbook();
	void outclear();
	int getAllBookNum();
	void showAllBooksInfo();
	bool borrow(string name);
	void Return(string id,string bookName);
	void initOutBook();
	void checekOutBook();
	void popularbook();
	void initBooks();
	int checkBorrowedBook(string userId);
	void viewBorrowerDetails(string id);
	bool checkTrueBorrow(string id,string bookName);
	void setMapValue(string userId, string bookName);
};
#endif

#ifndef CHARRANGE_H //各种改动尝试呢
#define CHARRANGE_H
#include <string>
class CharRange //进行字符有效性检验的类 
{
	private:
		string errMsg;
		char input;
		char lower;
		char upper;
	public:
		CharRange(char,char,string);
		char getChar();
};
#endif 

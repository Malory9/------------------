#include<iostream>
using namespace std;

//�������ʽΪ factor = (expr)  | digit
//						term = term * factor| term / factor | factor
//						expr = expr + term |expr - term | term
//�������ϲ���ʽΪ��ݹ�Ĺ�ϵ�����������ѭ��������ʽ�� A->A�� | ��;
//																						   	   A->��R;
//																							   R->��R | ��;
//��֮ת��Ϊ��Ӧ���ҵݹ�ķֽ�
//term->factor restTerm;
//restTerm -> *factor restTerm
//restTerm-> \factor restTerm
//restTerm->��
//����һ��ʽ�ӷֽ�ͬ��
																							
class Parser
{
private:
	char* stmt;
	void factor()
	{
		if (*stmt == '(')
		{
			match('(');
			cout << "(";
			expr();
			match(')');
			cout << ")";
		}
		else if (isdigit(*stmt))
		{
			char ch = *stmt;
			while (isdigit(ch)) {
				match(ch);
				cout << ch;
				ch = *stmt;
			}
		
		}
		else
			throw exception("match factor error");
	}
	void restTerm()
	{
		while(true){
		if (*stmt == '*')
		{
			match('*');
		
			factor();
			cout << "*";
			restTerm();
		}
		else if (*stmt == '/')
		{
			match('/');
			
			factor();
			cout << "/";
			restTerm();
		}
		else
			break;
		
	}
	}

	void term()
	{
		factor();
		restTerm();
	}
	void restExpr()
	{
		while (true) {
			if (*stmt == '+')
			{
				match('+');				
				term();
				cout << "+";
				restExpr();
			}
			else if (*stmt == '-')
			{
				match('-');
				
				term();
				cout << "-";
				restExpr();
			}
			else			
				break;
			
		}
	}
	void expr()
	{
		term();
		restExpr();
	}
	void match(char t)
	{
		if (*stmt == t) {
			
			++stmt;
		}
		else
			throw exception("not match");
	}
public:
	Parser():stmt(nullptr){}
	Parser(char* newExpr):stmt(newExpr){}

	 void parse(char * toParse)
	{
		 this->stmt = toParse;
		 expr();
		 if (*stmt != '\0')
			 throw exception("not at the end");
	}
};

int main()
{
	char* des = "4*5+3*(4+2)";
	Parser parser;
	try {
		parser.parse(des);
	}
	
	catch(exception e)
	{
		cout << e.what() << endl;
	}
	
}
#include<iostream>
using namespace std;

//具体产生式为                                   factor = (expr)  | digit
//						term = term * factor| term / factor | factor
//						expr = expr + term |expr - term | term
//由于以上产生式为左递归的关系，会产生无限循环，根据式子 A->Aα | β;
//					            A->βR;
//						    R->αR | ε;																							   R->αR | ε;
//将之转换为相应的右递归的分解
//term->factor restTerm;
//restTerm -> *factor restTerm
//restTerm-> \factor restTerm
//restTerm->ε
//另外一个式子分解同理
																							
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

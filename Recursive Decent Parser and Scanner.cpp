#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

 int Token_number=1;
 int LexicalErrorNumber=1;
 int SyntaxErrorNumber=1;

enum Token {
	program_sy,
	openCurlyBracket_sy,
	closeCurlyBracket_sy,
	semiColom_sy,
	read_sy,
	write_sy,
	if_sy,
	openParnthese_sy,
	closeParnthese_sy,
	equal_sy,
	quationMark_sy,
	colom_sy,
	openSquareBracket_sy,
	closeSquareBracket_sy,
	dot_sy,
	length_sy,
	new_sy,
	not_sy,
	plusEqual_sy,
	multEqual_sy,
	andEqual_sy,
	identifier_sy,
	integer_sy,
	error_sy,
	end_source_sy
};

class Compiler {
public:
	std::ifstream f;
	std::string S;
	Token current_token;
	
	Compiler(std::string filename);
	~Compiler(void);

	Token get_token(void);
	std::string Name(Token t);
	Token check_reserved(std::string s)
	{
		if (s == "program")	return program_sy;
		else if (s == "read")		return read_sy;
		else if (s == "write")		return write_sy;
		else if (s == "if")			return if_sy;
		else if (s == "lenght")		return length_sy;
		else if (s == "new")		return new_sy;
		else						return identifier_sy;
	}
	void Match(Token terminal);
	void Syntax_Error(Token t);
	void ScannerCheck(void);
	//Parser Functions
	void sample_parser(void);
	void Program(void);
	void State_Seq(void);
	void State(void);
	void State_Tail(void);
	void Expr_Seq(void);
	void Expr_zero(void);
	void Expr_first(void);
	void Expr_second(void);
	void term(void);
	void Operation(void);
};

Compiler::Compiler(std::string filename)
{
	int Token_number = 0;
	int LexicalErrorNumber = 0;
	int SyntaxErrorNumber = 0;
	f.open(filename);
	if (!f)
	{
		std::cout << "Unable to open file\n";
		system("pause");
	}
}

Compiler::~Compiler(void)
{
	f.close();
}

Token Compiler::get_token(void)
{
	char ch;
	std::string s = "";
	f.get(ch);
	if (f.fail())
	{
		return end_source_sy;
	}
	while (isspace(ch) && !f.fail())
	{
		f.get(ch);
	}
	if (ch == '$')
	{
		return end_source_sy;
	}
	else if (ch == '{')
	{
		return openCurlyBracket_sy;
	}
	else if (ch == '}')
	{
		return closeCurlyBracket_sy;
	}
	else if (ch == ';')
	{
		return semiColom_sy;
	}
	else if (ch == '(')
	{
		return openParnthese_sy;
	}
	else if (ch == ')')
	{
		return closeParnthese_sy;
	}
	else if (ch == '=')
	{
		return equal_sy;
	}
	else if (ch == '?')
	{
		return quationMark_sy;
	}
	else if (ch == ':')
	{
		return colom_sy;
	}
	else if (ch == '[')
	{
		return openSquareBracket_sy;
	}
	else if (ch == ']')
	{
		return closeSquareBracket_sy;
	}
	else if (ch == '.')
	{
		return dot_sy;
	}
	else if (ch == '!')
	{
		return not_sy;
	}
	else if (ch == '+')
	{
		f.get(ch);
		if (ch == '=')
		{
			return plusEqual_sy;
		}
	}
	else if (ch == '*')
	{
		f.get(ch);
		if (ch == '=')
		{
			return multEqual_sy;
		}
	}
	else if (ch == '&')
	{
		f.get(ch);
		if (ch == '&')
		{
			f.get(ch);
			if (ch == '=')
			{
				return andEqual_sy;
			}
		}
	}

	else if (isalpha(ch))
	{

		s = ch;
		f.get(ch);
		while (isalnum(ch))
		{
			s += ch;
			f.get(ch);
		}
		f.putback(ch);

		return check_reserved(s);
	}

	else if (isdigit(ch))
	{
		s = ch;
		f.get(ch);
		while (isdigit(ch))
		{
			s += ch;
			f.get(ch);
		}
		f.putback(ch);
		return integer_sy;
	}
	else
	{
		return error_sy;
	}
}

std::string Compiler::Name(Token t)
{
	switch (t)
	{
	case program_sy:
		return "program";
		break;

	case identifier_sy:
		return "Identifier";
		break;

	case openCurlyBracket_sy:
		return "{";
		break;

	case closeCurlyBracket_sy:
		return "}";
		break;

	case semiColom_sy:
		return ";";
		break;

	case read_sy:
		return "Read";
		break;

	case write_sy:
		return "Write";
		break;

	case andEqual_sy:
		return "&&=";
		break;

	case plusEqual_sy:
		return "+=";
		break;

	case multEqual_sy:
		return "*=";
		break;

	case if_sy:
		return "If";
		break;

	case openParnthese_sy:
		return "(";
		break;

	case closeParnthese_sy:
		return ")";
		break;

	case equal_sy:
		return "=";
		break;

	case quationMark_sy:
		return "?";
		break;

	case colom_sy:
		return ":";
		break;

	case openSquareBracket_sy:
		return "[";
		break;

	case closeSquareBracket_sy:
		return "]";
		break;

	case dot_sy:
		return ".";
		break;

	case length_sy:
		return "Length";
		break;

	case new_sy:
		return "New";
		break;

	case not_sy:
		return "!";
		break;

	case integer_sy:
		return "Integer";
		break;

	case error_sy:
		return "Error";
		break;

	case end_source_sy:
		return "$";
		break;

	default:
		return "undefined ";
		break;
	}
}

void Compiler::ScannerCheck(void)
{
	Token t = get_token();
	while (t != end_source_sy)
	{
		switch (t)
		{
		case error_sy:
			std::cout << "lexical error Number (" << LexicalErrorNumber++ << "):" << Name(t) << " illegal token\n\n" ;
			break;
		}
		t = get_token();
	}
	if (t == end_source_sy)
	{
		std::cout << "*****There are (" << LexicalErrorNumber - 1 << ") lexical errors in this file***** \n\n";

	}
}

void Compiler::Match(Token terminal)
{
	if (current_token == terminal && current_token != end_source_sy)
	{
		std::cout <<" Number("<<Token_number++<<")----->   "<<Name(current_token) << " is matched\n\n";
	}
	else if (current_token == end_source_sy)
	{
		std::cout << "*****There are (" << SyntaxErrorNumber - 1 << ") Synatx errors in this file***** \n\n";
	}
	else
		Syntax_Error(current_token);
	current_token = get_token();
}

void Compiler::Syntax_Error(Token t)
{
	std::cout <<"Syntax Error Number("<<SyntaxErrorNumber++<<") :: "<< Name(t) << " isn't expected\n\n";
}

void Compiler::sample_parser(void)
{
	current_token = get_token();
	Program();
	Match(end_source_sy);
}

void Compiler::Program(void)
{
	Match(program_sy);
	Match(identifier_sy);
	Match(openCurlyBracket_sy);
	Compiler::State_Seq();
	Match(closeCurlyBracket_sy);

}

void Compiler::State_Seq(void)
{
	Compiler::State();
	while (current_token == semiColom_sy)
	{
		Match(semiColom_sy);
		Compiler::State();
	}
}

void Compiler::State(void)
{
	switch (current_token)
	{
	case read_sy:
		Match(read_sy);
		Match(identifier_sy);
		break;

	case write_sy:
		Match(write_sy);
		Expr_Seq();
		break;

	case identifier_sy:
		Match(identifier_sy);
		State_Tail();
		break;

	case if_sy:
		Match(if_sy);
		Match(openParnthese_sy);
		Expr_Seq();
		Match(closeParnthese_sy);
		Match(openCurlyBracket_sy);
		State_Seq();
		Match(closeCurlyBracket_sy);
		break;
	
	default:
		Syntax_Error(current_token);
		break;
	}
}

void Compiler::State_Tail(void)
{
	switch (current_token)
	{
	case plusEqual_sy:
		Match(plusEqual_sy);
		Expr_Seq();
		break;

	case multEqual_sy:
		Match(multEqual_sy);
		Expr_Seq();
		break;

	case andEqual_sy:
		Match(andEqual_sy);
		Expr_Seq();
		break;

	case equal_sy:
		Match(equal_sy);
		Match(openParnthese_sy);
		Expr_Seq();
		Match(quationMark_sy);
		Expr_Seq();
		Match(colom_sy);
		Expr_Seq();
		Match(closeParnthese_sy);
		break;
	default:
		Syntax_Error(current_token);
		break;
	}
}

void Compiler::Expr_Seq(void)
{
	switch (current_token)
	{
	case identifier_sy:
		term();
		Expr_zero();
		break;

	case integer_sy:
		term();
		Expr_zero();
		break;

	case new_sy:
		Match(new_sy);
		Match(identifier_sy);
		Expr_second();
		break;

	case not_sy:
		Match(not_sy);
		Expr_Seq();
		break;

	case openParnthese_sy:
		Match(openParnthese_sy);
		Expr_Seq();
		Match(closeParnthese_sy);
		break;

	default:
		Syntax_Error(current_token);
		break;
	}
}

void Compiler::Expr_zero(void)
{
	
	while (current_token == plusEqual_sy || current_token == multEqual_sy || current_token == andEqual_sy || current_token == openSquareBracket_sy)
	{
			Expr_first();
	}
	
}

void Compiler::Expr_first(void)
{
	switch (current_token)
	{
	case plusEqual_sy :
			Match(plusEqual_sy);
			Expr_Seq();
		break;

	case multEqual_sy:
			Match(multEqual_sy);
			Expr_Seq();
		break;

	case andEqual_sy:
			Match(andEqual_sy);
			Expr_Seq();
		break;

	case openSquareBracket_sy:
			Match(openSquareBracket_sy);
			Expr_Seq();
			Match(closeSquareBracket_sy);
		break;

	case dot_sy:
			Match(dot_sy);
			Match(length_sy);
		break;
	
	default:
		Syntax_Error(current_token);
		break;
	}
}

void Compiler::Expr_second(void)
{
	switch (current_token)
	{
	case openSquareBracket_sy:
		Match(openSquareBracket_sy);
		Expr_Seq();
		Match(closeSquareBracket_sy);
		break;

	case openParnthese_sy:
		Match(openParnthese_sy);
		Match(closeParnthese_sy);
		break;

	default:
		Syntax_Error(current_token);
		break;
	}
}

void Compiler::term(void)
{
	switch(current_token)
	{
	case identifier_sy:
		Match(identifier_sy);
		break;
		
	case integer_sy:
		Match(integer_sy);
		break;
	
	default:
		Syntax_Error(current_token);
		break;

	}
}

void Compiler::Operation(void)
{
	switch (current_token)
	{
	case plusEqual_sy:
		Match(plusEqual_sy);
		break;

	case multEqual_sy:
		Match(multEqual_sy);
		break;
		
	case andEqual_sy:
		Match(andEqual_sy);
		break;

	default:
		Syntax_Error(current_token);
		break;
	}
}

void Run()
{
	int x = 0;
	std::string  FileName;
	do
	{
		std::cout << "Enter file name : ";
		std::cin >> FileName;
		std::cout << "*******Scanner Phase*******\n\n";
		Compiler w(FileName);
		w.ScannerCheck();
		std::cout << "------------------------------------------------\n\n";
		std::cout << "******Parser Phase******\n\n";
		Compiler y(FileName);
		y.sample_parser();
	     Token_number = 1;
		LexicalErrorNumber = 1;
		SyntaxErrorNumber = 1;
		std::cout << "	press 1 to try again = ";
		std::cin >> x;
	} while (x == 1);
}

int main()
{
	Run();
	system("pause");
	return 0;
}
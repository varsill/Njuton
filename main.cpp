
#include "Parser.h"
#include "Lexer.h"
int main()
{
	Lexer lexer("bah : integer");
	Parser parser(lexer.Lex());
	
	parser.Add_production("INSTRUKCJA", "POROWNANIE");
	parser.Add_production("INSTRUKCJA", "PRZYPISANIE");
	parser.Add_production("INSTRUKCJA", "DEKLARACJA");
	parser.Add_production("PRZYPISANIE", "ARGUMENT PRZYPISZ ARGUMENT");
	parser.Add_production("ARGUMENT", "LICZBA");
	parser.Add_production("ARGUMENT", "ZMIENNA");
	parser.Add_production("OPERATOR", "WIEKSZE");
	parser.Add_production("OPERATOR", "MNIEJSZE");
	parser.Add_production("OPERATOR", "ROWNE");
	parser.Add_production("POROWNANIE", "ARGUMENT OPERATOR ARGUMENT");
	parser.Add_production("DEKLARACJA", "ZMIENNA : TYP");
	parser.Check();


	cout << parser.str;
		system("PAUSE");
}

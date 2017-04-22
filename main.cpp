
#include "Parser.h"
#include "Lexer.h"
#include <fstream>

int main()
{
	fstream plik;
	string path = "D:\\p.nwt";
	plik.open(path);
	string bufor, buf;
	Lexer lexer("");
	
	Parser parser("");
	
	parser.Add_production("INSTRUKCJA", "POROWNANIE");
	parser.Add_production("INSTRUKCJA", "PRZYPISANIE");
	parser.Add_production("INSTRUKCJA", "WYPISZ");
	parser.Add_production("DEKLARACJA", "DEKLARACJA DEKLARACJA");
	parser.Add_production("INSTRUKCJA", "DEKLARACJA_T");
	//parser.Add_production("DEKLARACJA_T", "ZMIENNA : array [ LICZBA ] of TYP");
	parser.Add_production("PRZYPISANIE", "ZMIENNA PRZYPISZ LICZBA");
	parser.Add_production("PRZYPISANIE", "ZMIENNA PRZYPISZ ZMIENNA");
	parser.Add_production("OPERATOR", "WIEKSZE");
	parser.Add_production("OPERATOR", "MNIEJSZE");
	parser.Add_production("OPERATOR", "ROWNE");
	parser.Add_production("POROWNANIE", "LICZBA OPERATOR LICZBA");
	parser.Add_production("POROWNANIE", "LICZBA OPERATOR ZMIENNA");
	parser.Add_production("POROWNANIE", "ZMIENNA OPERATOR LICZBA");
	parser.Add_production("POROWNANIE", "ZMIENNA OPERATOR LICZBA");
	parser.Add_production("DEKLARACJA", "ZMIENNA : TYP");
	parser.Add_production("TYP", "integer");
	parser.Add_production("TYP", "bool");
	parser.Add_production("TYP", "short");
	parser.Add_production("TYP", "long");
	parser.Add_production("FUNKCJA", "TYP ZMIENNA ( DEKLARACJA )");
	
	if (plik.is_open())
	{
		while (!plik.eof())
		{
			bufor = buf = "";
			while (bufor != ";")
			{
				plik >> bufor;
				buf = buf + " " + bufor;
			}
			buf.erase(0, 1);
			buf.erase(buf.size() - 1, 1);
			lexer.str = buf;
			lexer.Create_Tree();
			lexer.Lex();
			parser.drzewa = lexer.trees;
			parser.Parse();
		
		
		}
	}
	plik.close();


	cout << parser.drzewa[0]->name;
	parser.trees[0];
	

		system("PAUSE");
}

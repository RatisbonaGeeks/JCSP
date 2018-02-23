#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Parser.h"

using namespace std;

int main(int argc, char * argv[]);

void showHelp();

string openFile(string filepath);

int main(int argc, char* argv[])
{
	if (argv[1] == NULL)
	{
		cout << "No Input file selected!";
		return 0;
	}

	//File
	string firstParam = argv[1]; // -f
	string firstValue = argv[2]; // test.jcsp

	//Variable declaration
	string secondParam = argv[3]; // -v
	string secondValue = argv[4]; // ON

	if (firstParam == "-h" ) 
	{
		showHelp();
	}

	//ToDo: Make it possible to mix parameters (not needed at the moment but more comfortable for the user)

	if (firstParam == "-f")
	{
		if (firstValue != "")
		{
			string code = openFile(firstValue);
			Parser parser(&code);

			if (argv[3] == "-v" && argv[4] == "MODERN")
			{
				parser.REP_variableDeclaration();
			}

			parser.REM_comments();
			parser.REP_import();
			parser.REP_function_void();
			parser.REP_for();
			parser.REP_cast();

			
			//Test-Output
			cout << code;

			//Output as file. - It's planned, that the user can name this. It's not required now.
			// For example we could add -o <filename> to the parameters (ADD TO GITHUB WIKI)
			ofstream outputFile("out.cpp");

			//TODO: Call g++ here
			outputFile << code;
			return 0;
		}
		else
		{
			cout << "No input file selected" << endl;
		}
	}
	else
	{
		cout << "No options selected" << endl;
		showHelp();
	}
	
	return 0;
}

//////////////////////////////////////////////////////////////
//
//  Opens the file which should be parsed
//
//////////////////////////////////////////////////////////////
string openFile(string filepath)
{
	string code;
	string line;
	ifstream inp(filepath);
	while(getline(inp, line)) 
	{
		istringstream iss(line);
		code = code + line + "\n";
	}
	return code;
}

void showHelp()
{
	cout << "To compile the program you can set these parameters:\n\n" <<
		"- f File(path) which you want to compile\n" <<
		"- s ON or OFF for Semicolons(Standard: OFF)\n" <<
		"- bco ON or OFF for curly brackets for conditions and loops(Standard: OFF)\n" <<
		"- bct ON or OFF for curly brackets for classes and functions(Standard: ON)\n" <<
		"- v C or MODERN for the variable declaration mode(Standard: MODERN)\n" <<
		"An example to command would be :\n\n" <<
		"JCSPTranslate -f HelloWorld.jcsp -s OFF -bco OFF -bct ON -v MODERN\n";
}

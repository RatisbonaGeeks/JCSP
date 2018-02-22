#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char * argv[]);

void showHelp();

string openFile(string filepath);
void REP_import(string * code);
void REM_comments(string * code);
void REP_function_void(string * code);
void REP_for(string * code);
void REP_variableDeclaration(string * code);
void REP_cast(string * code);

void replace(string * code, string regexstring, string result);

int main(int argc, char* argv[])
{
	if (argv[1] == NULL)
	{
		cout << "No Input file selected!";
		return 0;
	}

	if (argv[1] == "-h" ) 
	{
		showHelp();
	}
	cout << argv[1] << (argv[1] == " -f") << endl;
	if (argv[1] == " -f")
	{
		cout << "111";
		if (argv[2] != NULL)
		{
			cout << "222";
			string code = openFile(argv[2]);

			REM_comments(&code);
			REP_import(&code);
			REP_function_void(&code);
			REP_for(&code);
			REP_variableDeclaration(&code);
			REP_cast(&code);


			//Test-Output
			cout << code;

			//Output as file. - It's planned, that the user can name this. It's not required now.
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

//////////////////////////////////////////////////////////////
//
//  Basic replace function
//
//////////////////////////////////////////////////////////////
void replace(string * code, string regexstring, string result)
{
	regex exp(regexstring);
	*code = regex_replace(*code, exp, result);
}

//////////////////////////////////////////////////////////////
//
//  Replace import with #include
//
//////////////////////////////////////////////////////////////
void REP_import(string * code)
{
	replace(code, "import (\\w+)", "#include <inc\\$1.h>");
}

//////////////////////////////////////////////////////////////
//
//  Remove comments (not needed in cpp file)
//
//////////////////////////////////////////////////////////////
void REM_comments(string * code)
{
	replace(code, "[#\\/].+", "");
	replace(code, "\\/\\*[\\s\\w]+\\*\\/", "");
}

//////////////////////////////////////////////////////////////
//
//  Repace main function
//  
//////////////////////////////////////////////////////////////
void REP_function_void(string * code)
{
	replace(code, "func \\w+(\\(.+\\))", "void Main $1");
}


//////////////////////////////////////////////////////////////
//
//  Create a C-Loop
//  ToDo: Curly brackets
//
//////////////////////////////////////////////////////////////
void REP_for(string * code)
{
	replace(code, "for \\((\\w+) ([\\w\\d]+) in (\\d+)\\.\\.\\.(\\d+)\\)", "for ($1 $2 = $3; $2 <= $4; $2++)");
}

//////////////////////////////////////////////////////////////
//
//  Variable declaration conversion
//
//////////////////////////////////////////////////////////////
void REP_variableDeclaration(string * code)
{
	replace(code, "var (\\w+) : (\\w+)", "$2 $1");
}

//////////////////////////////////////////////////////////////
//
//  Convert a as-Cast 
//  ToDo: This will replace all " ... as ...." 
//
//////////////////////////////////////////////////////////////
void REP_cast(string * code)
{
	replace(code, "(\\w+) as (\\w+)", "($2)$1");
}
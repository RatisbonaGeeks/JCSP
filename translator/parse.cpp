#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

string openFile(string filepath);
void REP_import(string * code);
void REP_comments(string * code);
void REP_function_void(string * code);
void REP_for(string * code);
void REP_variableDeclaration(string * code);

void replace(string * code, string regexstring, string result);

int main(int argc, char* argv[])
{
	string code = openFile(argv[1]);
	
	REP_comments(&code);
	REP_import(&code);
	REP_function_void(&code);
	REP_for(&code);
	REP_variableDeclaration(&code);
	
	//Test-Output
	cout << code;
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
	replace(code, "import (\\w+)", "#include $1");
}

//////////////////////////////////////////////////////////////
//
//  Remove comments (not needed in cpp file)
//
//////////////////////////////////////////////////////////////
void REP_comments(string * code)
{
	replace(code, "[#\'](.+)", "");
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
	replace(code, "for \\((\\w+) ([\\w\\d]+) in (\\d+)\\.\\.\\.(\\d+)\\)", "for (int $1 = $2; $1 <= $3; $1++)");
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
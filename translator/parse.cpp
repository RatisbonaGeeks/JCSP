#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

string openFile(string filepath);
string REP_import(string code);
string REP_comments(string code);


int main(int argc, char* argv[])
{
	string code = openFile(argv[1]);
	
	code = REP_comments(code);
	code = REP_import(code);
	
	//Test-Output
	cout << code;
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
//  Replace import with #include
//
//////////////////////////////////////////////////////////////
string REP_import(string code)
{
	regex exp("import (\\w+)");
	return regex_replace(code, exp, "#include $1");
}

//////////////////////////////////////////////////////////////
//
//  Remove comments (not needed in cpp file)
//
//////////////////////////////////////////////////////////////
string REP_comments(string code)
{
	regex exp("[#\'(\\/\\/)](.+)");
	return regex_replace(code, exp, "");
}
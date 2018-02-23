#include <string>
using namespace std;

class Parser
{
public:
	Parser(string * code);
	~Parser();


	void REP_import();
	void REM_comments();
	void REP_function_void();
	void REP_for();
	void REP_variableDeclaration();
	void REP_cast();

private:
	void replace(string regexstring, string result);
	string code;
};


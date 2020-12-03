#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <regex>
#include <map>

using namespace std;

#define LOG_NEWLINE "\n"

void fill_table();
bool isSymbol(char ch);
bool isOperator(char ch);
void analyze(string token);
bool isWhitespace(char ch);
void print_val(string token);
bool isKeyword(string token);
bool isRealConst(string token);
bool isIdentifier(string token);
void print_dividers(char lookahead);

/*This table contains the glammar rules*/
typedef map<string, pair<int, int> > table;
regex identifier ("^[A-Za-z][0-9A-Za-z]*(_[0-9A-Za-z]+)*$");
regex float_rex ("[-+]?([0-9]*[.])?[0-9]*");
table t;

int main(int argc, char* argv[])
{
	string line;
	string token;	
	char output[512];
	char lookahead;	

	fill_table();
	cout << "Enter a text for lexical analysis: " << endl;
	getline(cin, line);
	
	bzero(output, 512);
	sprintf ( output + strlen ( output ), "%s====================================================================%s", LOG_NEWLINE, LOG_NEWLINE );
	sprintf ( output + strlen ( output ), "==================Lexical Analyzer==================================%s", LOG_NEWLINE );
	sprintf ( output + strlen ( output ), "====================================================================%s", LOG_NEWLINE );
	sprintf ( output + strlen ( output ), "| Type Num | Code |  Type        | Token                         %s", LOG_NEWLINE );
	sprintf ( output + strlen ( output ), "--------------------------------------------------------------------%s", LOG_NEWLINE );
	cout << output;
	
	/*inspect the entered test character by character*/
	for (int i = 0; i < line.length(); i++) {
		lookahead = line[i];
		
		/*If its a symbol )( or ; print in the table output*/
		if (isSymbol(lookahead)) {
			print_dividers(lookahead);
			cout << setw(8) << " Symbol";
			cout <<  setw(10) << "| ' " << lookahead << " ' " ;
			cout << endl;
			token.clear();
		} /*If its an operator + = * < > print in the table output*/
		else if (isOperator(lookahead)) {
			print_dividers(lookahead);
			cout << setw(10) << " Operator";
			cout << setw(8) << "| ' " << lookahead << " ' " ;
			cout << endl;
			token.clear();
		} /*If the character is alphanumeric or _ . - add in token because it could be part of an identifier, keyword or real constant*/
		else if (isalnum(lookahead) || lookahead == '_' || lookahead == '.' || lookahead == '-' ) {
			token.push_back(lookahead);
		} else if( (isWhitespace(lookahead)) && token.length() != 0){ /*If whitespace is encountered and the token is not empty - analyze the token*/
			analyze(token);
			token.clear();
		} else {
			if(isWhitespace(lookahead) == false){ /*In any other case print error*/
				cout << "|" << setw(2) << "X" << setw(11) << "| X";
				cout << setw(13) << "|  Error "  ;
				cout << setw(10) << "| ' " << lookahead << " ' " ;
				cout << endl;
			}
		}
	}
	
	/*If you encountered the end of the input and the token is not empty - analyze token*/
	if(token.length() > 0)
		analyze(token);
	
	bzero(output, 512);
	sprintf ( output + strlen ( output ), "====================================================================%s", LOG_NEWLINE );
	cout << output;
	return 0;
}

/*Fill the table with the grammar rules*/
void fill_table()
{
	t["identifier"] = make_pair(100, 0);
	t["real constant"] = make_pair(200, 0);
	t["if"] = make_pair(300, 301);
	t["else"] = make_pair(300, 302);
	t["for"] = make_pair(300, 303);
	t["+"] = make_pair(400, 401);
	t["*"] = make_pair(400, 402);
	t["="] = make_pair(400, 403);
	t[")"] = make_pair(400, 404);
	t["("] = make_pair(400, 405);
	t["<"] = make_pair(400, 406);
	t[">"] = make_pair(400, 407);
	t[";"] = make_pair(400, 408);	
}

/*Get type code and number for symbols and operators from the grammar table and print it*/
void print_dividers(char lookahead)
{
	pair<int, int> val;
	
	string key;
	key.push_back(lookahead);
	val = t[key];
		
	cout << setw(2) << "| " << val.first;
	cout << setw(8) << "| " << val.second << "  |" ;

}

/*Get type code and number for identifier, keyword and real constant from the grammar table and print it*/
void print_val(string token)
{
	pair<int, int> val;
	int width = 0;
	val = t[token];
	
	cout << "| " << setw(2) << val.first;
	cout << setw(8) << "| " << val.second;
}

/*Analyze identifier, keywords and real constant*/
void analyze(string token) {
	if (token.length() > 0) {
		if (isKeyword(token)) {
			print_val(token);
			cout << setw(12) << "|  Keyword";
			cout << setw(9) << "| ' " << token << " ' ";
			cout << endl;
		} else if (isIdentifier(token)) {
			print_val("identifier");
			cout << setw(17) << "|  Identifier";
			cout << setw(6) << "| ' " << token << " ' ";
			cout << endl;
		} else if (isRealConst(token)) {
			print_val("real constant");
			cout << setw(17) << "|  Real Const";
			cout << setw(6) << "| ' " << token << " ' ";
			cout << endl;
		} else {
			cout << "|" << setw(2) << "X" << setw(11) << "| X";
			cout << setw(13) << "|  Error "  ;
			cout << setw(10) << "| ' " << token << " ' " ;
			cout << endl;
		}
	}
}

bool isWhitespace(char ch) {
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',') {
		return true;
	} else {
		return false;
	}
}

bool isSymbol(char ch) {
	if ( ch == '(' || ch == ')' || ch == ';' ) {
		return true;
	} else {
		return false;
	}
}

bool isOperator(char ch) {
	if (ch == '+' || ch == '*' || ch == '=' || ch == '>' || ch =='<') {
		return true;
	} else {
		return false;
	}
}

bool isKeyword(string token) {
	if (token == "for" || token == "else" || token == "if" ) {
		return true;
	} else {
		return false;
	}
}

/*The identifier should always start with letter and can contain underscore _ and numbers*/
bool isIdentifier(string token) {
	if ( regex_match (token, identifier)) 
		return true;
	
	return false;
}

bool isRealConst(string token) {
	
	if(token.length() == 1 && token == ".")
		return false;
	
	if(token.length() == 1 && token == "-")
		return false;
		
	if (regex_match (token, float_rex)) 
		return true;
	
	return false;
}


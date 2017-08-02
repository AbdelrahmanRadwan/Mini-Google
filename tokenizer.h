#include"parser.h"
#include<queue>
#include<iostream>
using namespace std;

class Token
{
public:
  string expr;
  Parser::TOKENTYPE type;
  //enum TOKENTYPE {NOTHING = -1, DELIMETER, NUMBER, VARIABLE, FUNCTION, UNKNOWN};
  Token(string _expr, Parser::TOKENTYPE _type): expr(_expr), type(_type){}
  Token(){}
};

class TokenQueue
{
public:
    queue<Token> tokens;
    TokenQueue(){}
    TokenQueue(string expr);
    void SetExpr(string expr);
};
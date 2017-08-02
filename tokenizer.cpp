#include"tokenizer.h"

TokenQueue::TokenQueue(string expr)
{
  SetExpr(expr);
}


void TokenQueue::SetExpr(string expr)
{
  //clear the token queue
  while(! this->tokens.empty())
    this->tokens.pop();
  // initialize all variables
  Parser tokenizer;
  char * cstr;
  cstr = new char [ expr.size() + 1 ];
  strcpy (cstr, expr.c_str());
  
  tokenizer.e = cstr;   // let e point to the start of the expression
  tokenizer.getToken();
  while(tokenizer.token_type != Parser::DELIMETER || *(tokenizer.e) != '\0')
  {
    string ex(tokenizer.token);
    Token t(ex, tokenizer.token_type);
    tokens.push(t);
    tokenizer.getToken();  
  }
  delete[] cstr;
}

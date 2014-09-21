#include "Token.h"

Token::Token( TokenType type, std::string name ) :
    type( type ),
    name( name ) 
{}

Token::~Token() {}

Token::TokenType Token::GetType() const {
	return type;
}

const std::string& Token::GetName() const {
	return name;
}
#include "Token.h"

Token::Token( TokenType type, std::string property ) :
    type( type ),
    property( property ) 
{}

Token::~Token() {}

Token::TokenType Token::GetType() const {
	return type;
}

const std::string& Token::GetName() const {
	return property;
}
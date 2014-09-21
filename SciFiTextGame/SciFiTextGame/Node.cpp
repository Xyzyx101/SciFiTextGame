#include "Node.h"


Node::Node( Token* token, std::string myString ) :
    token( token ),
	myString( myString )
{
}

Node::~Node() {
	delete token;
}

const Token& Node::GetToken() const {
	return *token;
}

const std::string& Node::GetString() const {
	return myString;
}
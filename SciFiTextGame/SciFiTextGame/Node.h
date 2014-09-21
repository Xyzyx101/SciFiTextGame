#pragma once

#include<string>
#include"Token.h"

class Node {

friend class GrammarTree;

public:
	Node(Token* token, std::string myString);
	~Node();
	const Token& GetToken() const;
	const std::string& GetString() const;
private:
	Node* higher;
	Node* lower;
	Token* token;
	std::string myString;
};


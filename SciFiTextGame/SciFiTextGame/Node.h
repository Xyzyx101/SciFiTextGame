#pragma once

#include<string>
#include<map>
#include"Token.h"

class Node {

friend class GrammarTree;

public:
	Node();
	Node(Token* token);
	~Node();
private:
	std::map<std::string, Node*> children;
	Token* token;
};


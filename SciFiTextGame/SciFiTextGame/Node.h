#pragma once

#include<string>
#include<vector>
#include"Token.h"
#include"Edge.h"

class Node {

friend class GrammarTree;

public:
	Node();
	Node(Token* token);
	~Node();
private:
	std::vector<Edge> children;
	Token* token;
};


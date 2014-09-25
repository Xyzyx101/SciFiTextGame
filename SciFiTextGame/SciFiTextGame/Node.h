#pragma once

#include<string>
#include<vector>
#include"Token.h"
#include"Edge.h"

class Node {

friend class GrammarTree;

public:
	Node();
	Node(Token_ptr const token);
	~Node();
private:
	std::vector<Edge_ptr> children;
	Token_ptr const token;
};


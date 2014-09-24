#pragma once

#include<string>
#include<vector>
#include"Token.h"
#include"Edge.h"

class Node {

friend class GrammarTree;

public:
	Node();
	Node(const Token* const token);
	~Node();
private:
	std::vector<Edge> children;
	const Token* const token;
};


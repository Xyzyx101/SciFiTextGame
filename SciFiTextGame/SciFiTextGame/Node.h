#pragma once

#include<string>
#include<vector>
#include"CommonTypes.h"

class Node {

public:
	Node();
	Node(Token_ptr const token);
	~Node();
	std::vector<Edge_ptr>		children;
	Token_ptr const				token;
};

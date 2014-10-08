#pragma once

#include<string>
#include<vector>
#include"CommonTypes.h"

/* FIXME */
class Node {
public:
	Node();
	Node(Token_ptr const token);
	~Node();
	std::vector<Edge_ptr>		children;
	Token_ptr					token;
};

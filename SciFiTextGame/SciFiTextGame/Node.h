#pragma once

#include<string>
#include<vector>
#include"CommonTypes.h"

/* This an Node of a graph.  Making the properties public in this case is
safe because it is never exposed beyond. */
class Node {
public:
	Node();
	Node(Token_ptr const token);
	~Node();
	std::vector<Edge_ptr>		children;
	Token_ptr const				token;
};

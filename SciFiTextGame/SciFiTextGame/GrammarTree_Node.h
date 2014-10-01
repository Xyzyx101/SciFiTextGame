#pragma once

#include<string>
#include<vector>
#include"CommonTypes.h"

/* This an Node of GrammarTree graph.  Making the properties public in this case is
safe because Edge is never exposed beyond the GrammarTree. */
class Node {
public:
	Node();
	Node(Token_ptr const token);
	~Node();
	std::vector<Edge_ptr>		children;
	Token_ptr const				token;
};

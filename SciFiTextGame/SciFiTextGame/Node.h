#pragma once

#include<string>
#include<vector>
#include"CommonTypes.h"

/* This an node of a graph.  Making the properties public in this case is safe because nodes are
never exposed beyond the tree structures.  Used for GrammarTree and SyntaxTree. */
class Node {
public:
	Node();
	Node( Token_ptr const token );
	~Node();
	std::vector<Edge_ptr>		children;
	Token_ptr					token;
};

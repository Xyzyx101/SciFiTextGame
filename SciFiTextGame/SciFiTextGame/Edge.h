#pragma once
#include<string>
#include<set>
#include"CommonTypes.h"

class Node;

/* This an edge of a graph.  Making the properties public in this case is safe because Edge is 
never exposed beyond the tree. Used for GrammarTree, SyntaxTree and World */
class Edge {
public:
	Edge(std::string prefix, Node_ptr node);
	~Edge();
	std::string			prefix;
	Node_ptr			node;
};

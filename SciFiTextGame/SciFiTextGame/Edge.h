#pragma once

#include<string>
#include"CommonTypes.h"

class Node;

/* This an edge of GrammarTree graph */
class Edge {

	friend class GrammarTree;

public:
	Edge(std::string prefix, Node_ptr node);
	~Edge();
private:
	std::string prefix;
	Node_ptr node;
};
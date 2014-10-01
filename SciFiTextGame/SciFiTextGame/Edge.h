#pragma once

#include<string>
#include<set>
#include"CommonTypes.h"

class Node;

/* This an edge of a graph */
class Edge {
public:
	Edge(std::string prefix, Node_ptr node);
	~Edge();
	std::string			prefix;
	Node_ptr			node;
};

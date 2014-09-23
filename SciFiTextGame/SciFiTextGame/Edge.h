#pragma once

#include<string>

class Node;

class Edge {

	friend class GrammarTree;

public:
	Edge(std::string prefix, Node* node);
	~Edge();
private:
	std::string prefix;
	Node* node;
};
#pragma once
#include"CommonTypes.h"
#include<vector>

class SyntaxTree {
public:
	SyntaxTree();
	~SyntaxTree();
	Node_ptr							GetCurrentNode();
	void								NextSibling();
	void								MoveToChild();
	void								MoveToParent();
	void								Reset();
	void								InsertSibling(Node_ptr newNode);
	void								InsertChild(Node_ptr newNode);
private:
	Node_ptr							root;
	Node_ptr							currentNode;
	std::vector<Edge_ptr>::iterator		currentEdge;
	Node_ptr							currentParent;
};

#pragma once
#include"CommonTypes.h"
#include<vector>
#include<stack>

class SyntaxTree {
public:
	SyntaxTree();
	~SyntaxTree();
	void MoveToParent();
	void InsertChild(Edge_ptr);
	void InsertChildAndMakeCurrent( Edge_ptr );
	std::vector<Edge_ptr> GetChildren() const;
	void Reset();
private:
	Node_ptr							root;
	Node_ptr							currentNode;
	std::stack<Node_ptr>				parentStack;
};

#pragma once

#include"Node.h"

class GrammarTree {
public:
	GrammarTree();
	~GrammarTree();
	void AddNode(Node* node);
private:
	void Reset();
	void Delete(Node* node);
	Node* root;
	Node* current;
};


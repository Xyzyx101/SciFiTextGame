#pragma once

#include"Node.h"

class GrammarTree {
public:
	GrammarTree();
	~GrammarTree();
	void AddNode(Token* token, std::string alias);
	const Token * const Search(const std::string& string) const;
private:
	void AddNode(Node* node, Token* token, std::string alias);
	void Reset();
	void Delete(Node* node);
	void MoveNode(Node* node);
	Node* root;
	Node* current;
	Node* currentParent;
};


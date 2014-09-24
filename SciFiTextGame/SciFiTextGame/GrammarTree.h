#pragma once

#include"Node.h"
#include"Edge.h"

class GrammarTree {
public:
	GrammarTree();
	~GrammarTree();
	const Token* const Search( const std::string& string ) const;
	void AddNode(const Token* const token, const std::string& alias);
private:
	void AddNode(Node* node, const Token* const token, const std::string& alias);
	void Reset();
	void Delete(Node* node);
	void ChangeNode(Node* node);
	Node* root;
	Node* current;
	Node* currentParent;
};


#pragma once

#include"CommonTypes.h"
#include"Node.h"
#include"Edge.h"

class GrammarTree {
public:
	GrammarTree();
	~GrammarTree();
	Token_ptr const Search( const std::string& string ) const;
	void AddNode(Token_ptr const token, const std::string& alias);
private:
	void AddNode(Node_ptr node, Token_ptr const token, const std::string& alias);
	void Reset();
	Node_ptr root;
	Node_ptr current;
	Node_ptr currentParent;
};

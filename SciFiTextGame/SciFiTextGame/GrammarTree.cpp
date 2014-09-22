#include "GrammarTree.h"

GrammarTree::GrammarTree() :
current(nullptr),
currentParent(nullptr)
{
	root = new Node(nullptr);
}

GrammarTree::~GrammarTree() {}

void GrammarTree::Reset()
{
	current = root;
	currentParent = nullptr;
}

void GrammarTree::AddNode(Token* token, std::string alias) {
	AddNode(root, token, alias);
}

void GrammarTree::AddNode(Node* node, Token* token, std::string alias) {
	std::map<std::string, Node*>::iterator it = node->children.lower_bound(alias);
	std::string partial = "";
	while( partial == "" && it != node->children.end() ) {
		std::string edgeString = it->first;
		for(size_t i = 0; i < edgeString.length(); ++i ) {
			if( alias[i] == edgeString[i] ) {
				partial += alias[i];
			}
		}

		//TODO recursive depth call goes here

		++it;
	}
	Node* newNode = new Node(token);
	if( partial == "" ) {
		node->children.insert(std::pair<std::string, Node*>(alias, newNode));
	} else {
		std::map<std::string, Node*>::iterator oldNodeIt = node->children.lower_bound(partial);
		std::string oldString = oldNodeIt->first;
		Node* oldNode = oldNodeIt->second;
		Node* splitNode = new Node();
		splitNode->children.insert(std::pair<std::string, Node*>(alias.substr(partial.length()), newNode));
		splitNode->children.insert(std::pair<std::string, Node*>(oldString.substr(partial.length()), oldNode));
		node->children.insert(std::pair<std::string, Node*>(partial, splitNode));
		node->children.erase(oldNodeIt);
	}
}

const Token * const GrammarTree::Search(const std::string& string) const {
	return nullptr;
}
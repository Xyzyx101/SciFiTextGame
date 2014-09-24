#include "GrammarTree.h"
#include<vector>

GrammarTree::GrammarTree() :
current(nullptr),
currentParent(nullptr) {
	root = new Node();
}

GrammarTree::~GrammarTree() {}

void GrammarTree::Reset() {
	current = root;
	currentParent = nullptr;
}

void GrammarTree::AddNode(const Token* const token, const std::string& alias) {
	AddNode(root, token, alias);
}

void GrammarTree::AddNode(Node* node, const Token* const token, const std::string& alias) {

	std::vector<Edge>::iterator edgeIter = node->children.begin();

	std::string partial = "";
	while( edgeIter != node->children.end() ) {
		std::string edgeString = edgeIter->prefix;
		for( size_t i = 0; i < edgeString.length(); ++i ) {
			if( alias[i] == edgeString[i] ) {
				partial += alias[i];
			} else {
				break;
			}
		}
		if( partial == edgeString ) {
			AddNode(edgeIter->node, token, alias.substr(partial.length()));
			return;
		}
		else if( partial != "" ) {
			break;
		}
		++edgeIter;
	}
	Node* newNode = new Node(token);
	if( partial == "" ) {
		node->children.push_back(Edge(alias, newNode));
	} else {
		std::string oldString = edgeIter->prefix;
		Node* oldNode = edgeIter->node;
		node->children.erase( edgeIter );
		Node* splitNode = new Node();
		splitNode->children.push_back(Edge(alias.substr(partial.length()), newNode));
		splitNode->children.push_back(Edge(oldString.substr(partial.length()), oldNode));
		node->children.push_back(Edge(partial, splitNode));
	}
}

const Token * const GrammarTree::Search(const std::string& string) const {
	return nullptr;
}
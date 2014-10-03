#include"SyntaxTree.h"
#include"CommonTypes.h"
#include "Node.h"
#include<memory>

SyntaxTree::SyntaxTree() {
	root = std::make_shared<Node>();
}

SyntaxTree::~SyntaxTree() {}

Node_ptr SyntaxTree::GetCurrentNode() {
	return std::make_shared<Node>();
}

void SyntaxTree::NextSibling() {

}

void SyntaxTree::MoveToChild() {

}

void SyntaxTree::MoveToParent() {

}

void SyntaxTree::Reset() {

}

void InsertSibling(Node_ptr newNode) {

}

void InsertChild(Node_ptr newNode) {

}

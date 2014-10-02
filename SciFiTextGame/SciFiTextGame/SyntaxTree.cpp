#include"SyntaxTree.h"
#include"CommonTypes.h"
#include<memory>

SyntaxTree::SyntaxTree() {
	root = std::make_shared<Node_ptr>();
}

SyntaxTree::~SyntaxTree() {}

Node_ptr SyntaxTree::GetCurrentNode() {
	return current;
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

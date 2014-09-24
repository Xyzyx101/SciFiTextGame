#include "Node.h"

Node::Node() :
token(nullptr) {}

Node::Node(const Token* const token) :
token(token) {}

Node::~Node() {
	delete token;
}

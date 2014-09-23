#include "Node.h"

Node::Node() :
token(nullptr) {}

Node::Node(Token* token) :
token(token) {}

Node::~Node() {
	delete token;
}

#include<memory>

class Token;
typedef std::shared_ptr<const Token> Token_ptr;

class Node;
typedef std::shared_ptr<Node> Node_ptr;

class Edge;
typedef std::shared_ptr<Edge> Edge_ptr;
#include "GrammarTree.h"
#include "Node.h"
#include "Edge.h"
#include"TokenPool.h"
#include<cctype>
#include<fstream>
#include<string>

GrammarTree::GrammarTree() {
	root = std::make_shared<Node>();
}

GrammarTree::~GrammarTree() {}

void GrammarTree::AddNode( Token_ptr const token, const std::string& alias ) {
	AddNode_r( root, token, alias );
}

void GrammarTree::AddNode_r( Node_ptr node, Token_ptr const token, const std::string& alias ) {
	std::vector<Edge_ptr>::iterator edgeIter = node->children.begin();
	/* Partial hold letters we have found so far */
	std::string partial = "";
	while( edgeIter != node->children.end() ) {
		/* Search through the edges and check if any of the partial alias strings match the alias to be added */
		std::string edgeString = (*edgeIter)->prefix;
		for( size_t i = 0; i < edgeString.length(); ++i ) {
			if( alias[i] == edgeString[i] ) {
				partial += alias[i];
			} else {
				break;
			}
		}
		if( partial == edgeString ) {
			/* If the matching edge is identical to the start of the alias recurse deeper into the tree */
			AddNode_r( (*edgeIter)->node, token, alias.substr( partial.length() ) );
			return;
		} else if( partial != "" ) {
			/* If the start of the edge prefix matches but not the full length then we are at the correct 
			place in the tree to add a new node*/
			break;
		}
		++edgeIter;
	}

	/* Add the node */
	Node_ptr newNode = std::make_shared<Node>( token );
	if( partial == "" ) {
		/* If we are at the max depth where a match could be found and there is no partial match then
		add the node.  This could be the root.*/
		node->children.push_back( std::make_shared<Edge>( alias, newNode ) );
	} else {
		/* If there is a partial match then we need to make a new node with two edges.  One edge for 
		the old branch of the tree and a new one for the new node.*/
		std::string oldString = (*edgeIter)->prefix;
		Node_ptr oldNode = (*edgeIter)->node;
		node->children.erase( edgeIter );
		Node_ptr splitNode = std::make_shared<Node>();
		splitNode->children.push_back( std::make_shared<Edge>( alias.substr( partial.length() ), newNode ) );
		splitNode->children.push_back( std::make_shared<Edge>( oldString.substr( partial.length() ), oldNode ) );
		node->children.push_back( std::make_shared<Edge>( partial, splitNode ) );
	}
}

std::list<Token_ptr> GrammarTree::Tokenize( std::string& command ) const {
	std::list<Token_ptr> tokens;
	/* As the sentance is tokenized we remove the used parts of the command string. */
	while( command.length() > 0 ) {
		Token_ptr token = Find_r( root, command );
		if( token != nullptr ) {
			tokens.push_back( token );
		}
	}
	return tokens;
}

Token_ptr GrammarTree::Find_r( Node_ptr node, std::string& command ) const {
	/* Get the first element from the stream while ignoreing leading whitespace. */
	std::string::iterator commandIter = command.begin();
	while( std::isspace( *commandIter ) ) {
		++commandIter;
	}

	/* Iterate through the edges and search for a match. */
	int foundElements = 0;
	std::vector<Edge_ptr>::iterator edgeIter = node->children.begin();
	do {
		std::string prefix = (*edgeIter)->prefix;
		for( size_t i = 0; i < prefix.length(); ++i, ++commandIter ) {
			if( prefix[i] == std::tolower( *commandIter ) ) {
				++foundElements;
			} else {
				break;
			}
		}

		/* If part of a prefix is found but does not match the whole length then the word
		is not in the grammar tree and a nullptr will be returned. */
		if( foundElements == prefix.length() ) {
			/* A full matching prefix is found and there are two possible outcomes.
			First if this node has an associated token and the next char in the string
			is whitespace or the end of the string then we are at the correct node and the
			token should be returned.  If the next char in the stream is another letter we
			recurse deeper into the tree. The single letter 's' could return the 'go south'
			token but we do not want to stop at the beginning of every s word. */
			command = std::string( commandIter, command.end() );
			if( (*edgeIter)->node->token != nullptr
				&& (command.begin( ) == command.end( ) || std::isspace( *(command.begin( )) ))
				) {
				return (*edgeIter)->node->token;
			} else {
				return Find_r( (*edgeIter)->node, command );
			}
		}
		++edgeIter;
	} while( foundElements == 0
			 && edgeIter != node->children.end()
			 && commandIter != command.end() );

	/* If nothing is found return nullptr. */
	return nullptr;
}

void GrammarTree::AddDictionary( const std::string& dictFile ) {
	std::string fullName = ".\\Data\\";
	fullName += dictFile;
	std::ifstream fStream;
	std::string line;
	fStream.open( fullName, std::ifstream::in );
	while( fStream.good( ) ) {
		std::getline( fStream, line );
		AddNodeWithString( line );
	}
	fStream.close( );
}

void GrammarTree::AddNodeWithString(const std::string& line) {
	int firstSpace, lastSpace;
	firstSpace = line.find_first_of(' ');
	lastSpace = line.find_last_of(' ');

	std::string alias, type, token;
	alias = line.substr(0, firstSpace);
	type = line.substr(firstSpace + 1, lastSpace - firstSpace - 1);
	token = line.substr(lastSpace + 1);

	Token_ptr newToken = TokenPool::Instance().NewToken(type, token);
	AddNode(newToken, alias);
}



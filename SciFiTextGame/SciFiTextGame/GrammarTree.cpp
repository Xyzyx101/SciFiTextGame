#include "GrammarTree.h"
#include "Node.h"
#include "Edge.h"
#include"TokenPool.h"
#include"Token.h"
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
	/* alias will be "" when you try to add a node that already exists. */
	if( alias.length() == 0 ) {
		/* Adding the same node twice should have no effect */
		return;
	}
	std::vector<Edge_ptr>::iterator edgeIter = node->children.begin();
	/* Partial hold letters we have found so far */
	std::string partial = "";
	while( edgeIter != node->children.end() ) {
		/* Search through the edges and check if any of the partial alias strings match the alias to be added */
		std::string edgeString = ( *edgeIter )->prefix;
		for( size_t i = 0; i < edgeString.length(); ++i ) {
			if( alias[i] == edgeString[i] ) {
				partial += alias[i];
			} else {
				break;
			}
		}
		if( partial == edgeString ) {
			/* If the matching edge is identical to the start of the alias recurse deeper into the tree */
			AddNode_r( ( *edgeIter )->node, token, alias.substr( partial.length() ) );
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

		std::string oldString = ( *edgeIter )->prefix;
		Node_ptr oldNode = ( *edgeIter )->node;
		node->children.erase( edgeIter );
		Node_ptr splitNode;

		std::string newEdge = alias.substr( partial.length() );
		std::string oldEdge = oldString.substr( partial.length() );
		if( newEdge.length() == 0 ) {
			splitNode = std::make_shared<Node>( newNode->token );
			splitNode->children.push_back( std::make_shared<Edge>( oldEdge, oldNode ) );
		} else if( oldEdge.length() == 0 ) {
			splitNode = std::make_shared<Node>( oldNode->token );
			splitNode->children.push_back( std::make_shared<Edge>( newEdge, newNode ) );
		} else {
			splitNode = std::make_shared<Node>();
			splitNode->children.push_back( std::make_shared<Edge>( newEdge, newNode ) );
			splitNode->children.push_back( std::make_shared<Edge>( oldEdge, oldNode ) );
		}
		node->children.push_back( std::make_shared<Edge>( partial, splitNode ) );
	}
}

std::list<Token_ptr> GrammarTree::Tokenize( std::string& command ) const {
	std::list<Token_ptr> tokens;
	RemoveLeadingWhitespace( command );
	std::string failWord;
	/* As the sentance is tokenized we remove the used part of the command string. */
	while( command.length() > 0 ) {
		Token_ptr token;
		if( command[0] == '"' ) {
			token = GetStringToken( command );
		} else {
			token = Find_r( root, command, failWord );
		}
		if( token == nullptr ) {
			std::cout << "I do not understand the word " << failWord << "." << std::endl;
			tokens.clear();
			return tokens;
		} else {
			tokens.push_back( token );
		}
		RemoveLeadingWhitespace( command );
	}
	return tokens;
}

Token_ptr GrammarTree::Find_r( Node_ptr node, std::string& command, std::string& failWord ) const {
	std::string::iterator commandIter = command.begin();
	if( commandIter == command.end() ) {
		CompleteFailWord(command, failWord);
		return nullptr;
	}

	/* Iterate through the edges and search for a match. */
	int foundElements = 0;
	std::vector<Edge_ptr>::iterator edgeIter = node->children.begin();
	do {
		std::string prefix = ( *edgeIter )->prefix;
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
			if( ( *edgeIter )->node->token != nullptr
				&& ( command.begin() == command.end() || !std::isalpha( *( command.begin() ) ) )
				) {
				failWord = "";
				return ( *edgeIter )->node->token;
			} else {
				failWord += prefix;
				return Find_r( ( *edgeIter )->node, command, failWord );
			}
		}
		++edgeIter;
	} while( foundElements == 0
		&& edgeIter != node->children.end()
		&& commandIter != command.end() );

	/* If nothing is found complete the failWord and return nullptr. */
	CompleteFailWord(command, failWord);
	return nullptr;
}

void GrammarTree::CompleteFailWord( std::string& command, std::string& failWord ) const {
	std::string::iterator commandIter = command.begin( );
	while( commandIter != command.end( )
		&& std::isalpha( *commandIter ) ) {
		failWord += *commandIter;
		++commandIter;
	}
}

Token_ptr GrammarTree::GetStringToken( std::string& command ) const {
	std::string::iterator stringBegin, stringEnd;
	stringBegin = command.begin() + 1;
	stringEnd = stringBegin;
	while( *stringEnd != '"' ) {
		++stringEnd;
		if( stringEnd == command.end() ) {
			std::cout << "Error parsing string" << std::endl;
		}
	}
	std::string tokenString = std::string( stringBegin, stringEnd );
	command = std::string( stringEnd + 1, command.end() );
	return std::make_shared<Token>( Token::TokenType::STRING, tokenString );
}

void GrammarTree::AddDictionary( const std::string& dictFile ) {
	std::string fullName = ".\\Data\\";
	fullName += dictFile;
	std::ifstream fStream;
	std::string line;
	fStream.open( fullName, std::ifstream::in );
	while( fStream.good() ) {
		std::getline( fStream, line );
		AddNodeWithString( line );
	}
	fStream.close();
}

void GrammarTree::AddNodeWithString( const std::string& line ) {
	std::string wsCheck = line;
	RemoveLeadingWhitespace( wsCheck );
	if( wsCheck.length() == 0 ) {
		return;
	}
	std::string alias, type, token;
	int firstQuote, lastQuote;
	firstQuote = line.find_first_of( '"' );
	lastQuote = line.find_last_of( '"' );
	alias = line.substr( firstQuote + 1, lastQuote - firstQuote - 1 );

	int typeStart = lastQuote + 1 + line.substr( lastQuote + 1, std::string::npos ).find_first_not_of( " \n\t" );
	int lastSpace = line.find_last_of( ' ' );
	type = line.substr( typeStart, lastSpace - typeStart );
	token = line.substr( lastSpace + 1 );

	Token_ptr newToken = TokenPool::Instance().NewToken( type, token );
	AddNode( newToken, alias );
}

void GrammarTree::RemoveLeadingWhitespace( std::string& command ) const {
	std::string::iterator commandIter = command.begin();
	while( commandIter != command.end() && std::isspace( *commandIter ) ) {
		++commandIter;
	}
	command = std::string( commandIter, command.end() );
}
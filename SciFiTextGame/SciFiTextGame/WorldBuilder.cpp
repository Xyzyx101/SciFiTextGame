#include "WorldBuilder.h"
#include"GrammarTree.h"
#include"SyntaxTree.h"
#include"Token.h"
#include"TokenPool.h"
#include"Edge.h"
#include"Node.h"
#include<fstream>
#include<memory>
#include<string>

WorldBuilder::WorldBuilder() :
grammarTree( std::make_shared<GrammarTree>() ),
syntaxTree(std::make_shared<SyntaxTree>()) {}

WorldBuilder::~WorldBuilder() {}

void WorldBuilder::InitGrammarWithFile( const std::string& dictFileName ) {
	grammarTree->AddDictionary( "importer.dict" );
}

void WorldBuilder::Build( const std::string& dataFile, World& world ) {
	TokenizeFile( dataFile );
	BuildSyntaxTree();
	BuildWorldTree();
}

void WorldBuilder::TokenizeFile( const std::string& dataFile ) {
	std::string fullName = ".\\Data\\";
	fullName += dataFile;
	std::ifstream file;

	file.open( fullName, std::fstream::in );
	if( !file.good() ) {
		std::cout << std::endl << "Error opening file <" << dataFile << ">" << std::endl;
	} else {
		file.seekg( 0, std::ios::end );
		size_t fileSize = file.tellg();
		file.seekg( 0, std::ios::beg );
		std::string fileString( fileSize, ' ' );
		file.read( &fileString[0], fileSize );
		file.close();
		tokenList = grammarTree->Tokenize( fileString );
	}
}

void WorldBuilder::BuildSyntaxTree() {
	while( tokenList.size() != 0 ) {
		Token_ptr nextToken = *tokenList.begin();
		tokenList.pop_front();
		if( nextToken == TOKEN( "OPEN_LIST" ) ) {
			AddList_r();
		} else {
			AddNextToken( nextToken );
		}
	}
}

void WorldBuilder::AddNextToken( Token_ptr nextToken ) {
	if( nextToken == TOKEN( "NAME" ) ) {
		ExpectingToken( TOKEN( "COLON" ) );
		Node_ptr newNode = std::make_shared<Node>( nextToken );
		Edge_ptr newEdge = std::make_shared<Edge>( (*tokenList.begin())->GetProperty(), newNode );
		syntaxTree->InsertChildAndMakeCurrent( newEdge );
		tokenList.pop_front();
	} else if( nextToken == TOKEN( "TYPE" ) ) {
		ExpectingToken( TOKEN( "COLON" ) );
		Node_ptr newNode = std::make_shared<Node>( nextToken );
		Edge_ptr newEdge = std::make_shared<Edge>( "", newNode );
		syntaxTree->InsertChildAndMakeCurrent( newEdge );
		tokenList.pop_front();
		nextToken = *tokenList.begin();
		newNode = std::make_shared<Node>( nextToken );
		newEdge = std::make_shared<Edge>( "", newNode );
		syntaxTree->InsertChild( newEdge );
		tokenList.pop_front();
		syntaxTree->MoveToParent();
	} else if( nextToken == TOKEN( "DESCRIPTION" )
			   || nextToken == TOKEN( "LONG_DESCRIPTION" )
			   || nextToken == TOKEN( "ALIAS" ) ) {
		ExpectingToken( TOKEN( "COLON" ) );
		Node_ptr newNode = std::make_shared<Node>( nextToken );
		Edge_ptr newEdge = std::make_shared<Edge>( (*tokenList.begin())->GetProperty(), newNode );
		syntaxTree->InsertChild( newEdge );
		tokenList.pop_front();
	} else if( nextToken == TOKEN( "EXITS" )
			   || nextToken == TOKEN( "CHILDREN" ) ) {
		ExpectingToken( TOKEN( "COLON" ) );
		Node_ptr newNode = std::make_shared<Node>( nextToken );
		Edge_ptr newEdge = std::make_shared<Edge>( "", newNode );
		syntaxTree->InsertChildAndMakeCurrent( newEdge );
	} else {
		std::cout << "Error parsing token list.  Unexpected token " << nextToken->GetProperty() << " " << std::endl;
	}
}

void WorldBuilder::AddList_r() {
	Token_ptr nextToken = *tokenList.begin();
	tokenList.pop_front();
	while( nextToken != TOKEN( "CLOSE_LIST" ) ) {
		if( nextToken == TOKEN( "LIST_SEP" ) ) {
			/* Do nothing.  List sepearators are only used to seperate other commands so tokens don't mush together*/
		} else if( nextToken == TOKEN( "OPEN_LIST" ) ) {
			AddList_r();
		} else {
			AddNextToken( nextToken );
		}
		nextToken = *tokenList.begin();
		tokenList.pop_front();
	}
	syntaxTree->MoveToParent();
}

bool WorldBuilder::ExpectingToken( Token_ptr expectedToken ) {
	Token_ptr nextToken = *tokenList.begin();
	if( nextToken == expectedToken ) {
		tokenList.pop_front();
		return true;
	} else {
		std::cout << "Error parsing token list.  Expecting " << expectedToken->GetProperty() << " and found " << nextToken->GetProperty() << std::endl;
		return false;
	}
}

void WorldBuilder::BuildWorldTree() {

}
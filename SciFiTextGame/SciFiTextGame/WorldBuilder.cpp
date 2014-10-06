#include "WorldBuilder.h"
#include"GrammarTree.h"
#include"SyntaxTree.h"
#include"Token.h"
#include"TokenPool.h"
#include"Edge.h"
#include"Node.h"
#include"GameObject.h"
#include"Room.h"
#include"Player.h"
#include"World.h"
#include<fstream>
#include<memory>
#include<string>

WorldBuilder::WorldBuilder() :
grammarTree( std::make_shared<GrammarTree>() ),
syntaxTree( std::make_shared<SyntaxTree>() ) {}

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
		size_t fileSize = static_cast<size_t>(file.tellg());
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
		nextToken = *tokenList.begin();
		tokenList.pop_front();
		newNode = std::make_shared<Node>( nextToken );
		newEdge = std::make_shared<Edge>( "", newNode );
		syntaxTree->InsertChild( newEdge );
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
	AddAllObjectsToWorld();
	CreateWorldTreeStructure();
}

void WorldBuilder::AddAllObjectsToWorld() {
	syntaxTree->Reset();
	std::string name, description, longDescription;
	Token_ptr type;
	std::vector<Edge_ptr> allObjects = syntaxTree->GetChildren();
	std::vector<Edge_ptr>::iterator allObjectsIter = allObjects.begin();
	while( allObjectsIter != allObjects.end() ) {
		name = (*allObjectsIter)->prefix;
		Node_ptr thisObject = (*allObjectsIter)->node;
		std::vector<Edge_ptr>::iterator propertyIter = thisObject->children.begin();
		while( propertyIter != thisObject->children.end() ) {
			Token_ptr propToken = (*propertyIter)->node->token;
			if( propToken == TOKEN( "TYPE" ) ) {
				type = (*propertyIter)->node->children[0]->node->token;
			} else if( propToken == TOKEN( "DESCRIPTION" ) ) {
				description = (*propertyIter)->prefix;
			} else if( propToken == TOKEN( "LONG_DESCRIPTION" ) ) {
				longDescription = (*propertyIter)->prefix;
			}
			++propertyIter;
		}
		AddObjectToWorld( type, name, description, longDescription );
		AddObjectToDictionary( name );
		type = nullptr;
		name = description = longDescription = "";
		++allObjectsIter;
	}
}

void WorldBuilder::AddObjectToWorld( Token_ptr type, const std::string& name, const std::string& description, const std::string& longDescription ) const {
	GameObject_ptr newObject;
	if( type == TOKEN( "ROOM" ) ) {
		newObject = std::make_shared<Room>( name, description, longDescription );
	} else if( type == TOKEN( "PLAYER" ) ) {
		newObject = std::make_shared<Player>( name, description, longDescription );
	} else if( type == TOKEN( "OBJECT" ) ) {
		newObject = std::make_shared<GameObject>( name, description, longDescription );
	} else {
		std::cout << "Error unknown object type" << std::endl;
	}
	TokenPool::Instance().NewToken( "NOUN", name );
	TokenPool::Instance().NewToken( "NOUN", description );
	World::Instance().AddObject( newObject );
}


void WorldBuilder::AddObjectToDictionary( const std::string& name ) const {
	Token_ptr newToken = TokenPool::Instance().NewToken( "NOUN", name );

	//TODO add new token to the grammar tree

}

void WorldBuilder::CreateWorldTreeStructure() {
	syntaxTree->Reset();
	Token_ptr type;
	std::string name;
	std::vector<Edge_ptr> allObjects = syntaxTree->GetChildren();
	std::vector<Edge_ptr>::iterator allObjectsIter = allObjects.begin();
	while( allObjectsIter != allObjects.end() ) {
		name = (*allObjectsIter)->prefix;
		Node_ptr thisObject = (*allObjectsIter)->node;
		std::vector<Edge_ptr>::iterator propertyIter = thisObject->children.begin();
		while( propertyIter != thisObject->children.end() ) {
			Token_ptr propToken = (*propertyIter)->node->token;
			if( propToken == TOKEN( "TYPE" ) ) {
				type = (*propertyIter)->node->children[0]->node->token;
				if( type != TOKEN( "ROOM" ) ) {
					break;
				}
			} else if( propToken == TOKEN( "EXITS" ) ) {
				GameObject_ptr currentRoom = World::Instance().GetObjectFromToken( TOKEN( name ) );
				Node_ptr exitsNode = (*propertyIter)->node;
				AddExitsToRoom( currentRoom, exitsNode );
			} else if( propToken == TOKEN( "CHILDREN" ) ) {

			}
			++propertyIter;
		}

		// FIXME AddObjectToDictionary( name );

		type = nullptr;
		name = "";
		++allObjectsIter;
	}
}

void WorldBuilder::AddExitsToRoom( GameObject_ptr room, Node_ptr exitsNode ) const {
	if( room->GetType() != GameObject_t::ROOM ) {
		return;
	}
	std::vector<Edge_ptr>::iterator exitIter = exitsNode->children.begin();
	while( exitIter != exitsNode->children.end() ) {
		Token_ptr exitToken = TOKEN( (*exitIter)->prefix );
		std::vector<Edge_ptr>::iterator aliasIter = (*exitIter)->node->children.begin();
		while( aliasIter != (*exitIter)->node->children.end() ) {
			std::string alias = (*aliasIter)->prefix;
			// FIXME AddObjectToDictionary( alias );
			std::shared_ptr<Room> thisRoom;
			thisRoom = std::dynamic_pointer_cast<Room>(room);
			thisRoom->AddExit( TOKEN(alias), thisRoom );
		}
	}
}
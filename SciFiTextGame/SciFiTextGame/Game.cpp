#include"Game.h"
#include"GrammarTree.h"
#include"Token.h"
#include"World.h"
#include"GameObject.h"
#include"Room.h"
#include"Player.h"
#include<memory>
#include<assert.h>

Game Game::instance;

Game::Game() :
grammarTree( std::make_shared<GrammarTree>() ),
gameOver( false ) {}

Game::~Game() {}

Game& Game::Instance() {
	return instance;
}

void Game::InitGrammarWithFile( std::string filename ) {
	grammarTree->AddDictionary( filename );
}

void Game::Play() {
	while( !gameOver ) {
		DisplayCurrentLocation();
		GetPlayerInput();
		if( tokenList.size() != 0 ) {
			ExecuteCommand();
		}
	}
}

void Game::AddNodeToGrammarTree( Token_ptr const token, const std::string& alias ) {
	grammarTree->AddNode( token, alias );
}

void Game::DisplayCurrentLocation() {
	assert( World::Instance().GetPlayer()->GetParent()->GetType() == GameObject_t::ROOM );
	Room_ptr room = std::dynamic_pointer_cast<Room>( World::Instance().GetPlayer()->GetParent() );
	std::cout << std::endl << std::endl << room->GetDescription( ) << std::endl;
	if( room->SeenBefore() ) {
		DisplaySimpleRoomContents( room );
	} else {
		room->SetSeenBefore( true );
		std::cout << std::endl << room->GetLongDescription();
		std::vector<GameObject_ptr> contents = room->GetChildren();
		for( auto contentsIter = contents.begin(); contentsIter != contents.end(); ++contentsIter ) {
			if( ( *contentsIter )->GetType() == GameObject_t::PLAYER ) {
				continue;
			}
			std::cout << ".  " << ( *contentsIter )->GetLongDescription();
		}
		std::cout << ".  " << std::endl;
	}
}

void Game::DisplaySimpleRoomContents( Room_ptr room ) {
	std::vector<GameObject_ptr> contents = room->GetChildren();
	for( auto contentsIter = contents.begin(); contentsIter != contents.end(); ++contentsIter ) {
		if( ( *contentsIter )->GetType() == GameObject_t::PLAYER ) {
			continue;
		}
		std::cout << ( *contentsIter )->GetDescription() << std::endl;
	}
}

void Game::GetPlayerInput() {
	std::string playerInput;
	std::cout << ">> ";
	std::getline( std::cin, playerInput );
	tokenList.clear();
	tokenList = grammarTree->Tokenize( playerInput );
}

void Game::ExecuteCommand() {
	Token_ptr verbToken;
	std::list<Token_ptr> nounList;
	while( tokenList.size() > 0 ) {
		if( tokenList.back()->GetType() == Token::TokenType::VERB ) {
			verbToken = tokenList.back();
		} else if( tokenList.back()->GetType() == Token::TokenType::NOUN ) {
			if( World::Instance().IsObjectLocal( tokenList.back() ) ) {
				nounList.push_back( tokenList.back() );
			} else {
				std::cout << "There is no " << World::Instance().GetObjectFromToken( tokenList.back() )->GetDescription() << " here." << std::endl;
				return;
			}
		}
		tokenList.pop_back();
	}
	std::string verb = verbToken->GetProperty();
	if( verb == "DROP" ) {
		DropCommand( nounList );
	} else if( verb == "EXAMINE" ) {
		ExamineCommand();
	} else if( verb == "GO" ) {
		GoCommand();
	} else if( verb == "INVENTORY" ) {
		InventoryCommand();
	} else if( verb == "LOOK" ) {
		LookCommand();
	} else if( verb == "OPEN" ) {
		OpenCommand();
	} else if( verb == "PUT" ) {
		PutCommand();
	} else if( verb == "QUIT" ) {
		QuitCommand();
	} else if( verb == "SCORE" ) {
		ScoreCommand();
	} else if( verb == "TAKE" ) {
		TakeCommand( nounList );
	} else if( verb == "TOUCH" ) {

	} else if( verb == "USE" ) {

	} else if( verb == "WALK" ) {

	} else {
		std::cout << "Error: Undefined Verb" << std::endl;
	}

}

void Game::Win() {
	ScoreCommand();
	std::cout << "You win!" << std::endl;
	gameOver = true;
}

void Game::Die() {
	ScoreCommand();
	std::cout << "You died." << std::endl;
	gameOver = true;
}

void Game::DropCommand( std::list<Token_ptr> nounList ) {
	for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
		GameObject_ptr object = World::Instance().GetObjectFromToken( *nounIter );
		std::cout << object->GetDescription() << " Dropped" << std::endl;
		World::Instance().MoveObject( object, World::Instance().GetPlayer()->GetParent() );
	}
}

void Game::ExamineCommand() {

}

void Game::GoCommand() {

}

void Game::InventoryCommand() {
	std::vector<GameObject_ptr> inventory = World::Instance().GetPlayer()->GetChildren();
	std::cout << "You are carrying:" << std::endl;
	if( inventory.size() == 0 ) {
		std::cout << "Nothing" << std::endl;
	}
	for( auto inventoryIter = inventory.begin(); inventoryIter != inventory.end(); ++inventoryIter ) {
		std::cout << ( *inventoryIter )->GetDescription() << std::endl;
	}
}

void Game::LookCommand() {

}

void Game::OpenCommand() {

}

void Game::PutCommand() {

}

void Game::QuitCommand() {
	ScoreCommand();
	gameOver = true;
}

void Game::ScoreCommand() {

}

void Game::TakeCommand( std::list<Token_ptr> nounList ) {
	for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
		GameObject_ptr object = World::Instance().GetObjectFromToken( *nounIter );
		if( !World::Instance().IsObjectLocal( *nounIter ) ) {
			std::cout << "There is no " << object->GetDescription() << " here." << std::endl;
		} else if( !object->CanBePickedUp() ) {
			std::cout << "You cannot pick that up." << std::endl;
		} else {
			std::cout << object->GetDescription() << " Taken" << std::endl;
			World::Instance().MoveObject( object, World::Instance().GetPlayer() );
		}
	}
}

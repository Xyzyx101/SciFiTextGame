#include"Game.h"
#include"GrammarTree.h"
#include"Token.h"
#include"TokenPool.h"
#include"World.h"
#include"GameObject.h"
#include"Room.h"
#include"Player.h"
#include<memory>
#include<assert.h>

Game Game::instance;

Game::Game() :
grammarTree( std::make_shared<GrammarTree>() ),
gameOver( false ),
MAX_SCORE( 100 ) {}

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
		if( score >= MAX_SCORE ) {
			Win();
		}
	}
}

void Game::AddNodeToGrammarTree( Token_ptr const token, const std::string& alias ) {
	grammarTree->AddNode( token, alias );
}

void Game::DisplayCurrentLocation() {
	assert( World::Instance().GetPlayer()->GetParent()->GetType() == GameObject_t::ROOM );
	Room_ptr room = std::dynamic_pointer_cast<Room>(World::Instance().GetPlayer()->GetParent());
	std::cout << std::endl << std::endl << "**  " << room->GetDescription() << "  **" << std::endl << std::endl;
	if( room->SeenBefore() ) {
		DisplaySimpleRoomContents( room );
	} else {
		room->SetSeenBefore( true );
		std::cout << room->GetLongDescription();
		std::vector<GameObject_ptr> contents = room->GetChildren();
		for( auto contentsIter = contents.begin(); contentsIter != contents.end(); ++contentsIter ) {
			if( (*contentsIter)->GetType() == GameObject_t::PLAYER ) {
				continue;
			}
			std::cout << "  " << (*contentsIter)->GetLongDescription();
		}
		std::cout << std::endl;
	}
}

void Game::DisplaySimpleRoomContents( Room_ptr room ) {
	std::vector<GameObject_ptr> contents = room->GetChildren();
	if( contents.size() == 0 ) {
		return;
	}
	std::cout << "There are items here:" << std::endl;
	for( auto contentsIter = contents.begin(); contentsIter != contents.end(); ++contentsIter ) {
		if( (*contentsIter)->GetType() == GameObject_t::PLAYER ) {
			continue;
		}
		std::cout << (*contentsIter)->GetDescription() << std::endl;
	}
}

void Game::GetPlayerInput() {
	std::string playerInput;
	std::cout << ">> ";
	std::getline( std::cin, playerInput );
	std::cout << std::endl;
	tokenList.clear();
	tokenList = grammarTree->Tokenize( playerInput );
}

void Game::ExecuteCommand() {
	Token_ptr verb = nullptr;
	std::list<Token_ptr> nounList;
	while( tokenList.size() > 0 ) {
		if( tokenList.back()->GetType() == Token::TokenType::VERB ) {
			verb = tokenList.back();
		} else if( tokenList.back()->GetType() == Token::TokenType::NOUN ) {
			if( World::Instance().IsObjectLocal( tokenList.back() ) ) {
				nounList.push_back( tokenList.back() );
			} else {
				std::cout << "There is no " << World::Instance().GetObjectFromToken( tokenList.back() )->GetDescription() << " here." << std::endl;
				return;
			}
		} else if( tokenList.back()->GetType() == Token::TokenType::EXIT ) {
			nounList.push_back( tokenList.back() );
		}
		tokenList.pop_back();
	}
	if( verb == nullptr &&
		nounList.front()->GetType() == Token::EXIT ) {
		HandleOneWordMovement( nounList.front() );
	} else if( verb == TOKEN( "DROP" ) ) {
		DropCommand( nounList );
	} else if( verb == TOKEN( "EXAMINE" ) ) {
		ExamineCommand( nounList );
	} else if( verb == TOKEN( "GO" ) ) {
		GoCommand( nounList );
	} else if( verb == TOKEN( "GET" ) ) {
		GetCommand( nounList );
	} else if( verb == TOKEN( "INVENTORY" ) ) {
		InventoryCommand();
	} else if( verb == TOKEN( "LOOK" ) ) {
		LookCommand();
	} else if( verb == TOKEN( "OPEN" ) ) {
		OpenCommand( nounList );
	} else if( verb == TOKEN( "QUIT" ) ) {
		QuitCommand();
	} else if( verb == TOKEN( "SCORE" ) ) {
		//ScoreCommand();
	} else if( verb == TOKEN( "USE" ) ) {
		//UseCommand();
	} else {
		std::cout << "I do not understand what you want me to do." << std::endl;
	}
}

void Game::HandleOneWordMovement( Token_ptr exit ) {
	tokenList.push_back( TOKEN( "GO" ) );
	if( exit == TOKEN( "N" ) ) {
		tokenList.push_back( TOKEN( "NORTH" ) );
	} else if( exit == TOKEN( "S" ) ) {
		tokenList.push_back( TOKEN( "SOUTH" ) );
	} else if( exit == TOKEN( "E" ) ) {
		tokenList.push_back( TOKEN( "EAST" ) );
	} else if( exit == TOKEN( "W" ) ) {
		tokenList.push_back( TOKEN( "WEST" ) );
	} else if( exit == TOKEN( "U" ) ) {
		tokenList.push_back( TOKEN( "UP" ) );
	} else if( exit == TOKEN( "D" ) ) {
		tokenList.push_back( TOKEN( "DOWN" ) );
	} else {
		tokenList.push_back( exit );
	}
	ExecuteCommand();
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

void Game::ExamineCommand( std::list<Token_ptr> nounList ) {
	for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
		GameObject_ptr object = World::Instance().GetObjectFromToken( *nounIter );
		std::cout << object->GetDetail() << std::endl;
	}
}

void Game::GetCommand( std::list<Token_ptr> nounList ) {
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

void Game::GoCommand( std::list<Token_ptr> nounList ) {
	if( nounList.size() > 1 ) {
		std::cout << "I do not understand." << std::endl;
	}
	Room_ptr currentRoom = std::dynamic_pointer_cast<Room>(World::Instance().GetPlayer()->GetParent());
	Room_ptr targetRoom = currentRoom->GetExit( nounList.front() );
	if( targetRoom == nullptr ) {
		std::cout << "There is no exit in that direction." << std::endl;
	} else {
		World::Instance().MoveObject( World::Instance().GetPlayer(), targetRoom );
	}
}

void Game::InventoryCommand() {
	std::vector<GameObject_ptr> inventory = World::Instance().GetPlayer()->GetChildren();
	std::cout << "You are carrying:" << std::endl;
	if( inventory.size() == 0 ) {
		std::cout << "Nothing" << std::endl;
	}
	for( auto inventoryIter = inventory.begin(); inventoryIter != inventory.end(); ++inventoryIter ) {
		std::cout << (*inventoryIter)->GetDescription() << std::endl;
	}
}

void Game::LookCommand() {
	assert( World::Instance().GetPlayer()->GetParent()->GetType() == GameObject_t::ROOM );
	Room_ptr currentRoom = std::dynamic_pointer_cast<Room>(World::Instance().GetPlayer()->GetParent());
	currentRoom->SetSeenBefore( false );
}

void Game::OpenCommand( std::list<Token_ptr> nounList ) {
	for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
		if( *nounIter == TOKEN( "LOCKER" ) ) {
			GameObject_ptr spaceSuit = World::Instance().GetObjectFromToken( TOKEN( "SPACE_SUIT" ) );
			World::Instance().MoveObject( spaceSuit, World::Instance().GetPlayer()->GetParent() );
		} else {
			std::cout << "You can't open that." << std::endl;
		}
	}
}

void Game::PutCommand() {

}

void Game::QuitCommand() {
	ScoreCommand();
	gameOver = true;
}

void Game::ScoreCommand() {
	std::cout << "You scored " << score << " out a possible " << 100 << "." << std::endl;
}

void Game::IncrementScore( int points ) {
	score += points;
}
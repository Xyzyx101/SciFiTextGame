#include"Game.h"
#include"GrammarTree.h"
#include"Token.h"
#include"TokenPool.h"
#include"World.h"
#include"GameObject.h"
#include"Room.h"
#include"Player.h"
#include"Cable.h"
#include"Instructions.h"
#include<memory>
#include<assert.h>

Game Game::instance;

Game::Game() :
grammarTree( std::make_shared<GrammarTree>() ),
gameOver( false ),
airlockOpen( false ),
MAX_SCORE( 100 ) {}

Game::~Game() {}

Game& Game::Instance() {
	return instance;
}

void Game::InitGrammarWithFile( std::string filename ) {
	grammarTree->AddDictionary( filename );
}

void Game::Play() {
	do {
		CheckScore();
		DisplayCurrentLocation();
		CheckSpecialConditions();
		if( gameOver ) { break; } // this is an extra check in case you die because of a special condition
		GetPlayerInput();
		if( tokenList.size() != 0 ) {
			ExecuteCommand();
		}
		if( score >= MAX_SCORE ) {
			Win();
		}
	} while( !gameOver );
}

void Game::AddNodeToGrammarTree( Token_ptr const token, const std::string& alias ) {
	grammarTree->AddNode( token, alias );
}

void Game::DisplayCurrentLocation() {
	assert( World::Instance().GetPlayer()->GetParent()->GetType() == GameObject_t::ROOM );
	Room_ptr room = std::dynamic_pointer_cast< Room >(World::Instance().GetPlayer()->GetParent());
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
	if( contents.size() == 1 ) {
		/* This displays nothing if there are no contents.  It checks for 1 and not 0 because the player is always in the current room. */
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
void Game::CheckSpecialConditions() {
	Token_ptr currentRoom = TOKEN( World::Instance().GetPlayer()->GetParent()->GetName() );
	if( currentRoom == TOKEN( "ON_THE_CLIFF" ) ) {
		std::cout << "You slip and fall to your death.  I guess that's why they call the cliffs impassable." << std::endl;
		Die();
	} else if( currentRoom == TOKEN( "NARROW_PATH" ) ) {
		Cable_ptr foCable = std::dynamic_pointer_cast< Cable >(World::Instance().GetObjectFromToken( TOKEN( "FO_CABLE" ) ));
		if( foCable->OneEndPlugged() && World::Instance().IsObjectLocal( TOKEN( "FO_CABLE" ) ) ) {
			std::cout << std::endl << "The fibre optic cable suddenly pulls tight for a second and then goes slack.  The end must have pulled out of the data port.  The cable is long but not that long." << std::endl;
			foCable->SetOneEnd( nullptr );
		}
		if( foCable->TheOtherEndPlugged() && World::Instance().IsObjectLocal( TOKEN( "FO_CABLE" ) ) ) {
			std::cout << std::endl << "The fibre optic cable suddenly pulls tight for a second and then goes slack.  The end must have pulled out of the antenna.  The cable is long but not that long." << std::endl;
			foCable->SetOneEnd( nullptr );
		}
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
	} else if( verb == TOKEN( "CLIMB" ) ) {
		ClimbCommand( nounList );
	} else if( verb == TOKEN( "DROP" ) ) {
		DropCommand( nounList );
	} else if( verb == TOKEN( "EXAMINE" ) ) {
		ExamineCommand( nounList );
	} else if( verb == TOKEN( "GO" ) ) {
		GoCommand( nounList );
	} else if( verb == TOKEN( "GET" ) ) {
		GetCommand( nounList );
	} else if( verb == TOKEN( "HELP" ) ) {
		HelpCommand();
	} else if( verb == TOKEN( "INVENTORY" ) ) {
		InventoryCommand();
	} else if( verb == TOKEN( "LOOK" ) ) {
		LookCommand();
	} else if( verb == TOKEN( "OPEN" ) ) {
		OpenCommand( nounList );
	} else if( verb == TOKEN( "QUIT" ) ) {
		QuitCommand();
	} else if( verb == TOKEN( "SCORE" ) ) {
		ScoreCommand();
	} else if( verb == TOKEN( "USE" ) ) {
		UseCommand( nounList );
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

void Game::ClimbCommand( std::list<Token_ptr> nounList ) {
	if( nounList.size() < 1 ) {
		std::cout << "I don't understand." << std::endl;
		return;
	}
	for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
		if( *nounIter == TOKEN( "CLIFF" ) || *nounIter == TOKEN( "RAVINE" ) ) {
			tokenList.push_back( TOKEN( "GO" ) );
			tokenList.push_back( TOKEN( "UP" ) );
			ExecuteCommand();
		} else {
			std::cout << "You can't climb that." << std::endl;
		}
	}
}

void Game::DropCommand( std::list<Token_ptr> nounList ) {
	if( nounList.size() < 1 ) {
		std::cout << "I don't understand." << std::endl;
		return;
	}
	for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
		GameObject_ptr object = World::Instance().GetObjectFromToken( *nounIter );
		std::cout << object->GetDescription() << " dropped." << std::endl;
		World::Instance().MoveObject( object, World::Instance().GetPlayer()->GetParent() );
	}
}

void Game::ExamineCommand( std::list<Token_ptr> nounList ) {
	if( nounList.size() < 1 ) {
		std::cout << "I don't understand." << std::endl;
		return;
	}
	for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
		GameObject_ptr object = World::Instance().GetObjectFromToken( *nounIter );
		std::cout << object->GetDetail() << std::endl;
	}
}

void Game::GetCommand( std::list<Token_ptr> nounList ) {
	if( nounList.size() < 1 ) {
		std::cout << "I don't understand." << std::endl;
		return;
	}
	for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
		GameObject_ptr object = World::Instance().GetObjectFromToken( *nounIter );
		if( !World::Instance().IsObjectLocal( *nounIter ) ) {
			std::cout << "There is no " << object->GetDescription() << " here." << std::endl;
		} else if( !object->CanBePickedUp() ) {
			std::cout << "You cannot pick that up." << std::endl;
		} else {
			std::cout << object->GetDescription() << " taken" << std::endl;
			World::Instance().MoveObject( object, World::Instance().GetPlayer() );
		}
	}
}

void Game::GoCommand( std::list<Token_ptr> nounList ) {
	if( nounList.size() != 1 ) {
		std::cout << "I do not understand." << std::endl;
		return;
	}
	Room_ptr currentRoom = std::dynamic_pointer_cast< Room >(World::Instance().GetPlayer()->GetParent());
	Room_ptr targetRoom = currentRoom->GetExit( nounList.front() );
	if( targetRoom == nullptr ) {
		std::cout << "There is no exit in that direction." << std::endl;
	} else {
		World::Instance().MoveObject( World::Instance().GetPlayer(), targetRoom );
	}
}

void Game::HelpCommand() {
	Instructions i;
	i.Display();
	LookCommand();
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
	Room_ptr currentRoom = std::dynamic_pointer_cast< Room >(World::Instance().GetPlayer()->GetParent());
	currentRoom->SetSeenBefore( false );
}

void Game::OpenCommand( std::list<Token_ptr> nounList ) {
	if( nounList.size() < 1 ) {
		std::cout << "I don't understand." << std::endl;
		return;
	}
	for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
		if( *nounIter == TOKEN( "LOCKER" ) ) {
			std::cout << "The locker contains a space suit." << std::endl;
			GameObject_ptr spaceSuit = World::Instance().GetObjectFromToken( TOKEN( "SPACE_SUIT" ) );
			World::Instance().MoveObject( spaceSuit, World::Instance().GetPlayer()->GetParent() );
			LookCommand();
		} else if( *nounIter == TOKEN( "ACCESS_HATCH" ) ) {
			GameObject_ptr hatch = World::Instance().GetObjectFromToken( *nounIter );
			hatch->SetDetail( "The hatch is open." );
			hatch->SetLongDescription( "There is an hatch built into the side of the ship here.  The hatch is open and reveals an empty storage bay." );
			std::cout << "You open the hatch and a large power conduit and a solar panel spills out." << std::endl;
			GameObject_ptr powerConduit = World::Instance().GetObjectFromToken( TOKEN( "POWER_CONDUIT" ) );
			World::Instance().MoveObject( powerConduit, World::Instance().GetPlayer()->GetParent() );
			GameObject_ptr solarPanel = World::Instance().GetObjectFromToken( TOKEN( "SOLAR_PANEL" ) );
			World::Instance().MoveObject( solarPanel, World::Instance().GetPlayer()->GetParent() );
			LookCommand();
		} else if( *nounIter == TOKEN( "AIRLOCK_DOOR" ) ) {
			std::cout << "You push and pull the door but it is sealed tight.  Nothing happens." << std::endl;
		} else {
			std::cout << "You can't open that." << std::endl;
		}
	}
}

void Game::QuitCommand() {
	ScoreCommand();
	gameOver = true;
}

void Game::ScoreCommand() {
	std::cout << "Your score is " << score << " out a possible " << 100 << "." << std::endl;
}

void Game::UseCommand( std::list<Token_ptr> nounList ) {
	if( nounList.size() < 1 ) {
		std::cout << "I don't understand." << std::endl;
		return;
	}
	if( nounList.size() == 1 ) {
		for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
			if( *nounIter == TOKEN( "LOCKER" ) ) {
				GameObject_ptr spaceSuit = World::Instance().GetObjectFromToken( TOKEN( "SPACE_SUIT" ) );
				World::Instance().MoveObject( spaceSuit, World::Instance().GetPlayer()->GetParent() );
				std::cout << "The locker contains a space suit." << std::endl;
			} else if( *nounIter == TOKEN( "COMPUTER" ) ) {
				UseComputer();
			} else if( *nounIter == TOKEN( "SPACE_SUIT" ) ) {
				GameObject_ptr spaceSuit = World::Instance().GetObjectFromToken( TOKEN( "SPACE_SUIT" ) );
				World::Instance().MoveObject( spaceSuit, World::Instance().GetPlayer() );
				World::Instance().GetPlayer()->SetWearingSpaceSuit( true );
				spaceSuit->SetDetail( "You are wearing the spacesuit.  " + spaceSuit->GetDetail() );
				std::cout << "You are now wearing the space suit." << std::endl;
			} else if( *nounIter == TOKEN( "HANDLE" ) ) {
				if( World::Instance().GetPlayer()->WearingSpaceSuit() ) {
					std::cout << "The airlock door moves slowly at first then flies open with a whoosh as all of the air gets sucked out of the ship." << std::endl;
					GameObject_ptr airlock = World::Instance().GetObjectFromToken( TOKEN( "AIRLOCK_DOOR" ) );
					airlock->SetLongDescription( "You can see rocks and rubble through the open door to the west." );
					airlock->SetDetail( "The door is open." );
					assert( World::Instance().GetPlayer()->GetParent()->GetType() == GameObject_t::ROOM );
					Room_ptr currentRoom = std::dynamic_pointer_cast< Room >(World::Instance().GetPlayer()->GetParent());
					Room_ptr outside = std::dynamic_pointer_cast< Room >(World::Instance().GetObjectFromToken( TOKEN( "OUTSIDE_SHIP" ) ));
					currentRoom->AddExit( TOKEN( "EAST" ), outside );
					airlockOpen = true;
				} else {
					std::cout << "You let all of the air out of the ship.  Good call." << std::endl;
					Die();
				}
			} else if( *nounIter == TOKEN( "AIRLOCK_DOOR" ) ) {
				std::cout << "You push and pull the door but it is sealed tight.  Nothing happens." << std::endl;
			} else if( *nounIter == TOKEN( "AIRLOCK_CONTROLS" ) ) {
				std::cout << "You push the buttons but the system seems to be broken.  Nothing happens." << std::endl;
			} else {
				std::cout << "You can't do that." << std::endl;
			}
		}
	} else if( nounList.size() == 2 ) {
		for( auto nounIter = nounList.begin(); nounIter != nounList.end(); ++nounIter ) {
			if( *nounIter == TOKEN( "FO_CABLE" ) ) {
				nounList.erase( nounIter );
				if( nounList.front() == TOKEN( "DATA_PORT" ) ) {
					std::cout << "You plug one end of the fibre optic cable into the data port on the side of the ship." << std::endl;
					Cable_ptr cable = std::dynamic_pointer_cast< Cable >(World::Instance().GetObjectFromToken( TOKEN( "FO_CABLE" ) ));
					cable->SetOneEnd( World::Instance().GetObjectFromToken( TOKEN( "DATA_PORT" ) ) );
					if( cable->BothEndsPlugged() ) {
						tokenList.push_back( TOKEN( "DROP" ) );
						tokenList.push_back( TOKEN( "FO_CABLE" ) );
						ExecuteCommand();
					}
				} else if( nounList.front() == TOKEN( "ANTENNA" ) ) {
					std::cout << "You plug one end of the fibre optic cable into salvaged antenna." << std::endl;
					Cable_ptr cable = std::dynamic_pointer_cast< Cable >(World::Instance().GetObjectFromToken( TOKEN( "FO_CABLE" ) ));
					cable->SetTheOtherEnd( World::Instance().GetObjectFromToken( TOKEN( "ANTENNA" ) ) );
					if( cable->BothEndsPlugged() ) {
						tokenList.push_back( TOKEN( "DROP" ) );
						tokenList.push_back( TOKEN( "FO_CABLE" ) );
						ExecuteCommand();
					}
				} else if( nounList.front() == TOKEN( "RAVINE" ) ) {
					std::cout << "The end of the cable disappears into the ravine." << std::endl;
					Cable_ptr cable = std::dynamic_pointer_cast< Cable >(World::Instance().GetObjectFromToken( TOKEN( "FO_CABLE" ) ));
					GameObject_ptr slopeRoom = World::Instance().GetObjectFromToken( TOKEN( "SLOPE" ) );
					World::Instance().MoveObject( cable, slopeRoom );
				} else {
					std::cout << "That does nothing." << std::endl;
				}
				break;
			} else if( *nounIter == TOKEN( "POWER_CONDUIT" ) ) {
				nounList.erase( nounIter );
				if( nounList.front() == TOKEN( "SOCKET" ) ) {
					std::cout << "You plug one end of the power conduit into the auxiliary power socket of the computer." << std::endl;
					Cable_ptr conduit = std::dynamic_pointer_cast< Cable >(World::Instance().GetObjectFromToken( TOKEN( "POWER_CONDUIT" ) ));
					conduit->SetOneEnd( World::Instance().GetObjectFromToken( TOKEN( "SOCKET" ) ) );
					if( conduit->BothEndsPlugged() ) {
						tokenList.push_back( TOKEN( "DROP" ) );
						tokenList.push_back( TOKEN( "POWER_CONDUIT" ) );
						ExecuteCommand();
					}
				} else if( nounList.front() == TOKEN( "SOLAR_PANEL" ) ) {
					std::cout << "You plug one end of the power conduit into the spare solar panel." << std::endl;
					Cable_ptr conduit = std::dynamic_pointer_cast< Cable >(World::Instance().GetObjectFromToken( TOKEN( "POWER_CONDUIT" ) ));
					conduit->SetTheOtherEnd( World::Instance().GetObjectFromToken( TOKEN( "SOLAR_PANEL" ) ) );
					if( conduit->BothEndsPlugged() ) {
						tokenList.push_back( TOKEN( "DROP" ) );
						tokenList.push_back( TOKEN( "POWER_CONDUIT" ) );
						ExecuteCommand();
					}
				} else {
					std::cout << "That does nothing." << std::endl;
				}
				break;
			}
		}
	} else {
		std::cout << "What now?" << std::endl;
	}
	LookCommand();
}

void Game::CheckScore() {
	int newScore = 0;
	if( World::Instance().GetPlayer()->WearingSpaceSuit() ) {
		newScore += 5;
	}
	if( airlockOpen ) {
		newScore += 10;
	}
	GameObject_ptr solarPanel = World::Instance().GetObjectFromToken( TOKEN( "SOLAR_PANEL" ) );
	GameObject_ptr crystalGrotto = World::Instance().GetObjectFromToken( TOKEN( "CRYSTAL_GROTTO" ) );
	if( solarPanel->GetParent() == crystalGrotto ) {
		newScore += 15;
		Cable_ptr conduit = std::dynamic_pointer_cast< Cable >(World::Instance().GetObjectFromToken( TOKEN( "POWER_CONDUIT" ) ));
		if( conduit->BothEndsPlugged() ) {
			newScore += 15;
		}
	}
	GameObject_ptr antenna = World::Instance().GetObjectFromToken( TOKEN( "ANTENNA" ) );
	GameObject_ptr ravineTop = World::Instance().GetObjectFromToken( TOKEN( "RAVINE_TOP" ) );
	if( antenna->GetParent() == ravineTop ) {
		newScore += 15;
		Cable_ptr foCable = std::dynamic_pointer_cast< Cable >(World::Instance().GetObjectFromToken( TOKEN( "FO_CABLE" ) ));
		if( foCable->BothEndsPlugged() ) {
			newScore += 15;
		}
	}
	if( newScore > score ) {
		std::cout << "You have gained " << newScore - score << " points." << std::endl;
		score = newScore;
		ScoreCommand();
	} else if( newScore < score ) {
		std::cout << "You have lost " << score - newScore << " points." << std::endl;
		score = newScore;
		ScoreCommand();
	} else {
		//do nothing if the score didn't change
	}
}

void Game::UseComputer() {
	GameObject_ptr solarPanel = World::Instance().GetObjectFromToken( TOKEN( "SOLAR_PANEL" ) );
	GameObject_ptr crystalGrotto = World::Instance().GetObjectFromToken( TOKEN( "CRYSTAL_GROTTO" ) );
	Cable_ptr conduit = std::dynamic_pointer_cast< Cable >(World::Instance().GetObjectFromToken( TOKEN( "POWER_CONDUIT" ) ));
	if( solarPanel->GetParent() == crystalGrotto
		&& conduit->BothEndsPlugged() ) {
		GameObject_ptr antenna = World::Instance().GetObjectFromToken( TOKEN( "ANTENNA" ) );
		GameObject_ptr ravineTop = World::Instance().GetObjectFromToken( TOKEN( "RAVINE_TOP" ) );
		Cable_ptr foCable = std::dynamic_pointer_cast< Cable >(World::Instance().GetObjectFromToken( TOKEN( "FO_CABLE" ) ));
		if( antenna->GetParent() == ravineTop
			&& foCable->BothEndsPlugged() ) {
			std::cout << "The computer works.  You start the communication program and try to contact your orbiter.  You get a response \"We are reading you.  We have the second landing vehicle ready for a rescue mission.  We will be landing near your position ASAP.\" " << std::endl;
			score = MAX_SCORE;
		} else {
			std::cout << "The computer works.  You start the communication program and try to contact your orbiter.  Nothing happens.  It seems like the walls of the ravine are blocking the signal." << std::endl;
		}
	} else {
		std::cout << "The computer has no power.  Nothing happens." << std::endl;
	}
}

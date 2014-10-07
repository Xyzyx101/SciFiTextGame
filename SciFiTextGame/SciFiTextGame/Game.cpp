#include"Game.h"
#include"GrammarTree.h"
#include"Token.h"
#include<memory>

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
	DisplayCurrentLocation();
	GetPlayerInput();
	ExecuteCommand();
}

void Game::AddNodeToGrammarTree( Token_ptr const token, const std::string& alias ) {
	grammarTree->AddNode( token, alias );
}

void Game::DisplayCurrentLocation() {

}

void Game::GetPlayerInput() {
	std::string playerInput;
	std::cout << ">> ";
	std::cin >> std::noskipws >> playerInput;
	tokenList = grammarTree->Tokenize( playerInput );
}

void Game::ExecuteCommand() {
	Token_ptr verbToken;
	std::list<Token_ptr> nounList;
	while( tokenList.size() > 0 ) {
		if( tokenList.back()->GetType() == Token::TokenType::VERB ) {
			verbToken = tokenList.back();
		} else if( tokenList.back()->GetType() == Token::TokenType::NOUN ) {
			nounList.push_back( tokenList.back() );
		}
		tokenList.pop_back();
	}
	std::string verb = verbToken->GetProperty();
	if( verb == "DROP" ) {
		DropCommand();
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
		TakeCommand();
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

void Game::DropCommand() {

}

void Game::ExamineCommand() {

}

void Game::GoCommand() {

}

void Game::InventoryCommand() {

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

void Game::TakeCommand() {

}

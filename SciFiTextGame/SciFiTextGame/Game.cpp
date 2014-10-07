#include "Game.h"
#include"GrammarTree.h"
#include<memory>

Game Game::instance;

Game::Game() :
grammarTree( std::make_shared<GrammarTree>() ) {}

Game::~Game() {}

Game& Game::Instance() {
	return instance;
}

void Game::InitGrammarWithFile( std::string filename ) {
	grammarTree->AddDictionary( filename );
}

void Game::Play() {
	DisplayCurrentLocation( );
	GetPlayerInput();
	ExecuteCommand();
}

void Game::AddNodeToGrammarTree( Token_ptr const token, const std::string& alias ) {
	grammarTree->AddNode( token, alias );
}

void Game::DisplayCurrentLocation() {

}

void Game::GetPlayerInput() {

}

void Game::ExecuteCommand() {

}

void Game::Win() {

}
void Game::Die() {

}
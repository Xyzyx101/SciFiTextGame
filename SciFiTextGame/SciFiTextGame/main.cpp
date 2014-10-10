#include"CommonTypes.h"
#include"GrammarTree.h"
#include"TokenPool.h"
#include"WorldBuilder.h"
#include"World.h"
#include"Game.h"
#include"TitleScreen.h"
#include <iostream>

int main() {
	TitleScreen ts;
	ts.Display();
	WorldBuilder* wb = new WorldBuilder;
	wb->InitGrammarWithFile( "importer.dict" );
	wb->Build( "world.data", World::Instance() );
	delete wb;
	Game::Instance().InitGrammarWithFile( "verbs.dict" );
	Game::Instance().Play();

	system( "pause" );

	return 0;
}

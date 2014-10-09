#pragma once
#include<string>
#include<memory>
#include<list>
#include"CommonTypes.h"

class GrammarTree;

class Game {
public:
	static Game& Instance();
	~Game();
	void InitGrammarWithFile( std::string filename );
	void AddNodeToGrammarTree( Token_ptr const token, const std::string& alias );
	void Play();
private:
	static Game instance;
	Game();
	void DisplayCurrentLocation();
	void DisplaySimpleRoomContents( Room_ptr room );
	void GetPlayerInput();
	void ExecuteCommand();
	void HandleOneWordMovement( Token_ptr exit );
	void Win();
	void Die();
	void IncrementScore( int scoreIncrease );
	void GetScore() const;
	void DropCommand( std::list<Token_ptr> nounList );
	void ExamineCommand( std::list<Token_ptr> nounList );
	void GetCommand( std::list<Token_ptr> nounList );
	void GoCommand( std::list<Token_ptr> nounList );
	void InventoryCommand();
	void LookCommand();
	void OpenCommand( std::list<Token_ptr> nounList );
	void QuitCommand();
	void ScoreCommand();
	void TakeCommand( std::list<Token_ptr> nounList );
	void UseCommand( std::list<Token_ptr> nounList );
	std::shared_ptr<GrammarTree> grammarTree;
	std::list<Token_ptr> tokenList;
	bool gameOver;
	const int							MAX_SCORE;
	int									score;
};


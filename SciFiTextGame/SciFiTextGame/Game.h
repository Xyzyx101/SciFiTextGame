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
	void Win();
	void Die();
	void IncrementScore( int scoreIncrease );
	void GetScore() const;
	void DropCommand();
	void ExamineCommand();
	void GoCommand();
	void InventoryCommand();
	void LookCommand();
	void OpenCommand();
	void PutCommand();
	void QuitCommand();
	void ScoreCommand();
	void TakeCommand();
	std::shared_ptr<GrammarTree> grammarTree;
	std::list<Token_ptr> tokenList;
	bool gameOver;
	int									score;
	
};


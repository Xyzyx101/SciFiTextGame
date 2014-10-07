#pragma once
#include<string>
#include<memory>

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
	void GetPlayerInput();
	void ExecuteCommand();
	void Win();
	void Die();
	std::shared_ptr<GrammarTree> grammarTree;
};


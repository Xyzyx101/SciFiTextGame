#pragma once
#include<string>
#include<memory>
#include<list>
#include"CommonTypes.h"

class GrammarTree;

/* All of the actual game code is in this class. The class is a singleton. */
class Game {
public:
	static Game& Instance();
	~Game();
	/* Loads the initial dict file containing all of the game commands. */
	void						InitGrammarWithFile( std::string filename );

	/* Used by WorldBuilder to add Nouns representing game objects and aliases */
	void AddNodeToGrammarTree( Token_ptr const token, const std::string& alias );

	/* Starts the game. */
	void Play();
private:
	static Game						instance;
	Game();

	/* Displays the longDescription of the current room and the all of the
	current rooms contents. */
	void							DisplayCurrentLocation();

	/* A simplified version of DsiplayCurrentLocation used when the player has seen
	the room before. */
	void							DisplaySimpleRoomContents( Room_ptr room );

	/* Handles a few events that happen withour player input. */
	void							CheckSpecialConditions();

	/* Get input from the player and interprets the input as tokens.  the tokens are
	stored in tokenList. */
	void							GetPlayerInput();

	/* Searches the tokenList for a verb to figure out which command to execute and passes
	the nouns to the command if appropriate. */
	void							ExecuteCommand();

	/* Handles one letter edge cases like n, s, i, and x.*/
	void 							HandleOneWordMovement( Token_ptr exit );

	/* Win the game and exit. */
	void 							Win();

	/* Kill the playerand end the game*/
	void 							Die();

	/* Checks for any change to the score and updates the player and score variable. */
	void 							CheckScore();

	/* Use computer is factored out of the main UseCommand to avoid clutter because
	it is long.*/
	void 							UseComputer();

	/* All of the _Command functions are the code executed when the player uses each verb. */
	void 							ClimbCommand( std::list<Token_ptr> nounList );
	void 							DropCommand( std::list<Token_ptr> nounList );
	void 							ExamineCommand( std::list<Token_ptr> nounList );
	void 							GetCommand( std::list<Token_ptr> nounList );
	void 							GoCommand( std::list<Token_ptr> nounList );
	void 							HelpCommand();
	void 							InventoryCommand();
	void							LookCommand();
	void 							OpenCommand( std::list<Token_ptr> nounList );
	void 							QuitCommand();
	void 							ScoreCommand();
	void 							TakeCommand( std::list<Token_ptr> nounList );
	void 							UseCommand( std::list<Token_ptr> nounList );

	/* Grammar tree hold all of the verbs and nouns that may be used by the player. */
	std::shared_ptr<GrammarTree>	grammarTree;

	/* tokenList holds the token interpreted from player input. */
	std::list<Token_ptr>			tokenList;

	bool							gameOver;
	bool							airlockOpen;
	const int						MAX_SCORE;
	int								score;
};


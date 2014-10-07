#pragma once
#include"GameObject.h"
#include"CommonTypes.h"
#include<map>

class Token;
class GameObject;
class Player;

/* World is the root of a tree made up of all GameObjects. */
class World {
public:
	/* Gets a reference to the one instance of a game world */
	static World&							Instance();

	~World();

	/* Searches the gameworld for an instance of the object */
	GameObject_ptr							GetObjectFromName( std::string name ) const;

	/* Searches the gameworld for an instance of the object */
	GameObject_ptr							GetObjectFromToken( Token_ptr object ) const;

	/* Searches the game world for a game object.  Returns null if the game
	object is not in the current room or player inventory */
	GameObject_ptr							GetLocalObject( Token_ptr object ) const;

	/* Gets a pointer to the player */
	Player_ptr								GetPlayer() const;

	/* Adds an object to the world at the root of the world tree */
	void									AddObject( GameObject_ptr object );

	/* Adds an object to the world at the location passed to the function */
	void									AddObject( GameObject_ptr object, GameObject_ptr newParent );

	/* Moves an object from its current location to the location passed in */
	void									MoveObject( GameObject_ptr object, GameObject_ptr newParent );
private:
	void									AddObjectToMap( GameObject_ptr object );
	static World instance;
	World();
	std::vector<GameObject_ptr>				children;
	Player_ptr								player;
	std::map<Token_ptr, GameObject_ptr>		allObjects;
};


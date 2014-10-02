#pragma once
#include"GameObject.h"

/* World is the root of a tree made up of all GameObjects. */

class World {
public:
	/* Gets a reference to the one instance of a game world */
	static World&					Instance();

	~World();

	/* Searches the gameworld for an instance of the onject */
	GameObject_ptr					GetObjectFromName(std::string name) const;

	/* Searches the game world for a game object.  Returns null if the game
	object is not in the current room or player inventory */
	GameObject_ptr					GetLocalObject(std::string name) const;


	/* Gets a pointer to the player */
	GameObject_ptr					GetPlayer() const;

	/* Adds an object to the world at the location passed to the function */
	void							AddObject(GameObject_ptr);

	/* Moves an object from its current location to the location passed in */
	bool							MoveObject(GameObject_ptr object, GameObject_ptr newParent);
private:
	static World instance;
	World( );
	std::vector<GameObject_ptr>		children;
	GameObject_ptr					player;
};


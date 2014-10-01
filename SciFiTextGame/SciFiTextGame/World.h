#pragma once
#include"GameObject.h"

/* World is the root of a tree made up of all GameObjects. */

class World {
public:
	static World& Instance();
	~World();
	GameObject_ptr GetObjectFromName(std::string name) const;
	GameObject_ptr GetLocalObject(std::string name) const;
	GameObject_ptr GetPlayer() const;
	void AddObject(GameObject_ptr);
	bool MoveObject(GameObject_ptr object, GameObject_ptr newParent);
private:
	static World instance;
	World( );
	std::vector<GameObject_ptr> children;
	GameObject_ptr player;
};


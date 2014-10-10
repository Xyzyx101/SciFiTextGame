#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	Player( std::string name, std::string description, std::string longDescription );
	virtual ~Player();

	/* Runtime type query. */
	virtual inline GameObject_t			GetType() { return PLAYER; };

	/* Player can never be picked but could be queried by game code because all objects in the tree
	are stored as game objects. */
	virtual inline bool					CanBePickedUp() { return false; };

	void								SetWearingSpaceSuit( bool newValue ) { wearingSpaceSuit = newValue; };
	inline bool							WearingSpaceSuit() const { return wearingSpaceSuit; };
private:
	bool								wearingSpaceSuit;
};


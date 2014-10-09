#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	Player( std::string name, std::string description, std::string longDescription );
	virtual ~Player();
	virtual inline GameObject_t			GetType() { return PLAYER; };
	virtual inline bool					CanBePickedUp() { return false; };
	void								SetWearingSpaceSuit( bool newValue ) { wearingSpaceSuit = newValue; };
	inline bool							WearingSpaceSuit() const { return wearingSpaceSuit; };
private:
	bool								wearingSpaceSuit;
};


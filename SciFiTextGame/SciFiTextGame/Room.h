#pragma once
#include"GameObject.h"
#include"CommonTypes.h"
#include<map>

class Room : public GameObject {
public:
	Room( std::string name, std::string description, std::string longDescription );
	virtual ~Room();

	/* Runtime type query. */
	virtual inline GameObject_t				GetType() { return ROOM; };

	/* Exits are stored in a map with the alias as the key and a pointer to the room
	as the value.  e.g. 'east' would be the key and the value would be a pointer to
	the room you would get to when you go east from theis room.*/
	Room_ptr								GetExit( Token_ptr alias ) const;
	void									AddExit( Token_ptr alias, Room_ptr newExit );

	/* Rooms can never be picked up but may be attempted by the player. */
	virtual inline bool						CanBePickedUp() { return false; };

	/* This boolean is set so that the full text is not displayed everytime the player
	walks through a room. */
	inline bool								SeenBefore() { return seenBefore; };
	inline void								SetSeenBefore( bool value ) { seenBefore = value; };
private:
	std::map<Token_ptr, Room_ptr>			exits;
	bool									seenBefore;
};


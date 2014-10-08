#pragma once
#include"GameObject.h"
#include"CommonTypes.h"
#include<map>

class Room : public GameObject {
public:
	Room( std::string name, std::string description, std::string longDescription );
	virtual ~Room();
	Room_ptr								GetExit( Token_ptr alias ) const;
	void									AddExit( Token_ptr alias, Room_ptr newExit );
	virtual inline GameObject_t				GetType() { return ROOM; };
	virtual inline bool						CanBePickedUp() { return false; };
	inline bool								SeenBefore() { return seenBefore; };
	inline void								SetSeenBefore( bool value ) { seenBefore = value; };
private:
	std::map<Token_ptr, Room_ptr>			exits;
	bool									seenBefore;
};


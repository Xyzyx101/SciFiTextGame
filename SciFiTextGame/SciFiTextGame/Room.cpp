#include "Room.h"

Room::Room( std::string name, std::string description, std::string longDescription )
: GameObject( name, description, longDescription ),
seenBefore( false ) {}

Room::~Room() {}

Room_ptr Room::GetExit( Token_ptr alias ) const {
	auto foundRoom = exits.find( alias );
	if( foundRoom == exits.end() ) {
		return nullptr;
	} else {
		return foundRoom->second;
	}
}

void Room::AddExit( Token_ptr alias, Room_ptr newExit ) {
	exits.insert( std::pair<Token_ptr, Room_ptr>( alias, newExit ) );
}
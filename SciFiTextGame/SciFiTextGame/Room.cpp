#include "Room.h"


Room::Room(std::string name, GameObject_ptr parent, std::string description, std::string longDescription) 
	: GameObject(name, parent, description, longDescription)
{}

Room::~Room() {}

GameObject_ptr Room::GetExit(std::string name) const {
	auto exitIter = exits.begin();
	while( exitIter != exits.end() ) {
		if( (*exitIter)->GetName() == name ) {
			return *exitIter;
		}
	}
	return nullptr;
}

void Room::AddExit(GameObject_ptr newExit) {
	exits.push_back(newExit);
}
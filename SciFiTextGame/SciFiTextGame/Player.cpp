#include "Player.h"


Player::Player( std::string name, std::string description, std::string longDescription )
: GameObject( name, description, longDescription ),
wearingSpaceSuit( false ) {}

Player::~Player() {}

#include "Player.h"


Player::Player(std::string name, GameObject_ptr parent, std::string description, std::string longDescription)
: GameObject(name, parent, description, longDescription) {}

Player::~Player() {}

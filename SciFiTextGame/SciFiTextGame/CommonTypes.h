#include<memory>

class Token;
typedef	std::shared_ptr<const Token>	Token_ptr;

class Node;
typedef	std::shared_ptr<Node>			Node_ptr;

class Edge;
typedef	std::shared_ptr<Edge>			Edge_ptr;

class GameObject;
typedef std::shared_ptr<GameObject>		GameObject_ptr;

class Room;
typedef std::shared_ptr<Room>			Room_ptr;

class Player;
typedef std::shared_ptr<Player>			Player_ptr;

class Cable;
typedef std::shared_ptr<Cable>			Cable_ptr;
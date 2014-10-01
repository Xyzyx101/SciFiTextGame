#pragma once
#include<string>

class GrammarTree;
class World;

class WorldBuilder {
public:
	WorldBuilder();
	~WorldBuilder();
	void InitWithFile(const std::string& filename);
	void BuildWorld(const std::string&, World& world) const;
private:
	GrammarTree* grammarTree;
};


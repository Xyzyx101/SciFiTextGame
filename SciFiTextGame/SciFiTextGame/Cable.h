#pragma once
#include "GameObject.h"
class Cable :
	public GameObject {
public:
	Cable( std::string name, std::string description, std::string longDescription, std::string detail );
	virtual ~Cable();
	virtual const std::string		GetLongDescription() const;
	virtual const std::string		GetDetail() const;
	void							SetOneEnd(GameObject_ptr);
	void							SetTheOtherEnd(GameObject_ptr);
	bool							OneEndPlugged( );
	bool							BothEndsPlugged();
private:
	GameObject_ptr					oneEnd;
	GameObject_ptr					theOtherEnd;
};


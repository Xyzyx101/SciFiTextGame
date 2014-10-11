#pragma once
#include "GameObject.h"

/* Cable objects represent cables and wires that can be plugged into two other objects
at the same time.*/
class Cable : public GameObject {
public:
	Cable( std::string name, std::string description, std::string longDescription, std::string detail );
	virtual ~Cable();

	/* Runtime type query. */
	virtual inline GameObject_t			GetType() { return CABLE; };

	/* Description and detail dynamically update to reflect the status of being plugged in.*/
	virtual const std::string			GetLongDescription() const;
	virtual const std::string			GetDetail() const;

	/* The ends can be set to GameObjects or nullptr.  nullptr means not plugged in.*/
	void								SetOneEnd( GameObject_ptr );
	void								SetTheOtherEnd( GameObject_ptr );

	bool								OneEndPlugged();
	bool								TheOtherEndPlugged();
	bool								BothEndsPlugged();
private:
	GameObject_ptr						oneEnd;
	GameObject_ptr						theOtherEnd;
};


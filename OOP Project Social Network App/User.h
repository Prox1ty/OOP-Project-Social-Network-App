#pragma once
#include "UniqueElement.h"

class Page;

class User : public UniqueElement {
	const char* name;
	User** friendList; // storing pointers to users to save memory
	int friends;
	Page** likedPages; // same here
	int lP;

public:
	// constructors
	User();
	User(const char* id, const char* name, int friends, int lP);
	// copy constructor
	User(const User& other);

	// destructor
	~User();

	// rest of the functions i'll add later
};

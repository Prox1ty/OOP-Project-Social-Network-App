#pragma once
#include "UniqueElement.h"

class User;
class Post;

class Page : public UniqueElement {
	User* owner; // pointer to owner
	Post** sharedPosts;
	int likes;

public:
	// constructors
	Page();
	Page(const char* id, User* o, int likes = 0);

	// destructor
	~Page();
};
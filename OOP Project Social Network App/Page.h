#pragma once
#include "Author.h"

class User;
class Post;

class Page : public Author {
	const char* title;
	User* owner; // pointer to owner
	Post** sharedPosts;
	int postCount;
	int likes;

public:
	// constructors
	Page();
	Page(const char* id, const char* title, User* o, int likes = 0);

	// destructor
	~Page();

	const char* getName() const override;          
};
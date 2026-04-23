#pragma once
#include "UniqueElement.h"
#include "Author.h"

class Date;
class Page;
class Post;
class User : public Author {
	const char* name;
	User** friendList; // storing pointers to users to save memory
	int friends;
	Page** likedPages; // same here
	int lP;

	Post** timeline; // for user's own posts
	int posts;

public:
	// constructors
	User();
	User(const char* id, const char* name, int friends, int lP);
	// copy constructor
	User(const User& other);

	// destructor
	~User();

	// user functions
	const char* getName() const override;
	void viewFriendList() const;
	void viewTimeLine(const Date& currentDate) const;
	void addComment(istream& in, Post* post, Date& currDate); // requires a text, an author and a pointer to the post


	// rest of the functions i'll add later
};

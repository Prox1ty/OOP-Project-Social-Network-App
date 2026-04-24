#include "User.h"
#include "Post.h"
#include "Comment.h"
#include "Date.h"
#include "stringFunctions.h"
#include <stdexcept>
#include <iostream>
using namespace std;

User::User() : Author(), name(nullptr), friendList(nullptr), likedPages(nullptr), friends(0), lP(0), timeline(nullptr) {}

User::User(const char* id, const char* name, int friends, int lP) 
	: Author(id), name(nullptr), friendList(nullptr), likedPages(nullptr) {
	
	if (name) {
		int len = getLength(name);
		char* nm = new char[len + 1];
		copyString(nm, name);
		this->name = nm;
	}
	else {
		this->name = nullptr;
	}
	// friendList and likedPages are nullptrs by default
};

// copy constructor
User::User(const User& other) : Author() {
	// shallow copying pointer since id doesn't get destroyed when user is destroyed.
	id = other.id;

	if (other.name) {
		int len = getLength(other.name);
		char* nm = new char[len + 1];
		copyString(nm, other.name);
		this->name = nm;
	}
	else {
		this->name = nullptr;
	}

	// friends
	friends = other.friends;
	friendList = nullptr;
	// copying pointers
	
	if (other.friends > 0) {
		friendList = new User * [friends];
		for (int i = 0; i < other.friends; i++) {
			friendList[i] = other.friendList[i];
			// ensures we have pointers to user objects even if the original pointers are deleted.
			// consider a destructor execution deleting all the pointers pointing to the user objects, if we delete the friendList array, we delete all pointers
			// within. Thus leaving us with no pointers pointing to the object now. This isn't a memory leak per se but we still need to copy the pointers
			// since we're storing pointers in the friendList array
		}
	}
	// liked pages

	lP = other.lP;
	likedPages = nullptr; 

	if (other.lP > 0) {
		likedPages = new Page * [lP];
		for (int i = 0; i < lP; i++) {
			likedPages[i] = other.likedPages[i];
		}
	}
}

// destructor
User::~User() {
	delete[] name;
	delete[] friendList; // no memory leak because they just store pointers, not heap objects
	delete[] likedPages;
	// not deleting id because its not owned by User (managed by UniqueElement static array).
}

const char* User::getName() const {
	return this->name;
}

void User::viewFriendList() const {
	for (int i = 0; i < friends; i++) {
		cout << friendList[i]->getName() << '\n';
	}
}

void User::viewTimeLine(const Date& currDate) const {
	for (int i = 0; i < posts; i++) {
		if (timeline[i]->isPostRecent(currDate)) {
			timeline[i]->displayPost();
		}
	}
}

void User::likePost(Post* p) {
	// ensures max likes are 10
	if (p->countLikes == 10) return;

	int noOfLikes = p->countLikes;
	User** newLikedBy = new User* [noOfLikes + 1];

	for (int i = 0; i < noOfLikes; i++) {
		newLikedBy[i] = p->likedBy[i];
	}
	newLikedBy[noOfLikes] = this;
	delete[] p->likedBy;
	p->likedBy = newLikedBy;
	p->countLikes = noOfLikes + 1;
}

void User::addPost()
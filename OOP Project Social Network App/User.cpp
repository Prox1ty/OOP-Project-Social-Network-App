#include "User.h"
#include "Post.h"
#include "Page.h"
#include "Comment.h"
#include "Date.h"
#include "stringFunctions.h"
#include <stdexcept>
#include <iostream>
using namespace std;

User::User() : Author(), name(nullptr), friendList(nullptr), likedPages(nullptr), friends(0), lP(0), memories(0), memArr(nullptr) {}
//removed timeline from default cuz error was being thrown. i believe cuz compiler said inaccessible so belongs to author

User::User(char* id, char* name, int friends, int lP) 
	: Author(id), name(nullptr), friendList(nullptr), likedPages(nullptr), friends(0), lP(0), memories(0), memArr(nullptr) {
	
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
User::User(const User& other) : Author(other.id) {
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

	// memories
	memories = other.memories;
	memArr = nullptr;

	if (other.memories > 0) {
		memArr = new Post * [memories];
		for (int i = 0; i < memories; i++) {
			memArr[i] = other.memArr[i];
		}
	}
}

// destructor
User::~User() {
	delete[] name;
	delete[] friendList; // no memory leak because they just store pointers, not heap objects
	delete[] likedPages;
	delete[] memArr;
	// not deleting id because its not owned by User (managed by UniqueElement static array).
}

const char* User::getName() const {
	return this->name;
}

void User::viewFriendList() const {
	if (!friendList || friends == 0) {
		cout << "No friends yet. \n";
		return;
	}
	for (int i = 0; i < friends; i++) {
		if (friendList[i])
		cout << friendList[i]->getId() << " - " << friendList[i]->getName() << '\n';
	}
}



void User::likePost(Post* p) {
	// ensures max likes are 10
	if (p->addLike(this)) {
		cout << "Post liked!\n";
	}
	else {
		cout << "Error. Post has reached max number of likes\n";
	}
}

//added viewHome
void User::viewHome(const Date& currDate) const {
	cout << (name ? name : "Unknown") << "- Home Page\n";

	// posts from friends
	bool anyFriendPosts = false;
	if (friendList != nullptr) {
		for (int i = 0; i < friends; i++) {
			if (friendList[i] == nullptr) continue;
			for (int j = 0; j < friendList[i]->posts; j++) {
				if (friendList[i]->timeline[j]->isPostRecent(currDate)) {
					friendList[i]->timeline[j]->displayPost();
					anyFriendPosts = true;
				}
			}
		}
	}
	if (!anyFriendPosts) cout << "No recent posts from friends.\n";

	//TO DO: print posts from liked pages correctly
	// posts from liked pages
	bool anyPagePosts = false;
	if (likedPages != nullptr) {
		for (int i = 0; i < lP; i++) {
			if (likedPages[i] != nullptr) {
				for (int j = 0; j < likedPages[i]->countPosts(); j++) {
					Post** sP = likedPages[i]->getSharedPosts();
					if (sP != nullptr && sP[j] != nullptr) {
						if (sP[j]->isPostRecent(currDate)) {
							sP[j]->displayPost();
							anyPagePosts = true;
						}
					}
				}
			}
		}
	}
	if (!anyPagePosts) cout << "No recent posts from liked pages.\n";
}

void User::addFriend(User* u) {
	User** newFriendList = new User * [friends + 1];
	for (int i = 0; i < friends; i++) {
		newFriendList[i] = friendList[i];
	}
	delete[] friendList;
	newFriendList[friends] = u;
	friendList = newFriendList;
	friends++;
}

void User::likePage(Page* p) {
	Page** newLikedPages = new Page * [lP + 1];
	for (int i = 0; i < lP; i++) newLikedPages[i] = likedPages[i];

	newLikedPages[lP] = p;
	delete[] likedPages;
	likedPages = newLikedPages;
	lP++;
}

void User::viewLikedPages() const {
	for (int i = 0; i < lP; i++) {
		cout << likedPages[i]->getId() << " - " << likedPages[i]->getName() << endl;
	}
}

void User::addMemory(Post* m) {
	Post** newMemArr = new Post * [memories + 1];
	for (int i = 0; i < memories; i++) newMemArr[i] = memArr[i];
	newMemArr[memories] = m;
	delete[] memArr;
	memArr = newMemArr;
	memories++;
}

void User::viewMemories() const {
	for (int i = 0; i < memories; i++) {
		memArr[i]->displayPost();
	}
}
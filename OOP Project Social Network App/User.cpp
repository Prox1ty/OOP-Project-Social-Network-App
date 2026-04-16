#include "User.h"
#include "stringFunctions.h"
#include <stdexcept>


char** User::existingIds = nullptr;
int User::IdCnt = 0;
int User::IdCap = 0;

// static functions defs
bool User::doesIdExist(const char* u_id) {
	if (u_id == nullptr) return false;

	for (int i = 0; i < IdCnt; i++) {
		if (areEqual(existingIds[i], u_id)) return true;
	}

	return false;
}

void User::resize() {
	if (IdCnt < IdCap) return;

	int newCap = (IdCap == 0) ? 4 : IdCap * 2;
	char** newArr = new char* [newCap];
	// shallow copy the pointers
	for (int i = 0; i < IdCnt; i++) newArr[i] = existingIds[i];
	delete[] existingIds;
	existingIds = newArr;
	IdCap = newCap;
}

// returns pointer to stored Id. The Id itself is stored by the static array existingIds
// tried to make User Ids unique to an extent
const char* User::AddId(const char* newId) {
	if (newId == nullptr) return nullptr;
	
	for (int i = 0; i < IdCnt; i++) {
		if (areEqual(existingIds[i], newId)) {
			throw std::runtime_error("Duplicate Id passed\n");
			return nullptr;
		}
	}

	resize();
	int len = getLength(newId);
	existingIds[IdCnt] = new char [len + 1];
	copyString(existingIds[IdCnt], newId);
	IdCnt++;
	return existingIds[IdCnt - 1];
}

void User::freeIds() {
	if (existingIds) {
		for (int i = 0; i < IdCnt; i++) {
			delete[] existingIds[i];
			existingIds[i] = nullptr;
		}
		delete[] existingIds;
		existingIds = nullptr;
	}
	IdCnt = 0;
	IdCap = 0;
}

User::User() : id(nullptr), name(nullptr), friendList(nullptr), likedPages(nullptr), friends(0), lP(0) {}

User::User(const char* id, const char* name, int friends, int lP) 
	: id(nullptr), name(nullptr), friendList(nullptr), likedPages(nullptr) {
	
	this->id = AddId(id);

	if (name) {
		int len = getLength(name);
		char* nm = new char[len + 1];
		copyString(nm, name);
		this->name = nm;
	}
	else {
		name = nullptr;
	}
	// friendList and likedPages are nullptrs by default
};

// copy constructor
User::User(const User& other) {
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
	// not deleting id because its not owned by User.
}
#pragma once

class Page;

class User {
	static char** existingIds;
	static int IdCnt;
	static int IdCap;

	const char* id;
	const char* name;
	User** friendList; // storing pointers to users to save memory
	int friends;
	Page** likedPages; // same here
	int lP;

public:
	// static funcs
	static void resize();
	static const char* AddId(const char* newId);
	static bool doesIdExist(const char* id);
	static void freeIds(); // to manage deletion

	// constructors
	User();
	User(const char* id, const char* name, int friends, int lP);
	// copy constructor
	User(const User& other);

	// destructor
	~User();

	// rest of the functions i'll add later
};

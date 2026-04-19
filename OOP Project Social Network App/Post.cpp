#include "Post.h"
#include "stringFunctions.h"

// Default
Post::Post() {
	description = nullptr;
	date = nullptr;

	countLikes = 0;
	likedBy = nullptr;

	commentCount = 0;
}


// Parameterized
Post::Post(const char* text, const char* dat) {
	if (text) {
		description = new char[getLength(text) + 1];
		copyString(description, text);
	}
	else {
		description = nullptr;
	}

	if (dat) {
		description = new char[getLength(dat) + 1];
		copyString(date, dat);
	}
	else {
		date = nullptr;
	}

	countLikes = 0;
	likedBy = nullptr;

	commentCount = 0;
}

// Destructor
Post::~Post() {
	delete[] description;
	delete[] date;

	delete[] likedBy;

	if (comments) {
		for (int i = 0; i < commentCount; i++) {
			delete comments[i];
		}
		delete[] comments;
	}
}
#include "Post.h"
#include "Date.h"
#include "Author.h"
#include "Activity.h"
#include "stringFunctions.h"
#include <iostream>


// Default
Post::Post() : UniqueElement(), sharedDate() {
	description = nullptr;
	countLikes = 0;
	likedBy = nullptr;
	activity = nullptr;
	commentCount = 0;
	author = nullptr;
	comments = nullptr;
	imgPath = nullptr;
}


// Parameterized
Post::Post(const char* id, const char* text, const Date& currDate, Author* author, Activity* activity)
	: UniqueElement(id), comments(nullptr), imgPath(nullptr) { // currDate will be provided by the driver program
 	if (text) {
		description = new char[getLength(text) + 1];
		copyString(description, text);
	}
	else {
		description = nullptr;
	}

	sharedDate = currDate; 

	countLikes = 0;
	likedBy = nullptr;

	commentCount = 0;

	this->author = author; // assigning pointer
	this->activity = activity; // deep copy
}

// Destructor
Post::~Post() {
	// Destructor for Date runs automatically
	delete[] description;
	delete[] likedBy;
	author = nullptr;
	if (comments) {
		for (int i = 0; i < commentCount; i++) {
			delete comments[i]; // composed
		}
		delete[] comments;
	}
}

void Post::displayPost() const {
	cout << "---" << author->getName();
	if (this->activity != nullptr) {
		cout << " is " << activity->GetActivityTypeString() << " " << activity->GetValue();
	}
	else {
		cout << " shared ";
	}

	cout << " \"" << description << "\"\n";
}

bool Post::addLike(User* u) {
	if (countLikes == 10) return false;
	User** newLikedBy = new User * [countLikes + 1];
	
	for (int i = 0; i < countLikes; i++) {
		newLikedBy[i] = likedBy[i];
	}
	
	newLikedBy[countLikes] = u;
	delete[] likedBy;
	likedBy = newLikedBy;
	countLikes++;
	return true;
}

// addComments, filling likedBy (will be done in user class pretty sure), setting upper limit for comments

// added viewLikedList
void Post::viewLikedList(const char* postId) {
	if (!id || !postId) return;
	// verify this is the requested post
	int i = 0;
	while (id[i] && postId[i] && id[i] == postId[i]) i++;
	if (id[i] != postId[i]) return;

	cout << "=== Liked by ===\n";
	if (countLikes == 0) {
		cout << "No likes yet.\n";
		return;
	}
	for (int j = 0; j < countLikes; j++) {
		cout << likedBy[j]->getName() << '\n';
	}
}
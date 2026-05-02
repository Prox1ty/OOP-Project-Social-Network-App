#include "Post.h"
#include "Date.h"
#include "User.h"
#include "Author.h"
#include "Comment.h"
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
	cout << endl;
	cout << "---" << author->getName();
	if (this->activity != nullptr) {
		cout << " is " << activity->GetActivityTypeString() << " " << activity->GetValue();
	}
	else {
		cout << " shared ";
	}

	cout << endl;
	cout << " \"" << description << "\"\n";

	// to print comments for display
	for (int i = 0; i < commentCount; i++) {
		if (comments[i])
			comments[i]->displayComment();
	}

}

bool Post::addLike(Author* u) {
	if (!u) return false; // null check
	if (countLikes == 10) return false;
	Author** newLikedBy = new Author * [countLikes + 1];
	
	if (likedBy) {
		for (int i = 0; i < countLikes; i++) {
			newLikedBy[i] = likedBy[i];
		}
		delete[] likedBy;
	}
	
	newLikedBy[countLikes] = u;
	likedBy = newLikedBy;
	countLikes++;
	return true;
}

// addComments, filling likedBy (will be done in user class pretty sure), setting upper limit for comments

// added viewLikedList
void Post::viewLikedList() {

	cout << "Post Liked by:\n";
	cout << endl;
	if (countLikes == 0 || !likedBy) {
		cout << "No likes yet.\n";
		return;
	}
	for (int j = 0; j < countLikes; j++) {
		if (likedBy[j])
			cout << likedBy[j]->getName() << '\n';
	}
}

void Post::addComment(Comment* c) {
	if (!c) return; // null check
	int noOfComs = commentCount;

	// resize da array
	Comment** newComments = new Comment * [noOfComs + 1];
	if (comments) {
		for (int i = 0; i < noOfComs; i++) {
			newComments[i] = comments[i]; // copying pointers
		}
		delete[] comments;
	}
	newComments[noOfComs] = c;
	commentCount = noOfComs + 1;
	comments = newComments;
}

bool Post::isLikedBy(Author* au) {
	for (int i = 0; i < countLikes; i++) {
		if (likedBy[i] == au) {
			cout << "Already liked post\n";
			return true;
		}
	}

	return false;
}
#include "Post.h"
#include "Date.h"
#include "Author.h"
#include "Activity.h"
#include "stringFunctions.h"
#include <iostream>


// Default
Post::Post(): sharedDate() {
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
Post::Post(const char* text, const Date& currDate, Author* author, Activity* activity): comments(nullptr), imgPath(nullptr) { // currDate will be provided by the driver program
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

// addComments, filling likedBy (will be done in user class pretty sure), setting upper limit for comments

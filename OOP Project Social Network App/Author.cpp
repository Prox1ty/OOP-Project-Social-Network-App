#include <iostream>
#include "Author.h"
#include "Post.h"
#include "Date.h"
#include "Comment.h"
#include "Memory.h"
using namespace std;

void Author::addComment(const char* text, Post* post, Date& currDate) {
	Comment* newCmnt = new Comment(text, this, post, &currDate);
	post->addComment(newCmnt); 
} 

void Author::addPost(const Date& currDate, const char* text, Activity* activity, const char* id) { // the last bit of input in the instructions text file is basically the likedBy array thingy
	Post** newTimeline = new Post * [posts + 1];

	for (int i = 0; i < posts; i++) {
		newTimeline[i] = timeline[i];
	}

	//attempted to fix constructor issue, but like 50 other rise up so yk kill me
	Post* newP = new Post(id, text, currDate, this, activity);
	newTimeline[posts] = newP;
	delete[] timeline;
	timeline = newTimeline;
	posts++;
}

void Author::viewTimeLine(const Date& currDate) const {
	for (int i = 0; i < posts; i++) {
		if (timeline[i]->isPostRecent(currDate)) {
			timeline[i]->displayPost();
		}
	}
}

int Author::countPosts() {
	return posts;
}

void Author::addPost(Post* newP) {
	Post** newTimeline = new Post * [posts + 1];
	for (int i = 0; i < posts; i++) {
		newTimeline[i] = timeline[i];
	}
	newTimeline[posts] = newP;

	delete[] timeline; // Free the old array of pointers
	timeline = newTimeline;
	posts++;
}

void Author::shareMemory(Date& currDate, const char* text, Post* refPost) {
	Memory* newM = new Memory(text, currDate, refPost, this);
	addPost(newM);
}
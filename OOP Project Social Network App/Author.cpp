#include <iostream>
#include "Author.h"
#include "Post.h"
#include "Date.h"
#include "Comment.h"
using namespace std;

void Author::addComment(const char* text, Post* post, Date& currDate) {
	Comment* newCmnt = new Comment(text, this, post, &currDate);
	int noOfComs = post->commentCount;

	// resize da array
	Comment** newComments = new Comment * [noOfComs + 1];
	for (int i = 0; i < noOfComs; i++) {
		newComments[i] = post->comments[i]; // copying pointers
	}
	delete[] post->comments;
	newComments[noOfComs] = newCmnt;
	post->commentCount = noOfComs + 1;
	post->comments = newComments;
} // requires a text, an author and a pointer to the post

void Author::addPost(const Date& currDate, const char* text, Activity* activity) { // the last bit of input in the instructions text file is basically the likedBy array thingy
	Post** newTimeline = new Post * [posts + 1];

	for (int i = 0; i < posts; i++) {
		newTimeline[i] = timeline[i];
	}


	Post* newP = new Post(text, currDate, this, activity);
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
#include <iostream>
#include "Author.h"
#include "Post.h"
#include "Date.h"
#include "Comment.h"
#include "Memory.h"
#include "stringFunctions.h"
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
	if (posts == 0 || !timeline) {
		cout << "No posts yet. \n";
		return;
	}

	for (int i = 0; i < posts; i++) {
		if (timeline[i] && timeline[i]->isPostRecent(currDate)) {
			timeline[i]->displayPost();
		//display comments now part of Post
		}
	}
}

//adding a separate function for viewing pages
void Author::viewAllPosts() const {
	if (posts == 0 || !timeline) {
		cout << "No posts yet.\n";
		return;
	}
	for (int i = 0; i < posts; i++) {
		if (timeline[i])
			timeline[i]->displayPost();
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

Memory* Author::shareMemory(Date& currDate, const char* text, Post* refPost) {
	char buffer[256];
	buffer[0] = '\0'; // initialize so concatStr can find the terminator

	int dateDifference = 0;
	char dmy;
	if (currDate.getYear() - refPost->getDate().getYear() > 0) {
		dateDifference = currDate.getYear() - refPost->getDate().getYear();
		dmy = 'Y';
	}
	else if (currDate.getMonth() - refPost->getDate().getMonth() > 0) {
		dateDifference = currDate.getMonth() - refPost->getDate().getMonth();
		dmy = 'M';
	}
	else {
		throw std::runtime_error("Itna nostalgic hona achi baat nahi");
	}
	const char* dateDiffChar = convertIntToChar(dateDifference); // proper int-to-string conversion
	// devious concatenation
	concatStr(buffer, getName());
	concatStr(buffer, " shared a memory ~~~...");
	concatStr(buffer, currDate.getDateStr());
	concatStr(buffer, "\n\t");
	concatStr(buffer, dateDiffChar);
	concatStr(buffer, (dmy == 'Y') ? " year(s) ago" : " month(s) ago");
	concatStr(buffer, "\n");
	concatStr(buffer, refPost->getDesc());
	delete[] dateDiffChar; // free the heap string from convertIntToChar

	Memory* newM = new Memory(buffer, currDate, refPost, this); // use synthesized buffer
	addPost(newM);
	return newM;
}
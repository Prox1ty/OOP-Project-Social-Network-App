#pragma once
#include "UniqueElement.h"
#include <iostream>
#include "Date.h"
#include "Memory.h"
#include "Post.h"
using namespace std;

class Date;
class Activity;
class Post;
class Author : public UniqueElement {
protected:
	Post** timeline; // for author's own posts
	int posts;
public:
	Author(): UniqueElement() {
		id = nullptr;
		posts = 0;
		timeline = nullptr;
	}
	Author(const char* id) : UniqueElement(id), posts(0), timeline(nullptr) {}
	virtual ~Author() {
		for (int i = 0; i < posts; i++) {
			delete timeline[i];
		}
		delete[] timeline;
		posts = 0;
		timeline = nullptr;
	}
	virtual const char* getName() const = 0; // implementation based on child classes
	void addComment(const char* text, Post* post, Date& currDate); // requires a text, an author and a pointer to the post
	void addPost(const Date& currDate, const char* text, Activity* activity, const char* id); // the last bit of input in the instructions text file is basically the likedBy array thingy
	// overload of addPost
	void addPost(Post* newP);
	Memory* shareMemory(Date& currDate, const char* text, Post* refPost);
	void viewTimeLine(const Date& currentDate) const;
	int countPosts();
	
	void viewAllPosts() const;

	Post** getTimeline() const;

};
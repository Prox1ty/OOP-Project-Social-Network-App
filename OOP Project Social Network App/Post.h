#pragma once
#include "UniqueElement.h"
#include "Date.h"
#include <iostream>
using namespace std;

class Author; //idk i am just following what you did
class Comment;
class Activity;
class User;

class Post : public UniqueElement { //btw for all of this i am assuming unique deals with the whole assingning ids
	char* description;
	Date sharedDate; // composition
	Author* author;
	int countLikes;
	User** likedBy;

	//comments gonna be a class, right?
	Comment** comments; // what is a comment owned by? The user owns the comment so it handles the creation and deletions
	int commentCount;

	Activity* activity;

	const char* imgPath;

public:
	//default
	Post();

	//parameterized
	Post(const char* text,const Date& currDate, Author* owner, Activity*);
	//is a copy constructor needed? Muaaz: Maybe but we wont bother with that for now

	bool isPostRecent(const Date& currDate) const{	
		sharedDate.IsRecent(currDate); // provided by the main driver program
	}

	//deconstructor
	~Post();

	void displayPost() const;

	friend class Author;

};
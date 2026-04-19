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
	Comment** comments;
	int commentCount;

	Activity* activity;

	const char* imgPath;
	//Activity seems to be only a subset of Post so ig its not gonna
	//be its own separate class (P.S idk :p) 
	// (P.P.S: "Memory" being a further extension down the line)
	
	// All of this assuming the one other class Muaaz was 
	// dereferencing to was comments

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

	friend class User;

};
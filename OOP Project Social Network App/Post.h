#pragma once
#include "UniqueElement.h"
#include "User.h"
#include <iostream>
using namespace std;

class User; //idk i am just following what you did
class Comment;

class Post : public UniqueElement { //btw for all of this i am assuming unique deals with the whole assingning ids
	char* description;
	char* date;

	int countLikes;
	User** likedBy;

	//comments gonna be a class, right?
	Comment** comments;
	int commentCount;

	//Activity seems to be only a subset of Post so ig its not gonna
	//be its own separate class (P.S idk :p) 
	// (P.P.S: "Memory" being a further extension down the line)
	
	// All of this assuming the one other class Muaaz was 
	// dereferencing to was comments

public:
	//default
	Post();

	//parameterized
	Post(const char* text,const char* dat);

	//is a copy constructor needed?

	//deconstructor
	~Post();

};
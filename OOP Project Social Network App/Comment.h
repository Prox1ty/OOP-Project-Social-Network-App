#pragma once
#include "UniqueElement.h"
#include "User.h"
#include <iostream>
using namespace std;

class User;

class Comment : public UniqueElement {
	char* text;
	User* userMain;

public:
	//default
	Comment();

	//parameterized
	Comment(const char* txt, User* user);

	//deconstructor
	~Comment();

	//wth are we supposed to do with Page?
};
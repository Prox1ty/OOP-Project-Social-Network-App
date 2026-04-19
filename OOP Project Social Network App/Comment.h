#pragma once
#include "UniqueElement.h"
#include "User.h"
#include <iostream>
using namespace std;

class Author;

class Comment : public UniqueElement {
	char* text;
	Author* userMain;

public:
	//default
	Comment();

	//parameterized
	Comment(const char* txt, Author* user);

	//deconstructor
	~Comment();

	//wth are we supposed to do with Page?
};
#pragma once
#include "UniqueElement.h"
#include "User.h"
#include <iostream>
using namespace std;

class Author;

class Comment : public UniqueElement {
	char* text;
	Author* userMain;
	Post* origPost;
	Date* pDate;

public:
	//default
	Comment();

	//parameterized
	Comment(const char* txt, Author* user, Post* origPost, Date* pDate);

	//deconstructor
	~Comment();
};
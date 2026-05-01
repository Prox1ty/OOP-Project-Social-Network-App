#pragma once
#include "Post.h"


class Memory : public Post {
	static int memCount;
	char* text;
	Post* oPost;
public:
	Memory(const char* t, Date& cDate, Post* op, Author* o);
	~Memory();
	const char* generateId();
	void displayMemory() const;
};
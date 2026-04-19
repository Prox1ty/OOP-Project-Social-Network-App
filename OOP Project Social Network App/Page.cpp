#include "Page.h"
#include "Author.h"
#include "stringFunctions.h"
#include <stdexcept>

Page::Page() : Author(nullptr), owner(nullptr), sharedPosts(nullptr), likes(0) {}

Page::Page(const char* id, const char* title, User* o, int likes) : Author(id), title(title), owner(o), likes(likes), sharedPosts(nullptr) {}

Page::~Page() {
	delete[] sharedPosts;
	delete title;
	sharedPosts = nullptr;
	owner = nullptr;
	// not deleting id because its not owned by Page (managed by UniqueElement static array).
	// not deleting owner because we're just storing a pointer, not creating it
}

const char* Page::getName() const {
	return title;
}
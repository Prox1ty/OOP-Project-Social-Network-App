#include "Page.h"
#include "stringFunctions.h"
#include <stdexcept>

Page::Page() : UniqueElement(), owner(nullptr), sharedPosts(nullptr), likes(0) {}

Page::Page(const char* id, User* o, int likes) : UniqueElement(id), owner(o), likes(likes), sharedPosts(nullptr) {}

Page::~Page() {
	delete[] sharedPosts;
	// not deleting id because its not owned by Page (managed by UniqueElement static array).
	// not deleting owner because we're just storing a pointer, not creating it
}
// boingg
// boing boing
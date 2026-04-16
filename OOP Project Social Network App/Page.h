#pragma once

class User;
class Post;

class Page {
	const char* id;
	User* owner; // pointer to owner
	Post* sharedPosts;
	int likes;

public:
	Page() : id(nullptr), owner(nullptr), sharedPosts(nullptr), likes(0) {}
	Page(const char* id, User* o, int likes = 0): id(id), owner(o), likes(likes) {}


};
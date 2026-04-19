#include "Comment.h"
#include "stringFunctions.h"

Comment::Comment() {
	text = nullptr;
	userMain = nullptr;
}

Comment::Comment(const char* txt, User* user) {
	if (txt) {
		text = new char[getLength(txt) + 1];
		copyString(text, txt);
	}
	else
		text = nullptr;

	userMain = user;
}
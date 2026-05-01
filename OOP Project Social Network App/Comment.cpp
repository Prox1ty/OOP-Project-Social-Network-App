#include "Comment.h"
#include "stringFunctions.h"

Comment::Comment() {
	text = nullptr;
	userMain = nullptr;
}

Comment::Comment(const char* txt, Author* au, Post* origPost, Date* currDate) {
	if (origPost)
		this->origPost = origPost;
	if (txt) {
		text = new char[getLength(txt) + 1];
		copyString(text, txt);
	}
	else
		text = nullptr;

	userMain = au;
	this->pDate = currDate;
}

Comment::~Comment() {
	delete[] text;
	delete pDate;  
	userMain = nullptr; // not gonna delete here
}

void Comment::displayComment() const {
	cout << "                " << userMain->getName() << " wrote: " 
		<< text << endl;
    	
}
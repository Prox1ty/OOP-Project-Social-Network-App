#include "Memory.h"
#include "stringFunctions.h"
#include "Post.h"
#include "Date.h"
#include "Author.h"
using namespace std;
int Memory::memCount = 0;

// order doesn't really matter in the initializer list, it matters in the class definition (private vars order)
Memory::Memory(const char* mtext, Date& cDate, Post* op, Author* o) :
	Post(generateId(), mtext, cDate, o, nullptr), oPost(op) {
	if (mtext) {
		this->text = new char[getLength(mtext) + 1];
		copyString(this->text, mtext);
	}
	else {
		this->text = nullptr;
	}
}


const char* Memory::generateId() {
	const char* newId = join("m", convertIntToChar(Memory::memCount)); //max buffer size is 10
	return newId;
}

Memory::~Memory() {
	delete text;
	oPost = nullptr;
}

void Memory::displayMemory() const {
	cout << Post::getAuthor()->getName() << " Shared a memory\n";
	if (text) {
		cout << text << endl;
	}
	else {
		cout << "On this day\n";
	}
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
	oPost->displayPost();
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
}
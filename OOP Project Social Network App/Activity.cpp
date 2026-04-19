#include "Activity.h"
#include <iostream>
#include "stringFunctions.h"

using namespace std;

Activity::Activity(int k, const char* v) {
	// copying key
	switch (k) {
	case 1:
		const char* temp = "is feeling";
		key = new char[getLength(temp) + 1];
		copyString(key, temp);
		break;
	case 2:
		const char* temp = "is thinking about";
		key = new char[getLength(temp) + 1];
		copyString(key, temp);
		break;
	case 3:
		const char* temp = "is making";
		key = new char[getLength(temp) + 1];
		copyString(key, temp);
		break;
	case 4:
		const char* temp = "is celebrating";
		key = new char[getLength(temp) + 1];
		copyString(key, temp);
		break;
	}
	// copying value
	val = new char[getLength(v) + 1];
	copyString(val, v);
	
}

Activity::~Activity() {
	delete key;
	delete val;
}

const char* Activity::GetActivityTypeString() const {
	return key;
}

const char* Activity::GetValue() const {
	return val;
}
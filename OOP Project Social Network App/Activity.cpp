#include "Activity.h"
#include <iostream>
#include "stringFunctions.h"

using namespace std;

Activity::Activity(int k, const char* v) {
	// copying key
	const char* activitiesArr[] = {"is feeling", "is thinking about", "is making", "is celebrating"};
	switch (k) {
	case 1:
		key = new char[getLength(activitiesArr[0]) + 1];
		copyString(key, activitiesArr[0]);
		break;
	case 2:
		key = new char[getLength(activitiesArr[1]) + 1];
		copyString(key, activitiesArr[1]);
		break;
	case 3:
		key = new char[getLength(activitiesArr[2]) + 1];
		copyString(key, activitiesArr[2]);
		break;
	case 4:
		key = new char[getLength(activitiesArr[3]) + 1];
		copyString(key, activitiesArr[3]);
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
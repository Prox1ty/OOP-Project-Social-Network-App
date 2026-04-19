#pragma once

class Activity {
	char* key;
	char* val;

public:
	Activity(int k, const char* v);
	~Activity();

	const char* GetActivityTypeString() const;
	const char* GetValue() const;
};
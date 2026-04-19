#pragma once
#include "UniqueElement.h"
class Author : public UniqueElement {
public:
	Author() {
		id = nullptr;
	}
	Author(const char* id) : UniqueElement(id) {}
	virtual const char* getName() const = 0; // implementation based on child classes
};
#include "UniqueElement.h"
#include "stringFunctions.h"
#include <stdexcept>

char** UniqueElement::existingIds = nullptr;
int UniqueElement::IdCnt = 0;
int UniqueElement::IdCap = 0;

bool UniqueElement::doesIdExist(const char* u_id) {
	if (u_id == nullptr) return false;

	for (int i = 0; i < IdCnt; i++) {
		if (areEqual(existingIds[i], u_id)) return true;
	}

	return false;
}

void UniqueElement::resize() {
	if (IdCnt < IdCap) return;

	int newCap = (IdCap == 0) ? 4 : IdCap * 2;
	char** newArr = new char* [newCap];
	// shallow copy the pointers
	for (int i = 0; i < IdCnt; i++) newArr[i] = existingIds[i];
	delete[] existingIds;
	existingIds = newArr;
	IdCap = newCap;
}

// returns pointer to stored Id. The Id itself is stored by the static array existingIds
const char* UniqueElement::AddId(const char* newId) {
	resize();
	if (newId == nullptr) return nullptr;

	for (int i = 0; i < IdCnt; i++) {
		if (areEqual(existingIds[i], newId)) {
			throw std::runtime_error("Duplicate Id passed\n");
			return nullptr;
		}
	}

	int len = getLength(newId);
	existingIds[IdCnt] = new char [len + 1];
	copyString(existingIds[IdCnt], newId);
	IdCnt++;
	return existingIds[IdCnt - 1];
}

void UniqueElement::freeIds() {
	if (existingIds) {
		for (int i = 0; i < IdCnt; i++) {
			delete[] existingIds[i];
			existingIds[i] = nullptr;
		}
		delete[] existingIds;
		existingIds = nullptr;
	}
	IdCnt = 0;
	IdCap = 0;
}

UniqueElement::UniqueElement() : id(nullptr) {}

UniqueElement::UniqueElement(const char* newId) : id(nullptr) {
	this->id = AddId(newId);
}

UniqueElement::~UniqueElement() {
	// id is not deleted because it's managed by the static array
}

const char* UniqueElement::getId() const {
	return id;
}

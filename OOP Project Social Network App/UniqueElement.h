#pragma once

class UniqueElement {
protected:
	static char** existingIds;
	static int IdCnt;
	static int IdCap;
	const char* id;

public:
	// static funcs for ID management
	static void resize();
	static const char* AddId(const char* newId);
	static bool doesIdExist(const char* id);
	static void freeIds(); // to manage deletion

	// constructors/destructors
	UniqueElement();
	UniqueElement(const char* id);
	virtual ~UniqueElement();

	// getter
	virtual const char* getId() const;
};

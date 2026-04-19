#include "User.h"
#include "Page.h"
#include "Date.h"

// not sure what to do here
// somehow set const char** User::existingIds = nullptr
// int User::IdCnt = 0
class SocialMediaApp {
	const Date SystemDate; // will have the user enter this too. This is the main entry point of the program
public:
	SocialMediaApp(Date sysD) : SystemDate(sysD) {}
};
#include <iostream>
#include "SocialMediaApp.cpp"
#include "Date.h"
using namespace std;

int main() {
	Date today(15, 11, 2017);
	SocialMediaApp app(today);
	app.loadData();

	return 0;
}

//boop
//boop x2
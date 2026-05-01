#include <iostream>
#include "SocialMediaApp.cpp"
#include "Date.h"
using namespace std;

int main() {
	Date today(10, 12, 2024);
	SocialMediaApp app(today);
	app.loadData();

	return 0;
}

//boop
//boop x2
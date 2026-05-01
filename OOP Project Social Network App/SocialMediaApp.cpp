#include "User.h"
#include "Page.h"    
#include "Date.h"
#include "Author.h"
#include "Activity.h"
#include "Comment.h"
#include "Post.h"
#include "UniqueElement.h"
#include "stringFunctions.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

class SocialMediaApp {
	User** allUsers;
	Page** allPages;
	Post** allPosts;
	Comment** allComments;

	int userCnt;
	int pageCnt;
	int postCnt;
	int commentCnt;

	const Date SystemDate; // will have the user enter this too. This is the main entry point of the program
public:
	SocialMediaApp(Date sysD) : SystemDate(sysD), allUsers(nullptr), allPages(nullptr)
	, allPosts(nullptr), allComments(nullptr), userCnt(0), pageCnt(0), postCnt(0), commentCnt(0) {}

	void loadData() {
		cout << "Load data running" << endl; // debug message
		loadPages("Pages.txt");
		loadUsers("Users.txt");
		for (int i = 0; i < userCnt; i++) {
			if (allUsers[i] != nullptr) 
				cout << allUsers[i]->getName() << endl;
		}
		/*loadUsers();
		loadPosts();*/
	}

	void loadPages(const char* filename) {
		try {
			ifstream infile(filename);
			int cnt;
			if (!infile.is_open()) {
				throw std::runtime_error("Error in opening file");
			}

			infile >> cnt;
			pageCnt = cnt;
			infile.ignore(10000, '\n'); // skip rest of the characters, if any.

			allPages = new Page * [pageCnt];
			for (int i = 0; i < pageCnt; i++) allPages[i] = nullptr;

			char idBuf[256];
			char titleBuf[256];

			// lambda function to help with finding valid indices
			// returns an int
			// [] empty because we don't capture any variable
			auto parseIndex = [](const char* id) -> int {
				if (!id) return -1; // nullptr
				int val = 0;
				int i = 1; // first index
				while (id[i] != '\0') {
					if (id[i] >= '0' && id[i] <= '9')
						val = val * 10 + (id[i] - '0');
					else break;
					i++;
				}

				return val > 0 ? (val - 1) : -1;
			};

			for (int p = 0; p < pageCnt; p++) {
				// read id
				if (!(infile >> idBuf)) break;

				// title may contain spaces so we switch to getline
				infile.getline(titleBuf, 256);

				// starting spaces handling
				int start = 0;
				while (titleBuf[start] == ' ') start++;

				char* title = nullptr;
				if (titleBuf[start] == '\0') {
					// empty title
					title = new char[1];
					title[0] = '\0';
				}
				else {
					// pass in an array that starts at index start
					int len = getLength(&titleBuf[start]);
					// &titleBuf[start] just passes memory address of the character at index start
					// if we pass titleBuf as is, what it does under the hood is also just pass a pointer to the first element of the array
					// so &titleBuf[start] does the same. We need the & because [] operator dereferences the pointer, we now need to go back a step to get the address
					
					title = new char[len + 1];
					copyString(title, &titleBuf[start]);
				}

				// copying id
				char* id = new char[getLength(idBuf) + 1];
				copyString(id, idBuf);

				int idx = parseIndex(idBuf); // validate index
				if (idx < 0 || idx >= pageCnt) {
					throw std::runtime_error("Invalid id");
				}

				Page* newPage = new Page(id, title, nullptr, 0);
				allPages[idx] = newPage;

				delete[] id;
				delete[] title;
			}
		}
		catch (const exception& e) {
			cout << "Error occured in loadPages: " << e.what() << endl;
		}
	}
	void loadUsers(const char* filename) {
		try {
			ifstream infile(filename);
			int cnt;
			if (!infile.is_open()) {
				throw std::runtime_error("Error in opening file");
			}

			infile >> cnt;
			userCnt = cnt;

			infile.ignore(10000, '\n');

			allUsers = new User * [userCnt];
			for (int i = 0; i < userCnt; i++) allUsers[i] = nullptr;

			char idBuf[256];
			char fName[256];
			char lName[256];

			// could've also made a private function but this method is cooler hehe
			auto parseIndex = [](const char* id) {
				if (!id) return -1;
				int i = 1;
				int val = 0;

				while (id[i] != '\0') {
					if (id[i] >= '0' && id[i] <= '9') {
						val = val * 10 + (id[i] - '0');
					}
					else break;
					i++;
				}
				return val > 0 ? (val - 1) : -1;
			};

			// initialize user by reading id and name and skip the rest of the line (for now)
			for (int u = 0; u < userCnt; u++) {
				if (!(infile >> idBuf)) throw std::runtime_error("Error reading id");
				if (!(infile >> fName)) throw std::runtime_error("Error reading first name");
				if (!(infile >> lName)) throw std::runtime_error("Error reading last name");

				char fullName[512];
				copyString(fullName, fName);
				concatStr(fullName, " ");
				concatStr(fullName, lName);

				char* id = new char[getLength(idBuf) + 1];
				copyString(id, idBuf);

				char* name = new char[getLength(fullName) + 1];
				copyString(name, fullName);

				int idx = parseIndex(idBuf);
				if (idx < 0 || idx >= userCnt) {
					throw std::runtime_error("Invalid Id. Either below zero or exceeds the total number of users");
				}

				allUsers[idx] = new User(id, name, 0, 0);
				infile.ignore(10000, '\n');

				delete[] id;
				delete[] name;
			}

			// seek to the beginning of the file to read again
			infile.clear();
			infile.seekg(0, ios::beg);

			infile >> cnt; // just to proceed the stream cursor
			for (int u = 0; u < userCnt; u++) {
				if (!(infile >> idBuf)) throw std::runtime_error("Error reading id");
				if (!(infile >> fName)) throw std::runtime_error("Error reading first name");
				if (!(infile >> lName)) throw std::runtime_error("Error reading last name");

				int currIdx = parseIndex(idBuf); // current user idx in allUsers

				// now read friends till we encounter -1
				char token[256];
				if (!(infile >> token)) throw std::runtime_error("Error reading friend");
				while (!areEqual(token, "-1")) {
					int fIdx = parseIndex(token);
					if (fIdx >= 0 && fIdx < userCnt && allUsers[fIdx] && allUsers[currIdx]) {
						allUsers[currIdx]->addFriend(allUsers[fIdx]);
					}

					if (!(infile >> token)) throw std::runtime_error("Error reading friend");
				}

				// now read liked pages
				if (!(infile >> token)) throw std::runtime_error("Error reading liked page");
				while (!areEqual(token, "-1")) {
					int pIdx = parseIndex(token);
					if (pIdx >= 0 && pIdx < pageCnt && allPages[pIdx] && allUsers[currIdx]) {
						allUsers[currIdx]->likePage(allPages[pIdx]);
					}

					if (!(infile >> token)) throw std::runtime_error("Error reading liked page");
				}
				infile.ignore(10000, '\n');
			}

		}
		catch (const exception& e) {
			cout << "Error occured in loadUsers: " << e.what() << endl;
		}
	}
	
};
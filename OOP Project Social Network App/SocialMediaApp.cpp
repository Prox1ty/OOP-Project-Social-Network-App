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
		loadPages("Pages.txt");
		loadUsers("Users.txt");
		for (int i = 0; i < userCnt; i++) {
			allUsers[i]->getName();
		}
		/*loadUsers();
		loadPosts();*/
	}

	void loadUsers(const char* filename) {
		ifstream infile(filename);
		int cnt;
		if (!infile.is_open()) {
			std::cerr << "An error in opening file" << endl;
			return;
		}
		infile >> cnt;
		userCnt = cnt;

		// initilize userArr
		allUsers = new User * [userCnt];
		
		char buffer[256];
		int counter = 0;

		char* name;
		char* id;
		
		while (infile >> buffer) {
			if (areEqual(buffer, "\n")) {
				counter = 0; // new line
			}
			if (counter == 0) {
				id = new char[getLength(buffer) + 1];
				copyString(id, buffer);
			}
			if (counter == 1) {
				name = new char[getLength(buffer) + 1];
				copyString(name, buffer);
			}
			if (counter == 2) {
				char* zaUser = nullptr;
				while (!(areEqual("-1", buffer))) {
					copyString(zaUser, buffer);
					int zaUserNum = (zaUser[1] - '0') - 1; // converting to int
					// - 1 to account for 0 based indexing
					// note the txt file must contain userIDs in ascending order otherwise this thing just breaks
					int currUserNum = (id[1] - '0') - 1;

					allUsers[currUserNum] = new User(id, name, 0, 0);
					User* thisUserPtr = allUsers[currUserNum]; // just to make life easier
					thisUserPtr->addFriend(allUsers[zaUserNum]); // adding a friend yay
					infile >> buffer; 
				}
			}
			if (counter == 3) {
				char* pageId = nullptr;
				while (!(areEqual("-1", buffer))) {
					pageId = new char[getLength(buffer) + 1];
					copyString(pageId, buffer);

					int pageIdx = (pageId[1] - '0') - 1;	
					int currUserIdx = (id[1] - '0') - 1;
					allUsers[currUserIdx]->likePage(allPages[pageIdx]);
					// what is happening here basically is, we calculate the postIdx in the allPosts array
					// and we take our current user from the allUsers array and like the post using it's method
				}
			}

			counter++;
		}

		
	}

	void loadPages(const char* filename) {
		ifstream infile(filename);
		int cnt;
		if (!infile.is_open()) {
			std::cerr << "An error in opening file" << endl;
			return;
		}
		infile >> cnt;
		int pageCnt;
		pageCnt = cnt; // kinda redundant since pageCnt and cnt store the exact same info

		allPages = new Page* [pageCnt];
		char buffer[256];
		int counter = 0;

		char* title, *id;
		int idx;
		while (infile >> buffer) {
			if (areEqual(buffer, "\n")) counter = 0;

			if (counter == 0) {
				id = new char[getLength(buffer) + 1];
				copyString(id, buffer);

				idx = (id[1] - '0') - 1;
			}
			else if (counter == 1) {
				title = new char[getLength(buffer) + 1];
				copyString(title, buffer);
				Page* newPage = new Page(id, title, nullptr, 0);
				allPages[idx] = newPage;
			}
			counter++;
		}
	}
	
};
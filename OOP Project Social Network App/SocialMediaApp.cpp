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
		/*loadUsers();
		loadPosts();*/
	}

	void loadUsers(const char* filename) {
		
	}
	
};
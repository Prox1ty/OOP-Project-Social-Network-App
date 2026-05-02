#include <iostream>
#include "SocialMediaApp.cpp"
#include "Date.h"
using namespace std;

int main() { 
	try {
		SocialMediaApp app;
		app.setSystemDate();
		app.loadData();
		char temp[10];

		
		int choice;
		char uId[10];
		char pId[10];
		char postId[10];
		char buffer[256];
		
		//Can now login on runtime
		while (true) { 
			cout << "Set current user to: ";
			cin >> temp;

			while (!app.setCurrUser(temp)) {
				cout << "Invalid user. Please select an existing user: ";
				cin >> temp;
			}


			bool userSelection = false;
			while (!userSelection) {
				cout << "\nEnter command: \n"
					<< "0. Login to Another Account\n"
					<< "1. View Home\n"
					<< "2. Like a post\n"
					<< "3. View Liked Pages\n"
					<< "4. Comment on a Post\n"
					<< "5. View a Post\n"
					<< "6. Share a Memory\n"
					<< "7. View a User's profile (Timeline)\n"
					<< "8. View Friend List\n"
					<< "9. View Page\n"
					<< "10. View Liked List\n"
					<< "Your choice: ";

				cin >> choice;
				cout << endl;

				switch (choice) {

				case 0:
					userSelection = true;
					break;

				case 1:
					app.viewHome();
					break;
				case 2:
					cout << "Enter post Id: ";
					cin >> postId;
					app.likePost(postId);
					break;
				case 3:
					app.viewLikedPages();
					break;

				case 4:
					cout << "Enter post Id: ";
					cin >> postId;
					cin.ignore(10000, '\n');
					cout << "Type comment: ";
					cin.getline(buffer, 256);

					app.addComent(postId, buffer);
					break;

				case 5:
					cout << "Enter post Id: ";
					cin >> postId;
					app.viewPost(postId);
					break;

				case 6:
					cout << "Enter post Id: ";
					cin >> postId;
					cin.ignore(10000, '\n');
					cout << "Enter memory description: ";
					cin.getline(buffer, 256);
					app.shareMemory(postId, buffer);
					break;

				case 7:
					cout << "Enter User Id: ";
					cin >> uId;
					app.viewUProfile(uId);
					break;

				case 8:
					app.viewFrientList();
					break;

				case 9:
					cout << "Enter page Id: ";
					cin >> pId;
					app.viewPageProfile(pId);
					break;

				case 10:
					cout << "Enter post Id: ";
					cin >> postId;
					app.viewLikedList(postId);
					break;

				default:
					cout << "Invalid action" << endl;
					break;
				}
			}
		}
	}
	catch (const exception e) {
		cout << "An Error occured in main: " << e.what();
	}

	cout << endl;

	return 0;
}

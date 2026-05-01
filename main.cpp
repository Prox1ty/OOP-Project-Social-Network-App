#include <iostream>
#include "SocialMediaApp.cpp"
#include "Date.h"
using namespace std;

int main() {
    cout << "main() start\n" << flush;
    Date today(10, 12, 2024);
    cout << "constructed Date\n" << flush;
    SocialMediaApp app(today);
    cout << "constructed SocialMediaApp\n" << flush;

    app.loadData(); 

    cout << "returned from loadData\n" << flush;
    cout << "Press Enter to exit...\n";
    cin.get(); // keep console open so you can read output
    return 0;
}
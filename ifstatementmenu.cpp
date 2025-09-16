#include <iostream>
using namespace std;

int main(){
    int choice;
    string link;
    cout << "Please make a choice from the following";
    cout << "\n1. Upload a video link";
    cout << "\n2. View current uploaded videos";
    cout << "\n3. Remove an uploaded video";
    cout << "\n4. Exit\n";
    cin >> choice;

    if (choice == 1) {
        cout <<"\nPlease input the video link!";
        cin >> link;
        cout <<"\nVideo uploaded, thank you!";
    }

    else if (choice == 2){
        cout <<"\nLoading uploaded videos...";
    }
    
    else if (choice == 3){
        cout <<"\nDeleting uploaded video...";
    }

    else if (choice == 4){
        cout <<"\nExiting ... Have a great day!";
    }

    else {cout <<"\nInvalid Option. Please restart. ";}
    return 0;
}
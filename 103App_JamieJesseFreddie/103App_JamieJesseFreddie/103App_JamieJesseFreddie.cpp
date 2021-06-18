#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <vector>

using namespace std;

//-----Structs and Function Prototypes-----

// CODE SECTION - Jamie

void Parent_AccessNotices();    // These two functions are just placeholders and could change return types or arguments
void Parent_AccessChildRecords();

typedef struct ParentDetails {  // Any records starting with e are for emergency contact info.
    string username;
    string password;
    string firstName;
    string lastName;
    string dob;
    string email;
    string contactNumber;
    string eFirstName;
    string eLastName;
    string eContactNumber;
    // Find a way to have student data here, may have to just add more strings

    ParentDetails(string un="", string pw="", string fn="", string ln="", string db="", string em="", string cn="", 
                    string efn="", string eln="", string ecn="") {
        username = un;
        password = pw;
        firstName = fn;
        lastName = ln;
        dob = db;
        email = em;
        contactNumber = cn;
        eFirstName = efn;
        eLastName = eln;
        eContactNumber = ecn;
        
    }

} Parent;

typedef struct StudentRecords {
    string firstName;
    string lastName;
    vector<string> Classes;


} Student;

// CODE SECTION - End

//-----------------------------------------

int main()
{

    //// Jesse Simpson - Start
    //int option; // Stores the user's option.
    //ifstream inputDetails; // File identifier for reading purposes
    //string str; // For storing getline data from the inputDetails file
    //
    //// Operates while the User has not exited. Not final, and is subject to change based on other functions/screens.
    //do {
    //    // Output menu
    //    cout << "-------------------------------------------------------" << endl;
    //    cout << "|     Emerald Hill High School Information System     |" << endl;
    //    cout << "-------------------------------------------------------" << endl;
    //    cout << "\n1. Contact Details";
    //    cout << "\n2. Events";
    //    cout << "\n3. Term Dates";
    //    cout << "\n4. Account Settings" << endl;
    //    cout << "\n5. Exit" << endl;
    //    cout << "\n[Enter your option:] ";
    //    
    //    cin >> option; // User Input for Menu Selection
    //    
    //    cout << "\n"; // New line so it doesn't look too close together, helping with readability

    //    // Menu options switch case. Account Settings does not work at this time, as I am waiting on the Login screen stuff to get underway.
    //    // Options 1-3 all do the same basic operation of reading from an existing txt file. Said txt file plans to be modifiable by an Admin.
    //    // Sleep only works on windows at this time.
    //    switch (option) {
    //    case 1:
    //        inputDetails.open("contactDetails.txt", ios::in);
    //        while (getline(inputDetails, str)) {
    //            cout << str << endl;
    //        }
    //        cout << "\n";
    //        inputDetails.close();
    //        Sleep(1500);
    //        break;
    //    case 2:
    //        inputDetails.open("eventDetails.txt", ios::in);
    //        while (getline(inputDetails, str)) {
    //            cout << str << endl;
    //        }
    //        cout << "\n";
    //        inputDetails.close();
    //        Sleep(1500);
    //        break;
    //    case 3:
    //        inputDetails.open("termDetails.txt", ios::in);
    //        while (getline(inputDetails, str)) {
    //            cout << str << endl;
    //        }
    //        cout << "\n";
    //        inputDetails.close();
    //        Sleep(1500);
    //        break;
    //    default: // Explaining that the user has inputted the incorrect number, clears screen before showing menu again. Only works on Windows.
    //        cout << "What you entered does not match the menu options listed, please try again." << endl;
    //        Sleep(1500);
    //        system("CLS");
    //    }
    //    } while (option != 5);

    //    // Jesse Simpson - End

    Parent_AccessNotices();

        return 0;
 }


// CODE SECTION - Jamie

#pragma region ParentScreen

void Parent_AccessNotices() {
    string line;

    fstream fs;

    fs.open("data/notices.txt", ios::in);
    
    while (getline(fs, line)) {
        cout << line << endl;
    }

    fs.close();
}

void Parent_AccessChildRecords() {

}

#pragma endregion

// CODE SECTION - End
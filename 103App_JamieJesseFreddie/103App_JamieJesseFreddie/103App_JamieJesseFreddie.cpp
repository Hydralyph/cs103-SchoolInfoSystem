#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <vector>
#include <windows.h>

using namespace std;

//these are used to automatically generate students with androgynous first names (found them on a list dont judge me)
string firstNames[] = { "Bailey", "Cameron", "Harper", "Keegan", "Blake", "Phoenix", "Regan", "Shawn", "Rory", "Ryan", "Whitney", "Madison", "Hunter", "Logan", "Casey", "Parker", "Spencer", "Taylor", "Charlie", "Sawyer" };
string lastNames[] = { "Smith","Johnston","Rayn","Proops","Jameson","Erikson","Layn","Bigge","Ronaldo","Nuce","Forbe","Glasser","Rumble","Sailor","Faird","Levvy","Noy" };

int GetIntInput(int min = -2147483647, int max = 2147483647); //Freddie Rive

//-----Structs and Function Prototypes-----
struct Date //Freddie Rive
{
	unsigned int day, month, year;
	string fullDate, dayName;

	Date(int d = 1, int m = 1, int y = 2021) //constructor that takes 3 ints
	{
		year = min(max(y, 1), 2021);  //all inputs are validated to ensure that they fall into acceptable parameters (e.g. months can only be between 1 and 12)
		monthLength[1] = (y % 4 == 0) ? 29 : 28; //account for leap years
		month = min(max(m, 1), 12);
		day = min(max(d, 1), monthLength[m - 1]);

		fullDate = (day > 9) ? day + "/" : (string)("0" + day) + "/"; //date string is constructed out of the validated integers
		fullDate += (month > 9) ? month + "/" : (string)("0" + month) + "/";
		fullDate += year;

		int dayNo = 0; //attempting to accurately calculate the name of the day
		for (int i = 0; i < m - 1; i++)
		{
			dayNo += monthLength[i];
		}
		dayNo += day;

		dayName = days[Loop(dayNo % 7 + 3)]; //this will only be accurate for 2021
	}

	Date(string str) //constructor that takes a string (in dd/mm/yyyy format only)
	{
		if (str.length() == 10) //stops the constructor if the string is obviously incompatible
		{
			int d = ((str[0] - '0') * 10) + (str[1] - '0'); //convert the first 2 chars to an int
			int m = ((str[3] - '0') * 10) + (str[4] - '0');//convert the month chars to an int
			int y = ((str[6] - '0') * 1000) + ((str[7] - '0') * 100) + ((str[8] - '0') * 10) + (str[0] - '0'); //convert the year chars to an int

			year = min(max(y, 1), 2021); //all inputs are validated to ensure that they fall into acceptable parameters (e.g. months can only be between 1 and 12)
			monthLength[1] = (year % 4 == 0) ? 29 : 28; //account for leap years
			month = min(max(m, 1), 12);
			day = min(max(d, 1), monthLength[month - 1]);

			fullDate = str; //the input string can be stored as is

			int dayNo = 0; //attempting to accurately calculate the name of the day
			for (int i = 0; i < m - 1; i++)
			{
				dayNo += monthLength[i];
			}
			dayNo += day;

			dayName = days[Loop(dayNo % 7 + 3)]; //this will only be accurate for 2021
		}
		else //default values given if string entered is incompatible
		{
			day = 1;
			month = 1;
			year = 2021;
			fullDate = "01/01/2021";
			dayName = "Friday";
		}
	}

	int Loop(int input) //for the days
	{
		while (input > 6)
		{
			input -= 7;
		}
		return input;
	}

private:
	int monthLength[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //lengths of months
	string days[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" }; //names of days
};

// CODE SECTION - Jamie

void Parent_AccessNotices();    // These two functions are just placeholders and could change return types or arguments
void Parent_AccessChildRecords();

typedef struct ParentDetails {  // Any records starting with e are for emergency contact info.
	string firstName;
	string lastName;
	Date dob;
	string email;
	string contactNumber;
	string eFirstName;
	string eLastName;
	string eContactNumber;
	// Find a way to have student data here, may have to just add more strings

	ParentDetails(string fn = "", string ln = "", Date db = Date(), string em = "", string cn = "",
		string efn = "", string eln = "", string ecn = "") {
		firstName = fn;
		lastName = ln;
		dob = db;
		email = em;
		contactNumber = cn;
		eFirstName = efn;
		eLastName = eln;
		eContactNumber = ecn;
	}

	void DisplayInfo(int index = 0)
	{
		if (index > 0)
		{
			cout << "Information for parent " << index << " (" << firstName << " " << lastName << ")\n";
		}
		else
		{
			cout << "Information for parent " << firstName << " " << lastName << endl;
		}
		cout << "Date of birth: " << dob.fullDate << "\nEmail Address: " << email << "\nContact Phone: " << contactNumber << "\n\nEmergenct Contact : " << eFirstName << " " << eLastName 
			<< "\nEmergenct Contact Phone Number: " << eContactNumber << endl << endl;
	}
} Parent;

// CODE SECTION - End

struct Teacher //Freddie Rive
{
	string firstName, middleName, lastName, gender, email, contactNo;
	int age, yrTaught, classNo;
	Date dob;

	Teacher(string* str, int a, int tght, int clss, Date d)
	{
		this->firstName = *(str + 2);
		this->middleName = *(str + 3);
		this->lastName = *(str + 4);
		this->gender = *(str + 5);
		this->email = *(str + 6);
		this->age = a;
		this->contactNo = *(str + 7);
		this->yrTaught = tght;
		this->classNo = clss;
		this->dob = d;
	}

	Teacher() //default constructor; make sure you check firstname when making a new teacher struct
	{
		this->firstName = "NULL";
	}

	void DisplayInfo(int index = 0)
	{
		if (index > 0)
		{
			cout << "Information for teacher " << index << " (" << firstName << " " << middleName << " " << lastName << ")\n";
		}
		else
		{
			cout << "Information for teacher " << firstName << " " << middleName << " " << lastName << endl;
		}
		cout << "Age: " << age << "\nDate of birth: " << dob.fullDate << "\nGender: " << gender << "\nContact Phone: " << contactNo << "\nEmail Address: " << email << "\nYear Taught: "
			<< yrTaught << "\nClassroom number: " << classNo << endl << endl;
	}
};

enum accessLevels { defaultUser, parentKey, teacherKey, adminKey };
enum subjects { maths, science, english, sports, arts, behaviour };

struct Account
{
	struct AccountType 
	{
		Teacher teacher;
		Parent parent;
	} type;
	string username, password;
	int accessLevel;

	Account(string* str, Teacher* teach) //constructor for teacher account
	{
		this->username = *str;
		this->password = *(str + 1);
		this->type.teacher = *teach;
		this->accessLevel = teacherKey;
	}

	Account(string uname, string pword, Parent* prnt) //constructor for parent account
	{
		this->username = uname;
		this->password = pword;
		this->type.parent = *prnt;
		this->accessLevel = parentKey;
	}

	Account(string* str) //constructor for admin account
	{
		this->username = *str;
		this->password = *(str + 1);
		this->accessLevel = adminKey;
	}

	Account() //default user / logged out of account
	{
		this->accessLevel = defaultUser;
	}
};

struct StudentRecord { // Jamie - Placeholder Student Struct, just for testing. Work out a new one with Freddie.
	string firstName; // Could also put these two name strings together and seperate when necessary by splitting the string by space
	string lastName;
	string gender;
	int studentScore[6] = { 0, 0, 0, 0, 0, 0 };
	int year;

	StudentRecord(string* str, int* i)
	{
		this->firstName = *str;
		this->lastName = *(str + 1);
		this->gender = *(str + 2);
		this->studentScore[0] = *(i);
		this->studentScore[1] = *(i + 1);
		this->studentScore[2] = *(i + 2);
		this->studentScore[3] = *(i + 3);
		this->studentScore[4] = *(i + 4);
		this->studentScore[5] = *(i + 5);
		this->year = *(i + 6);
	}

	StudentRecord()
	{
		this->firstName = "NULL";
	}

	void WriteToFile()
	{
		ofstream file("data/students.csv", ios::out | ios::app);
		file << this->firstName << "," << this->lastName << "," << this->gender << "," << this->studentScore[0] << "," << this->studentScore[1] << "," << this->studentScore[2] << ","
			<< this->studentScore[3] << "," << this->studentScore[4] << "," << this->studentScore[5] << "," << this->year << "\n";
		file.close();
	}

	void DisplayInfo(int index = 0)
	{
		if (index > 0)
		{
			cout << "Information for student " << index << " (" << firstName << " " << lastName << ")\n";
		}
		else
		{
			cout << "Information for student " << firstName << " " << lastName << endl;
		}
		cout << "Gender: " << gender << "\nYear: " << year << "\nMaths : " << studentScore[maths] << "\nScience : " << studentScore[science] << "\nEnglish : " << studentScore[english] <<
			"\nSports : " << studentScore[sports] << "\nArts : " << studentScore[arts] << "\nOverall Behaviour : " << studentScore[behaviour] << endl;
	}

	void DisplayName()
	{
		cout << firstName << " " << lastName << endl;
	}

	void EditInfo()
	{
		int option;
		cout << "1. First Name: " << firstName << "\n2. Last Name: " << lastName << "\n3. Gender: " << gender << "\n4. Year: " << year << "\n5. Maths : " << studentScore[maths] << "\n6. Science : " << studentScore[science] << "\n7.English : " << studentScore[english] <<
			"\n8. Sports : " << studentScore[sports] << "\n9. Arts : " << studentScore[arts] << "\n\n10. Overall Behaviour : " << studentScore[behaviour] << endl;
		cout << "\nPlease enter the index of the information you wish to change: ";
		option = GetIntInput(1, 10);
		cout << "\nPlease enter the new data: ";
		switch (option)
		{
		case 1:
			getline(cin, firstName);
		case 2:
			getline(cin, lastName);
		case 3:
			getline(cin, gender);
		case 4:
			year = GetIntInput(5, 13);
		case 5:
			studentScore[0] = GetIntInput(1, 4);
		case 6:
			studentScore[1] = GetIntInput(1, 4);
		case 7:
			studentScore[2] = GetIntInput(1, 4);
		case 8:
			studentScore[3] = GetIntInput(1, 4);
		case 9:
			studentScore[4] = GetIntInput(1, 4);
		case 10:
			studentScore[5] = GetIntInput(1, 4);
		}
	}
};

string GetNewPassword(); //Freddie Rive
Account ParentAccountManagement(Account user);
Account TeacherAccountManagement(Account user); //Freddie Rive
Account AdminManagement(Account user); //Freddie Rive
void ParentFunctions();
void TeacherFunctions();
void AdminFunctions();
void DisplayStudent();
void EditStudent();
void DisplayAllStudents(int value = -1, string str = "");

//-----------------------------------------

int main()
{

	// Jesse Simpson - Start
	int option; // Stores the user's option.
	ifstream inputDetails; // File identifier for reading purposes
	string str; // For storing getline data from the inputDetails file
	Account user = Account();

	// Operates while the User has not exited. Not final, and is subject to change based on other functions/screens.
	do {
		// Output menu
		string accountSettings = (user.accessLevel == defaultUser) ? "Log In / Register" : "Log Out";
		cout << "-------------------------------------------------------" << endl;
		cout << "|     Emerald Hill High School Information System     |" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "\n1. Contact Details";
		cout << "\n2. Events";
		cout << "\n3. Term Dates";
		cout << "\n4. " << accountSettings;
		cout << "\n5. View/Edit Records\n";
		cout << "\n6. Exit" << endl;
		cout << "\n[Enter your option:] ";

		option = GetIntInput(1, 6); // User Input for Menu Selection

		cout << "\n"; // New line so it doesn't look too close together, helping with readability

		// Menu options switch case. Account Settings does not work at this time, as I am waiting on the Login screen stuff to get underway.
		// Options 1-3 all do the same basic operation of reading from an existing txt file. Said txt file plans to be modifiable by an Admin.
		// Sleep only works on windows at this time.
		switch (option) {
		case 1:
			inputDetails.open("contactDetails.txt", ios::in);
			while (getline(inputDetails, str)) {
				cout << str << endl;
			}
			cout << "\n";
			inputDetails.close();
			Sleep(1500);
			break;
		case 2:
			inputDetails.open("eventDetails.txt", ios::in);
			while (getline(inputDetails, str)) {
				cout << str << endl;
			}
			cout << "\n";
			inputDetails.close();
			Sleep(1500);
			break;
		case 3:
			inputDetails.open("termDetails.txt", ios::in);
			while (getline(inputDetails, str)) {
				cout << str << endl;
			}
			cout << "\n";
			inputDetails.close();
			Sleep(1500);
			break;
		case 4:
			switch (user.accessLevel)
			{
			case defaultUser:
				cout << "\nWhich account do you want to log into:\n1. Parent\n2. Teacher\n3. Admin\n\n4. Return to previous menu\n\n[Enter your option]: ";
				option = GetIntInput(1, 4);
				switch (option)
				{
				case 1:
					user = ParentAccountManagement(user);
					break;
				case 2:
					user = TeacherAccountManagement(user);
					break;
				case 3:
					user = AdminManagement(user);
					break;
				default:
					break;
				}
				break;
			case parentKey:
				user = ParentAccountManagement(user);
				break;
			case teacherKey:
				user = TeacherAccountManagement(user);
				break;
			case adminKey:
				user = AdminManagement(user);
				break;
			}
			break;
		case 5:
			switch (user.accessLevel)
			{
			case parentKey:
				ParentFunctions();
				break;
			case teacherKey:
				TeacherFunctions();
				break;
			case adminKey:
				AdminFunctions();
				break;
			default:
				cout << "\nPlease log in before attempting to access student records\n\n";
				Sleep(1500);
				break;
			}
			break;
		case 6:
			break;
		default: // Explaining that the user has inputted the incorrect number, clears screen before showing menu again. Only works on Windows.
			cout << "What you entered does not match the menu options listed, please try again." << endl;
			Sleep(1500);
			system("CLS");
		}
	} while (option != 6);

	// Jesse Simpson - End

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

Account RegisterNewParent()
{
	string username, password, firstname, lastname, dateString, email, contactNumber, eFirstName, eLastName, eContactNumber;
	Date dob;

	cout << "\nPlease enter your new username: ";
	getline(cin, username);
	password = GetNewPassword();
	cout << "\nPlease enter your first name: ";
	getline(cin, firstname);
	cout << "\nPlease enter your last name: ";
	getline(cin, lastname);
	cout << "\nPlease enter your date of birth (in dd/mm/yyyy format): ";
	getline(cin, dateString);
	dob = Date(dateString);
	cout << "\nPlease enter your email adress: ";
	getline(cin, email);
	cout << "\nPlease enter your contact number: ";
	getline(cin, contactNumber);
	cout << "\n\nPlease enter your emergency contacts first name: ";
	getline(cin, eFirstName);
	cout << "\nPlease enter your emergency contacts last name: ";
	getline(cin, eLastName);
	cout << "\nPlease enter your emergency contact's contact number: ";
	getline(cin, eContactNumber);

	ofstream parentFile("data/parents.csv", ios::app);
	parentFile << username << "," << password << "," << firstname << "," << lastname << "," << dob.fullDate << "," << email << "," << contactNumber << "," << eFirstName << ","
		<< eLastName << "," << eContactNumber << "\n";
	parentFile.close();

	Parent parent = Parent(firstname, lastname, dob, email, contactNumber, eFirstName, eLastName, eContactNumber);

	Account rtrn = Account(username, password, &parent);
	return rtrn;
}

Parent FetchParent(int index)
{
	ifstream parentFile("data/parents.csv", ios::in);

	string username, password, firstname, lastname, dateString, email, contactNumber, eFirstName, eLastName, eContactNumber;
	Date dob;

	for (int i = 0; i < index; i++)
	{
		getline(parentFile, username, '\n');
	}

	getline(parentFile, username, ',');
	getline(parentFile, password, ',');
	getline(parentFile, firstname, ',');
	getline(parentFile, lastname, ',');
	getline(parentFile, dateString, ',');
	dob = Date(dateString);
	getline(parentFile, email, ',');
	getline(parentFile, contactNumber, ',');
	getline(parentFile, eFirstName, ',');
	getline(parentFile, eLastName, ',');
	getline(parentFile, eContactNumber, ',');

	parentFile.close();
	return Parent(firstname, lastname, dob, email, contactNumber, eFirstName, eLastName, eContactNumber);
}

Parent GetParentByUsername(string input, string* password)
{
	int index = 0;
	string username;

	ifstream parentFile("data/parents.csv", ios::in);

	while (parentFile.peek() != -1)
	{
		getline(parentFile, username, ',');
		if (username == input)
		{
			getline(parentFile, username, ',');
			*password = username;
			parentFile.close();
			return FetchParent(index);
		}
		getline(parentFile, username, '\n');
		index++;
	}

	parentFile.close();
	return Parent();
}

Account LogInAsParent()
{
	string input, username, password;
	Parent parent;
	Account rtrn;

	ifstream parentFile("data/parents.csv", ios::in);

	try
	{
		cout << "\nPlease enter your username: ";
		getline(cin, input);
		parent = GetParentByUsername(input, &password);
		if (parent.firstName == "")
		{
			throw (string)"\nUsername not found in our records";
		}
		username = input;

		for (int attempts = 3; attempts > 0; attempts--)
		{
			cout << "\n(Attempts remaining: " << attempts << ") Please enter your password: ";
			getline(cin, input);
			if (input == password)
			{
				cout << "\nYou have now logged in as " << parent.firstName << " " << parent.lastName << endl;
				rtrn = Account(username, password, &parent);
				Sleep(1500);
				return rtrn;
			}
			else
			{
				cout << "\nYour password was incorrect." << endl;
				if (attempts == 1)
				{
					throw (string)"You ran out of attempts to enter the password";
				}
			}
		}
	}
	catch (string error)
	{
		cout << endl << error << endl;
		Sleep(1500);
	}

	return Account();
}

void FetchParents()
{
	ifstream parentFile("data/parents.csv", ios::in);
	int index = 1;
	while (parentFile.peek() != -1)
	{
		string username, password, firstName, lastName, dateString, email, contactNumber, eFirstName, eLastName, eContactNumber;
		Date dob;

		getline(parentFile, username, ',');
		getline(parentFile, password, ',');
		getline(parentFile, firstName, ',');
		getline(parentFile, lastName, ',');
		getline(parentFile, dateString, ',');
		dob = Date(dateString);
		getline(parentFile, email, ',');
		getline(parentFile, contactNumber, ',');
		getline(parentFile, eFirstName, ',');
		getline(parentFile, eLastName, ',');
		getline(parentFile, eContactNumber, ',');

		Parent parent = Parent(firstName, lastName, dob, email, contactNumber, eFirstName, eLastName, eContactNumber);
		parent.DisplayInfo(index);
		index++;
	}
	parentFile.close();
}

Account ParentAccountManagement(Account user)
{
	while (true)
	{
		if (user.accessLevel == parentKey)
		{
			int option = 0;
			system("CLS");
			cout << "-------------------------------------------------------" << endl;
			cout << "|     Emerald Hill High School Information System     |" << endl;
			cout << "|                    Parent Log Out                   |" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "\n1. Log out\n\n2. Return to main menu\n[Enter your option]: ";
			option = GetIntInput(1, 2);
			switch (option)
			{
			case 1:
				user = Account();
				cout << "\nYou have been logged out.";
				Sleep(1500);
				break;
			case 2:
				system("CLS");
				return user;
			}
		}
		else if (user.accessLevel == defaultUser)
		{
			int option = 0;
			system("CLS");
			cout << "-------------------------------------------------------" << endl;
			cout << "|     Emerald Hill High School Information System     |" << endl;
			cout << "|              Parent Log In / Register               |" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "\n1. Log into an existing account\n2. Register a new account\n3. Return to Main Menu\n[Enter your option]: ";
			option = GetIntInput(1, 3);
			switch (option)
			{
			case 1:
				user = LogInAsParent();
				break;
			case 2:
				user = RegisterNewParent();
				break;
			case 3:
				system("CLS");
				return user;
			}
		}
		else
		{
			system("CLS");
			cout << "Please log out of your current account before attempting to log in as a parent";
			Sleep(1500);
			return user;
		}
	}
}

void ParentFunctions()
{
	while (true)
	{
		int option = 0;
		system("CLS");
		cout << "-------------------------------------------------------" << endl;
		cout << "|     Emerald Hill High School Information System     |" << endl;
		cout << "|           Parent Student Record Management          |" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "\n1. View Student Record\n\n2. Return to main menu\n[Enter your option]: ";
		option = GetIntInput(1, 2);
		switch (option)
		{
		case 1:
			DisplayStudent();
			Sleep(1500);
			break;
		case 2:
			system("CLS");
			return;
		}
	}
}

#pragma endregion

// CODE SECTION - End

//----------------------------------Generic-Functions-------------------------------------//

int GetIntInput(int min, int max) //default variables are declared with the function at the top of the program
{
	int rtrn;
	while (true)
	{
		try
		{
			cin >> rtrn;
			if (cin.fail())
			{
				throw string("Error: Please only enter digits.");
			}
			else if (rtrn < min || rtrn > max)
			{
				throw string("Error: Input outside of acceptable range.");
			}
			break;
		}
		catch (string error)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << error << "Try again: ";
		}
	}
	cin.ignore();
	return rtrn;
}

string GetNewPassword()
{
	string rtrn, check;
	cout << "\nPlease enter your new password: ";
	getline(cin, rtrn);
	while (true)
	{
		cout << "\nPlease re-enter your password to confirm: ";
		getline(cin, check);
		if (check != rtrn)
		{
			cout << "\nYour entries do not match up. Do you want to:\n 1. Attempt again\n 2. Enter a new password\n ?: ";
			int i;
			i = GetIntInput(1, 2);
			if (i == 1)
			{
				continue;
			}
			else
			{
				rtrn = GetNewPassword();
				break;
			}
		}
		break;
	}
	return rtrn;
}

//-------------------------------Teacher-Functions------------------------------//
Account RegisterNewTeacher()
{
	string str[8], dateStr;
	int age, yrTaught, classNo;
	Date dob;

	cout << "\nPlease enter your new username: ";
	getline(cin, str[0]);
	str[1] = GetNewPassword();
	cout << "\nPlease enter your first name: ";
	getline(cin, str[2]);
	cout << "\nPlease enter your middle name: ";
	getline(cin, str[3]);
	cout << "\nPlease enter your last name: ";
	getline(cin, str[4]);
	cout << "\nPlease enter your age: ";
	age = GetIntInput(0, 127);
	cout << "\nPlease enter your Date of birth (in dd/mm/yyyy format): ";
	getline(cin, dateStr);
	Date date = Date(dateStr);
	dob = date;
	cout << "\nPlease enter your gender: ";
	getline(cin, str[5]);
	cout << "\nPlease enter your email address: ";
	getline(cin, str[6]);
	cout << "\nPlease enter your contact phone number: ";
	getline(cin, str[7]);
	cout << "\nPlease enter the year you teach at our school: ";
	yrTaught = GetIntInput(0, 13);
	cout << "\nPlease enter your classroom number: ";
	classNo = GetIntInput(0, 100);

	ofstream teacherFile("data/teachers.csv", ios::app);

	teacherFile << str[0] << ',' << str[1] << ',' << str[2] << ',' << str[3] << ',' << str[4] << ',' << str[5] << ',' << str[6] << ',' << str[7] << ',' << age << ','
		<< dob.fullDate << ',' << yrTaught << ',' << classNo << '\n';

	teacherFile.close();

	Teacher teach = Teacher(str, age, yrTaught, classNo, dob);

	Account rtrn = Account(str, &teach);

	return rtrn;
}

void FetchTeachers()
{
	ifstream teacherFile("data/teachers.csv", ios::in);
	int index = 1;
	while (teacherFile.peek() != -1)
	{
		string str[8], temp;
		int age, contactNo, yrTaught, classNo;
		Date dob;

		getline(teacherFile, str[0], ',');
		getline(teacherFile, str[1], ',');
		getline(teacherFile, str[2], ',');
		getline(teacherFile, str[3], ',');
		getline(teacherFile, str[4], ',');
		getline(teacherFile, str[5], ',');
		getline(teacherFile, str[6], ',');
		getline(teacherFile, str[7], ',');
		getline(teacherFile, temp, ',');
		age = stoi(temp);
		getline(teacherFile, temp, ',');
		dob = Date(temp);
		getline(teacherFile, temp, ',');
		yrTaught = stoi(temp);
		getline(teacherFile, temp, '\n');
		classNo = stoi(temp);

		Teacher teach = Teacher(str, age, yrTaught, classNo, dob);
		teach.DisplayInfo(index);
		index++;
	}
	teacherFile.close();
}

Teacher FetchTeacher(int index)
{
	ifstream teacherFile("data/teachers.csv", ios::in);

	string str[8], temp;
	int age, yrTaught, classNo;
	Date dob;

	for (int i = 0; i < index; i++)
	{
		getline(teacherFile, temp, '\n');
	}

	getline(teacherFile, str[0], ',');
	getline(teacherFile, str[1], ',');
	getline(teacherFile, str[2], ',');
	getline(teacherFile, str[3], ',');
	getline(teacherFile, str[4], ',');
	getline(teacherFile, str[5], ',');
	getline(teacherFile, str[6], ',');
	getline(teacherFile, str[7], ',');
	getline(teacherFile, temp, ',');
	age = stoi(temp);
	getline(teacherFile, temp, ',');
	dob = Date(temp);
	getline(teacherFile, temp, ',');
	yrTaught = stoi(temp);
	getline(teacherFile, temp, '\n');
	classNo = stoi(temp);

	teacherFile.close();
	return Teacher(str, age, yrTaught, classNo, dob);
}

Teacher GetTeacherByUsername(string username, string* login)
{
	ifstream teacherFile("data/teachers.csv", ios::in);
	string fileName;
	int index = 0;
	while (teacherFile.peek() != -1)
	{
		getline(teacherFile, fileName, ',');
		if (fileName == username)
		{
			*login = fileName;
			getline(teacherFile, fileName, ',');
			*(login + 1) = fileName;
			teacherFile.close();
			return FetchTeacher(index);
		}
		getline(teacherFile, fileName, '\n');
		index++;
	}
	teacherFile.close();
	return Teacher();
}

Account LogInAsTeacher()
{
	string input;
	Teacher teacher;
	Account rtrn;
	string loginDetails[2];
	try
	{
		cout << "\nPlease enter your username: ";
		getline(cin, input);

		teacher = GetTeacherByUsername(input, loginDetails);
		if (teacher.firstName == "NULL")
		{
			throw (string)"\nUsername not found.";
		}

		for (int attempts = 3; attempts > 0; attempts--)
		{
			cout << "\n(Attempts remaining: " << attempts << ") Please enter your password: ";
			getline(cin, input);
			if (input == loginDetails[1])
			{
				cout << "\nYou have now logged in as " << teacher.firstName << " " << teacher.lastName << endl;
				rtrn = Account(loginDetails, &teacher);
				break;
			}
			else
			{
				cout << "\nYour password was incorrect." << endl;
				if (attempts == 1)
				{
					throw (string)"You ran out of attempts to enter the password";
				}
			}
		}
	}
	catch (string error)
	{
		cout << endl << error << endl;
	}

	Sleep(1500);
	return rtrn;
}

Account TeacherAccountManagement(Account user)
{
	while (true)
	{
		if (user.accessLevel >= teacherKey)
		{
			int option = 0;
			system("CLS");
			cout << "-------------------------------------------------------" << endl;
			cout << "|     Emerald Hill High School Information System     |" << endl;
			cout << "|                   Teacher Log out                   |" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "\n1. Log out\n\n2. Return to Main Menu\n[Enter your option]: ";
			option = GetIntInput(1, 2);
			switch (option)
			{
			case 1:
				user = Account();
				cout << "\nYou have logged out";
				Sleep(1500);
				break;
			case 2:
				system("CLS");
				return user;
			}
		}
		else if (user.accessLevel == defaultUser)
		{
			int option = 0;
			system("CLS");
			cout << "-------------------------------------------------------" << endl;
			cout << "|     Emerald Hill High School Information System     |" << endl;
			cout << "|              Teacher Log In / Register              |" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "\n1. Log into an existing account\n2. Register a new account\n3. Return to Main Menu\n[Enter your option]: ";
			option = GetIntInput(1, 4);
			switch (option)
			{
			case 1:
				user = LogInAsTeacher();
				break;
			case 2:
				user = RegisterNewTeacher();
				break;
			case 3:
				system("CLS");
				return user;
			case 4:
				FetchTeachers();
				Sleep(15000);
				break;
			}
		}
		else
		{
			system("CLS");
			cout << "Please log out of your current account before attempting to log in as a teacher";
			Sleep(1500);
			return user;
		}
	}
}

void TeacherFunctions()
{
	while (true)
	{
		int option = 0;
		system("CLS");
		cout << "-------------------------------------------------------" << endl;
		cout << "|     Emerald Hill High School Information System     |" << endl;
		cout << "|          Teacher Student Record Management          |" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "\n1. View Student Record\n2. Edit Student Record\n\n3. Return to main menu\n[Enter your option]: ";
		option = GetIntInput(1, 3);
		switch (option)
		{
		case 1:
			DisplayStudent();
			Sleep(1500);
			break;
		case 2:
			EditStudent();
			Sleep(1500);
			break;
		case 3:
			system("CLS");
			return;
		}
	}
}

//-------------------Admin-Functions----------------------
void ChangeAdminPassword()
{
	string input, password;
	ifstream adminFile("data/admin.txt", ios::in);

	getline(adminFile, password);

	adminFile.close();

	cout << "Please enter the current admin password before attempting to change it: ";
	getline(cin, input);
	if (input != password)
	{
		cout << "Sorry, you entered the wrong password. You cannot change the password.";
		Sleep(1500);
		return;
	}

	cout << "Please enter your new password: ";
	getline(cin, input);

	ofstream adminFile2("data/admin.txt", ios::trunc);

	adminFile2 << input;

	adminFile2.close();

	cout << "\nYou have changed the admin password to " << input;
	Sleep(1500);

	return;
}

Account LogInAsAdmin()
{
	ifstream adminFile("data/admin.txt", ios::in);
	string input, login[2] = { "admin", "null" };
	
	getline(adminFile, login[1]);

	cout << "\nPlease enter the admin password: ";
	getline(cin, input);

	if (input == login[1])
	{
		cout << "\nYou have now logged in as the Admin";
		Sleep(1500);
		return Account(login);
	}

	cout << "\nYour password was incorrect. You have not been logged in as the admin";
	Sleep(1500);
	return Account();
}

Account AdminManagement(Account user)
{
	while (true)
	{
		if (user.accessLevel == adminKey)
		{
			int option = 0;
			system("CLS");
			cout << "-------------------------------------------------------" << endl;
			cout << "|     Emerald Hill High School Information System     |" << endl;
			cout << "|                    Admin Log Out                    |" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "\n1. Log out\n2. Change Admin Password\n\n3. Return to Main Menu\n[Enter your option]: ";
			option = GetIntInput(1, 4);
			switch (option)
			{
			case 1:
				user = Account();
				cout << "\nYou have now logged out";
				Sleep(1500);
				break;
			case 2:
				ChangeAdminPassword();
				break;
			case 3:
				system("CLS");
				return user;
			}
		}
		else if (user.accessLevel == defaultUser)
		{
			int option = 0;
			system("CLS");
			cout << "-------------------------------------------------------" << endl;
			cout << "|     Emerald Hill High School Information System     |" << endl;
			cout << "|                     Admin Log In                    |" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "\n1. Log in\n\n2. Return to Main Menu\n[Enter your option]: ";
			option = GetIntInput(1, 2);
			switch (option)
			{
			case 1:
				user = LogInAsAdmin();
				break;
			case 2:
				system("CLS");
				return user;
			}
		}
		else
		{
			system("CLS");
			cout << "Please log out of your current account before attempting to log in as the admin";
			Sleep(1500);
			return user;
		}
	}
}

void GenerateStudents(int count);

void AdminFunctions()
{
	while (true)
	{
		int option = 0;
		system("CLS");
		cout << "-------------------------------------------------------" << endl;
		cout << "|     Emerald Hill High School Information System     |" << endl;
		cout << "|            Admin School Record Management           |" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "\n1. View Student Records\n2. View Parent Records\n3. Report of stuggling children\n4. Report of successful children\n\n5. Return to main menu\n\n[Enter your option]: ";
		option = GetIntInput(1, 6);
		switch (option)
		{
		case 1:
			DisplayAllStudents();
			break;
		case 2:
			FetchParents();
			break;
		case 3:
			DisplayAllStudents(1, "struggling");
			break;
		case 4:
			DisplayAllStudents(4, "excelling");
			break;
		case 5:
			system("CLS");
			return;
		case 6:
			GenerateStudents(50);
			break;
		}

		cout << "\nPress enter to continue... ";
		string temp;
		getline(cin, temp, '\n');
	}
}

//-------------------Student-Functions----------------------
void GenerateStudents(int count)
{
	srand(count);
	for (int i = 0; i < count; i++)
	{
		int ints[7];
		string strings[3];
		
		strings[0] = firstNames[rand() % 20];
		strings[1] = lastNames[rand() % 17];
		strings[2] = (rand() % 2 == 1) ? "Female" : "Male";
		ints[0] = rand() % 4 + 1;
		ints[1] = rand() % 4 + 1;
		ints[2] = rand() % 4 + 1;
		ints[3] = rand() % 4 + 1;
		ints[4] = rand() % 4 + 1;
		ints[5] = rand() % 4 + 1;
		ints[6] = rand() % 7 + 5;

		StudentRecord student = StudentRecord(strings, ints);
		student.WriteToFile();
	}
}

StudentRecord FetchStudent(int index)
{
	ifstream studentFile("data/students.csv", ios::in);

	int ints[7];
	string strings[4];

	try
	{
		for (int i = 0; i < index; i++)
		{
			getline(studentFile, strings[0], '\n');
		}

		if (studentFile.peek() == -1)
		{
			throw (string)"Your Student Number was not found in our records";
		}
		getline(studentFile, strings[0], ',');
		getline(studentFile, strings[1], ',');
		getline(studentFile, strings[2], ',');
		getline(studentFile, strings[3], ',');
		ints[0] = stoi(strings[3]);
		getline(studentFile, strings[3], ',');
		ints[1] = stoi(strings[3]);
		getline(studentFile, strings[3], ',');
		ints[2] = stoi(strings[3]);
		getline(studentFile, strings[3], ',');
		ints[3] = stoi(strings[3]);
		getline(studentFile, strings[3], ',');
		ints[4] = stoi(strings[3]);
		getline(studentFile, strings[3], ',');
		ints[5] = stoi(strings[3]);
		getline(studentFile, strings[3], '\n');
		ints[6] = stoi(strings[3]);

		studentFile.close();
		return StudentRecord(strings, ints);
	}
	catch (string error)
	{
		cout << error << endl;
		Sleep(1500);
		return StudentRecord();
	}
}

StudentRecord GetStudentByName(int* rtrn = nullptr)
{
	string fn, ln;
	int index = 0;

	ifstream studentFile("data/students.csv", ios::in);

	cout << "\nPlease enter the students first name: ";
	getline(cin, fn);
	cout << "\nPlease enter the students last name: ";
	getline(cin, ln);
	cout << "\n\nSearching for student " << fn << " " << ln;
	while (studentFile.peek() != -1)
	{
		string f1, f2;
		getline(studentFile, f1, ',');
		if (fn == f1)
		{
			cout << ". ";
			getline(studentFile, f2, ',');
			if (ln == f2)
			{
				cout << endl << endl;
				*rtrn = index;
				return FetchStudent(index);
			}
		}
		getline(studentFile, f1, '\n');
		index++;
	}

	cout << "\nYour name was not found in our records";
	Sleep(1500);
	return StudentRecord();
}

void DisplayStudent()
{
	int choice;
	cout << "\n\nWould you rather find a student by\n1. Name\n2. Student number\n[Enter your option]: ";
	choice = GetIntInput(1, 2);
	StudentRecord student;
	switch (choice)
	{
	case 1:
		student = GetStudentByName();
		break;
	case 2:
		int index;
		cout << "\n\nPlease enter the Student Number of the student you wish to view: ";
		index = GetIntInput(1);
		student = FetchStudent(index - 1);
		break;
	}

	if (student.firstName == "NULL")
	{
		return;
	}
	student.DisplayInfo();
	cout << "Press enter to continue... ";
	string temp;
	getline(cin, temp, '\n');
}

void EditStudent()
{
	int input = 0, index = 0;
	vector<StudentRecord> students;
	int choice;
	cout << "\n\nWould you rather find a student by\n1. Name\n2. Student number\n[Enter your option]: ";
	choice = GetIntInput(1, 2);
	StudentRecord student;
	switch (choice)
	{
	case 1:
		student = GetStudentByName(&input);
		break;
	case 2:
		cout << "\n\nPlease enter the Student Number of the student you wish to edit: ";
		input = GetIntInput(1);
		student = FetchStudent(index - 1);
		break;
	}

	ifstream readFile("data/students.csv");

	while (readFile.peek() != -1)
	{
		int ints[7];
		string strings[4];

		getline(readFile, strings[0], ',');
		getline(readFile, strings[1], ',');
		getline(readFile, strings[2], ',');
		getline(readFile, strings[3], ',');
		ints[0] = stoi(strings[3]);
		getline(readFile, strings[3], ',');
		ints[1] = stoi(strings[3]);
		getline(readFile, strings[3], ',');
		ints[2] = stoi(strings[3]);
		getline(readFile, strings[3], ',');
		ints[3] = stoi(strings[3]);
		getline(readFile, strings[3], ',');
		ints[4] = stoi(strings[3]);
		getline(readFile, strings[3], ',');
		ints[5] = stoi(strings[3]);
		getline(readFile, strings[3], '\n');
		ints[6] = stoi(strings[3]);

		StudentRecord student = StudentRecord(strings, ints);

		if (index == input)
		{
			student.EditInfo();
		}

		students.push_back(student);

		index++;
	}

	readFile.close();

	ofstream writeFile("data/students.csv", ios::trunc);
	writeFile.close();

	for (StudentRecord student : students)
	{
		student.WriteToFile();
	}
}

void DisplayAllStudents(int value, string str)
{
	int index = 0;

	ifstream readFile("data/students.csv", ios::in);
	if (value == -1)
	{
		while (readFile.peek() != -1)
		{
			int ints[7];
			string strings[4];

			getline(readFile, strings[0], ',');
			getline(readFile, strings[1], ',');
			getline(readFile, strings[2], ',');
			getline(readFile, strings[3], ',');
			ints[0] = stoi(strings[3]);
			getline(readFile, strings[3], ',');
			ints[1] = stoi(strings[3]);
			getline(readFile, strings[3], ',');
			ints[2] = stoi(strings[3]);
			getline(readFile, strings[3], ',');
			ints[3] = stoi(strings[3]);
			getline(readFile, strings[3], ',');
			ints[4] = stoi(strings[3]);
			getline(readFile, strings[3], ',');
			ints[5] = stoi(strings[3]);
			getline(readFile, strings[3], '\n');
			ints[6] = stoi(strings[3]);

			StudentRecord student = StudentRecord(strings, ints);
			student.DisplayInfo(index);
			cout << endl;
		}
	}
	else
	{
		int ints[7];
		string strings[4];
		vector<StudentRecord> mathsVec, scienceVec, englishVec, sportsVec, artVec, behaviourVec;

		while (readFile.peek() != -1)
		{
			int ints[7];
			string strings[4];

			getline(readFile, strings[0], ',');
			getline(readFile, strings[1], ',');
			getline(readFile, strings[2], ',');
			getline(readFile, strings[3], ',');
			ints[0] = stoi(strings[3]);
			getline(readFile, strings[3], ',');
			ints[1] = stoi(strings[3]);
			getline(readFile, strings[3], ',');
			ints[2] = stoi(strings[3]);
			getline(readFile, strings[3], ',');
			ints[3] = stoi(strings[3]);
			getline(readFile, strings[3], ',');
			ints[4] = stoi(strings[3]);
			getline(readFile, strings[3], ',');
			ints[5] = stoi(strings[3]);
			getline(readFile, strings[3], '\n');
			ints[6] = stoi(strings[3]);

			StudentRecord student = StudentRecord(strings, ints);

			if (student.studentScore[maths] == value)
			{
				mathsVec.push_back(student);
			}
			if (student.studentScore[science] == value)
			{
				scienceVec.push_back(student);
			}
			if (student.studentScore[english] == value)
			{
				englishVec.push_back(student);
			}
			if (student.studentScore[sports] == value)
			{
				sportsVec.push_back(student);
			}
			if (student.studentScore[arts] == value)
			{
				artVec.push_back(student);
			}
			if (student.studentScore[behaviour] == value)
			{
				behaviourVec.push_back(student);
			}
		}

		if (mathsVec.size() > 0)
		{
			cout << "\n-----------------------\nStudents who are " << str << " at maths\n-----------------------\n";
			for (StudentRecord student : mathsVec)
			{
				student.DisplayName();
			}
		}
		else
		{
			cout << "\n-----------------------\nThere are currently no students who are " << str << " at maths\n-----------------------";
		}
		if (scienceVec.size() > 0)
		{
			cout << "\n-----------------------\nStudents who are " << str << " at science\n-----------------------\n";
			for (StudentRecord student : scienceVec)
			{
				student.DisplayName();
			}
		}
		else
		{
			cout << "\n-----------------------\nThere are currently no students who are " << str << " at science\n-----------------------";
		}
		if (englishVec.size() > 0)
		{
			cout << "\n-----------------------\nStudents who are " << str << " at english\n-----------------------\n";
			for (StudentRecord student : englishVec)
			{
				student.DisplayName();
			}
		}
		else
		{
			cout << "\n-----------------------\nThere are currently no students who are " << str << " at english\n-----------------------";
		}
		if (sportsVec.size() > 0)
		{
			cout << "\n-----------------------\nStudents who are " << str << " at sports\n-----------------------\n";
			for (StudentRecord student : sportsVec)
			{
				student.DisplayName();
			}
		}
		else
		{
			cout << "\n-----------------------\nThere are currently no students who are " << str << " at sports\n-----------------------";
		}
		if (artVec.size() > 0)
		{
			cout << "\n-----------------------\nStudents who are " << str << " in the arts\n-----------------------\n";
			for (StudentRecord student : artVec)
			{
				student.DisplayName();
			}
		}
		else
		{
			cout << "\n-----------------------\nThere are currently no students who are " << str << " in the arts\n-----------------------";
		}
		if (behaviourVec.size() > 0)
		{
			cout << "\n-----------------------\nStudents who are " << str << " with their behaviour\n-----------------------\n";
			for (StudentRecord student : behaviourVec)
			{
				student.DisplayName();
			}
		}
		else
		{
			cout << "\n-----------------------\nThere are currently no students who are " << str << " with their behaviour\n-----------------------";
		}
	}

	readFile.close();
}

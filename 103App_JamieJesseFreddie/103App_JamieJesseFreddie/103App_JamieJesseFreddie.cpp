#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <vector>
#include <windows.h>

using namespace std;

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
			cout << "Information for [arent " << index << " (" << firstName << " " << lastName << ")\n";
		}
		else
		{
			cout << "Information for teacher " << firstName << " " << lastName << endl;
		}
		cout << "Date of birth: " << dob.fullDate << "\Email Address: " << email << "\nContact Phone: " << contactNumber << "\n\nEmergenct Contact : " << eFirstName << " " << eLastName 
			<< "\nEmergenct Contact Phone Number: " << eContactNumber << endl << endl;
	}
} Parent;

typedef struct StudentRecords { // Jamie - Placeholder Student Struct, just for testing. Work out a new one with Freddie.
	string firstName;
	string lastName;
	vector<string> Classes;


} Student;

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

int GetIntInput(int min = -2147483647, int max = 2147483647); //Freddie Rive
string GetNewPassword(); //Freddie Rive
Account ParentAccountManagement(Account user);
Account TeacherAccountManagement(Account user); //Freddie Rive
Account AdminManagement(Account user); //Freddie Rive
void ParentFunctions();
void TeacherFunctions();
void AdminFunctions();
int main();

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
	ifstream parentFile("data/teachers.csv", ios::in);

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

	return Account();
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
		cout << "\n1. View Student Record\n2. Edit student record\n3. View class report\n\n4. Return to main menu\n[Enter your option]: ";
		option = GetIntInput(1, 5);
		switch (option)
		{
		case 1:
			cout << "cant do this yet";
			Sleep(1500);
			break;
		case 2:
			cout << "cant do this yet";
			Sleep(1500);
			break;
		case 3:
			cout << "cant do this yet";
			Sleep(1500);
			break;
		case 4:
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
			cout << error << " Try again: ";
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
	classNo = GetIntInput(0);

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
		cout << "\n1. View Student Record\n2. Edit student record\n3. View class report\n\n4. Return to main menu\n[Enter your option]: ";
		option = GetIntInput(1, 4);
		switch (option)
		{
		case 1:
			cout << "cant do this yet";
			Sleep(1500);
			break;
		case 2:
			cout << "cant do this yet";
			Sleep(1500);
			break;
		case 3:
			cout << "cant do this yet";
			Sleep(1500);
			break;
		case 4:
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
		cout << "\n1. View Class Records\n2. View Parent Records\n3. Report of stuggling children\n4. Report of successful children\n\n5. Return to main menu\n\n[Enter your option]: ";
		option = GetIntInput(1, 5);
		switch (option)
		{
		case 1:
			cout << "waiting for the student records";
			break;
		case 2:
			cout << "ill do this in a sec";
			break;
		case 3:
			cout << "waiting for the student records";
			break;
		case 4:
			cout << "waiting for the student records";
			break;
		case 5:
			system("CLS");
			return;
		}
	}
}


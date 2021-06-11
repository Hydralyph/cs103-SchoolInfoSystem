#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

int GetIntInput(int min = -2147483647, int max = 2147483647);
string GetNewPassword();

struct Date
{
	unsigned int day, month, year;
	string fullDate, dayName;

	Date(int d = 1, int m = 1, int y = 2021)
	{
		y = max(y, 1);
		monthLength[1] = (y % 4 == 0) ? 29 : 28;
		m = min(max(m, 1), 12);
		d = min(max(d, 1), monthLength[m - 1]);
		fullDate = d + "/";
		fullDate += m + "/";
		fullDate += y;
		day = d;
		month = m;
		year = y;

		int dayNo = 0;
		for (int i = 0; i < m - 1; i++)
		{
			dayNo += monthLength[i];
		}
		dayNo += day;

		dayName = days[Loop(dayNo % 7 + 3)];
	}

	Date(string str)
	{
		if (str.length() == 10)
		{
			int d = ((str[0] - '0') * 10) + (str[1] - '0');
			int m = ((str[3] - '0') * 10) + (str[4] - '0');
			int y = ((str[6] - '0') * 1000) + ((str[7] - '0') * 100) + ((str[8] - '0') * 10) + (str[0] - '0');

			y = max(y, 1);
			monthLength[1] = (y % 4 == 0) ? 29 : 28;
			m = min(max(m, 1), 12);
			d = min(max(d, 1), monthLength[m - 1]);

			fullDate = str;
			day = d;
			month = m;
			year = y;

			int dayNo = 0;
			for (int i = 0; i < m - 1; i++)
			{
				dayNo += monthLength[i];
			}
			dayNo += day;

			dayName = days[Loop(dayNo % 7 + 3)];
		}
		else
		{
			day = 1;
			month = 1;
			year = 2021;
			fullDate = "01/01/2021";
			dayName = "Friday";
		}
	}

	int Loop(int input)
	{
		while (input > 6)
		{
			input -= 7;
		} 
		return input;
	}

private:
	int monthLength[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	std::string days[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
};

struct Teacher {
	string firstName, middleName, lastName, gender, email, username, password, contactNo;
	int age, yrTaught, classNo;
	Date dob;
	Teacher* ptr[2];

	Teacher(string* str, int a = 0, int tght = 0, int clss = 0, Date d = Date())
	{
		this->firstName = *(str + 2);
		this->middleName = *(str + 3);
		this->lastName = *(str + 4);
		this->gender = *(str + 5);
		this->email = *(str + 6);
		this->username = *(str);
		this->password = *(str + 1);
		this->age = a;
		this->contactNo = *(str + 7);
		this->yrTaught = tght;
		this->classNo = clss;
		this->dob = d;
		this->ptr[0] = nullptr;
		this->ptr[1] = nullptr;
	}

	void DisplayInfo()
	{
		cout << "\nInformation for teacher " << lastName << ", " << firstName << " " << middleName << endl;
		cout << "Age: " << age << "\nDate of birth: " << dob.fullDate << "\nGender: " << gender << "\nContact Phone: " << contactNo << "\nEmail Address: " << email << "\nYear Taught: " 
			<< yrTaught << "\nClassroom number: " << classNo << endl;
	}
};

Teacher RegisterNewTeacher(Teacher *first)
{
	string str[8], dateStr;
	int age, contactNo, yrTaught, classNo;
	Date dob;

	cout << "Please enter your new username: ";
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

	ofstream teacherFile("teachers.txt", ios::app);

	teacherFile << str[0] << endl << str[1] << endl << str[2] << endl << str[3] << endl << str[4] << endl << age << endl << date.fullDate << endl << str[5] << endl << str[6] << endl
		<< str[7] << endl << yrTaught << endl << classNo << endl;

	teacherFile.close();

	Teacher rtrn = Teacher(str, age, yrTaught, classNo, dob);

	if (first != nullptr)
	{
		while (first->ptr[1] != nullptr)
		{
			first = first->ptr[1];
		}

		rtrn.ptr[0] = first;
		first->ptr[1] = &rtrn;
	}
	return rtrn;
}

Teacher* FetchTeachers()
{
	ifstream teacherFile("teachers.txt", ios::in);

	Teacher* first = nullptr;
	Teacher* prev = nullptr;
	while (teacherFile.peek() != -1)
	{
		string str[8], dateStr, temp;
		int age, contactNo, yrTaught, classNo;
		Date dob;

		getline(teacherFile, str[0]);
		getline(teacherFile, str[1]);
		getline(teacherFile, str[2]);
		getline(teacherFile, str[3]);
		getline(teacherFile, str[4]);
		teacherFile >> age;
		getline(teacherFile, temp);//moving down line in file
		getline(teacherFile, dateStr);
		dob = Date(dateStr);
		getline(teacherFile, str[5]);
		getline(teacherFile, str[6]);
		getline(teacherFile, str[7]);
		teacherFile >> yrTaught;
		getline(teacherFile, temp);//moving down line in file
		teacherFile >> classNo;
		getline(teacherFile, temp);//moving down line in file
		getline(teacherFile, temp);//moving down line in file

		Teacher teach = Teacher(str, age, yrTaught, classNo, dob);
		teach.DisplayInfo();

		if (prev != nullptr)
		{
			prev->ptr[1] = &teach;
			teach.ptr[0] = prev;
		}
		prev = &teach;

		if (first == nullptr)
		{
			first = &teach;
		}
	}

	return first;
}

int main()
{
	Teacher* teacherLinkedList = FetchTeachers();
	Teacher teach = RegisterNewTeacher(teacherLinkedList);
	
	teach.DisplayInfo();

	return 0;
}

int GetIntInput(int min, int max)
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
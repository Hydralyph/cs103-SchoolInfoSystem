#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Class {
	string className;
};

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

		dayName = days[((int)floor(dayNo / 7) + dayNo % 7) + 5];
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

			dayName = days[((int)floor(dayNo / 7) + dayNo % 7) + 5];
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

private:
	int monthLength[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	std::string days[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
};

struct Teacher {
	string firstName, middleName, lastName, gender, email, username, password;
	int age, contactNo, yrTaught, classNo;
	Date dob;

	Teacher(string *str, int a = 0, int cntc = 0, int tght = 0, int clss = 0, Date d = Date())
	{
		this->firstName = *(str + 2);
		this->middleName = *(str + 3);
		this->lastName = *(str + 4);
		this->gender = *(str + 5);
		this->email = *(str + 6);
		this->username = *(str);
		this->password = *(str + 1);
		this->age = a;
		this->contactNo = cntc;
		this->yrTaught = tght;
		this->classNo = clss;
		this->dob = d;
	}
};

int GetIntInput(int min = -2147483647, int max = 2147483647)
{
	int rtrn;
	while (true)
	{
		try
		{
			cin >> rtrn;
			if (rtrn < min || rtrn > max )
			{
				throw rtrn;
			}
			break;
		}
		catch (...)
		{
			cin.ignore();
			cin.clear();
			cout << "Invalid input. Try again: ";
		}
	}
	cin.ignore();
	return rtrn;
}

string GetNewPassword()
{
	string rtrn, check;
	cout << "\n\nPlease enter your new password: ";
	getline(cin, rtrn);
	while (true)
	{
		cout << "\n\nPlease re-enter your password to confirm: ";
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



Teacher RegisterNewTeacher()
{
	string str[7], dateStr;
	int age, contactNo, yrTaught, classNo;
	Date *dob;
	bool flag;
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
	dob = &date;
	cout << "\nPlease enter your gender: ";
	getline(cin, str[5]);
	cout << "\nPlease enter your email address: ";
	getline(cin, str[6]);
	cout << "\nPlease enter your contact phone number: ";
	contactNo = GetIntInput(0);
	cout << "\nPlease enter the year you teach at our school: ";
	yrTaught = GetIntInput(0, 13);
	cout << "\nPlease enter your classroom number: ";
	classNo = GetIntInput(0);

	return Teacher(str, age, contactNo, yrTaught, classNo, *dob);
}

int main()
{
	Teacher teach = RegisterNewTeacher();

	cout << teach.lastName << ", " << teach.firstName << ": " << teach.dob.fullDate;

	return 0;
}
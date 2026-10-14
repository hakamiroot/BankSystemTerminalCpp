#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace myinput
{
	// Declarations
	void swap(int&, int&);
	void ReadVectorNumbers(vector <int>&);
	int ReadInteger();
	int ReadInteger(int From, int To);
	int ReadPositiveInteger();
	int ReadPositiveInteger(int From, int To);
	short ReadShort();
	short ReadShort(short From, short To);
	bool isYes(string Text);
	string ReadString();
	char ReadChar();

	// Definitions
	void swap(int& num1, int& num2)
	{
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}

	int ReadInteger()
	{
		string text = "";
		cin >> text;
		char sign = 1;

		while (true)
		{
		start:
			if (text[0] == '-' && text.length() > 1)
			{
				text = text.substr(1, text.length() - 1);
				sign = -1;
			}

			for (char c : text)
			{
				int n = (int)c;

				if (n < 48 || n > 57)
				{
					cout << "Invalid integer number, please enter a valid one: ";
					cin >> text;
					goto start;
				}
			}
			return std::stoi(text) * sign;
		}
	}

	int ReadInteger(int From, int To)
	{
		int number = ReadInteger();
		From = _CMATH_::abs(From);
		To = _CMATH_::abs(To);

		if (From > To)
			swap(From, To);

		while (number < From || number > To)
		{
			cout << "Please enter a number between " + to_string(From) + " and " + to_string(To) + ": ";
			number = ReadInteger();
		}

		return number;
	}

	int ReadPositiveInteger()
	{
		int number = ReadInteger();

		while (number < 0)
		{
			cout << "Please enter a positive number: ";
			number = ReadInteger();
		}

		return number;
	}

	int ReadPositiveInteger(int From, int To)
	{
		int number = ReadPositiveInteger();

		From = _CMATH_::abs(From);
		To = _CMATH_::abs(To);

		if (From > To)
			swap(From, To);

		while (number < From || number > To)
		{
			cout << "Please enter a number between " + to_string(From) + " and " + to_string(To) + ": ";
			number = ReadPositiveInteger();
		}

		return number;
	}

	short ReadShort()
	{
		return (short) ReadInteger();
	}

	short ReadShort(short From, short To)
	{
		return (short)ReadInteger(From, To);
	}

	bool isYes(string Text = "")
	{
		string answer = "";

		do
		{
			cout << Text + " (y/n): ";
			cin >> answer;
			cin.ignore();

			if (answer == "y")
				return true;
			else if (answer == "n")
				return false;

		} while (true);
	}

	void ReadVectorNumbers(vector <int>& vNumbers)
	{
		short counter = 0;
		do
		{
			counter++;
			cout << "Enter number [" + to_string(counter) + "]: ";
			vNumbers.push_back(myinput::ReadInteger());

		} while (isYes("\nDo you want to add more number?"));
	}

	string ReadString()
	{
		string text = "";

		// Clear any leftover characters in the input buffer
		if (cin.peek() == '\n')
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		getline(cin, text);

		return text;
	}

	char ReadChar()
	{
		return (char)ReadInteger();
	}
}
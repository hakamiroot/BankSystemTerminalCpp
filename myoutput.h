#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

namespace myoutput
{
	// Declarations
	void PrintVector(vector <int>&);
	void PrintVectro(vector <string>&);
	void PrintFileContent(string);
	string AdjustColumn(string, short);
	string getLineOfChars(char, short);

	// Definitions
	void PrintVector(vector <int>& vNumbers)
	{
		cout << "\nInt Vector:\n[";
		for (int& num : vNumbers)
		{
			cout << num << " ";
		}
		cout << "]\n";
	}

	void PrintVectro(vector <string>& vTexts)
	{
		cout << "\nString Vectro:\n";

		for (string& line : vTexts)
		{
			cout << line << endl;
		}
	}

	void PrintFileContent(string FileName)
	{
		fstream file;
		file.open(FileName, ios::in); // Read Mode

		if (file.is_open()) // Check whether the file is open or exist.
		{
			string line = "";

			// Print file content line by line.
			while (getline(file, line))
			{
				cout << line << endl;
			}

			file.close();
		}
	}

	string AdjustColumn(string Text, short ColumnWidth)
	{
		ColumnWidth = ColumnWidth - (short)Text.length();

		if (ColumnWidth >= 0)
		{
			for (short i = 1; i <= ColumnWidth; i++)
				Text += " ";
		}

		return Text;
	}

	string getLineOfChars(char c, short LineLength)
	{
		string line = "";

		for (short i = 1; i <= LineLength; i++)
			line += c;

		return line;
	}
}

#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace mystring
{
	string UpperFirstLetterOfEachWord(string Text)
	{
		bool isFirstLetter = true;

		for (int x = 0; x < Text.length(); x++)
		{
			if (Text[x] != ' ' && isFirstLetter)
			{
				Text[x] = std::toupper(Text[x]);
			}

			isFirstLetter = (Text[x] == ' ' ? true : false);
		}

		return Text;
	}

	string LowerFirstLetterOfEachWord(string Text)
	{
		bool isFirstLetter = true;

		for (int x = 0; x < Text.length(); x++)
		{
			if (Text[x] != ' ' && isFirstLetter)
			{
				Text[x] = std::tolower(Text[x]);
			}

			isFirstLetter = (Text[x] == ' ' ? true : false);
		}

		return Text;
	}

	string UpperAllString(string Text)
	{
		for (int x = 0; x < Text.length(); x++)
		{
			Text[x] = std::toupper(Text[x]);
		}

		return Text;
	}

	string LowerAllString(string Text)
	{
		for (char& c : Text)
		{
			c = std::tolower(c);
		}

		return Text;
	}

	char InvertLetterCase(char L)
	{
		return (isupper(L) ? tolower(L) : toupper(L));
	}

	string InvertAllLettersCase(string Text)
	{
		for (char& c : Text)
		{
			c = InvertLetterCase(c);
		}

		return Text;
	}

	int CountCapitalLetters(string Text)
	{
		int counter = 0;

		for (char& c : Text)
		{
			if (isupper(c))
				counter++;
		}

		return counter;
	}

	int CountSmallLetters(string Text)
	{
		int counter = 0;

		for (char& c : Text)
		{
			if (islower(c))
				counter++;
		}

		return counter;
	}

	short CountLetter(string Text, char Letter, bool MatchCase = true)
	{
		short counter = 0;

		for (const char& c : Text)
		{
			if (MatchCase)
			{
				if (c == Letter)
					counter++;
			}
			else if (tolower(c) == tolower(Letter))
				counter++;
		}
		return counter;
	}

	bool isVowel(char Letter)
	{
		Letter = tolower(Letter);
		return (Letter == 'a' || Letter == 'e' || Letter == 'i' || Letter == 'o' || Letter == 'u');
	}

	short CountAllVowels(string Text)
	{
		short Counter = 0;

		for (const char& Letter : Text)
		{
			if (isVowel(Letter))
				Counter++;
		}

		return Counter;
	}

	short CountWords(string Text)
	{
		short Position = 0, Counter = 0;

		while ((Position = Text.find(" ")) != std::string::npos)
		{
			if (Text.substr(0, Position) != "")
				Counter++;

			Text.erase(0, Position + 1);
		}

		if (Text != "")
			Counter++;

		return Counter;
	}

	vector<string> SplitStringIntoVector(string Text, string Delimitor)
	{
		vector<string> vString;
		short Position = 0;
		string Word = "";

		while ((Position = Text.find(Delimitor)) != std::string::npos)
		{
			Word = Text.substr(0, Position);

			if (Word != "")
				vString.push_back(Word);

			Text.erase(0, Position + Delimitor.length());
		}

		if (Text != "")
			vString.push_back(Text);

		return vString;
	}

	string TrimLeft(string Text)
	{
		for (int x = 0; x < Text.length(); x++)
		{
			if (Text[x] != ' ')
				return Text.substr(x, Text.length() - x);
		}

		return "";
	}

	string TrimRight(string Text)
	{
		for (int x = Text.length() - 1; x >= 0; x--)
		{
			if (Text[x] != ' ')
				return Text.substr(0, x + 1);
		}

		return "";
	}

	string Trim(string Text)
	{
		return TrimLeft(TrimRight(Text));
	}

	string JoinString(vector<string> vString, string Delimiter)
	{
		string Text = "";

		for (const string& Word : vString)
		{
			Text += Word + Delimiter;
		}

		return Text.substr(0, Text.length() - Delimiter.length());
	}

	string JoinString(string arrString[], short Length, string Delimiter)
	{
		string text = "";

		for (int x = 0; x < Length; x++)
		{
			text += arrString[x] + Delimiter;
		}

		return text.substr(0, text.length() - Delimiter.length());
	}

	string ReverseWords(string Text, string Delimiter)
	{
		vector<string> vString = SplitStringIntoVector(Text, Delimiter);
		Text = "";

		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			iter--;
			Text += *iter + Delimiter;
		}

		return Text.substr(0, Text.length() - Delimiter.length());
	}

	string ReplaceWord(string Text, string ReplacedWord, string AlternativeWord, bool MatchCase = true)
	{
		vector<string> vString = SplitStringIntoVector(Text, " ");
		Text = "";

		for (string& Word : vString)
		{
			if (MatchCase)
			{
				if (Word == ReplacedWord)
					Word = AlternativeWord;
			}
			else
			{
				if (LowerAllString(Word) == LowerAllString(ReplacedWord))
					Word = AlternativeWord;
			}
			Text += Word + " ";
		}

		return Text.substr(0, Text.length() - 1);
	}

	string RemovePunctuation(string Text)
	{
		string Punctuation = ".,;:?(){}[]'!_-";
		short Position = 0;

		for (const char& c : Punctuation)
		{
			while ((Position = Text.find(c)) != std::string::npos)
			{
				Text.erase(Position, 1);
			}
		}

		return Text;
	}

	void AddDataLineToFile(string FileName, string Line)
	{
		fstream File;

		File.open(FileName, ios::app);

		if (File.is_open())
		{
			File << Line << endl;
			File.close();
		}
	}
}

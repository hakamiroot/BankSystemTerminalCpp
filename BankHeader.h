#pragma once
#include <iostream>	
#include <vector>
#include <fstream>
#include "myinput.h"
#include "mystring.h"

using namespace std;

namespace BankHeader
{
	struct stUser
	{
		string Username;
		string Password;
		short Permissions;
	};

	struct stClient
	{
		string AccountNumber;
		string PIN;
		string Name;
		string Phone;
		double AccountBalance;
	};

	vector<stUser> vUsers;
	vector<stClient> vClients;
	stUser CurrentUser;
	const string ClientsFileName = "Clients.txt";
	const string UsersFileName = "Users.txt";
	const string Separator = "#//#";

	enum enMainMenu { eShowClientsList, eAddClients, eDeleteClient, eUpdateClient, eFindClient, eTransactions, eManageUsers, eLogout };
	enum enTransactionsMenu { eDeposit, eWithdraw, eTotalBalances, eMainMenuInTransactionsMenu };
	enum enUsersMenu { eListUsers, eAddUsers, eDeleteUser, eUpdateUser, eFindUser, eMainMenuInUsersMenu };
	enum enUserPermissions { pAll = -1, pShowClientsList = 1, pAddClients = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64 };

	void AddLineToFile(string FileName, string Line)
	{
		fstream File;

		File.open(FileName, ios::app);

		if (File.is_open())
		{
			File << Line << endl;
		}
		File.close();
	}

	// -----------------------------
	stClient ConvertClientLineToClientRecord(string Line)
	{
		stClient Client;
		vector<string> vString = mystring::SplitStringIntoVector(Line, Separator);

		if (vString.size() == 5)
		{
			Client.AccountNumber = vString[0];
			Client.PIN = vString[1];
			Client.Name = vString[2];
			Client.Phone = vString[3];
			Client.AccountBalance = stod(vString[4]);
		}

		return Client;
	}

	string ConvertClientRecordToClientLine(const stClient& Client)
	{
		return (Client.AccountNumber + Separator + Client.PIN + Separator + Client.Name + Separator + Client.Phone + Separator + to_string(Client.AccountBalance));
	}

	vector<stClient> LoadClientsDataFromFileIntoClientVector(string FileName)
	{
		fstream File;
		vClients = {};

		File.open(FileName, ios::in);

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				vClients.push_back(ConvertClientLineToClientRecord(Line));
			}
		}
		File.close();

		return vClients;
	}

	void SaveClientsDataFromVectorIntoFile(const vector<stClient>& Local_vClients)
	{
		fstream File;

		File.open(ClientsFileName, ios::out);
		for (const stClient& Client : Local_vClients)
		{
			File << ConvertClientRecordToClientLine(Client) << endl;
		}
		File.close();
	}

	bool isAccountNumberExists(string& AccountNumber)
	{
		for (const stClient& Client : vClients)
		{
			if (Client.AccountNumber == AccountNumber)
				return true;
		}
		return false;
	}

	string ReadAccountNumber()
	{
		cout << "Enter Account Number: ";
		string AccountNumber = myinput::ReadString();

		while (isAccountNumberExists(AccountNumber))
		{
			cout << "Client with [" + AccountNumber + "] already exists. Enter another one: ";
			AccountNumber = myinput::ReadString();
		}

		return AccountNumber;

	}

	stClient ReadClientData()
	{
		stClient Client;

		cout << endl;
		Client.AccountNumber = ReadAccountNumber();
		cout << "Enter PIN: ";
		Client.PIN = myinput::ReadString();
		cout << "Enter Name: ";
		Client.Name = myinput::ReadString();
		cout << "Enter Phone Number: ";
		Client.Phone = myinput::ReadString();
		cout << "Enter Account Balance: ";
		cin >> Client.AccountBalance;

		return Client;
	}

	stClient ChangeClientData()
	{
		stClient Client;

		cout << "Enter PinCode: ";
		cin >> Client.PIN;
		cout << "Enter Name: ";
		Client.Name = myinput::ReadString();
		cout << "Enter Phone Number: ";
		Client.Phone = myinput::ReadString();
		cout << "Enter Account Balance: ";
		cin >> Client.AccountBalance;

		return Client;
	}

	// -----------------------------
	stUser ConvertUserLineToUserRecord(string Line)
	{
		stUser User;
		vector<string> vUserData = mystring::SplitStringIntoVector(Line, Separator);

		if (vUserData.size() == 3)
		{
			User.Username = vUserData[0];
			User.Password = vUserData[1];
			User.Permissions = stoi(vUserData[2]);
		}

		return User;
	}

	string ConvertUserRecordToUserLine(const stUser& User)
	{
		return User.Username + Separator + User.Password + Separator + to_string(User.Permissions);
	}

	vector<stUser> LoadUsersDataFromFileIntoUserVector()
	{
		fstream File;
		vUsers = {};

		File.open(UsersFileName, ios::in);

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				vUsers.push_back(ConvertUserLineToUserRecord(Line));
			}
		}
		File.close();

		return vUsers;
	}

	bool isUsernameExists(string Username)
	{
		for (const stUser& User : vUsers)
		{
			if (User.Username == Username)
				return true;
		}
		return false;
	}

	bool CheckAccessPermission(enUserPermissions Permission)
	{
		if (CurrentUser.Permissions == enUserPermissions::pAll)
			return true;

		if ((Permission & CurrentUser.Permissions) == Permission)
			return true;
		else
			return false;
	}

	string ReadUsername()
	{
		string Username = myinput::ReadString();
		while (isUsernameExists(Username))
		{
			cout << "Username [" << Username << "] is already exists, enter another one: ";
			Username = myinput::ReadString();
		}

		return Username;
	}

	short ReadUserPermissions()
	{
		short Permissions = 0;

		cout << "\nDo you want to give full access?";
		if (myinput::isYes())
			return -1;

		cout << "\nDo you want to give access to:\nShow Clients List?";
		if (myinput::isYes())
			Permissions += enUserPermissions::pShowClientsList;

		cout << "\nDo you want to give access to:\nAdd Clients?";
		if (myinput::isYes())
			Permissions += enUserPermissions::pAddClients;

		cout << "\nDo you want to give access to:\nDelete Client?";
		if (myinput::isYes())
			Permissions += enUserPermissions::pDeleteClient;

		cout << "\nDo you want to give access to:\nUpdate Client?";
		if (myinput::isYes())
			Permissions += enUserPermissions::pUpdateClient;

		cout << "\nDo you want to give access to:\nFind Client?";
		if (myinput::isYes())
			Permissions += enUserPermissions::pFindClient;

		cout << "\nDo you want to give access to:\nTransactions?";
		if (myinput::isYes())
			Permissions += enUserPermissions::pTransactions;

		return Permissions;
	}

	stUser ReadUserData()
	{
		stUser User;

		cout << endl;
		cout << "Enter the username : ";
		User.Username = ReadUsername();
		cout << "Enter the password: ";
		User.Password = myinput::ReadString();
		cout << "Enter the permissions: ";
		User.Permissions = ReadUserPermissions();

		return User;
	}
}

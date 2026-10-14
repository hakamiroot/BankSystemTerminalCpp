#include <iostream>
#include <vector>
#include <string>
#include "myinput.h"
#include "myoutput.h"
#include "mystring.h"
#include "BankHeader.h"

using namespace std;
using namespace BankHeader;

void ShowManageUsersMenu();
void ShowTransactionsMenu();
void PrintClient(const stClient& Client);
void GoBackToMainMenu();
void ShowMainMenuScreen();
void Login();


int main()
{
	vUsers = LoadUsersDataFromFileIntoUserVector();
	vClients = LoadClientsDataFromFileIntoClientVector(ClientsFileName);
	Login();
}


// -----------------------------
void ShowAccessDeniedMessage()
{
	system("cls");
	cout
		<< "\n-------------------------------------\n"
		<< "Access denied,\nYou don't have permission to do this."
		<< "\n-------------------------------------\n";
}

void PrintUserCard(const stUser& User)
{
	cout
		<< "\nUsername: " << User.Username
		<< "\nPassword: " << User.Password
		<< "\nPermissions: " << User.Permissions
		<< "\n==================================\n";
}

void FindUser()
{
	cout << "==================================================\n";
	cout << "\t\tFind User\n";
	cout << "==================================================\n";

	cout << "Enter the username: ";
	string Username = myinput::ReadString();

	for (const stUser& User : vUsers)
	{
		if (User.Username == Username)
		{
			PrintUserCard(User);
			return;
		}
	}
	cout << "Username [" << Username << "] not found.";
}

void UpdateUser()
{
	cout << "==================================================\n";
	cout << "\t\tUpdate User\n";
	cout << "==================================================\n";

	fstream File;
	string Username;
	bool isUserFound = false, isSure = false;

	cout << "Enter the username to update: ";
	Username = myinput::ReadString();

	File.open(UsersFileName, ios::out);
	for (stUser& User : vUsers)
	{
		if (User.Username == Username)
		{
			isUserFound = true;
			cout << "The following are the user details:";
			PrintUserCard(User);

			if (myinput::isYes("Are you sure you want to update this user?"))
			{
				isSure = true;
				User = ReadUserData();
			}
		}
		File << ConvertUserRecordToUserLine(User);
	}
	File.close();

	if (isSure)
		vUsers = LoadUsersDataFromFileIntoUserVector();
	else if (isUserFound == false)
		cout << "Username [" << Username << "] not found.";
}

void DeleteUser()
{
	cout << "==================================================\n";
	cout << "\t\tDelete User\n";
	cout << "==================================================\n";

	fstream File;
	string Username;
	bool isUserFound = false, isSure = false;

	cout << "Enter the username to delete: ";
	Username = myinput::ReadString();
	
	File.open(UsersFileName, ios::out);
	for (const stUser& User : vUsers)
	{
		if (User.Username != Username)
			File << ConvertUserRecordToUserLine(User) << endl;
		else
		{
			isUserFound = true;
			cout << "The following are the user details:";
			PrintUserCard(User);

			if (myinput::isYes("Are you sure you want to delete this user?"))
				isSure = true;
			else
				File << ConvertUserRecordToUserLine(User) << endl;
		}
	}
	File.close();

	if (isSure)
		vUsers = LoadUsersDataFromFileIntoUserVector();
	else if (isUserFound == false)
		cout << "Username [" << Username << "] not found.";

}

void AddUsers()
{
	cout << "==================================================\n";
	cout << "\t\tAdd Users\n";
	cout << "==================================================\n";

	stUser User;
	do
	{
		User = ReadUserData();
		vUsers.push_back(User);
		AddLineToFile(UsersFileName, ConvertUserRecordToUserLine(User));

	} while (myinput::isYes("\nDo you want to add another user?"));
}

void PrintUser(const stUser& User)
{
	cout
		<< "|" << myoutput::AdjustColumn(User.Username, 15)
		<< "|" << myoutput::AdjustColumn(User.Password, 15)
		<< "|" << myoutput::AdjustColumn(to_string(User.Permissions), 15) << endl;
}

void ListUsers()
{
	cout << "\n\t\t\tUsers List (" << vUsers.size() << ") User(s).\n";

	cout << myoutput::getLineOfChars('-', 90) << endl;
	cout
		<< "|" << myoutput::AdjustColumn("Username", 15)
		<< "|" << myoutput::AdjustColumn("Password", 15)
		<< "|" << myoutput::AdjustColumn("Permissions", 15) << endl;
	cout << myoutput::getLineOfChars('-', 90) << endl;

	for (const stUser& User : vUsers)
	{
		PrintUser(User);
	}
	cout << myoutput::getLineOfChars('-', 90) << endl;
}

void GoBackToManageUsersMenu()
{
	cout << "Press any key to go back to manage users menu...";
	system("pause>0");
	ShowManageUsersMenu();
}

void PerformUsersTask(const enUsersMenu Choice)
{
	switch (Choice)
	{
	case enUsersMenu::eListUsers:
		system("cls");
		ListUsers();
		GoBackToManageUsersMenu();
		break;

	case enUsersMenu::eAddUsers:
		system("cls");
		AddUsers();
		GoBackToManageUsersMenu();
		break;

	case enUsersMenu::eDeleteUser:
		system("cls");
		DeleteUser();
		GoBackToManageUsersMenu();
		break;

	case enUsersMenu::eUpdateUser:
		system("cls");
		UpdateUser();
		GoBackToManageUsersMenu();
		break;

	case enUsersMenu::eFindUser:
		system("cls");
		FindUser();
		GoBackToManageUsersMenu();
		break;

	case enUsersMenu::eMainMenuInUsersMenu:
		GoBackToMainMenu();
		break;
	}
}

void PrintManageUsersMenuScreen()
{
	cout << myoutput::getLineOfChars('=', 50) << endl;
	cout << "\t\tManage Users Menu Screen\n";
	cout << myoutput::getLineOfChars('=', 50) << endl;

	cout
		<< "\t[1] List Users.\n"
		<< "\t[2] Add New User.\n"
		<< "\t[3] Delete User.\n"
		<< "\t[4] Update User.\n"
		<< "\t[5] Find User.\n"
		<< "\t[6] Main Menu.\n";

	cout << myoutput::getLineOfChars('=', 50) << endl;
}

void ShowManageUsersMenu()
{
	if (!CheckAccessPermission(enUserPermissions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	PrintManageUsersMenuScreen();

	cout << "Choose what do you want to do? [1 to 6]: ";
	PerformUsersTask((enUsersMenu) (myinput::ReadShort(1, 6) - 1) );
}



// -----------------------------
void ReadWithdrawAmount(stClient& Client)
{
	double Amount;

	cout << "\nEnter the amount to withdraw: ";
	cin >> Amount;

	if (Amount > Client.AccountBalance)
	{
		cout << "\nThe amount larger than the account balance.\n";
		return;
	}
	Client.AccountBalance -= Amount;
}

void PrintTotalBalances()
{
	cout << myoutput::getLineOfChars('=', 90) << endl;
	cout
		<< "|" + myoutput::AdjustColumn("Account Number", 15)
		+ "|" + myoutput::AdjustColumn("Name", 30)
		+ "|" + myoutput::AdjustColumn("Balance", 15) << endl;
	cout << myoutput::getLineOfChars('=', 90) << endl;

	for (const stClient& Client : vClients)
	{
		cout
			<< "|" + myoutput::AdjustColumn(Client.AccountNumber, 15)
			+ "|" + myoutput::AdjustColumn(Client.Name, 30)
			+ "" + myoutput::AdjustColumn(to_string(Client.AccountBalance), 15) << endl;
	}
}

void PrintWithdrawHeader()
{
	cout << "==================================================\n";
	cout << "\t\tWithdraw\n";
	cout << "==================================================\n";
}

void Withdraw()
{
	cout << "Enter the account number: ";
	string AccountNumber = myinput::ReadString();
	fstream File;

	File.open(ClientsFileName, ios::out);
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			cout << "\nThe following are the client details:\n";
			PrintClient(Client);

			ReadWithdrawAmount(Client);
		}
		File << ConvertClientRecordToClientLine(Client) << endl;
	}
	File.close();
}

void PrintDepositHeader()
{
	cout << "==================================================\n";
	cout << "\t\tDeposit\n";
	cout << "==================================================\n";
}

void Deposit()
{
	PrintDepositHeader();

	cout << "Enter the account number: ";
	string AccountNumber = myinput::ReadString();
	fstream File;

	File.open(ClientsFileName, ios::out);
	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			cout << "\nThe following are the client details:\n";
			PrintClient(Client);

			cout << "Please enter deposit amount: ";
			double amount;
			cin >> amount;
			Client.AccountBalance += amount;
		}
		File << ConvertClientRecordToClientLine(Client) << endl;
	}
	File.close();
}

void GoBackToTransactionsMenu()
{
	cout << "\n\nPress any key to go back to the transactions menu. . .";
	system("pause>0");
	ShowTransactionsMenu();
}

void PerformTransactionsTask(const enTransactionsMenu& Option)
{
	switch (Option)
	{
	case enTransactionsMenu::eDeposit:
		system("cls");
		Deposit();
		GoBackToTransactionsMenu();
		break;

	case enTransactionsMenu::eWithdraw:
		system("cls");
		Withdraw();
		GoBackToTransactionsMenu();
		break;

	case enTransactionsMenu::eTotalBalances:
		system("cls");
		PrintTotalBalances();
		GoBackToTransactionsMenu();
		break;

	case enTransactionsMenu::eMainMenuInTransactionsMenu:
		system("cls");
		ShowMainMenuScreen();
		break;
	}
}

void PrintTransactionsMenuScreen()
{
	cout << myoutput::getLineOfChars('=', 50) << endl;
	cout << "\t\tTransactions Menu Screeen\n";
	cout << myoutput::getLineOfChars('=', 50) << endl;

	cout
		<< "\t[1] Deposit.\n"
		<< "\t[2] Withdraw.\n"
		<< "\t[3] Total Balances.\n"
		<< "\t[4] Main Menu.\n";
	cout << myoutput::getLineOfChars('=', 50) << endl;
}

void ShowTransactionsMenu()
{
	if (!CheckAccessPermission(enUserPermissions::pTransactions))
	{
		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	PrintTransactionsMenuScreen();

	cout << "Choose what do you want to do? [1 - 4]: ";
	const enTransactionsMenu UserChoice = (enTransactionsMenu)(myinput::ReadInteger(1, 4) - 1);
	PerformTransactionsTask(UserChoice);
}

// -----------------------------
void FindClient()
{
	if (!CheckAccessPermission(enUserPermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "Enter the account number: ";
	string AccountNumber = myinput::ReadString();

	for (const stClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			PrintClient(Client);
			return;
		}
	}
	cout << "\nClient of [" + AccountNumber + "] account number not found.";
}

// -----------------------------
void UpdateClient()
{
	if (!CheckAccessPermission(enUserPermissions::pUpdateClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	fstream File;
	bool isClientFound = false, isSure = false;

	cout << "\nEnter the account number: ";
	string AccountNumber = myinput::ReadString();

	File.open(ClientsFileName, ios::out);

	for (stClient& Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			isClientFound = true;

			cout << "\nThe following are the client details:\n";
			PrintClient(Client);

			if (myinput::isYes("Are you sure you want to update it? "))
			{
				isSure = true;
				Client = ChangeClientData();
				Client.AccountNumber = AccountNumber;
				cout << "Client updated successfully.\n";
			}
		}
		File << ConvertClientRecordToClientLine(Client) << endl;
	}
	File.close();

	if (isSure)
		vClients = LoadClientsDataFromFileIntoClientVector(ClientsFileName);
	else if (isClientFound == false)
		cout << "\nClient of [" + AccountNumber + "] account number not found.\n";
}

// -----------------------------
void DeleteClient()
{
	if (!CheckAccessPermission(enUserPermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	fstream File;
	bool isClientFound = false, isSure = false;

	cout << "Enter the account number: ";
	string AccountNumber = myinput::ReadString();

	File.open(ClientsFileName, ios::out);
	for (const stClient& Client : vClients)
	{
		if (Client.AccountNumber != AccountNumber)
		{
			File << ConvertClientRecordToClientLine(Client) << endl;
		}
		else
		{
			isClientFound = true;
			cout << "\nThe following are the client details:\n";
			PrintClient(Client);

			if (myinput::isYes("\nAre sure you want to delete it? "))
			{
				cout << "\nThe client successfully deleted.\n";
				isSure = true;
			}
			else
				File << ConvertClientRecordToClientLine(Client) << endl;
		}
	}
	File.close();

	if (isSure)
		vClients = LoadClientsDataFromFileIntoClientVector(ClientsFileName);
	else if (isClientFound == false)
		cout << "\nClient of [" + AccountNumber + "] account number not found.";
}

// -----------------------------
void AddClients()
{
	if (!CheckAccessPermission(enUserPermissions::pAddClients))
	{
		ShowAccessDeniedMessage();
		return;
	}

	stClient Client;
	do
	{
		Client = ReadClientData();
		vClients.push_back(Client);
		AddLineToFile(ClientsFileName, ConvertClientRecordToClientLine(Client));
		cout
			<< "Client added successfully."
			<< "\n-------------------------------------\n";

	} while (myinput::isYes("Do you want to add more client? "));
}

// -----------------------------
void PrintClient(const stClient& Client)
{
	cout
		<< "|" << myoutput::AdjustColumn(Client.AccountNumber, 15)
		<< "|" << myoutput::AdjustColumn(Client.PIN, 15)
		<< "|" << myoutput::AdjustColumn(Client.Name, 30)
		<< "|" << myoutput::AdjustColumn(Client.Phone, 15)
		<< "|" << myoutput::AdjustColumn(to_string(Client.AccountBalance), 15) << endl;
}

void ShowClientsList()
{
	if (!CheckAccessPermission(enUserPermissions::pShowClientsList))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n\t\t\t\tClients List (" << vClients.size() << ") Client(s).\n";

	cout << myoutput::getLineOfChars('_', 90) << endl;
	cout
		<< "|" + myoutput::AdjustColumn("Account Number", 15)
		+ "|" + myoutput::AdjustColumn("PinCode", 15)
		+ "|" + myoutput::AdjustColumn("Name", 30)
		+ "|" + myoutput::AdjustColumn("Phone", 15)
		+ "|" + myoutput::AdjustColumn("Balance", 15) << endl;
	cout << myoutput::getLineOfChars('_', 90) << endl;

	if (vClients.size() == 0)
		cout << "No clients available yet.\n";
	else
	{
		for (const stClient& Client : vClients)
		{
			PrintClient(Client);
		}
	}
	cout << myoutput::getLineOfChars('_', 90) << endl;
}

// -----------------------------
void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to the main menu. . .";
	system("pause>0");
	ShowMainMenuScreen();
}

void PerformMainMenuTask(const enMainMenu Choice)
{
	switch (Choice)
	{
	case enMainMenu::eShowClientsList:
		system("cls");
		ShowClientsList();
		GoBackToMainMenu();
		break;

	case enMainMenu::eAddClients:
		AddClients();
		GoBackToMainMenu();
		break;

	case enMainMenu::eDeleteClient:
		DeleteClient();
		GoBackToMainMenu();
		break;

	case enMainMenu::eUpdateClient:
		UpdateClient();
		GoBackToMainMenu();
		break;

	case enMainMenu::eFindClient:
		FindClient();
		GoBackToMainMenu();
		break;

	case enMainMenu::eTransactions:
		system("cls");
		ShowTransactionsMenu();
		GoBackToMainMenu();
		break;

	case enMainMenu::eManageUsers:
		ShowManageUsersMenu();
		GoBackToMainMenu();
		break;

	case enMainMenu::eLogout:
		system("cls");
		Login();
		break;
	}
}

void PrintMainMenuScreen()
{
	cout << myoutput::getLineOfChars('=', 50) << endl;
	cout << "\t\tMain Menu Screen\n";
	cout << myoutput::getLineOfChars('=', 50) << endl;

	cout
		<< "\t[1] Show Clients List.\n"
		<< "\t[2] Add New Client.\n"
		<< "\t[3] Delete Client.\n"
		<< "\t[4] Update Client Info.\n"
		<< "\t[5] Find Client.\n"
		<< "\t[6] Transactions.\n"
		<< "\t[7] Manage Users.\n"
		<< "\t[8] Logout.\n";

	cout << myoutput::getLineOfChars('=', 50) << endl;
}

void ShowMainMenuScreen()
{
	system("cls");
	PrintMainMenuScreen();

	cout << "Choose what do you want to do? [1-8]: ";
	PerformMainMenuTask( (enMainMenu) (myinput::ReadInteger(1, 8) - 1) );
}

void PrintLoginScreen()
{
	cout << "==================================================\n";
	cout << "\t\tLogin Screen\n";
	cout << "==================================================\n";
}

void Login()
{
	PrintLoginScreen();
	string Username, Password;

	while (true)
	{
		cout << "Enter the username: ";
		Username = myinput::ReadString();
		cout << "Enter the password: ";
		Password = myinput::ReadString();

		for (const stUser& User : vUsers)
		{
			if (User.Username == Username && User.Password == Password)
			{
				CurrentUser = User;
				ShowMainMenuScreen();
				return;
			}
		}
		system("cls");
		PrintLoginScreen();
		cout << "Invalid username/password.\n";
	}
}
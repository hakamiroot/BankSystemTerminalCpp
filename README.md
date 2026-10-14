# Bank System Terminal (C++)

C++ console app project. Managing admin/users authentication, CRUD clients, transactions management, local .txt files storage. Developed as part of the https://programmingadvices.com platform under the guidance of Dr. Mohammed Abu-Hadhoud.

## Features
* **Access Control:** Secure login with bitwise permissions for system users.
* **Client Management:** CRUD operations (Create, Read, Update, Delete) for bank accounts (clients).
* **Transactions:** Process deposits and withdrawas with balance validation.
* **Persistent Storage:** Data is saved locally in text files (`Clients.txt` and `Users.txt`).

## Technology Stack
* **Language:** C++
* **Environment:** Visual Studio 2022
* **Core Libraries:** `<iostream>`, `<vector>`, `<fstream>`, `<string>`

## Project Structure
* `MainApp.cpp`:\
  Main entry file and front-end terminal interface.
  
* `BankHeader.h`:\
Back-end logic, it contains structs (`stClient`, `stUser`) and enums (`enMainMenu`, `enTransactionsMenu`, `enUsersMenu`, `enUserPermissions`) and vectors/filenames/separator and functionalities.

* `myinput.h` / `myoutput.h` / `mystring.h`:\
  Custom utility libraries for input validation, layout formatting, and string parsing.

* `Users.txt`\
  This file store users. It has 3-columns: Username, Password and Permissions. The column separator is `#//#`.

* `Clients.txt`\
  This file store clients. It has 5 columns: Account Number, PIN, Name, Phone, Balance. Also the same column separator `#//#`.

## How to run
* Create a new C++ Console App project in visual studio.
* Name the solution, for example: "BankSystemTerminalCppSolution"
* Name the project, for example: "BankSystemTerminalCpp"
* If a .cpp file that contains main function created, delete it or comment main function.
* Upload the source files and data files inside "BankSystemTerminalCpp" project folder.
* Enjoy

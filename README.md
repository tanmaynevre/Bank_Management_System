## Bank Management System in C++

This is a console-based Bank Management System developed using C++ as part of a CDC project at IIT Kharagpur.

It allows users to perform essential banking operations such as creating, modifying, deleting, and viewing bank accounts. All data is stored persistently with binary file handling.

---

### Features

* **Create New Account**  
  Users can open a savings or current account by entering basic information.

* **Deposit & Withdraw Amount**  
  Easily update the account balance with deposit or withdrawal options.

* **Balance Enquiry**  
  View complete details of a specific account using the account number.

* **Display All Accounts**  
  Lists all account holders in a table.

* **Modify Account**  
  Update the account holder's name, type, and balance.

* **Delete Account**  
  Permanently removes an account by copying data to a temporary file.

---

### Technical Details

* **Language:** C++
* **File I/O:** All account data is stored in a binary file (`account.dat`) using `fstream`.
* **OOP Concepts:** Encapsulation, class methods, private attributes.
* **CLI Interface:** Simple menu-driven UI using the terminal.

---

### File Structure

* `main.cpp` – Contains all logic for account operations and file handling.
* `account.dat` – Binary file that stores all user account information.

---

### Author Info

* Name: **Tanmay Nevre**
* Roll No: 23ME10091
* IIT Kharagpur
* Project: CDC Submission

---

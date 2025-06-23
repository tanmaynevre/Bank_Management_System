# Bank_Management_System
A comprehensive **Bank Management System** implemented in **C++** that replicates core banking operations with secure transaction processing, data persistence, and efficient data management using object-oriented programming principles.

## Table of Contents
- Features
- Technical Stack
- Architecture
- Installation
- Usage
- File Structure
- Screenshots
- Contributing

## Features

### Core Banking Operations
- **Account Creation** - Create new accounts with unique account numbers
- **Deposit/Withdrawal** - Secure money transactions with balance validation
- **Balance Inquiry** - Check account balance with PIN authentication
- **Account Modification** - Update customer details (name, address, phone, PIN)
- **Account Deletion** - Remove accounts with confirmation safeguards
- **Transaction History** - Complete audit trail of all transactions
- **Account Summary Export** - Generate detailed account reports

### Security & Data Integrity
- **PIN-based Authentication** - 4-digit PIN security for all operations
- **Input Validation** - Comprehensive validation for all user inputs
- **Exception Handling** - Robust error handling throughout the system
- **Data Persistence** - Automatic data saving and loading using file I/O
- **Transaction Logging** - Complete transaction history with timestamps

### Advanced Features
- **Professional UI** - Clean console-based interface with intuitive navigation
- **Minimum Balance** - Configurable minimum balance requirements
- **Data Recovery** - Automatic data loading on system restart
- **Account Statistics** - Detailed account summaries and export functionality

## Technical Stack

- **Language:** C++ (C++11 and above)
- **Paradigm:** Object-Oriented Programming (OOP)
- **Data Structures:** STL Containers (map, vector, string)
- **File I/O:** fstream for persistent data storage
- **Architecture:** Modular design with separation of concerns

## Architecture

### Core Classes
```cpp
 BankManagementSystem
 ┣  Account Class
 ┃ ┣ - Private Members (accountNumber, customerName, balance, etc.)
 ┃ ┣ - Transaction Methods (deposit, withdraw, addTransaction)
 ┃ ┗ - File I/O Methods (toFileString, fromFileString)
 ┣  Transaction Structure
 ┃ ┗ - Transaction logging (type, amount, date, balance)
 ┗  Bank Management System
   ┣ - Account Management Operations  
   ┣ - Security & Authentication
   ┗ - File Operations & Data Persistence
```

### Key Data Structures
- **`std::map<int, Account>`** - Efficient O(log n) account lookups by account number
- **`std::vector<Transaction>`** - Dynamic transaction history storage
- **Custom Classes** - Account and Transaction classes with proper encapsulation

## Installation

### Prerequisites
- C++ Compiler (GCC/Clang/MSVC)
- C++11 or higher support

### Steps
1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/bank-management-system.git
   cd bank-management-system
   ```

2. **Compile the program**
   ```bash
   g++ -std=c++11 -o bank_system main.cpp
   ```

3. **Run the application**
   ```bash
   ./bank_system
   ```

## Usage

### Main Menu Options
  BANK MANAGEMENT SYSTEM
   1. Create New Account                   
   2. Deposit Amount                       
   3. Withdraw Amount                      
   4. Check Balance                        
   5.Modify Account                       
   6. Delete Account                       
   7. Transaction History                  
   8. Export Account Summary               
   9. Exit                                 

### Example Workflow
1. **Create Account**: Enter customer details and set 4-digit PIN
2. **Make Deposit**: Use account number and PIN to deposit funds
3. **Check Balance**: Verify current balance with secure authentication
4. **View History**: Access complete transaction history
5. **Export Data**: Generate account summary reports

## File Structure

```
bank-management-system/
│
├── main.cpp                 # Main application file
├── bank_data.txt           # Auto-generated data storage file
├── README.md               # Project documentation
├── LICENSE                 # Project license
└── screenshots/            # Application screenshots
    ├── main_menu.png
    ├── account_creation.png
    └── transaction_history.png
```

## Key Programming Concepts Demonstrated

### Object-Oriented Programming
- **Encapsulation** - Private data members with controlled access
- **Abstraction** - Clean interfaces hiding implementation details
- **Constructor/Destructor** - Proper resource management

### Data Structures & Algorithms
- **Hash Maps** - Efficient account lookup and management
- **Dynamic Arrays** - Transaction history storage
- **File I/O** - Custom serialization and deserialization

### Software Engineering Practices
- **Error Handling** - Comprehensive exception management
- **Input Validation** - Robust user input processing
- **Code Organization** - Modular design with clear separation
- **Documentation** - Well-commented and maintainable code

## Security Features

- **Authentication System** - PIN-based access control
- **Input Sanitization** - Prevention of invalid data entry
- **Balance Validation** - Overdraft protection
- **Data Integrity** - Consistent state management
- **Secure File Storage** - Protected data persistence

## Performance Characteristics

- **Time Complexity**: O(log n) for account operations using std::map
- **Space Complexity**: O(n) where n is the number of accounts
- **File I/O**: Efficient serialization with minimal overhead
- **Memory Management**: No memory leaks with proper RAII

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

### Development Guidelines
1. Follow existing code style and conventions
2. Add appropriate comments and documentation
3. Test thoroughly before submitting
4. Update README if adding new features

## Project Highlights

- **Complete Banking Solution** - Full-featured system with all essential operations
- **Production-Ready Code** - Robust error handling and data validation
- **Educational Value** - Demonstrates advanced C++ concepts and best practices
- **Scalable Architecture** - Modular design for easy extension and maintenance
- **Professional UI/UX** - Clean, intuitive console interface

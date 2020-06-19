#include "BankingSystem.h"
#include <iomanip>
#include <iostream>

using namespace std;

int main() {

    BankingSystem B;

    int input;
    string fName, sName; int cid;
    double balance, amount;
    int aid;
    int faid, taid;

    std::cout << std::left;
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    do {

        std::cout << "Welcome to pocket bank, use the folliwing keys to navigate: " << '\n';
        std::cout << '\n';
        std::cout << "\t 1 - Add a customer" << '\n';
        std::cout << "\t 2 - Delete a customer" << '\n';
        std::cout << "\t 3 - Add an account for a specific customer" << '\n';
        std::cout << "\t 4 - Delete a specific account of a customer" << '\n';
        std::cout << "\t 5 - Display all present accounts in the system" << '\n';
        std::cout << "\t 6 - Display all present customers in the system" << '\n';
        std::cout << "\t 7 - Display detailed information about the specific user" << '\n';
        std::cout << "\t 8 - To deposit to an account" << '\n';
        std::cout << "\t 9 - To withdraw from an account" << '\n';
        std::cout << "\t 10 - To transfer credit from one account to another" << '\n';
        std::cout << "\t Any other key - To exit" << '\n';
        std::cout << '\n';


        std::cout << "Your command goes here--> ";
        std::cin >> input;

        if (input == 1) {

            std::cout << "First name of the customer to be added: ";
            std::cin >> fName;
            std::cout << "Last name of the customer to be added: ";
            std::cin >> sName;
            std::cout << "Provide a customer id: ";
            std::cin >> cid;

            B.addCustomer( cid, fName, sName );

        } else if (input == 2) {

            std::cout << "Plase provide an id of the customer you would like to delete: ";
            std::cin >> cid;
            B.deleteCustomer(cid);

        } else if (input == 3){

            std::cout << "Id of the customer to add account to: ";
            std::cin >> cid;
            std::cout << "Initial balance of this account: ";
            std::cin >> balance;
            B.addAccount(cid, balance);

        } else if (input == 4) {

            std::cout << "Plase provide an id of the account to delete: ";
            std::cin >> aid;
            B.deleteAccount(aid);

        } else if (input == 5) {

            B.showAllAccounts();

        } else if (input == 6) {

            B.showAllCustomers();

        } else if (input == 7) {

            std::cout << "Plase provide an id of the customer to view: ";
            std::cin >> cid;
            B.showCustomer(cid);

        } else if (input == 8) {

            std::cout << "Plase provide an id of the account to deposit: ";
            std::cin >> aid;
            std::cout << "Plase provide an amount to deposit: ";
            std::cin >> amount;
            B.deposit(aid, amount);

        } else if (input == 9) {

            std::cout << "Plase provide an id of the account to withdraw: ";
            std::cin >> aid;
            std::cout << "Plase provide an amount to withdraw: ";
            std::cin >> amount;
            B.withdraw(aid, amount);

        } else if (input == 10) {

            std::cout << "Plase provide an id of the account to transfer from: ";
            std::cin >> faid;
            std::cout << "Plase provide an id of the account to transfer to: ";
            std::cin >> taid;
            std::cout << "Plase provide an amount to transfer: ";
            std::cin >> amount;
            B.transfer(faid, taid, amount);

        } else {
                std::cout << "Terminating..." << '\n';
        }

        std::cout << '\n';

    } while( input != 0);

    return 0;
}

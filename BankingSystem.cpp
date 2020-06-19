#include "BankingSystem.h"
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

BankingSystem::BankingSystem(): customerHead(0), accountHead(0){}

BankingSystem::~BankingSystem(){

    for(Customer* curCustomer = customerHead; curCustomer != 0; curCustomer = curCustomer->next)
    {
        delete curCustomer;
    }

    for(Account* curAccount = accountHead; curAccount!=0; curAccount = curAccount->next)
    {
        delete curAccount;
    }
}

void BankingSystem::addCustomer( const int customerId, const string firstName, const string lastName )
{

    if (doesCustomerExist(customerId)) {
        cout<<"Customer "<<customerId<<" already exist"<<endl;
        return;
    }

    if (isDuplicateCustomer(firstName, lastName)) {
        std::cout << "Customer "<<firstName<<" "<<lastName<<" already exist"<< '\n';
        return;
    }

    insertCustomer(customerId, firstName, lastName );

}

void BankingSystem::deleteCustomer( const int customerId )
{

    if(doesCustomerExist(customerId) == false){
        std::cout << "Customer "<< customerId << " does not exist" << '\n';
        return;
    }

    Customer * curCustomer = customerHead;
    Customer * prevCustomer = 0;

    while (curCustomer != 0) {

        if(curCustomer->theCustomerId == customerId){
            break;
        }

        prevCustomer = curCustomer;
        curCustomer = curCustomer->next;
    }

    if (prevCustomer) {
        prevCustomer->next = curCustomer->next;
    }
    else{
        customerHead = curCustomer->next;
    }

    curCustomer->next = 0;
    delete curCustomer;
    curCustomer = 0;

    //Delete customer's accounts
    deleteCustomerAccounts(customerId);

    cout<<"Customer "<<customerId<<" has been deleted"<<endl;

}

int BankingSystem::addAccount( const int customerId, const double amount )
{

    if(doesCustomerExist(customerId) == false){
        std::cout << "Customer "<< customerId << " does not exist" << '\n';
        return -1;
    }

    Account *newAccount = new Account;
    newAccount->theCustomerId = customerId;
    newAccount->theAmount = amount;
    newAccount->theAccountId = generateAccountId();

    Account* curAccount = accountHead;
    Account* prevAccount = 0;

    while( curAccount != 0 )
    {
        if (newAccount->theAccountId < curAccount->theAccountId){
            break;
        }
        prevAccount = curAccount;
        curAccount = curAccount->next;
    }

    if (prevAccount) {
        newAccount->next = prevAccount->next;
        prevAccount->next = newAccount;
    }
    else{
        newAccount->next = accountHead;
        accountHead = newAccount;
    }
    cout<<"Account "<<newAccount->theAccountId<<" has been added for customer "<< customerId <<endl;

    return newAccount->theAccountId;
}

void BankingSystem::deleteAccount( const int accountId )
{

    if(doesAccountExist(accountId) == false){
        std::cout << "Account "<< accountId << " does not exist" << '\n';
        return;
    }

    Account * curAccount = accountHead;
    Account * prevAccount = 0;

    while (curAccount != 0) {

        if(curAccount->theAccountId == accountId){
            break;
        }

        prevAccount = curAccount;
        curAccount = curAccount->next;
    }

    if (prevAccount) {
        prevAccount->next = curAccount->next;
    }
    else{
        accountHead = curAccount->next;
    }

    curAccount->next = 0;
    delete curAccount;
    curAccount = 0;

    cout<<"Account "<<accountId<<" has been deleted"<<endl;
}

void BankingSystem::showAllAccounts()
{
    int customerId;
    string customerName;

    std::cout << std::setw(12) << "Account id" << std::setw(18) << "Customer id" << std::setw(26) << "Customer name" << "Balance" <<'\n';

    for(Customer* curCustomer = customerHead; curCustomer != 0; curCustomer = curCustomer->next)
    {
        customerId = curCustomer->theCustomerId;
        customerName = curCustomer->theFirstName + " " + curCustomer->theLastName;

        for(Account* curAccount = accountHead; curAccount!=0; curAccount = curAccount->next)
        {
            if (customerId==curAccount->theCustomerId)
            {
                cout<< std::setw(12) <<curAccount->theAccountId<< std::setw(18) <<customerId<< std::setw(26) << customerName <<curAccount->theAmount<<endl;
            }
        }
    }
}

void BankingSystem::showAllCustomers()
{
    cout << std::setw(16) << "Customer id" << "Customer name" << '\n';
    for(Customer* curCustomer = customerHead; curCustomer != 0; curCustomer = curCustomer->next)
    {
        cout<< std::setw(16) << curCustomer->theCustomerId << curCustomer->theFirstName<<"  "<<curCustomer->theLastName<<endl;
    }
}

void BankingSystem::showCustomer( const int customerId )
{
    if(doesCustomerExist(customerId) == false){
        std::cout << "Customer "<< customerId << " does not exist" << '\n';
        return;
    }

    int NoAccounts=0;
    for(Customer* curCustomer = customerHead; curCustomer != 0; curCustomer = curCustomer->next)
    {

        if (customerId==curCustomer->theCustomerId)
        {
            for(Account* curAccount = accountHead; curAccount!=0; curAccount = curAccount->next)
            {
                if (curAccount->theCustomerId==customerId)
                    NoAccounts = NoAccounts + 1;
            }

            cout<<"Customer id: "<<customerId<<" Customer name: "<<curCustomer->theFirstName<<" "<<curCustomer->theLastName<<" Number of accounts: "<<NoAccounts<<endl;

            if(NoAccounts > 0){
                std::cout << "Accounts of this customer: " << '\n';
            }

            for(Account* curAccount = accountHead; curAccount != 0; curAccount = curAccount->next)
            {
                if (customerId == curAccount->theCustomerId)
                {
                    cout<< curAccount->theAccountId <<" "<<curAccount->theAmount<<endl;
                }
            }

        }

    }
}

void BankingSystem::withdraw(const int accountId, const double amount) {

    if(doesAccountExist(accountId) == false){
        std::cout << "Account "<< accountId << " does not exist" << '\n';
        return;
    }

    Account * curAccount = accountHead;

    while (curAccount != 0) {

        if(curAccount->theAccountId == accountId){
            break;
        }
        curAccount = curAccount->next;
    }

    if (curAccount->theAmount < amount){
        std::cout << "Not enough balance amount to perform the withdrawal" << '\n';
    } else {
        curAccount->theAmount = curAccount->theAmount - amount;
        std::cout << "Withdrawal successful, current balance: " << curAccount->theAmount << '\n';
    }

}

void BankingSystem::deposit(const int accountId, const double amount) {

    if(doesAccountExist(accountId) == false){
        std::cout << "Account "<< accountId << " does not exist" << '\n';
        return;
    }

    Account * curAccount = accountHead;

    while (curAccount != 0) {

        if(curAccount->theAccountId == accountId){
            break;
        }
        curAccount = curAccount->next;
    }

    curAccount->theAmount = curAccount->theAmount + amount;
    std::cout << "Deposit successful, current balance: " << curAccount->theAmount << '\n';
}

void BankingSystem::transfer(const int fromAccount, const int toAccount, const double amount) {

    if(doesAccountExist(fromAccount) == false || doesAccountExist(toAccount) == false){
        std::cout << "At least one of the accounts is not genuine" << '\n';
        return;
    }

    Account * fAccount = accountHead;
    Account * sAccount = accountHead;

    while (fAccount != 0) {

        if(fAccount->theAccountId == fromAccount){
            break;
        }
        fAccount = fAccount->next;

    }

    while (sAccount != 0) {

        if(sAccount->theAccountId == toAccount){
            break;
        }
        sAccount = sAccount->next;

    }

    if (fAccount->theAmount < amount){
        std::cout << "Not enough balance amount to perform the transfer" << '\n';
    } else {
        fAccount->theAmount = fAccount->theAmount - amount;
        sAccount->theAmount = sAccount->theAmount + amount;
        //std::cout << "Transfer performed, New balance of account: " << fAccount->theAccountId << ": " << curAccount->theAmount << '\n';
        printf("Transfer performed, new balance of account %d: %.2lf, new balance of account %d: %.2lf\n", fAccount->theAccountId, fAccount->theAmount, sAccount->theAccountId, sAccount->theAmount);
    }
}



bool BankingSystem::doesCustomerExist(const int customerId){

    Customer * curCustomer = customerHead;

    while (curCustomer != 0) {

        if (curCustomer->theCustomerId == customerId) {
            return true;
        }

        curCustomer = curCustomer->next;
    }

    return false;
}

bool BankingSystem::doesAccountExist(const int accountId){

    Account * curAccount = accountHead;

    while (curAccount != 0) {

        if (curAccount->theAccountId == accountId) {
            return true;
        }

        curAccount = curAccount->next;
    }

    return false;
}

bool BankingSystem::isDuplicateCustomer(const string firstName, const string lastName){

    Customer * curCustomer = customerHead;

    while (curCustomer != 0) {

        if (curCustomer->theLastName == lastName) {
            if (curCustomer->theFirstName == firstName) {
                return true;
            }
        }

        curCustomer = curCustomer->next;
    }

    return false;
}

void BankingSystem::insertCustomer( const int customerId, const string firstName, const string lastName ){

    Customer * newCustomer = new Customer;
    newCustomer->theCustomerId = customerId;
    newCustomer->theFirstName = firstName;
    newCustomer->theLastName = lastName;


    Customer* curCustomer = customerHead;
    Customer* prevCustomer = 0;



    while( curCustomer != 0 )
    {
        if (lastName < curCustomer->theLastName){
            break;
        }
        if (lastName == curCustomer->theLastName) {
            if (firstName < curCustomer->theFirstName) {
                break;
            }
            else{
                continue;
            }
        }
        prevCustomer = curCustomer;
        curCustomer = curCustomer->next;
    }

    if (prevCustomer) {
        newCustomer->next = prevCustomer->next;
        prevCustomer->next = newCustomer;
    }
    else{
        newCustomer->next = customerHead;
        customerHead = newCustomer;
    }
    cout<<"Customer "<<customerId<<" has been added"<<endl;

}

void BankingSystem::deleteCustomerAccounts(const int customerId) {

    Account* curAccount = accountHead;
    Account* prevAccount = 0;

    while( curAccount != 0 )
    {

        if (customerId == curAccount->theCustomerId) {
            if (prevAccount) {
                prevAccount->next = curAccount->next;
            }
            else{
                accountHead = curAccount->next;
            }

            curAccount->next = 0;
            delete curAccount;
            curAccount = 0;
        }

        prevAccount = curAccount;
        curAccount = curAccount->next;
    }

    std::cout << "Accounts of " << customerId << " has been deleted, if existed" << '\n';
}

int BankingSystem::generateAccountId() {

    int id = 0;
    Account* curAccount = accountHead;

    while( curAccount != 0 )
    {

        if (id < curAccount->theAccountId) {
            break;
        }

        id++;
        curAccount = curAccount->next;
    }

    return id;


}

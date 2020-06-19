#include <string>
using namespace std;

struct Customer;
struct Account;

class BankingSystem {
public:
BankingSystem();
~BankingSystem();

void addCustomer( const int customerId, const string firstName, const string lastName );
void deleteCustomer( const int customerId );

int addAccount( const int customerId, const double amount );
void deleteAccount( const int accountId );

void showAllAccounts();
void showAllCustomers();
void showCustomer( const int customerId );

void withdraw(const int accountId, const double amount);
void deposit(const int accountId, const double amount);
void transfer(const int fromAccount, const int toAccount, const double amount);

private:
    struct Customer{

        int theCustomerId;
        string theFirstName;
        string theLastName;
        Customer *next;
    };

    struct Account{

        int theCustomerId;
        int theAccountId;
        double theAmount;
        Account *next;
    };

    Customer *customerHead;
    Account *accountHead;

    bool doesCustomerExist(const int customerId);
    bool isDuplicateCustomer( const string firstName, const string lastName);
    void insertCustomer( const int customerId, const string firstName, const string lastName );
    void deleteCustomerAccounts(const int customerId);
    bool doesAccountExist(const int accountId);
    int generateAccountId();

};

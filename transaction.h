# ifndef TRANSACTION_DATA_H
# define TRANSACTION_DATA_H

# include <iostream>

using namespace std;

struct TransactionData
{
    string sender;
    string receiver;
    time_t time_stamp;
    double amount; // CapyCoins! :)

    TransactionData(string sender, string receiver, double amount);
};

TransactionData::TransactionData(string sender, string receiver, double amount){
    this->sender = sender;
    this->receiver = receiver;
    this->amount = amount;
    this->time_stamp = time(nullptr);
}

ostream& operator<<(ostream& os, const TransactionData& transaction)
{
    os << "\tAmount: " << transaction.amount << " CapyCoins\n";
    os << "\tDate: " << ctime(&transaction.time_stamp);
    os << "\tFrom: " << transaction.sender << "\n";
    os << "\tTo: " << transaction.receiver << "\n";
    return os;
}






# endif // TRANSACTION_DATA_H
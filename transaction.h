# ifndef TRANSACTION_DATA_H
# define TRANSACTION_DATA_H

# include <iostream>

using namespace std;

class Transaction
{
    protected:
        double amount; // CapyCoins! :)
        time_t time_stamp;

    public:
        Transaction();
        Transaction(double amount);
        void print(ostream& os) const;
};

class Transfer : public Transaction 
{
    private:
        string sender;
        string receiver;

    public:
        Transfer();
        Transfer(double amount, string sender, string receiver);
        void print(ostream& os) const;
};

Transaction::Transaction()
{
    this->amount = 0.0;
    this->time_stamp = time(nullptr);
}

Transaction::Transaction(double amount)
{
    this->amount = amount;
    this->time_stamp = time(nullptr);
}

void Transaction::print(ostream& os) const
{
    os << "\tAmount: " << amount << " CapyCoins\n";
    os << "\tTime stamp: " << ctime(&time_stamp);
}

// Transfer implementation

Transfer::Transfer() : Transaction()
{
    this->sender = "";
    this->receiver = "";
}

Transfer::Transfer(double amount, string sender, string receiver) : Transaction(amount)
{
    this->sender = sender;
    this->receiver = receiver;
}

void Transfer::print(ostream& os) const
{
    os << "\tAmount: " << amount << "CapyCoins\n";
    os << "\tTime stamp: " << ctime(&time_stamp);
    os << "\tSender: " << sender << "\n";
    os << "\tReceiver: " << receiver << "\n";
}

ostream& operator<<(ostream& os, const Transaction& transaction)
{
    transaction.print(os);
    return os;
}

// ostream& operator<<(ostream& os, const Transaction**& transaction)
// {
//     (*transaction)->print(os);
//     return os;
// }



// class Withdrawal : public Transaction
// {

// };

// class Deposit : public Transaction
// {

// };






# endif // TRANSACTION_DATA_H
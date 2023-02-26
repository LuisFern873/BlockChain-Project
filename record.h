# ifndef RECORD_H
# define RECORD_H

# include <iostream>

using namespace std;

class BankAccount
{
    private:
        double balance;
        string user;
        string password;
};

class Record
{
    public:
        Record();
        virtual void print(ostream& os) const;
    
    protected:
        time_t time_stamp;
};

class Transfer : public Record 
{
    public:
        Transfer();
        Transfer(double amount, string sender, string receiver);
        void print(ostream& os) const override;
        
        size_t id_block;
        string get_sender();
        string get_receiver();
        double get_amount();
    
    private:
        double amount; // CapyCoins! :)
        string sender;
        string receiver;
};

// Record implementation

Record::Record()
{
    this->time_stamp = time(nullptr);
}

void Record::print(ostream& os) const
{
    os << "\tDate: " << ctime(&time_stamp);
}

// Transfer implementation

Transfer::Transfer() : Record()
{
    this->amount = 0.0;
    this->sender = "";
    this->receiver = "";
}

Transfer::Transfer(double amount, string sender, string receiver) : Record()
{
    this->amount = amount;
    this->sender = sender;
    this->receiver = receiver;
}

void Transfer::print(ostream& os) const
{
    Record::print(os);
    os << "\tAmount: " << amount << " CapyCoins\n";
    os << "\tSender: " << sender << "\n";
    os << "\tReceiver: " << receiver << "\n";
}

ostream& operator<<(ostream& os, const Record& record)
{
    record.print(os);
    return os;
}

string Transfer::get_sender()
{ 
    return sender;
}

string Transfer::get_receiver()
{
    return receiver;
}

double Transfer::get_amount()
{
    return amount;
}


# endif // RECORD_H
# ifndef RECORD_H
# define RECORD_H

# include <iostream>

using namespace std;

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

        // For indexing
        string get_sender(){ 
            return sender;
        }
        string get_receiver(){
            return receiver;
        }
    
    private:
        double amount; // CapyCoins! :)
        string sender;
        string receiver;

    friend class indexing;
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

Transfer::Transfer()
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


# endif // RECORD_H
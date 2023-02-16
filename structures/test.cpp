# include <iostream>
# include <vector>
# include "b+tree.h"

struct Transfer
{
    double amount;
    string sender;
    string receiver;

    Transfer(double amount, string sender, string receiver){
        this->amount = amount;
        this->sender = sender;
        this->receiver = receiver;
    }

    Transfer(const Transfer& other){
        cout << "other\n";
        this->amount = other.amount;
        this->sender = other.sender;
        this->receiver = other.receiver;
    }
};

ostream& operator<<(ostream& os, const Transfer& transfer)
{
    os << "Amount: " << transfer.amount << "\n";
    os << "Sender: " << transfer.sender << "\n";
    os << "Receiver: " << transfer.receiver << "\n";
    return os;
}



int main()
{
    BPlusTree<double,Transfer> tree;

    tree.insert(5, Transfer(5, "Luis", "Pierina"));
    tree.insert(35, Transfer(35, "Luis", "Pierina"));
    tree.insert(45, Transfer(45, "Luis", "Pierina"));
    tree.insert(90, Transfer(90, "Diego", "Alberto"));
    tree.insert(15, Transfer(15, "Luis", "Pierina"));
    tree.insert(65, Transfer(65, "Luis", "Pierina"));
    tree.insert(75, Transfer(75, "Luis", "Pierina"));
    tree.insert(20, Transfer(20, "Luis", "Pierina"));
    tree.insert(10, Transfer(10, "Luis", "Pierina"));
    tree.insert(100, Transfer(100, "Luis", "Pierina"));
    tree.insert(80, Transfer(80, "Luis", "Pierina"));
    tree.insert(50, Transfer(50, "Luciana", "Mafer"));
    

    tree.displayPretty();
    cout << "\n";

    tree.search(90);
    tree.search(50);


    

    return 0;
}
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

    vector<double> amounts = {15, 45, 35, 25}; // , 5, 55, 40, 30, 30, 90, 100

    // for (const double& amount : amounts) {
    //     Transfer T(amount, "Luis", "Pierina");
    //     tree.insert(amount, T);
    // }
    tree.insert(5, Transfer(5, "Luis", "Pierina"));
    tree.insert(35, Transfer(35, "Luis", "Pierina"));
    tree.insert(45, Transfer(45, "Luis", "Pierina"));
    tree.insert(90, Transfer(90, "Luis", "Pierina"));
    tree.insert(15, Transfer(15, "Luis", "Pierina"));
    tree.insert(65, Transfer(65, "Luis", "Pierina"));
    tree.insert(75, Transfer(75, "Luis", "Pierina"));
    tree.insert(20, Transfer(20, "Luis", "Pierina"));
    tree.insert(10, Transfer(10, "Luis", "Pierina"));

    tree.insert(100, Transfer(100, "Luis", "Pierina"));
    tree.insert(80, Transfer(80, "Luis", "Pierina"));
    tree.insert(50, Transfer(50, "Luis", "Pierina"));
    

    tree.displayPretty();
    cout << "\n";

    // tree.search(90);
    // tree.search(35);
    // tree.search(45);
    // tree.search(5);

    // tree.iterateLeafNodes();

    // tree.remove(15);
    // tree.remove(5);
    // tree.remove(45);


    // tree.displayPretty();

    // for (int i = 0; i < 5; ++i) {
    //     tree->insert(rand() % 100);
    // }
    // tree->displayPretty();
    return 0;
}
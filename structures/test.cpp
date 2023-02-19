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
    BPlusTree<double, Transfer*> tree;

    vector<double> amounts = {5, 35, 45, 90, 15, 65, 75, 20, 10, 100, 80, 50};

    for (const double& amount : amounts) {
        tree.insert(amount, new Transfer(amount, "Luis", "Pierina"));
    }

    tree.displayPretty();
    cout << "\n";

    cout << *tree.search(90) << "\n";
    cout << *tree.search(50) << "\n";
    cout << *tree.min() << "\n";
    cout << *tree.max() << "\n";
    cout << "\nrangeSearch(15, 65)\n";

    vector<Transfer*> transfers = tree.rangeSearch(15, 65);

    for (auto& transfer : transfers) {
        cout << *transfer << "\n";
    }

    

    return 0;
}
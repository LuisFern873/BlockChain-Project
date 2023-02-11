# include "blockchain.h"
# include "index.h"
# include "tester.h"
# include "menu.h"
# include <fstream>
# include <string>
# include <sstream>
# include <vector>
 
using namespace std;

// void LoadData(string name, BlockChain<Transfer>& chain)
// {
//     ifstream file(name);
//     string line;

//     while (getline(file, line))
//     {
//         istringstream iss(line);
//         vector<string> fields;
//         string field;

//         while (getline(iss, field, ','))
//         {
//             fields.push_back(field);
//         }

//         double amount = stod(fields[0]);
//         string sender = fields[1];
//         string receiver = fields[2];

//         cout << "Amount: " << amount << "\n";
//         cout << "Sender: " << sender << "\n";
//         cout << "Receiver: " << receiver << "\n";
//         cout << "\n";

//         // chain.insert(Transfer(amount, sender, receiver));
//     }
// }

void LoadData(string const& filename, BlockChain<Transfer>& chain)
{
    string text;

    ifstream file(filename);

    while(getline(file, text)){
        cout << text << endl;
    }

    file.close();
}

int main()
{
    // // Load data
    BlockChain<Transfer> chain;

    LoadData("assets/transfers.csv", chain);

    // chain.display();

    // // Sender and Receiver Hash Index
    // Index index;
    // index.create_hash_index(chain);

    // cout << index.EqualTo(Member::sender, "Pedro");
    // cout << index.EqualTo(Member::receiver, "Mario");

    // Display menu
    // auto menu = Menu::init();
    // menu->display_main();

    return 0;
}
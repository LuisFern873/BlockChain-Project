# include "blockchain.h"
# include <fstream>
# include <string>
# include <sstream>
# include <vector>
 
using namespace std;

struct DataManager
{
    static void load(string filename, BlockChain<Transfer>& chain);
};

void DataManager::load(string filename, BlockChain<Transfer>& chain)
{
    cout << "Loading data ...\n";
    string line;
    ifstream file(filename);

    while (getline(file, line))
    {
        istringstream iss(line);

        vector<string> fields;
        string field;

        while (getline(iss, field, ','))
        {
            fields.push_back(field);
        }

        double amount = stod(fields[0]);
        string sender = fields[1];
        string receiver = fields[2];

        chain.insert(Transfer(amount, sender, receiver));
    }

    file.close();
    cout << "Data have been loaded successfully.\n";
}
